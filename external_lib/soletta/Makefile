LIB_NAME=soletta
LIB_URL=https://github.com/solettaproject/soletta.git
LIB_BRANCH=master
LIB_DIR=$(CURDIR)/$(LIB_NAME)

.PHONY: all clean patch reset

all:
### fetch lib source
	test -d "$(LIB_DIR)" || git clone "$(LIB_URL)" "$(LIB_DIR)";
	cd "$(LIB_DIR)" && git checkout "$(LIB_BRANCH)"
### apply patches
	cd "$(LIB_DIR)" && git am --ignore-whitespace "$(CURDIR)"/*.patch
### configure and build
	cd "$(LIB_DIR)" && TARGETCC=$(CC) TARGETLD=$(LD) TARGETAS=$(AS) PKG_CONFIG=test make alldefconfig
	cd "$(LIB_DIR)" && TARGETCC=$(CC) TARGETLD=$(LD) TARGETAS=$(AS) PKG_CONFIG=test make install DESTDIR=$(LIB_DIR)/install
### create a link of the lib on the place expected
	ln $(LIB_DIR)/install/usr/lib/libsoletta.a $(CURDIR)/soletta.a

clean::
distclean::
	rm -f $(CURDIR)/soletta.a
	rm -rf "$(LIB_DIR)"