#! /bin/bash

#
# Given a hotspot build directory this script creates settings.xml and a zip
# archive with referenced system headers and generated sources for a hotspot
# build platform which can be imported in the cdt project as a build
# configuration.
# 
# Given that the OUTPUTDIR and WORK_DIR are shared, this script can be run locally for a remote
# BUILD_HOST. Calls of the C++ compiler are executed on the build host through ssh.
#

if [ $# -ne 4 ] ; then
    echo
    echo "*** ERROR: wrong number of arguments"
    echo
    echo "usage: [DEBUG_MODE=1] `basename $0` <build-host> <gnu-sed> <tmp dir> <dir with *.cmdline files>"
    echo
    exit 1
fi

BUILD_HOST=$1
GSED=$2
TMP_DIR=$3
CMDLINE_DIR=$4
WORK_DIR=$TMP_DIR/work

ADD_SYMLINKS_TO_ARCHIVE_CMD="$(dirname $0)/cdt_gen_add_symlinks.sh"

# assume ascii and sort based on characters byte values
export LC_ALL=C

####################
# Development aids #
####################
function report_and_exit() {
    msg=$1
    BS_IDX=$2
    if [ "$BS_IDX" = "" ] ; then
        BS_IDX=1
    fi
    BL_IDX=$(($BS_IDX-1))
    i=0
    echo
    echo "*** ERROR(${FUNCNAME[$BS_IDX]}():$(basename ${BASH_SOURCE[$BS_IDX]}):${BASH_LINENO[$BL_IDX]}): $msg"
    echo
    print_stack $(($BS_IDX+1))
    exit 1
}

function print_stack() {
    DEPTH=${#BASH_SOURCE[@]}
    i=$1
    if [ "$i" = "" ] ; then
        i=1
    fi
    echo "*** Call Stack:"
    while [ $i -lt $DEPTH ] ; do
        echo "${FUNCNAME[$i]}():$(basename ${BASH_SOURCE[$i]}):${BASH_LINENO[(($i-1))]}"
        ((i++))
    done
}

# Mark Todos during development #
function TODO() {
    echo
    report_and_exit "*** TODO" 2
}

function debug_print() {
    [ "$DEBUG_MODE" != "1" ] || echo "$1" 1>&2
}

function del_contents() {
    [ ! -e $1 ] || rm $1
    touch $1
}

# Don't rely on shared file system, when generating a script on host h1 to
# execute it on host h2. Instead copy it fro h1 to h2
function exec_script_on_build_host_synchronized() {
    if [ $BUILD_HOST != "localhost" ] ; then
        SCRIPT_NAME=$1
        SCRIPT_NAME_REMOTE=$1.remote.sh
        scp $SCRIPT_NAME $BUILD_HOST:$SCRIPT_NAME_REMOTE
        shift
        $EXEC_SCRIPT_ON_BUILD_HOST $SCRIPT_NAME_REMOTE "$@"
        $EXEC_ON_BUILD_HOST rm $SCRIPT_NAME_REMOTE
    else
        $EXEC_SCRIPT_ON_BUILD_HOST $SCRIPT_NAME_REMOTE "$@"
    fi
}

function initialize() {
    mkdir -p $WORK_DIR
    cmdline_file=$CMDLINE_DIR/globalDefinitions.*.cmdline

    if ! $GSED -n "/DONT_USE_PRECOMPILED_HEADER/! q 1" <$cmdline_file > /dev/null ; then
        echo
        echo "*** ERROR(line $LINENO): you must use a build without precompiled headers!"
        echo
        exit 1
    fi

    INCLUDE_SUFFIX_OS=`$GSED -n '/.*INCLUDE_SUFFIX_OS=\([^ ]*\).*/s//\1/p' <$cmdline_file`
    INCLUDE_SUFFIX_CPU=`$GSED -n '/.*INCLUDE_SUFFIX_CPU=\([^ ]*\).*/s//\1/p' <$cmdline_file`
    

    # Greater than or equal JDK10 means,
    #   - hotspot sources are located at ROOT/src/hotspot, before they used to be at ROOT/hotspot
    #   - src directory under hotspot is eliminated
    IS_GTE_JDK10=0
    if [ "`$GSED -n '\%.*src/hotspot/share/utilities/globalDefinitions.cpp% s//DETECTED JDK10/p' <$cmdline_file`" != "" ] ; then
        IS_GTE_JDK10=1
    fi

    OS=`echo $INCLUDE_SUFFIX_OS   | $GSED 's/_\(.*\)/\1/'`
    CPU=`echo $INCLUDE_SUFFIX_CPU | $GSED 's/_\(.*\)/\1/'`
    case $OS in
        solaris)
            BITS=`$GSED -n '/-m64/! s/.*/32/p; /-m64/ s/.*/64/p' <$cmdline_file`;;
        aix)
            BITS=`$GSED -n '/-q64/! s/.*/32/p; /-q64/ s/.*/64/p' <$cmdline_file`;;
        *)
            BITS=`$GSED -n '/_LP64/! s/.*/32/p; /_LP64/ s/.*/64/p' <$cmdline_file`;;
        esac
        
    echo "detected $OS $CPU $BITS"

    EXEC_ON_BUILD_HOST=
    EXEC_SCRIPT_ON_BUILD_HOST=bash
    if [ $BUILD_HOST != "localhost" ] ; then
        EXEC_ON_BUILD_HOST="ssh -x $BUILD_HOST"
        EXEC_SCRIPT_ON_BUILD_HOST="ssh -x $BUILD_HOST $EXEC_SCRIPT_ON_BUILD_HOST"
    fi
    
    READLINK=readlink
    # readlink command to be used on build host
    READLINK_BUILD_HOST=$READLINK
    SORT=sort
    FIND=find
    if [ $OS = windows ] ; then
        # don't use find, sort, etc. in c:/WINDOWS/System32/ 
        SORT=/bin/sort
        FIND=/bin/find
    fi
    if [ $OS = bsd ] ; then
        READLINK=greadlink # https_proxy=http://proxy.wdf.sap.corp:8080/ brew install coreutils
        SORT=gsort
        FIND=gfind         # https_proxy=http://proxy.wdf.sap.corp:8080/ brew install findutils
    fi
    if [ $OS = solaris -o $OS = aix ] ; then
        # aix: /opt/freeware/bin/readlink
        READLINK_BUILD_HOST=$($EXEC_ON_BUILD_HOST bash -c '"which readlink"')
        debug_print "READLINK_BUILD_HOST:$READLINK_BUILD_HOST"
        if [ "${READLINK_BUILD_HOST:0:11}" = "no readlink" ] ; then
            READLINK_BUILD_HOST="/usr/work/d038402/bin/readlink_${BUILD_HOST}"
        fi
        $EXEC_ON_BUILD_HOST test -e $READLINK_BUILD_HOST || report_and_exit "$READLINK_BUILD_HOST does not exist on $BUILD_HOST"
        debug_print "READLINK_BUILD_HOST:$READLINK_BUILD_HOST"
    fi

    # use absolute paths
    TMP_DIR=`$READLINK -f $TMP_DIR`
    WORK_DIR=$TMP_DIR/work
    CMDLINE_DIR=`$READLINK -f $CMDLINE_DIR`

    # find OUTPUTDIR looking for spec.gmk
    OUTPUTDIR="$CMDLINE_DIR"
    while [ ! -f "$OUTPUTDIR/spec.gmk" ] ; do
        OUTPUTDIR="$(readlink -f "$OUTPUTDIR/..")"
        if [ "$OUTPUTDIR" = "/" ] ; then
            report_and_exit "Could not determine OUTPUTDIR, because spec.gmk was not found looking upwards from $CMDLINE_DIR"
        fi
    done
    echo "OUTPUTDIR is $OUTPUTDIR"

    ALL_INCLUDED_FILES=$WORK_DIR/all_included_files
    ALL_INCLUDE_DIRS=$WORK_DIR/all_include_dirs
    ALL_DEFINES=$WORK_DIR/all_defines
    ALL_SYSTEM_INCLUDES=$WORK_DIR/all_included_system_headers
    ALL_OUTPUTDIR_INCLUDES=$WORK_DIR/all_included_outputdir_headers
    SETTINGS_XML=$TMP_DIR/settings_${OS}_${CPU}_${BITS}.xml

    del_contents $ALL_INCLUDED_FILES
    del_contents $ALL_SYSTEM_INCLUDES
    del_contents $ALL_OUTPUTDIR_INCLUDES
    del_contents $ALL_INCLUDE_DIRS
    del_contents $ALL_DEFINES
    del_contents $SETTINGS_XML

    INCLUDED_SYS_HEADERS_ARCHIVE=$WORK_DIR/included_sys_headers_${OS}_${CPU}_${BITS}.zip
    OUTPUTDIR_SRC_FILES_ARCHIVE=$WORK_DIR/outputdir_source_files_${OS}_${CPU}_${BITS}.zip
    SYS_HEADERS_AND_OUTPUTDIR_SRC_ARCHIVE=$TMP_DIR/sys_headers_and_outputdir_src_${OS}_${CPU}_${BITS}.zip
    SYS_HEADERS_AND_OUTPUTDIR_SRC_ARCHIVE_TOP_DIR=hotspot_sys_headers_and_outputdir_src
    SYS_HEADERS_AND_OUTPUTDIR_SRC_ARCHIVE_STEM_DIR=$SYS_HEADERS_AND_OUTPUTDIR_SRC_ARCHIVE_TOP_DIR/${OS}_${CPU}_${BITS} # e.g. hotspot_sys_headers_and_outputdir_src/windows_x86_64
    SYS_HEADERS_AND_OUTPUTDIR_SRC_ARCHIVE_STEM_DIR_ABS=$WORK_DIR/$SYS_HEADERS_AND_OUTPUTDIR_SRC_ARCHIVE_STEM_DIR # e.g. /tmp/cdt/work/hotspot_sys_headers_and_outputdir_src/windows_x86_64
    SYS_HEADERS_ARCHIVE_DIR=sys_headers
    SYS_HEADERS_ARCHIVE_DIR_ABS=$SYS_HEADERS_AND_OUTPUTDIR_SRC_ARCHIVE_STEM_DIR_ABS/$SYS_HEADERS_ARCHIVE_DIR # e.g. /tmp/cdt/work/hotspot_sys_headers_and_outputdir_src/windows_x86_64/sys_headers
    GENSRC_DIR=gensrc
    OUTPUTDIR_IN_ARCHIVE_DIR=output
    OUTPUTDIR_IN_ARCHIVE_DIR_ABS=$SYS_HEADERS_AND_OUTPUTDIR_SRC_ARCHIVE_STEM_DIR_ABS/$OUTPUTDIR_IN_ARCHIVE_DIR # e.g. /tmp/cdt/work/hotspot_sys_headers_and_outputdir_src/windows_x86_64/gensrc
    GENSRC_DIR_ABS=$(find $OUTPUTDIR/hotspot -name $GENSRC_DIR -type d)
    [ -d "$GENSRC_DIR_ABS" ] || report_and_exit "Could not find GENSRC_DIR=$GENSRC_DIR in $OUTPUTDIR/hotspot"
    echo "GENSRC_DIR_ABS is $GENSRC_DIR_ABS"
    GENSRC_DIR_REL=$(echo $GENSRC_DIR_ABS|sed "s:${OUTPUTDIR}/::g")
    echo "GENSRC_DIR_REL is $GENSRC_DIR_REL"

    if [ -e $SYS_HEADERS_AND_OUTPUTDIR_SRC_ARCHIVE_STEM_DIR_ABS ] ; then rm -fr $SYS_HEADERS_AND_OUTPUTDIR_SRC_ARCHIVE_STEM_DIR_ABS ; fi
    if [ -e $INCLUDED_SYS_HEADERS_ARCHIVE ] ; then rm $INCLUDED_SYS_HEADERS_ARCHIVE ; fi
    if [ -e $OUTPUTDIR_SRC_FILES_ARCHIVE ] ; then rm $OUTPUTDIR_SRC_FILES_ARCHIVE ; fi
    if [ -e $SYS_HEADERS_AND_OUTPUTDIR_SRC_ARCHIVE ] ; then rm $SYS_HEADERS_AND_OUTPUTDIR_SRC_ARCHIVE ; fi
}

