#!/bin/sh
set -e
. ./build.sh

mkdir -p isodir
mkdir -p isodir/boot
mkdir -p isodir/boot/grub

cp sysroot/boot/ofs.kernel isodir/boot/ofs.kernel
cat >isodir/boot/grub/grub.cfg <<EOF
menuentry "ofs" {
	multiboot /boot/ofs.kernel
}
EOF
grub2-mkrescue -o ofs.iso isodir
