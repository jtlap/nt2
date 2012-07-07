#!/bin/bash

if [ $# -lt 1 ]
then
    echo "Usage: `basename $0` [-j<N>] <file>..."
    echo "NT2_SOURCE_ROOT, NT2_BINARY_ROOT and BOOST_ROOT must be defined"
    exit 65
fi

if echo $1 | grep -E "^-j[0-9]" > /dev/null
then
  args=${@:2}
  jobs=$(echo $1 | sed 's/-j//')
else
  args=$@
  jobs=1
fi

include_dirs=$(find $NT2_SOURCE_ROOT -regex $NT2_SOURCE_ROOT'/modules/.*/include' | grep -E -v $NT2_SOURCE_ROOT'/modules/.*/include/.*/include')
include_dirs="$BOOST_ROOT $include_dirs $NT2_BINARY_ROOT/include"

include_string=''
for i in $include_dirs
do
  include_string="$include_string -I$i"
done

function wait_jobs()
{
  while [ $(ps ax | grep $1 | grep -v grep | wc -l) -ge $2 ]
  do
    sleep 1
  done
}

for i in $args
do
  command="g++ -x c++ -Wfatal-errors -fsyntax-only $include_string $i"
  if [ $VERBOSE ]
  then
    echo $command
  fi
  wait_jobs cc1plus $jobs
  $command |& grep -v -F Wfatal-errors &
done
wait_jobs g++ 1
