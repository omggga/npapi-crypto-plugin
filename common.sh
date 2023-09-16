#!/bin/bash

RUN_FROM=$(dirname "$0")
FB_ROOT=$(cd "${RUN_FROM}"; pwd)
BUILDDIR=""
PROJDIR=""
USED_ARGS=0

print_usage() {
    echo "usage: $0 [<project dir> [<build dir>]] [<params ...>]"
}

check_proj_dir() {
    if [[ ! -d $1 && ! -L $1 ]]; then
        echo "ERROR: Project directory $1 does not exist."
        print_usage
        exit 1
    fi
}

# Check if $1 is set and doesn't start with '-'
if [[ -n "$1" && ! "$1" =~ ^- ]]; then 
    check_proj_dir "$1"
    PROJDIR="$1"
    USED_ARGS=1

    # Check if $2 is set and doesn't start with '-'
    if [[ -n "$2" && ! "$2" =~ ^- ]]; then
        BUILDDIR="$2"
        USED_ARGS=2
    fi
fi

# Set default values if not provided
PROJDIR=${PROJDIR:-"${RUN_FROM}/projects"}
BUILDDIR=${BUILDDIR:-$( [[ "$PROJDIR" == "examples" ]] && echo "${RUN_FROM}/buildex" || echo "${RUN_FROM}/build" )}

check_proj_dir "$PROJDIR"
PROJDIR=$(cd "$PROJDIR"; pwd)

mkdir -p "$BUILDDIR"
BUILDDIR=$(cd "$BUILDDIR"; pwd)

echo "Using projects in: $PROJDIR"
echo "Generating build files in: $BUILDDIR"
echo "NOTE: The build files in $BUILDDIR should *NEVER* be modified directly. Make changes in cmake and re-run this script."

# Remove consumed arguments
shift $USED_ARGS