# Expects -D macro definitions with shell quoting where necessarry
function extract_quoted_macro_definitions() {
    # Extract -D defined macros by splitting lines before -D and after the end of the definition.
    #
    #    V1 -D_LP64                             -> -D_LP64
    #    V2 -D_LP64=1                           -> -D_LP64=1
    #    V3 -DHOTSPOT_LIB_ARCH=\"amd64\"        -> V5
    #    V4 -D"COMPANY_NAME=\"SAP AG\""         -> V7
    #    V5 -DHOTSPOT_LIB_ARCH='"amd64"'        -> -DHOTSPOT_LIB_ARCH="amd64" 
    #    V6 -D "_WINSOCKAPI_"                   -> V1
    #    V7 -DSAPJVM_PLATFORM="\"windows\""     -> V5
    #

    file_with_definitions=$1

    V7_2_V5='s/"\\"/'"'"'"/g ; s/\\""/"'"'"'/g'
    V3_2_V5='s/=\\"\([^\ ]*\)\\"/'"='\"\1\"'/g"  #'s/=\\"/='"'"'/g'
    V4_2_V7="s/-D\"\([^=\"]*\)=/-D\1=\"/g"
    V6_2_V1='s/-D"\([^" ]*\)"/-D\1\n/g'
    V5="s/-D\([^=]*\)='\([^']*\)'/-D\1=\2\n/g"
    V1='s/-D\([^= ]*\) \|$/-D\1\n/g'
    V2="s/-D\([^= ]*\)=\([^ '\"]\+\)/-D\1=\2\n/g"

    $GSED "s/-D */\n-D/g; $V4_2_V7 ; $V6_2_V1 ; $V7_2_V5 ; $V3_2_V5 ; $V5 ; $V1 ; $V2" <$file_with_definitions \
        | $GSED -n '/^-D/s///p' | $GSED -n '/THIS_FILE=/!p'
}

