#!/bin/sh

#setup env
WD=$PWD
mkdir -p opt/cross/build
PREFIX="$(realpath opt/cross)"
TARGET=i386-elf
cd opt/cross/build

#download and extract binutils
wget https://ftp.gnu.org/gnu/binutils/binutils-2.42.tar.gz
tar xf binutils-2.42.tar.gz

#build binutils
mkdir build-binutils
cd build-binutils
../binutils-2.42/configure --target=$TARGET --prefix="$PREFIX" --with-sysroot --disable-nls --disable-werror
make -j8
make install
cd ..
echo "[>>>] BINUTILS DONE"

#download and extract gcc
wget https://ftp.gnu.org/gnu/gcc/gcc-14.1.0/gcc-14.1.0.tar.gz
tar xf gcc-14.1.0.tar.gz

#build gcc
mkdir build-gcc
cd build-gcc
../gcc-14.1.0/configure --target=$TARGET --prefix="$PREFIX" --disable-nls --enable-languages=c,c++ --without-headers
make -j8 all-gcc
make -j8 all-target-libgcc
make install-gcc
make install-target-libgcc
echo "[>>>] GCC DONE"
cd $WD

#create envsetup.sh
echo "export PREFIX=\"$PREFIX\"" >envsetup.sh
echo "export TARGET=\"$TARGET\"" >>envsetup.sh
echo "export PATH=\"$PREFIX/bin:\$PATH\"" >>envsetup.sh
echo "export TEST=\"48\"" >>envsetup.sh
echo "Done"
echo
echo
echo "Please run:"
echo "   source envsetup.sh"
