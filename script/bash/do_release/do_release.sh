#!/bin/bash

#NT2_SOURCE_ROOT=../../..
BUILDNAME=Linux-x86_64
BLACKLISTED="arch.cuda;arch.opencl;arch.arm;arch.x86;arch.mic;matlab;extern"

VERSION=$(git -C "$NT2_SOURCE_ROOT" describe --tags)

rm -rf install nt2 boost-simd source *.tgz
mkdir -p install/nt2
mkdir -p install/boost-simd

mkdir nt2 && cd nt2
cmake $NT2_SOURCE_ROOT -G Ninja -DCMAKE_INSTALL_PREFIX=../install/nt2 -DNT2_INSTALL_SHARE_DIR:STRING=. -DNT2_WITH_TESTS=0 -DNT2_IGNORE_DEPENDENCIES=1 -DNT2_MODULES_BLACKLIST="$BLACKLISTED"
ninja
ninja -j1 doc && ninja -j1 doc
ninja install
cd ..
cd install
echo $VERSION > nt2/tagname
tar -zcf ../nt2-$VERSION-$BUILDNAME.tgz nt2
cd ..

mkdir boost-simd && cd boost-simd
cmake $NT2_SOURCE_ROOT -G Ninja -DCMAKE_INSTALL_PREFIX=../install/boost-simd -DNT2_INSTALL_SHARE_DIR:STRING=. -DNT2_WITH_TESTS=0 -DNT2_IGNORE_DEPENDENCIES=1 -DNT2_MODULES="boost.simd" -DNT2_DOC_MAIN="boost.simd_doc" -DNT2_MODULES_BLACKLIST="$BLACKLISTED"
ninja
ninja -j1 doc && ninja -j1 doc
ninja install
cd ..
cd install
tar -zcf ../boost-simd-$VERSION.tgz boost-simd
cd ..

mkdir -p source
cp -r $NT2_SOURCE_ROOT source/nt2

OIFS=$IFS
IFS=';'
for i in $BLACKLISTED
do
  rm -rf "source/nt2/modules/$(echo "$i" | tr '.' '/')"
done
IFS=$OIFS

rm -rf source/nt2/.git
cd source
echo $VERSION > nt2/tagname
tar -zcf ../nt2-$VERSION-source.tgz nt2
cd ..