# Like extract_quoted_macro_definitions, but all quotes removed.
function extract_macro_definitions() {
    # Extract -D defined macros by splitting lines before -D and after the end of the definition.
    #
    #    V1 -D_LP64                             -> -D_LP64
    #    V2 -D_LP64=1                           -> -D_LP64=1
    #    V3 -DSAPJVM_BUILD_ID="1.internal"      -> -DSAPJVM_BUILD_ID="1.internal"
    #

    file_with_definitions=$1

    V1='s/-D\([^= ]*\) \|$/-D\1\n/g'
    V2="s/-D\([^= ]*\)=\([^ '\"]\+\)/-D\1=\2\n/g"
    V3="s/-D\([^= ]*\)=\"\([^\"]\+\)\"/-D\1=\"\2\"\n/g"

    $GSED "s/-D */\n-D/g; $V1 ; $V2 ; $V3" <$file_with_definitions \
        | $GSED -n '/^-D/s///p' | $GSED -n '/THIS_FILE=/!p'
}


function add_included_files_using_cxx_cmdline() {
    cmdline_file=$1
    
    echo "adding included files"
    cmdline_file_mod=$WORK_DIR/cmdline_mod

    # modify cmdline to let the compiler print included files
    case $OS in
        linux|bsd)   SED_CXX_SHOW_INCLUDES="s!-c -MMD \(-MP \|\)-MF .\+\.o!-E -H -o /dev/null!";;
        solaris)   SED_CXX_SHOW_INCLUDES="s!-c .\+\.o!-E -H!";;
        aix)
            SED_CD="1i cd ${WORK_DIR}"
            SED_CXX_SHOW_INCLUDES="s!-c -qmakedep=gcc .\+\.o!-qsyntaxonly -qlist -qshowinc!"
            SED_CAT_AND_DEL_LST_FILE='$a cat *.lst && rm *.lst'
            ;;
        windows)
            SED_CXX_SHOW_INCLUDES="s!-c -showIncludes .\+\.obj!-E -showIncludes!"
            ;;
        *)       report_and_exit "unhandled OS case ($OS)";;
    esac
    $GSED -e "$SED_CD" -e "$SED_CXX_SHOW_INCLUDES" -e "$SED_CAT_AND_DEL_LST_FILE" <$cmdline_file >$cmdline_file_mod

    # execute modified cmdline
    case $OS in
        linux|bsd)
            # filter lines that begin with ... to get rid of gcc "Multiple include guards may be useful for:..."
            # and then remove leading ...
            $EXEC_SCRIPT_ON_BUILD_HOST $cmdline_file_mod 2>&1 | $GSED -n '/^\./s/^\.\+ //p' >> $ALL_INCLUDED_FILES
            ;;
        solaris)
            $EXEC_SCRIPT_ON_BUILD_HOST $cmdline_file_mod 2>&1 1> /dev/null | $GSED 's/^\s\+//' >> $ALL_INCLUDED_FILES
            ;;
        aix)
            # execute script and extract lines like the following from the generated .lst file
            #   10  =  /usr/vacpp/include/sys/types.h
            exec_script_on_build_host_synchronized $cmdline_file_mod 2>/dev/null | $GSED -n '\%^\s*[0-9]\+  =  \(/.*\)% s//\1/p' >> $ALL_INCLUDED_FILES
            ;;
        windows)
            $EXEC_SCRIPT_ON_BUILD_HOST $cmdline_file_mod 2>&1 1> /dev/null | $GSED -n '/Note: including file: *\(.*\)/s//\1/p' >>$ALL_INCLUDED_FILES
            ;;
        *)  report_and_exit "unhandled OS case ($OS)";;
    esac

    # remove duplicates
    mv $ALL_INCLUDED_FILES ${ALL_INCLUDED_FILES}.old
    $SORT --output=$ALL_INCLUDED_FILES -u ${ALL_INCLUDED_FILES}.old
}

