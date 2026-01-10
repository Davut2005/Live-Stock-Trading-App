#!/usr/bin/bash
set -e  # stop on any error

echo "Starting Cppcheck..."

cppcheck --enable=all \
    --inline-suppr \
    --project="${BUILD_DIR:-build}"/compile_commands.json \
    -i"${BUILD_DIR:-build}" --suppress="*:${BUILD_DIR:-build}/*" \
    -i"${EXT_DIR:-ext}" --suppress="*:${EXT_DIR:-ext}/*" \
    --suppress=missingIncludeSystem \
    --suppress=unmatchedSuppression \
    --suppress=unusedFunction \
    --suppress=useStlAlgorithm \
    --check-level=exhaustive 2>&1 | tee cppcheck.log

echo "Cppcheck completed successfully"

# Ensure the action doesn't fail even if cppcheck finds warnings
exit 0
