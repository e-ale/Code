OBJS = eale-gpio-app.o
LIBS = -lgpiod

all: eale-gpio-app

eale-gpio-app: $(OBJS)
	$(CC) -o $@ $< $(LIBS)

install:
	install -D -m 0755 eale-gpio-app $(DESTDIR)/usr/bin/eale-gpio-app
