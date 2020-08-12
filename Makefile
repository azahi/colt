include config.mk

SRCS = ${PROG}.c
OBJS = ${SRCS:.c=.o}

all: ${PROG}

${PROG}: ${OBJS}
	${CC} -o $@ ${OBJS} ${LDFLAGS}

.c.o:
	${CC} ${CFLAGS} -c $<

clean:
	rm -f ${OBJS} ${PROG}

install: all
	install -D -m 755 ${PROG} ${DESTDIR}${PREFIX}/bin/${PROG}

uninstall:
	rm -f ${DESTDIR}${PREFIX}/bin/${PROG}

.PHONY: all clean install uninstall
