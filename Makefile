# dwm-ito - dynamic window manager
# See LICENSE file for copyright and license details.

include config.mk

SRC = dwm-ito.c
OBJ = ${SRC:.c=.o}

all: options dwm-ito

options:
	@echo dwm-ito build options:
	@echo "CFLAGS   = ${CFLAGS}"
	@echo "LDFLAGS  = ${LDFLAGS}"
	@echo "CC       = ${CC}"

.c.o:
	@echo CC $<
	@${CC} -c ${CFLAGS} $<

${OBJ}: config.h config.mk

config.h:
	@echo creating $@ from config.def.h
	@cp config.def.h $@

dwm-ito: ${OBJ}
	@echo CC -o $@
	@${CC} -o $@ ${OBJ} ${LDFLAGS}

clean:
	@echo cleaning
	@rm -f dwm-ito ${OBJ} dwm-ito-${VERSION}.tar.gz

dist: clean
	@echo creating dist tarball
	@mkdir -p dwm-ito-${VERSION}
	@cp -R LICENSE Makefile README config.def.h config.mk \
		dwm-ito.1 ${SRC} dwm-ito-${VERSION}
	@tar -cf dwm-ito-${VERSION}.tar dwm-ito-${VERSION}
	@gzip dwm-ito-${VERSION}.tar
	@rm -rf dwm-ito-${VERSION}

install: all
	@echo installing executable file to ${DESTDIR}${PREFIX}/bin
	@mkdir -p ${DESTDIR}${PREFIX}/bin
	@cp -f dwm-ito ${DESTDIR}${PREFIX}/bin
	@chmod 755 ${DESTDIR}${PREFIX}/bin/dwm-ito
	@echo installing manual page to ${DESTDIR}${MANPREFIX}/man1
	@mkdir -p ${DESTDIR}${MANPREFIX}/man1
	@sed "s/VERSION/${VERSION}/g" < dwm-ito.1 > ${DESTDIR}${MANPREFIX}/man1/dwm-ito.1
	@chmod 644 ${DESTDIR}${MANPREFIX}/man1/dwm-ito.1

uninstall:
	@echo removing executable file from ${DESTDIR}${PREFIX}/bin
	@rm -f ${DESTDIR}${PREFIX}/bin/dwm-ito
	@echo removing manual page from ${DESTDIR}${MANPREFIX}/man1
	@rm -f ${DESTDIR}${MANPREFIX}/man1/dwm-ito.1

.PHONY: all options clean dist install uninstall
