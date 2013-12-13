#!/bin/bash

cd `dirname "$BASH_SOURCE"`

# define NT2_SOURCE_ROOT
old_path=`pwd`
cd ../../..
export NT2_SOURCE_ROOT=`pwd`
cd "$old_path"

# Find all modules in parent directory
directories=`find .. -name CMakeLists.txt | sed s/CMakeLists.txt$//g`

for i in $directories
do
    if echo "$directories" | grep $i > /dev/null
    then
      directories=`echo "$directories" | grep -v $i`
      directories=`echo -ne "$directories\n$i"`
    fi
done

# Transform paths to modules
modules=`echo "$directories" | sed -r 's@^../(.*)/$@boost/\1@g' | sed  's@/@.@g'`

# $1 path to install dir, $2+ list of modules
function build_modules
{
    echo "Building modules ${@:2}"
    modules=`echo ${@:2} | sed 's/ /;/g'`
    mkdir "/tmp/_nt2_build"
    old_path=`pwd`
    cd "$1"
    install_prefix=`pwd`
    cd "/tmp/_nt2_build"
    cmake "$NT2_SOURCE_ROOT" "-DCMAKE_INSTALL_PREFIX=$install_prefix" "-DNT2_MODULES=$modules"
    make -j8 && make -j8 postconfigure
    make install
    cd "$old_path"
    rm -rf "/tmp/_nt2_build"
}

function cleanup
{
    for i in `find . -name bin -type d`
    do
        rm -rf "$i"
    done
    for i in `find . -name '*.manifest'`
    do
        rm -rf "$i"
    done
    for i in `find . -name '*.xml' -not -name 'boost.xml'`
    do
        rm -f "$i"
    done
}

# get a clean directory
cleanup
rm -rf boost
for i in `find libs -name '*.cpp'`
do
    rm -rf "$i"
done

# configure and build the modules to generate all headers and use 'install' target
mkdir install_tmp
build_modules install_tmp $modules

# copy all boost simd includes
cp -r install_tmp/include/boost .

# copy mini_nt2 into Boost.SIMD (to reduce to bare minimum)
cwd=`pwd`
rm -rf libs/simd/mini_nt2
cd install_tmp/include
for j in `find nt2 -name '*.hpp'`
do
    mkdir -p "$cwd/libs/simd/mini_nt2"
    cp --parents "$j" "$cwd/libs/simd/mini_nt2"
done
cd "$cwd"

# copy sources and unit tests
for i in `echo "$directories"`
do
    top=`echo $i | sed -r 's@^../([^/]+)/.*$@\1@g'`

    # copy sources
    cd $i/src
    for j in `find . -name '*.cpp'`
    do
        mkdir -p "$cwd/libs/$top/src"
        cp --parents "$j" "$cwd/libs/$top/src"
    done;
    cd $cwd

    # copy tests (jamfiles to generate still)
    cd $i/unit
    for j in `find . -name '*.cpp'`
    do
        mkdir -p "$cwd/libs/$top/test"
        cp --parents "$j" "$cwd/libs/$top/test"
    done;
    cd $cwd

done

rm -rf install_tmp

# build documentation
cd doc
if   [ -e "$BOOST_ROOT/b2" ]
then
    "$BOOST_ROOT/b2"
elif [ -e "$BOOST_ROOT/bjam" ]
then
    "$BOOST_ROOT/bjam"
else
    bjam
fi
cd ..

cleanup

echo -ne "\n"
echo -ne "----------------------------\n"
echo -ne "  Boostification complete.  \n"
echo -ne "----------------------------\n"
