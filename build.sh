#!/bin/sh

set -e

tmpFile=$(mktemp)
gcc -o $tmpFile $(find src/ -name "*.c")

exec "$tmpFile" "$@"
