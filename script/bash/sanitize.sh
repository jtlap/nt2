#!/bin/bash

sed -i 's@'$'\t''@  @g' $1
sed -i -r 's@ +$@@g' $1
sed -i -e '$a\' $1
