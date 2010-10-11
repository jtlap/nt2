#/bin/sh
more /proc/cpuinfo | grep altivec | uniq | wc -l
