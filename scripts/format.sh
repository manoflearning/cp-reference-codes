#!/usr/bin/env bash
root="$(cd "$(dirname "$0")/.." && pwd)"
target="$root"
mapfile -t files < <(find "$target" -type f \( -name '*.cpp' -o -name '*.hpp' \))
((${#files[@]})) || { echo "no .cpp/.hpp files in $target"; exit 0; }
declare -A before
for f in "${files[@]}"; do before["$f"]="$(sha1sum "$f" | cut -d' ' -f1)"; done
clang-format -i "${files[@]}"
changed=()
for f in "${files[@]}"; do [[ ${before["$f"]} != "$(sha1sum "$f" | cut -d' ' -f1)" ]] && changed+=("$f"); done
echo "formatted ${#files[@]} file(s) in $target"
((${#changed[@]})) && printf 'changed %d file(s):\n%s\n' "${#changed[@]}" "$(printf '%s\n' "${changed[@]}")" || echo "no files changed"
