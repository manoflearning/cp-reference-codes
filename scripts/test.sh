#!/usr/bin/env bash
set -euo pipefail
shopt -s nullglob

root_dir=$(cd "$(dirname "$0")/.." && pwd)
cd "$root_dir"

out_dir=$(mktemp -d)
trap 'rm -rf "$out_dir"' EXIT

all_targets=(1-ds 2-graph 3-tree 4-optimizations 5-string 6-geometry 7-math 8-misc)
targets=()

if (($# == 0)); then
  targets=("${all_targets[@]}")
else
  for arg in "$@"; do
    case "$arg" in
      all) targets=("${all_targets[@]}") ;;
      1-ds|2-graph|3-tree|4-optimizations|5-string|6-geometry|7-math|8-misc) targets+=("$arg") ;;
      *) echo "usage: $0 [all|${all_targets[*]}]"; exit 1 ;;
    esac
  done
fi

files=()
for t in "${targets[@]}"; do
  files+=(tests/"$t"/test_*.cpp)
done

if ((${#files[@]} == 0)); then
  echo "no tests matched"
  exit 0
fi

for src in "${files[@]}"; do
  bin="$out_dir/$(basename "${src%.cpp}")"
  echo "[build] $src"
  cflags=(-std=c++17 -O2 -pipe)
  if [[ $(basename "$src") == "test_simd.cpp" ]]; then cflags+=(-mavx2); fi
  g++ "${cflags[@]}" "$src" -o "$bin"
  echo "[run] $bin"
  "$bin"
done

echo "ok"