function add_include_dirs_using_cxx_cmdline() {
    cmdline_file=$1
    
    echo "adding include directories"

    case $OS in
        linux|bsd)
            cmdline_file_mod=$WORK_DIR/cmdline_mod
            
            # modify cmdline to let the compiler print list of dirs searched for includes
            $GSED 's%\(.*\) -c .* \([^ ]\+\.cpp\)%\1 -E -Wp,-v \2%' <$cmdline_file >$cmdline_file_mod

            # execute modified cmdline
            $EXEC_SCRIPT_ON_BUILD_HOST $cmdline_file_mod 2>&1 1>/dev/null | $GSED -n '/^ *\//s/^ *//p' >> $ALL_INCLUDE_DIRS
            ;;
        solaris)
            cmdline_file_mod=$WORK_DIR/cmdline_mod
            
            # modify cmdline to let the compiler print list of dirs searched for includes
            $GSED 's%\(.*\) -c .* \([^ ]\+\.cpp\)%\1 -verbose=diags \2%' <$cmdline_file >$cmdline_file_mod

            # execute modified cmdline
            $EXEC_SCRIPT_ON_BUILD_HOST $cmdline_file_mod 2>&1 1>/dev/null | $GSED 's/-I/\n-I/g' | $GSED -n '/-I\([^-][^ ]\+\).*/ s//\1/p' >> $ALL_INCLUDE_DIRS
            ;;
        windows|aix)
            $GSED 's/-I/\n-I/g' <$cmdline_file | $GSED -n '/-I\([^ ]\+\).*/ s//\1/p ; /-I \+"\([^"]\+\)".*/ s//\1/p ; /-I \+\([^ ]\+\).*/ s//\1/p' >> $ALL_INCLUDE_DIRS
            ;;
        *)  report_and_exit "unhandled OS case ($OS)";;
    esac

    # remove duplicates
    mv $ALL_INCLUDE_DIRS ${ALL_INCLUDE_DIRS}.old
    $SORT --output=$ALL_INCLUDE_DIRS -u ${ALL_INCLUDE_DIRS}.old
}

function add_defines_from_cxx_cmdline() {
    cmdline_file=$1
    echo "adding defined macros"

    extract_quoted_macro_definitions $cmdline_file >> $ALL_DEFINES

    # remove duplicates
    mv $ALL_DEFINES ${ALL_DEFINES}.old
    $SORT --output=$ALL_DEFINES -u ${ALL_DEFINES}.old
}

