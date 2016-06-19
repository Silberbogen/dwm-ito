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
	@echo Installiere ausführbare Datei nach ${DESTDIR}${PREFIX}/bin
	@mkdir -p ${DESTDIR}${PREFIX}/bin
	@cp -f dwm-ito ${DESTDIR}${PREFIX}/bin
	@cp -f surf-proxy.sh ${DESTDIR}${PREFIX}/bin
	@chmod 755 ${DESTDIR}${PREFIX}/bin/dwm-ito
	@echo Installiere Handbuch-Seiten nach ${DESTDIR}${MANPREFIX}/man1
	@mkdir -p ${DESTDIR}${MANPREFIX}/man1
	@sed "s/VERSION/${VERSION}/g" < dwm-ito.1 > ${DESTDIR}${MANPREFIX}/man1/dwm-ito.1
	@chmod 644 ${DESTDIR}${MANPREFIX}/man1/dwm-ito.1
	@echo Installiere Desktop-Datei nach /usr/share/xsessions
	@cp -f dwm-ito.desktop /usr/share/xsessions
	@chmod 644 /usr/share/xsessions/dwm-ito.desktop
	@echo Installiere Beispielkonfiguration nach /etc/skel/
	@mkdir -p /etc/skel/.dwm-ito
	@cp -f .dwm-ito/* /etc/skel/.dwm-ito
	@chmod 644 /etc/skel/.dwm-ito/*

uninstall:
	@echo Entferne ausführbare Datei aus ${DESTDIR}${PREFIX}/bin
	@rm -f ${DESTDIR}${PREFIX}/bin/dwm-ito
	@rm -f ${DESTDIR}${PREFIX}/bin/surf-proxy.sh
	@echo Entferne Handbuch-Seiten aus ${DESTDIR}${MANPREFIX}/man1
	@rm -f ${DESTDIR}${MANPREFIX}/man1/dwm-ito.1
	@echo Entferne Desktop-Datei aus /usr/share/xsessions
	@rm -f /usr/share/xsessions/dwm-ito.desktop
	@echo Entferne die Beispielkonfigurationsdateien aus /etc/skel
	@rm -f /etc/skel/.dwm-ito/autostart.sh
	@rm -f /etc/skel/.dwm-ito/conkydwm-ito
	@rmdir /etc/skel/.dwm-ito

.PHONY: all options clean dist install uninstall
