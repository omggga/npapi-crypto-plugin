#!/bin/bash -e

GEN="${GEN:-Unix Makefiles}"

# Source the common script and shift arguments
source "${0%/*}/common.sh" "$@"
shift $USED_ARGS

# Change to the build directory and run CMake
pushd "$BUILDDIR" > /dev/null
if ! cmake -G "$GEN" -DFB_ROOT="${FB_ROOT}" "$@" "${PROJDIR}"; then
    echo "CMake failed. Please check error messages"
    popd > /dev/null
    exit 1
fi

popd > /dev/null