function add_cxx_compiler_predifined_macros_and_include_dirs() {
    echo
    echo "adding c++ compiler predefined macros"
    
    os_cmdline=`$READLINK -f $CMDLINE_DIR/os_${OS}_${CPU}.*.cmdline`
    echo "using $os_cmdline"

    if [ ! -e $os_cmdline ] ; then
        report_and_exit "$os_cmdline missing"
    fi
    
    cxx_predefines_cmdline_file=$WORK_DIR/cxx_predefines.cmdline
    predefines_file=$WORK_DIR/cxx_predefines.cpp
    empty_cpp=$WORK_DIR/empty.cpp
    del_contents $empty_cpp

    case $OS in
        linux|bsd|solaris)
            # /usr/include is assumed to be in the include file search path, but on solaris the
            # option '-verbose=diags' used in add_include_dirs_using_cxx_cmdline does not show
            # it, so we add it here
            echo "/usr/include" >>$ALL_INCLUDE_DIRS
            if [ $OS = solaris ] ; then
                $GSED "s!-c -xMMD \(-xMP \|\)-xMF .*!-E -xdumpmacros $empty_cpp!" <$os_cmdline >$cxx_predefines_cmdline_file
            else
                $GSED "s!-c -MMD \(-MP \|\)-MF .*\$!-E -dM -o $predefines_file $empty_cpp!" <$os_cmdline >$cxx_predefines_cmdline_file
            fi


            # execute modified cmdline
            $EXEC_SCRIPT_ON_BUILD_HOST $cxx_predefines_cmdline_file 2>$predefines_file 1>/dev/null

            EXCL_ARG_MACROS='/#define [^ ]\+(/! p'
            $GSED -n "$EXCL_ARG_MACROS" <$predefines_file | $GSED '/#define \([^ ]\+\) \(.*\)/s//\1=\2/ ; /#define \(.*\)/s//\1/' >>$ALL_DEFINES

            if [ $OS = solaris ] ; then
	        # Sun Studio specific modifiers that can be ignored
                echo "__global"   >>$ALL_DEFINES
                echo "__hidden"   >>$ALL_DEFINES
                echo "__symbolic" >>$ALL_DEFINES
                echo "__thread"   >>$ALL_DEFINES
            fi
            ;;
        aix)
            # -V -> internal commandlines used by the compiler.
            # Include search paths are given with switches -qcpp_stdinc and -qc_sdtinc.
            # Some predefined macros are given with -D switches (shell quoting already removed)
            # -qshowmacros=pre -> predefined macros in preprocessor syntax, i.e. #define MACRO VALUE
            $GSED "s!-c -qmakedep=gcc .*!-E -qshowmacros=pre -V $empty_cpp!" <$os_cmdline >$cxx_predefines_cmdline_file

            # execute modified cmdline
            exec_script_on_build_host_synchronized $cxx_predefines_cmdline_file 2>/dev/null 1>$predefines_file
            $GSED -n '/.*-qcpp_stdinc=\([^ ]*\).*-qc_stdinc=\([^ ]*\).*/ s//\1:\2/p' <$predefines_file | $GSED 's/:/\n/g' >>$ALL_INCLUDE_DIRS

            EXCL_ARG_MACROS='/#define [^ ]\+(/! p'
            $GSED -n "$EXCL_ARG_MACROS" <$predefines_file | $GSED -n '/#define \([^ ]\+\) \(.*\)/s//\1=\2/p ; /#define \(.*\)/s//\1/p' >>$ALL_DEFINES
            # -D defines from xlCentry command line (shell quoting already removed)
            extract_macro_definitions $predefines_file >> $ALL_DEFINES
            ;;
        windows)
            CMDLINE_PATTERN_TO_REPLACE='-c -showIncludes .*'
            $GSED "s!$CMDLINE_PATTERN_TO_REPLACE!-E -Bxread_predefs_from_env.cmd $empty_cpp!" <$os_cmdline >$cxx_predefines_cmdline_file

            echo "@set MSC" > read_predefs_from_env.cmd # will be invoked because of -Bx option

            # execute modified cmdline
            $EXEC_SCRIPT_ON_BUILD_HOST $cxx_predefines_cmdline_file >$predefines_file

            extract_quoted_macro_definitions $predefines_file >> $ALL_DEFINES

            # Unfortunately we cannot use CDT's support for the Microsoft C++
            # toolchain, as it causes problems with a 64 bit configuration, because
            # it always defines _M_IX86. So we have to add predefined macros we do
            # not obtain with the method above
            # See https://github.com/eclipse/cdt/blob/master/windows/org.eclipse.cdt.msw.build/src/org/eclipse/cdt/msw/build/WinDiscoveredPathInfo.java
            # echo "_M_IX86=600" >> $ALL_DEFINES   # must not be defined in amd64 configurations
	    # echo "_WIN32=1" >> $ALL_DEFINES      # this we get with the method above
	    # echo "_MSC_VER=1400" >> $ALL_DEFINES # this we get with the method above
	    
	    # Microsoft specific modifiers that can be ignored
	    echo "__cdecl" >> $ALL_DEFINES
	    echo "__fastcall" >> $ALL_DEFINES
	    echo "__restrict" >> $ALL_DEFINES
	    echo "__sptr" >> $ALL_DEFINES
	    echo "__stdcall" >> $ALL_DEFINES
	    echo "__unaligned" >> $ALL_DEFINES
	    echo "__uptr" >> $ALL_DEFINES
	    echo "__w64" >> $ALL_DEFINES
	    
	    # Redefine some things so that the CDT parser can handle them, until there is a VC specific parser
	    echo "__forceinline=__inline" >> $ALL_DEFINES
	    echo "__int8=char" >> $ALL_DEFINES
	    echo "__int16=short" >> $ALL_DEFINES
	    echo "__int32=int" >> $ALL_DEFINES
	    echo "__int64=long long" >> $ALL_DEFINES
            ;;
        *)  report_and_exit "unhandled OS case ($OS)";;
    esac

    # There are a few places in the hotspot sources that needed small modifications to
    # aid CDT parsing and indexing (e.g. usage of microsoft's ia64 suffix). The places depend on ECLIPSE_CDT.
    echo "ECLIPSE_CDT" >> $ALL_DEFINES

    # sort and eliminate duplicates
    mv $ALL_DEFINES ${ALL_DEFINES}.old
    $SORT --output=$ALL_DEFINES -u ${ALL_DEFINES}.old
    mv $ALL_INCLUDE_DIRS ${ALL_INCLUDE_DIRS}.old
    $SORT --output=$ALL_INCLUDE_DIRS -u ${ALL_INCLUDE_DIRS}.old
}

