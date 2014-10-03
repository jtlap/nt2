::set NT2_SOURCE_ROOT=..\..\..
set BUILDNAME=Windows-i686-vc100
set BLACKLISTED="arch.cuda;arch.opencl;arch.arm;arch.x86;arch.mic;matlab;extern"

del VERSION.txt
git -C "%NT2_SOURCE_ROOT%" describe --tags > VERSION.txt
set /p VERSION=<VERSION.txt

rmdir /S /Q install nt2_msvc
mkdir install\nt2

mkdir nt2_msvc && cd nt2_msvc
cmake "%NT2_SOURCE_ROOT%" -G Ninja -DCMAKE_INSTALL_PREFIX=../install/nt2 -DNT2_WITH_TESTS=0 -DNT2_IGNORE_DEPENDENCIES=1 -DNT2_MODULES_BLACKLIST="%BLACKLISTED%"
ninja
xcopy /S /I ..\nt2\doc\html doc\html
ninja package
copy nt2-%VERSION%.exe ..\nt2-%VERSION%-%BUILDNAME%.exe
ninja install
cd ..
cd install
echo %VERSION% > nt2/tagname
del ..\nt2-%VERSION%-%BUILDNAME%.zip
"C:\Program Files\7-Zip\7z.exe" a ..\nt2-%VERSION%-%BUILDNAME%.zip nt2
cd ..
