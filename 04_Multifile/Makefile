GENERATES = prog prog-a prog-so README liboutput_static.so
TRASH = *.o *~ o.* *.a *output.txt prog-test
CFLAGS=-fPIC

PARAM1 = 1
PARAM3 = 1 2 3

all:    README prog prog-a prog-so

prog:   const.o fun.o prog.o

liboutput_static.a:		const.o fun.o
	ar rcs $@ $^

prog-a:		prog.o liboutput_static.a
	cc -L. $< -loutput_static -o $@	

liboutput_static.so:		const.o fun.o
	cc -shared $^ -o $@

prog-so: 	prog.o liboutput_static.so
	cc -L. $< -loutput_static -o $@	

test: prog prog-a prog-so
	cp prog prog-test
	./prog-test 2> prog_output.txt 
	./prog-test $(PARAM1) >> prog_output.txt
	./prog-test $(PARAM3) >> prog_output.txt
	cp prog-a prog-test
	./prog-test 2> prog-a_output.txt 
	./prog-test $(PARAM1) >> prog-a_output.txt
	./prog-test $(PARAM3) >> prog-a_output.txt
	cp prog-so prog-test
	LD_LIBRARY_PATH=`pwd` ./prog-test 2> prog-so_output.txt 
	LD_LIBRARY_PATH=`pwd` ./prog-test $(PARAM1) >> prog-so_output.txt
	LD_LIBRARY_PATH=`pwd` ./prog-test $(PARAM3) >> prog-so_output.txt
	cmp prog_output.txt prog-a_output.txt
	cmp prog_output.txt prog-so_output.txt

README: prog
	./$< 2> $@

fun.o:  outlib.h

clean:
	rm -f $(TRASH)

distclean:      clean
	rm -rf $(GENERATES)
  