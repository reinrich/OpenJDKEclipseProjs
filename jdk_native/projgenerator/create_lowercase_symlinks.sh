#!/bin/bash
#
# Recurses through given directory and adds lowercase symbolic links
# for every file that contains capital characters.
# This is necessary for the hotspot eclipse-cdt project, if the MS Windows
# system headers are kept on a filesystem that is case sensitive (typically
# on Linux).
#

function print_usage_and_exit() {
    echo
    echo "usage: `basename $0` [-n] <directory to process>"
    echo
    exit 1
}

if [ $# -ne 1 -a $# -ne 2 ] ; then
    print_usage_and_exit
fi

DOIT=1
if [ $# -eq 2 ] ; then
    if [ "$1" = "-n" ] ; then DOIT=0 ; else print_usage_and_exit ; fi
    shift
fi

DIR="$1"
cd "$DIR"

function process_dir() {
    pushd . 1> /dev/null
    _cur_dir="$1"
    cd "$_cur_dir"
    echo "processing directory $_cur_dir"
    for ff in * ; do
        if [ -d "$ff" ] ; then continue ; fi  # skip if it is a directory
        ffl="`echo $ff | tr '[:upper:]' '[:lower:]'`"
        # add symlink to lowercase version if $ff contains capitals and if
        # lowercase version does not exist
        if [ ! -e "$ffl" ] ; then
            echo "   $ff: adding symlink $ffl"
            if [ $DOIT -eq 1 ] ; then
                ln -s "$ff" "$ffl"
            fi
        else
            echo "   $ff: nothing to do"
        fi
    done
    popd 1> /dev/null
}

find . -type d | while read -r cur_dir ; do process_dir "$cur_dir"; done
