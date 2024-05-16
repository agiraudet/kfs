WD              := $(shell pwd)
PREFIX          := $(WD)
BUILD_DIR       := build
TARGET          := i386-elf

BINUTILS_V      := 2.42
BINUTILS_DIR    := binutils-$(BINUTILS_V)
BINUTILS_TARBALL := $(BINUTILS_DIR).tar.gz
BINUTILS_URL    := https://ftp.gnu.org/gnu/binutils/$(BINUTILS_TARBALL)

GCC_V           := 14.1.0
GCC_DIR         := gcc-$(GCC_V)
GCC_TARBALL     := $(GCC_DIR).tar.gz
GCC_URL         := https://ftp.gnu.org/gnu/gcc/gcc-$(GCC_V)/$(GCC_TARBALL)


$(BUILD_DIR)/$(BINUTILS_TARBALL):
	wget -P $(BUILD_DIR) $(BINUTILS_URL)
	
$(BUILD_DIR)/$(GCC_TARBALL):
	wget -P $(BUILD_DIR) $(GCC_URL)

binutils: $(BUILD_DIR)/$(BINUTILS_TARBALL)
	mkdir -p $(BUILD_DIR)/$(BINUTILS_DIR)
	tar xf $(BUILD_DIR)/$(BINUTILS_TARBALL) -C $(BUILD_DIR)/$(BINUTILS_DIR) --strip-components=1
	cd $(BUILD_DIR)/$(BINUTILS_DIR) && ./configure --target=$(TARGET) --prefix=$(PREFIX) --with-sysroot --disable-nls --disable-werror
	make -C $(BUILD_DIR)/$(BINUTILS_DIR) -j8
	make -C $(BUILD_DIR)/$(BINUTILS_DIR) install

gcc: $(BUILD_DIR)/$(GCC_TARBALL)
	mkdir -p $(BUILD_DIR)/$(GCC_DIR)
	tar xf $(BUILD_DIR)/$(GCC_TARBALL) -C $(BUILD_DIR)/$(GCC_DIR) --strip-components=1
	cd $(BUILD_DIR)/$(GCC_DIR) && ./configure --target=$(TARGET) --prefix=$(PREFIX) --disable-nls --enable-languages=c --without-headers
	make -C $(BUILD_DIR)/$(GCC_DIR) -j8 all-gcc
	make -C $(BUILD_DIR)/$(GCC_DIR) -j8 all-target-libgcc
	make -C $(BUILD_DIR)/$(GCC_DIR) install-gcc
	make -C $(BUILD_DIR)/$(GCC_DIR) install-target-libgcc

all: binutils gcc

.PHONY: all binutils gcc envsetup clean
