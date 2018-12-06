#!/bin/bash
#
# DESCRIPTION: finds symbolic links in $ALL_INCLUDE_DIRS, converts them to
# relative links, if necessary and adds them to the archive root directory
# $SYS_HEADERS_ARCHIVE_DIR_ABS
#

if [ $# -ne 3 ] ; then
    echo
    echo "*** ERROR: wrong number of arguments"
    echo
    echo "usage: [DEBUG_MODE=1] `basename $0` <file with include dirs> <readlink command> <sys headers archive dir>"
    echo
    exit 1
fi

ALL_INCLUDE_DIRS=$1
READLINK=$2
SYS_HEADERS_ARCHIVE_DIR_ABS=$3

function debug_print() {
    [ "$DEBUG_MODE" != "1" ] || echo "$1" 1>&2
}

VIDX=0
SIDX=0
function already_visited() {
    for ((ii=0; ii < $VIDX; ii++)) ; do
        [ "${VISITED[$ii]}" != "$1" ] || return 0 # found -> true
    done
    return 1 # not found -> false
}

# Find symlinks below given directory and collect them in $ALL_SYMLINKS.
# Recurse with link targets
function discover_symlinks_in_include_dir() {
    if already_visited "$1" ; then echo "skipping '$1' (already visited)" ; return ; fi
    if [ ! -d "$1" -a ! -h "$1" ] ; then echo "skipping '$1' (not directory or symlink)" ; return ; fi

    echo "scanning '$1' for symlinks"
    VISITED[$((VIDX++))]="$1"
    if [ -h "$1" ] ; then
        SYMLINKS="$1"
    else
        SYMLINKS=$(find "$1" -type l)
    fi
    if [ "$SYMLINKS" != "" ] ; then
        for ss in $SYMLINKS ; do
            echo "  found $ss"
            ALL_SYMLINKS[$((SIDX++))]="$ss"
            debug_print "RECURSING"
            discover_symlinks_in_include_dir $($READLINK -f $ss)
        done
    fi
}

function discover_symlinks_in_include_dirs () {
    echo "adding symbolic links under include dirs"

    while read -r dd ; do
        discover_symlinks_in_include_dir $dd
    done
}

# $1: START_DIR
# $2: TARGET
# prints path to $TARGET relative to $START_DIR
function to_relative_path() {
    START_DIR=$($READLINK -f "$1")
    ABS_TARGET=$($READLINK -f "$2")
    debug_print "ABS_TARGET:$ABS_TARGET"
    REL_PATH=
    while [ 1 -eq 1 ] ; do
        ABS_DIR=$($READLINK -f "$START_DIR/$REL_PATH")
        debug_print "ABS_DIR:$ABS_DIR   REL_PATH:$REL_PATH"
        if [ "${ABS_TARGET:0:${#ABS_DIR}}" = "${ABS_DIR}" ] ; then
            TARGET_OFFSET=$((${#ABS_DIR} + 1))
            [ $TARGET_OFFSET -gt 2 ] || TARGET_OFFSET=1 # special case for ABS_DIR = /
            if [ "$REL_PATH" = "" ] ; then
                REL_PATH="${ABS_TARGET:$TARGET_OFFSET}"
            else
                REL_PATH="$REL_PATH/${ABS_TARGET:$TARGET_OFFSET}"
            fi
            debug_print "REL_PATH:$REL_PATH"
            echo "$REL_PATH"
            return 0
        fi
        if [ "$REL_PATH" = "" ] ; then
            REL_PATH=".."
        else
            REL_PATH="$REL_PATH/.."
        fi
    done
}

function add_symlinks() {
    echo "## adding symlinks:"
    cur_dir=$(pwd)
    for ((ii=0; ii < $SIDX; ii++)) ; do
        cd $cur_dir
        LINK="${ALL_SYMLINKS[$ii]}"
        ls -l -o -g $LINK
        LINK_NAME="$(basename $LINK)"
        SRC_DIR="$(dirname $LINK)"
        SRC_DIR="$($READLINK -f "$SRC_DIR")" # make canonical
        TARGET="$($READLINK "$LINK")"
        SRC_DIR_MAPPED="${SYS_HEADERS_ARCHIVE_DIR_ABS}${SRC_DIR}"
        mkdir -p "$SRC_DIR_MAPPED"
        cd "$SRC_DIR_MAPPED"
        debug_print '$SRC_DIR_MAPPED:'"$SRC_DIR_MAPPED"
        debug_print '$LINK_NAME:'"$LINK_NAME"
        [ ! -e "$LINK_NAME" -a ! -h "$LINK_NAME" ] || continue
        if [ ${TARGET:0:1} = / ] ; then
            echo "absolut target: $TARGET"
            TARGET=$(to_relative_path "$SRC_DIR" "$TARGET")
            echo "converted to $TARGET"
        fi
        ln -s "$TARGET" "$LINK_NAME"
    done
    cd $cur_dir
}

discover_symlinks_in_include_dirs <$ALL_INCLUDE_DIRS
add_symlinks
