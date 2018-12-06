#!/bin/bash

##
## Generates a CMD script to fixup symbolic links in system header archive for MS Windows
##
## Searches for symbolic links and creates a MS Windows shell script in the parent directory that
## recreates the symbolic links as NTFS symbolic links.
##

PROJ_ROOT=..
SYS_HEADERS_ARCHIVE=hotspot_sys_headers_and_outputdir_src
OUTPUT_FILE=$PROJ_ROOT/as_administrator_regen_symlinks_on_windows.cmd

if [ ! -d "$PROJ_ROOT/$SYS_HEADERS_ARCHIVE" ] ; then
    echo "ERROR: system header archive not found at $PROJ_ROOT/$SYS_HEADERS_ARCHIVE"
    exit 1
fi

echo "generating $OUTPUT_FILE"

function process_link() {
    while read link ; do
        link_target="$(readlink $link)"
        link_target_canon="$(readlink -f $link)"
        # / -> \ in link and link_target
        link="${link//\//\\}"
        link_target="${link_target//\//\\}"
        # first delete the link
        echo "del \"$link\""
        if [ -d "$link_target_canon" ] ; then
            # target is a directory
            echo "mklink /D \"$link\" \"$link_target\""
        else
            # target is a directory
            echo "mklink    \"$link\" \"$link_target\""
        fi
    done
}

cat <<EOF > $OUTPUT_FILE
@setlocal

REM
REM This script deletes UNIX symbolic links and recreates them as windows symbolic links.
REM Creating symbolic links requires special permissions therefore you have to run
REM this script as administrator (right click in Explorer and select "Run as administrator")
REM

REM change to parent directory of the running script
cd %~dp0

EOF

# change to proj root directory
(cd $PROJ_ROOT && find "$SYS_HEADERS_ARCHIVE" -type l | process_link) >> $OUTPUT_FILE

echo pause >> $OUTPUT_FILE

echo "DONE!"