function eliminate_duplicated_and_unwanted_macros() {
    # The gcc preprocessor produces #define ASSERT 1 when running
    #     g++ [...] -DASSERT -dM [...] 
    # so we end up with two definitions of ASSERT in $ALL_DEFINES.
    # Here we eliminate them.
    mv $ALL_DEFINES $ALL_DEFINES.dupl
    (
        prev_line=""
        while read -r cur_line ; do
            if [ "$prev_line" = "" ] ; then
                prev_line=$cur_line
                continue
            fi
            # check if $prev_line is a prefix of $cur_line
            prev_line_length=${#prev_line}
            if [ "$prev_line" != "${cur_line:0:$prev_line_length}" ] ; then
                echo -E "$prev_line"
            fi
            prev_line=$cur_line
        done
        echo $prev_line
    ) <$ALL_DEFINES.dupl >$ALL_DEFINES

    # -xdumpmacros on solaris gives __FILE__ and __LINE__
    mv $ALL_DEFINES $ALL_DEFINES.unwanted
    UNWANTED_MACROS="THIS_FILE\|__FILE__\|__LINE__"
    $GSED -n "/\($UNWANTED_MACROS\)/!p" <$ALL_DEFINES.unwanted >$ALL_DEFINES
}

function canonicalize_paths() {
    echo "eliminating relative path components and symlinks"
    mv $ALL_INCLUDE_DIRS ${ALL_INCLUDE_DIRS}.old
    mv $ALL_INCLUDED_FILES ${ALL_INCLUDED_FILES}.old
    case $OS in
        linux|bsd)
            ( while read line ; do $READLINK -f $line ; done ) <${ALL_INCLUDE_DIRS}.old >$ALL_INCLUDE_DIRS
            ( while read line ; do $READLINK -f $line ; done ) <${ALL_INCLUDED_FILES}.old >$ALL_INCLUDED_FILES
            ;;
        solaris|aix)
            $EXEC_SCRIPT_ON_BUILD_HOST -c "'while read line ; do $READLINK_BUILD_HOST -f \$line ; done'" <${ALL_INCLUDE_DIRS}.old >$ALL_INCLUDE_DIRS
            $EXEC_SCRIPT_ON_BUILD_HOST -c "'while read line ; do $READLINK_BUILD_HOST -f \$line ; done'" <${ALL_INCLUDED_FILES}.old >$ALL_INCLUDED_FILES
            ;;
        windows)
            # convert to short and then long format to get case of the file names right
            cygpath -w -s -f ${ALL_INCLUDE_DIRS}.old > ${ALL_INCLUDE_DIRS}.ws.txt
            cygpath -w -l -f ${ALL_INCLUDE_DIRS}.ws.txt > ${ALL_INCLUDE_DIRS}.wl.txt
            cygpath -u -f ${ALL_INCLUDE_DIRS}.wl.txt >${ALL_INCLUDE_DIRS}

            cygpath -w -s -f ${ALL_INCLUDED_FILES}.old > ${ALL_INCLUDED_FILES}.ws.txt
            cygpath -w -l -f ${ALL_INCLUDED_FILES}.ws.txt > ${ALL_INCLUDED_FILES}.wl.txt
            cygpath -u -f ${ALL_INCLUDED_FILES}.wl.txt >${ALL_INCLUDED_FILES}
            ;;
        *)  report_and_exit "unhandled OS case ($OS)";;
    esac
    mv ${ALL_INCLUDE_DIRS} ${ALL_INCLUDE_DIRS}.unsorted
    $SORT --output=${ALL_INCLUDE_DIRS} -u ${ALL_INCLUDE_DIRS}.unsorted
    mv ${ALL_INCLUDED_FILES} ${ALL_INCLUDED_FILES}.unsorted
    $SORT --output=${ALL_INCLUDED_FILES} -u ${ALL_INCLUDED_FILES}.unsorted
}

function find_top_dir() {
    if [ $IS_GTE_JDK10 -ne 0 ] ; then
        # looks for a line ending with '/hotspot/share' in $ALL_INCLUDE_DIRS and uses the path before as top dir
        JDK_DIR_ABS=`$GSED -n '\%^\(.*\)/src/hotspot/share$%s//\1/p' <$ALL_INCLUDE_DIRS`
        echo "JDK_DIR_ABS is $JDK_DIR_ABS"
        # >=JDK10: ROOT/src/hotspot
        TOP_DIR_ABS=$JDK_DIR_ABS
    else # <JDK10
        # looks for a line ending with '/src/share/vm' in $ALL_INCLUDE_DIRS and uses the path before as top dir
        HOTSPOT_DIR_ABS=`$GSED -n '\%^\(.*\)/src/share/vm$%s//\1/p' <$ALL_INCLUDE_DIRS`
        echo "HOTSPOT_DIR_ABS is $HOTSPOT_DIR_ABS"
        HOTSPOT_TO_TOP_PATH=..                                # if == JDK9  ROOT/hotspot
        [ $IS_GTE_JDK10 -eq 0 ] || HOTSPOT_TO_TOP_PATH=../..  # if >= JDK10 ROOT/src/hotspot
    fi
    echo "TOP_DIR_ABS is $TOP_DIR_ABS"
}

