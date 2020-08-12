PROG = colt

PREFIX = /usr/local
MANPREFIX = ${PREFIX}/share/man

LOCALINC = /usr/local/include
LOCALLIB = /usr/local/lib

X11INC = /usr/X11R6/include
X11LIB = /usr/X11R6/lib

INCS = -I${LOCALINC} -I${X11INC}
LIBS = -L${LOCALLIB} -L${X11LIB} -lX11 -lXrandr

CPPFLAGS =
CFLAGS = -Wall -Wextra ${INCS} ${CPPFLAGS}
LDFLAGS = ${LIBS}

CC = cc
