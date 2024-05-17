# Define the cross compiler tools
HOST=$(shell ./default-host.sh)
CROSS_DIR=cross
XCC=$(shell realpath $(CROSS_DIR)/bin/$(HOST)-gcc)
AR=$(HOST)-ar
AS=$(HOST)-as
CC=$(XCC) --sysroot=$(PWD)/sysroot

# Directories
PREFIX=/usr
EXEC_PREFIX=$(PREFIX)
BOOTDIR=/boot
LIBDIR=$(EXEC_PREFIX)/lib
INCLUDEDIR=$(PREFIX)/include
SYSROOT=$(PWD)/sysroot
ISODIR=$(PWD)/isodir
ISO=ofs.iso

# Flags
CFLAGS=-O2 -g
CPPFLAGS=

# Projects
SYSTEM_HEADER_PROJECTS=libc kernel
PROJECTS=libc kernel

# Make command
MAKE=make

# Default target
.PHONY: all
all: build

$(XCC):
	make -C $(CROSS_DIR)

# Build target
.PHONY: build
build: headers $(XCC)
	@for PROJECT in $(PROJECTS); do \
		(cd $$PROJECT && CC="$(CC)" DESTDIR="$(SYSROOT)" SYSROOT="$(SYSROOT)" $(MAKE) install); \
	done

# Clean target
.PHONY: clean
clean:
	@for PROJECT in $(PROJECTS); do \
		(cd $$PROJECT && $(MAKE) clean); \
	done
	rm -rf $(SYSROOT)
	rm -rf $(ISODIR)
	rm -rf $(ISO)

# Install headers
.PHONY: headers
headers:
	mkdir -p $(SYSROOT)$(INCLUDEDIR)
	@for PROJECT in $(SYSTEM_HEADER_PROJECTS); do \
		(cd $$PROJECT && CC="$(CC)" DESTDIR="$(SYSROOT)" SYSROOT="$(SYSROOT)" $(MAKE) install-headers); \
	done

$(ISO): build
	mkdir -p $(ISODIR)/boot/grub
	cp $(SYSROOT)/boot/ofs.kernel $(ISODIR)/boot/ofs.kernel
	echo 'menuentry "ofs" {' > $(ISODIR)/boot/grub/grub.cfg
	echo '  multiboot /boot/ofs.kernel' >> $(ISODIR)/boot/grub/grub.cfg
	echo '}' >> $(ISODIR)/boot/grub/grub.cfg
	grub2-mkrescue -o ofs.iso $(ISODIR)

# Run in QEMU
.PHONY: qemu
qemu: $(ISO)
	qemu-system-$(shell ./target-triplet-to-arch.sh $(HOST)) -cdrom ofs.iso

# Build cross-compiler
.PHONY: cross
cross:
	$(MAKE) -C cross all

