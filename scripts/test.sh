#!/usr/bin/env bash
set -euo pipefail

root_dir=$(cd "$(dirname "$0")/.." && pwd)
cd "$root_dir"

out_dir=$(mktemp -d)
trap 'rm -rf "$out_dir"' EXIT

for src in tests/1-ds/test_*.cpp; do
  bin="$out_dir/$(basename "${src%.cpp}")"
  echo "[build] $src"
  g++ -std=c++17 -O2 -pipe "$src" -o "$bin"
  echo "[run] $bin"
  "$bin"
done

echo "ok"
