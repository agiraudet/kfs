# Variables
WD := $(shell pwd)
PREFIX := $(WD)/opt/cross
TARGET := i386-elf
SYSROOT := $(WD)/sysroot
MAKE := make
HOST := $(shell ./default-host.sh)
PROJECTS := libc kernel
SYSTEM_HEADER_PROJECTS := libc kernel

# Compiler and binutils versions
BINUTILS_VERSION := 2.42
GCC_VERSION := 14.1.0

# Paths
BINUTILS_TARBALL := binutils-$(BINUTILS_VERSION).tar.gz
GCC_TARBALL := gcc-$(GCC_VERSION).tar.gz
BINUTILS_URL := https://ftp.gnu.org/gnu/binutils/$(BINUTILS_TARBALL)
GCC_URL := https://ftp.gnu.org/gnu/gcc/gcc-$(GCC_VERSION)/$(GCC_TARBALL)

# Flags
CFLAGS := -O2 -g
CPPFLAGS := 

# Host tools
AR := $(HOST)-ar
AS := $(HOST)-as
CC := $(HOST)-gcc

# Work around that the -elf gcc targets doesn't have a system include directory
# because it was configured with --without-headers rather than --with-sysroot.
CC_SYSROOT_FLAGS := --sysroot=$(SYSROOT)
ifneq (,$(findstring -elf,$(HOST)))
    CC_SYSROOT_FLAGS += -isystem=$(SYSROOT)/usr/include
endif

# Exported variables
export PREFIX TARGET SYSROOT MAKE HOST AR AS CC CFLAGS CPPFLAGS CC_SYSROOT_FLAGS

# Targets

.PHONY: all build-env cross-compiler headers build clean iso qemu

all: build-env cross-compiler headers build iso

build-env:
	@mkdir -p opt/cross/build

cross-compiler: $(PREFIX)/bin/$(TARGET)-gcc

$(PREFIX)/bin/$(TARGET)-gcc: $(PREFIX)/bin/$(TARGET)-as

$(PREFIX)/bin/$(TARGET)-as: $(PREFIX)/bin/$(TARGET)-ld

$(PREFIX)/bin/$(TARGET)-ld: binutils gcc
	@if [ ! -f $(PREFIX)/bin/$(TARGET)-ld ]; then \
		$(MAKE) binutils-build; \
	fi
	@if [ ! -f $(PREFIX)/bin/$(TARGET)-gcc ]; then \
		$(MAKE) gcc-build; \
	fi

binutils: opt/cross/build/$(BINUTILS_TARBALL)

gcc: opt/cross/build/$(GCC_TARBALL)

opt/cross/build/$(BINUTILS_TARBALL):
	cd opt/cross/build && wget $(BINUTILS_URL)

opt/cross/build/$(GCC_TARBALL):
	cd opt/cross/build && wget $(GCC_URL)

binutils-build: opt/cross/build/$(BINUTILS_TARBALL)
	cd opt/cross/build && tar xf $(BINUTILS_TARBALL)
	mkdir -p opt/cross/build/build-binutils
	cd opt/cross/build/build-binutils && ../binutils-$(BINUTILS_VERSION)/configure --target=$(TARGET) --prefix="$(PREFIX)" --with-sysroot --disable-nls --disable-werror CC=gcc
	cd opt/cross/build/build-binutils && $(MAKE) -j8
	cd opt/cross/build/build-binutils && $(MAKE) install
	@echo "[>>>] BINUTILS DONE"

gcc-build: opt/cross/build/$(GCC_TARBALL)
	cd opt/cross/build && tar xf $(GCC_TARBALL)
	mkdir -p opt/cross/build/build-gcc
	cd opt/cross/build/build-gcc && ../gcc-$(GCC_VERSION)/configure --target=$(TARGET) --prefix="$(PREFIX)" --disable-nls --enable-languages=c,c++ --without-headers CC=gcc
	cd opt/cross/build/build-gcc && $(MAKE) -j8 all-gcc
	cd opt/cross/build/build-gcc && $(MAKE) -j8 all-target-libgcc
	cd opt/cross/build/build-gcc && $(MAKE) install-gcc
	cd opt/cross/build/build-gcc && $(MAKE) install-target-libgcc
	@echo "[>>>] GCC DONE"

headers: cross-compiler
	@mkdir -p $(SYSROOT)
	@for PROJECT in $(SYSTEM_HEADER_PROJECTS); do \
		(cd $$PROJECT && DESTDIR="$(SYSROOT)" $(MAKE) install-headers); \
	done

build: headers
	@for PROJECT in $(PROJECTS); do \
		(cd $$PROJECT && DESTDIR="$(SYSROOT)" $(MAKE) install); \
	done

clean:
	@for PROJECT in $(PROJECTS); do \
		(cd $$PROJECT && $(MAKE) clean); \
	done
	rm -rf sysroot isodir ofs.iso

iso: build
	mkdir -p isodir/boot
	cp $(SYSROOT)/boot/ofs.kernel isodir/boot/ofs.kernel
	echo 'menuentry "ofs" {' > isodir/boot/grub/grub.cfg
	echo '	multiboot /boot/ofs.kernel' >> isodir/boot/grub/grub.cfg
	echo '}' >> isodir/boot/grub/grub.cfg
	grub2-mkrescue -o ofs.iso isodir

qemu: iso
	qemu-system-$(shell ./target-triplet-to-arch.sh $(HOST)) -cdrom ofs.iso

