#!/bin/sh

set -e

tmpFile=$(mktemp)
gcc -o $tmpFile $(find src/ -name "*.c") -lpython3.12

exec "$tmpFile" "$@"
