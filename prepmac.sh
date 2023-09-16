#!/bin/bash -e

GEN='Xcode'

# Source the common script and shift arguments
source "${0%/*}/common.sh" "$@"
shift $USED_ARGS

# Set architecture if not already set
ARCH=-DCMAKE_OSX_ARCHITECTURES="${CMAKE_OSX_ARCHITECTURES:-i386;x86_64}"

# Change to the build directory and run CMake
pushd "$BUILDDIR" > /dev/null
echo cmake -G "$GEN" -DFB_ROOT="${FB_ROOT}" ${ARCH} "$@" "${PROJDIR}"
if ! cmake -G "$GEN" -DFB_ROOT="${FB_ROOT}" ${ARCH} "$@" "${PROJDIR}"; then
    echo "CMake failed. Please check error messages"
    popd > /dev/null
    exit 1
fi

popd > /dev/null
