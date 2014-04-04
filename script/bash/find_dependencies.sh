#!/bin/bash

full_name=$(readlink -e "$1")
nt2_module_root=$(echo "$full_name" | sed -r 's@/modules/.*$@/modules@')
nt2_module_dirs=$(find "$nt2_module_root" -name 'include' -prune)
nt2_binary_include="$NT2_BINARY_ROOT/include"

tryfile="boost/simd/include/functions/plus.hpp"
if ! [ -e "$nt2_binary_include/$tryfile" ]
then
  try1=$(echo "$nt2_module_root" | sed 's@/modules$@/build/include@')
  try2=$(echo "$nt2_module_root" | sed 's@/dev/nt2/modules$@/build/nt2/include@')
  if [ -e "$try1/$tryfile" ]
  then
    nt2_binary_include=$try1
  elif [ -e "$try2/$tryfile" ]
  then
    nt2_binary_include=$try2
  else
    echo "couldn't find NT2 generated headers, set NT2_BINARY_ROOT"
    exit 1
  fi
fi

modules=
not_found=
while read i
do
  file=$(echo "$i" | sed -r 's@^#include <([^>]+)>$@\1@')
  in_module=

  while [ "$file" != "" ] && [ -e "$nt2_binary_include/${file}" ] && [ "$in_module" == "" ]
  do
    in_module=$(grep -Eo "Automatically generated for module [^ ]+" "$nt2_binary_include/$file" | cut -d' ' -f5)
    if [ "$in_module" == "" ]
    then
      file=$(grep -E "^#include <([^>]+)>$" "$nt2_binary_include/$file" | head -n 1 | sed -r 's@^#include <([^>]+)>$@\1@')
    fi
  done

  if [ $VERBOSE ]; then echo "looking for $file"; fi
  while read dir
  do
    if [ "$file" != "" ] && [ -e "$dir/$file" ]
    then
      in_module=$(echo "$dir" | sed -r 's@'$nt2_module_root'/(.*?)/include@\1@' | tr '/' '.')
    fi
  done < <(echo "$nt2_module_dirs")

  modules=$(echo $modules $in_module)
  if [ "$in_module" == "" ]
  then
    not_found=$(echo $not_found $file)
    if [ $VERBOSE ]
    then
      echo "not found!"
    fi
  elif [ $VERBOSE ]
  then
    echo "in module $in_module"
  fi

done < <(grep -E "^#include <([^>]+)>$" "$1")

if [ $VERBOSE ]; then echo -e "\nall dependencies:"; fi
for module in $modules
do
  echo $module
done | sort | uniq

if [ $VERBOSE ] && [ "$not_found" != "" ]
then
  echo -e "\nnot found:"
  for file in $not_found
  do
    echo "$file"
  done
fi
