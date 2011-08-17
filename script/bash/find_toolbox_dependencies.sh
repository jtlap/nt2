#!/bin/bash

if [ $# -ne 3 ]
then
    echo "Usage: `basename $0` <binary-include-path> <prefix> <directory>..."
    exit 65
fi

for i in `find ${@:3} -name '*.hpp'`
do
    for j in `grep -E "$2/include/(functions|constants)/([^/]+).hpp" $i | sed -r 's@^.*'$2'/include/([^.]+).hpp.*$@'$2'/include/\1.hpp@'`
    do
      grep -E "$2/toolbox/([^/]+)/" "$1/$j" | sed -r 's@^.*'$2'/toolbox/([^/]+)/.*$@\1@'
    done
    grep -E "$2/toolbox/([^/]+)/" $i | sed -r 's@^.*'$2'/toolbox/([^/]+)/.*$@\1@'
done | sort | uniq