function remove_from() {
    FILE_LIST=$1
    FILTER_PATH=$2
    cp $FILE_LIST ${FILE_LIST}.old
    $GSED -n "\%${FILTER_PATH}%!p" <$FILE_LIST.old >$FILE_LIST
}

function keep_only() {
    FILE_LIST=$1
    FILTER_PATH=$2
    cp $FILE_LIST ${FILE_LIST}.old
    $GSED -n "\%${FILTER_PATH}%p" <$FILE_LIST.old >$FILE_LIST
}

function generate_proj_settings {
    echo "generating $SETTINGS_XML"
    CDT_PROJECT_NAME="HotSpot"
    if [ $IS_GTE_JDK10 -eq 0 ] ; then
        MAP_HS_SRC="\%$HOTSPOT_DIR_ABS/src% s%%!$CDT_PROJECT_NAME/hotspot_src%"
    else
        MAP_HS_SRC="\%$JDK_DIR_ABS/src/hotspot% s%%!$CDT_PROJECT_NAME/hotspot_src%"
        # jni.h and jvm.h
        MAP_JAVA_BASE_INCLUDE="\%$JDK_DIR_ABS/src/java.base% s%%!$CDT_PROJECT_NAME/java_base_include%"
    fi
    MAP_GENSRC="\%$OUTPUTDIR% s%%!$CDT_PROJECT_NAME/hotspot_sys_headers_and_outputdir_src/${OS}_${CPU}_${BITS}/${OUTPUTDIR_IN_ARCHIVE_DIR}%"
    MAP_SYSINCLS="s%^/%!$CDT_PROJECT_NAME/hotspot_sys_headers_and_outputdir_src/${OS}_${CPU}_${BITS}/${SYS_HEADERS_ARCHIVE_DIR}/%"
    XML_DECO_INCLUDE="s%\(.*\)%<includepath workspace_path=\"true\">\1</includepath>%"
    MAP_MACRO_NOVAL="\%^[^=]*$%s%%<macro><name>&</name><value/></macro>%"
    MAP_MACRO_VAL="\%^\([^=]*\)=\(.*\)$%s%%<macro><name>\1</name><value>\2</value></macro>%"

cat >> $SETTINGS_XML <<EOF    
<?xml version="1.0" encoding="UTF-8"?>
<cdtprojectproperties>
<section name="org.eclipse.cdt.internal.ui.wizards.settingswizards.IncludePaths">
<language name="C++ Source File">

EOF
$GSED "$MAP_HS_SRC ; $MAP_JAVA_BASE_INCLUDE ; $MAP_J2SE ; $MAP_LIBS ; $MAP_GENSRC ; $MAP_SYSINCLS ; s%!%/% ; $XML_DECO_INCLUDE" <$ALL_INCLUDE_DIRS >>$SETTINGS_XML
cat >> $SETTINGS_XML <<EOF    

</language>

<language name="C Source File">

EOF
$GSED "$MAP_HS_SRC ; $MAP_JAVA_BASE_INCLUDE ; $MAP_J2SE ; $MAP_LIBS ; $MAP_GENSRC ; $MAP_SYSINCLS ; s%!%/% ; $XML_DECO_INCLUDE" <$ALL_INCLUDE_DIRS >>$SETTINGS_XML
cat >> $SETTINGS_XML <<EOF    

</language>

</section>
<section name="org.eclipse.cdt.internal.ui.wizards.settingswizards.Macros">
<language name="C++ Source File">

EOF
$GSED "$MAP_MACRO_NOVAL ; $MAP_MACRO_VAL" <$ALL_DEFINES >>$SETTINGS_XML
cat >> $SETTINGS_XML <<EOF    

</language>

<language name="C Source File">

EOF
$GSED "$MAP_MACRO_NOVAL ; $MAP_MACRO_VAL" <$ALL_DEFINES >>$SETTINGS_XML
cat >> $SETTINGS_XML <<EOF

</language>

</section>
</cdtprojectproperties>
EOF
}

#
# MAIN code
#

initialize

CMDLINE_FILE_PATTERNS=(
#     jni.
#     g1CollectedHeap.
#     concurrentMarkSweepGeneration.
# #    dependencyContext.
# #    jvm.
# #    os
# #    thread
)
CMDLINE_FILE_PATTERNS=${CMDLINE_FILE_PATTERNS[*]}

if [ "$CMDLINE_FILE_PATTERNS" = "" ] ; then
    # we could scan all cmdline files, but it's probabbly sufficient to do it for representative ones
    CMDLINE_FILE_PATTERNS='ad_ assembler_*_ c1_FrameMap_ c1_IR c1_LIR c2compiler g1CollectedHeap g1_globals genMarkSweep globalDefinitions globals jni jniFastGetField_ jniHandles jniPeriodicChecker jvm jvmEnv jvmExt jvm_ jvmtiEnv jvmtiEnvBase jvmtiEnvThreadState jvmtiEventController jvmtiExport jvmtiExtensions jvmtiImpl jvmtiManageCapabilities klass klassFactory klassVtable kvmFacade macroAssembler_*_cos macroAssembler_ mallocSiteTable mallocTracker management markOop markSweep metaspace mutex mutexLocker nativeCallStack nmethod objectMonitor oop orderAccess os osThread osThread_ os_ ostream output park profilingControl profilingHprofAddons profilingIOTrace profilingMethodParameters profilingTBS profilingThreadDump profilingThreadInfo profilingThreadState regExpUtil runtime_ sharedMemory_ sharedRuntime_ taskqueue templateInterpreterGenerator_ templateTable_ thread thread_*_ timer timerTrace trc trcex uniqueId universe universe_ext utf8 vSphereFacade vmThread vm_version_'
