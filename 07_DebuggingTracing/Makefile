GENERATES = my_unlinkat.so
TRASH = abc.txt abc-FIX.txt

my_unlinkat.so: 	my_unlinkat.c
	cc -Wall -shared -fPIC $< -ldl -o $@

test: 	my_unlinkat.so
	touch abc.txt
	touch abc-FIX.txt
	LD_PRELOAD=`pwd`/$< rm abc.txt
	LD_PRELOAD=`pwd`/$< rm abc-FIX.txt || true
	! test -f abc.txt	
	test -f abc-FIX.txt
	touch abc.txt
	touch abc-FIX.txt
	rm abc.txt
	rm abc-FIX.txt
	! test -f abc.txt	
	! test -f abc-FIX.txt

clean:
	rm -rf $(TRASH)

distclean:      clean
	rm -rf $(GENERATES)

