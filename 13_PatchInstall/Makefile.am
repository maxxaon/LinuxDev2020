AM_CFLAGS = -D LOCALEDIR='"$(localedir)"'

bin_PROGRAMS=guess
pkgdata_DATA=ru/LC_MESSAGES/guess.mo
pkgdatadir = $(localedir)/ru/LC_MESSAGES

ru/LC_MESSAGES/guess.mo: ru.po
	mkdir -p `dirname $@`
	msgfmt $< -o $@

ru.po:	messages.pot
	msgmerge -U $@ $<

messages.pot:	guess.pot guess.c
	xgettext -k_ -c guess.c -o messages.new.pot
	cp guess.pot messages.pot
	msgmerge -U messages.pot messages.new.pot

gitclean:
	git clean -fd

clean:
	rm -rf ru messages.new.pot messages.pot