fi

# add *.cmdline to each pattern given in CMDLINE_FILE_PATTERNS
CMDLINE_FILE_PATTERNS=$(
    set -f # no globbing
    for pattern in $CMDLINE_FILE_PATTERNS ; do
        echo -n "$CMDLINE_DIR/$pattern*.cmdline "
    done
)

# expand wildcards in $CMDLINE_FILE_PATTERNS
CMDLINE_FILES=$(shopt -s nullglob ; ls -1 $CMDLINE_FILE_PATTERNS | $SORT -u)

# process *.cmdline files
for cur_cmdline_file in $CMDLINE_FILES ; do
    if [ ! -e $cur_cmdline_file ] ; then continue ; fi
    echo -E "processing $cur_cmdline_file"
    if ! $GSED -n '/\.cpp$/! q 1' <$cur_cmdline_file ; then
        echo "no cpp compilation - skipping."
        continue
    fi
    add_included_files_using_cxx_cmdline $cur_cmdline_file
    add_include_dirs_using_cxx_cmdline $cur_cmdline_file
    add_defines_from_cxx_cmdline $cur_cmdline_file
done

add_cxx_compiler_predifined_macros_and_include_dirs
eliminate_duplicated_and_unwanted_macros
canonicalize_paths

echo
find_top_dir
# list of system headers
cp $ALL_INCLUDED_FILES $ALL_SYSTEM_INCLUDES
remove_from $ALL_SYSTEM_INCLUDES $TOP_DIR_ABS
remove_from $ALL_SYSTEM_INCLUDES $OUTPUTDIR
# files included from output dir
cp $ALL_INCLUDED_FILES $ALL_OUTPUTDIR_INCLUDES
keep_only $ALL_OUTPUTDIR_INCLUDES $OUTPUTDIR
# add other relevant sources from OUTPUTDIR to the list
(cd $OUTPUTDIR ; $FIND $GENSRC_DIR_REL  -type f  -regex '.*\.\(cpp\|hpp\|c\|h\|java\|ad\)') >> $ALL_OUTPUTDIR_INCLUDES
# remove $OUTPUTDIR prefix
mv $ALL_OUTPUTDIR_INCLUDES ${ALL_OUTPUTDIR_INCLUDES}.old
sed "s:${OUTPUTDIR}/::g" ${ALL_OUTPUTDIR_INCLUDES}.old > $ALL_OUTPUTDIR_INCLUDES

# create zip archives
echo
echo "creating $INCLUDED_SYS_HEADERS_ARCHIVE with referenced system headers "
$EXEC_ON_BUILD_HOST zip -@ $INCLUDED_SYS_HEADERS_ARCHIVE <$ALL_SYSTEM_INCLUDES >${INCLUDED_SYS_HEADERS_ARCHIVE}.log
echo "creating $OUTPUTDIR_SRC_FILES_ARCHIVE with source files from the output directory"
(cd $OUTPUTDIR ; zip -@ $OUTPUTDIR_SRC_FILES_ARCHIVE <$ALL_OUTPUTDIR_INCLUDES) >${OUTPUTDIR_SRC_FILES_ARCHIVE}.log

echo "creating $SYS_HEADERS_AND_OUTPUTDIR_SRC_ARCHIVE with the expected directory structure"
mkdir -p $SYS_HEADERS_ARCHIVE_DIR_ABS
mkdir -p $OUTPUTDIR_IN_ARCHIVE_DIR_ABS
cd $SYS_HEADERS_ARCHIVE_DIR_ABS
unzip -o $INCLUDED_SYS_HEADERS_ARCHIVE >${INCLUDED_SYS_HEADERS_ARCHIVE}_unzip.log
#find and include symbolic links under include dirs
if [ $OS != windows ] ; then
    $EXEC_SCRIPT_ON_BUILD_HOST $ADD_SYMLINKS_TO_ARCHIVE_CMD $ALL_INCLUDE_DIRS $READLINK_BUILD_HOST $SYS_HEADERS_ARCHIVE_DIR_ABS
fi
cd $OUTPUTDIR_IN_ARCHIVE_DIR_ABS
unzip -o $OUTPUTDIR_SRC_FILES_ARCHIVE >${OUTPUTDIR_SRC_FILES_ARCHIVE}_unzip.log
# zip system headers and referenced sources from outputdir
cd $WORK_DIR
# but remove dangling symlinks first
find $SYS_HEADERS_AND_OUTPUTDIR_SRC_ARCHIVE_STEM_DIR -xtype l | xargs -r rm
zip -y -r $SYS_HEADERS_AND_OUTPUTDIR_SRC_ARCHIVE $SYS_HEADERS_AND_OUTPUTDIR_SRC_ARCHIVE_STEM_DIR >${SYS_HEADERS_AND_OUTPUTDIR_SRC_ARCHIVE}.log

generate_proj_settings

echo
echo "DONE!"
echo "Please import"
echo "$SYS_HEADERS_AND_OUTPUTDIR_SRC_ARCHIVE"
echo "$SETTINGS_XML"
echo "into the hotspot cdt project"
echo
