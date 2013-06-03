#!/bin/bash

current_path=$(readlink -e $(dirname "${BASH_SOURCE[0]}"))
nt2_root=$(echo "$current_path" | sed -r 's@/script/bash$@@')

nt2_module_dirs=$(find "$nt2_root/modules" -name 'include' -prune "$@")

for module_dir in $nt2_module_dirs
do
  module=$(echo "$module_dir" | sed -r 's@'$nt2_root'/modules/(.*?)/include@\1@' | tr '/' '.')
  echo "$module:"

  if [ "$VERBOSE" == 1 ]
  then
    while read file
    do
      echo $'\t'"find dependencies of file $file"
      while read i
      do
        echo $'\t'"$i"
      done < <($nt2_root/script/bash/find_dependencies.sh "$file")
    done < <(find "$module_dir" -name '*.hpp')
  else
    while read file
    do
      for i in $($nt2_root/script/bash/find_dependencies.sh "$file")
      do
        echo $'\t'"$i"
      done
    done < <(find "$module_dir" -name '*.hpp') | sort | uniq | grep -vFx $'\t'"$module"
  fi
  echo ""
done
