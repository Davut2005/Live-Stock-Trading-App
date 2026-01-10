#!/usr/bin/env bash

# Never fail the CI because of cppcheck findings
set +e

echo "Starting Cppcheck (GitHub-safe mode)..."

BUILD_DIR="${BUILD_DIR:-build}"
EXT_DIR="${EXT_DIR:-third-party}"

# Ensure compile_commands.json exists
if [ ! -f "${BUILD_DIR}/compile_commands.json" ]; then
  echo "WARNING: ${BUILD_DIR}/compile_commands.json not found. Skipping cppcheck."
  exit 0
fi

cppcheck \
  --enable=all \
  --check-level=exhaustive \
  --inline-suppr \
  --project="${BUILD_DIR}/compile_commands.json" \
  -i"${BUILD_DIR}" \
  -i"${EXT_DIR}" \
  --suppress=missingIncludeSystem \
  --suppress=unmatchedSuppression \
  --suppress=unusedFunction \
  --suppress=useStlAlgorithm \
  --max-ctu-depth=2 \
  --timeout=300 \
  --force \
  --quiet \
  2>&1 | tee cppcheck.log

echo "Cppcheck finished (warnings allowed)."

exit 0
