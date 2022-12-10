static:
	mkdir -p build
	mkdir -p build/lib
	mkdir -p build/lib/release
	mkdir -p build/objects
	g++ lib.cpp -c -I.
	ar rs libhashset.a lib.o
	mv *.o build/objects
	mv *.a build/lib/release

shared:
	mkdir -p build
	mkdir -p build/lib
	mkdir -p build/lib/release
	mkdir -p build/objects
	g++ -fPIC src/lib.cpp -c -I include -I lib
	g++ -shared -o libhashset.so lib.o
	mv *.o build/objects
	mv *.so build/lib/release

debug:
	mkdir -p build
	mkdir -p build/lib
	mkdir -p build/lib/release
	mkdir -p build/objects
	g++ -g -fPIC src/lib.cpp -c -I include -I lib
	g++ -shared -o libhashset.so lib.o
	mv *.o build/objects
	mv *.so build/lib/release
	
install: shared
	mv build/lib/release/libhashset.so /usr/lib/libhashset.so

clean:
	rm -rf build

test.o: tests/test.cpp
	g++ tests/test.cpp -c -I include -I lib

libhashset.a:
	mkdir -p build
	mkdir -p build/lib
	mkdir -p build/lib/release
	mkdir -p build/objects
	g++ src/lib.cpp -c -I include -I lib
	ar rs libhashset.a lib.o

test: test.o libhashset.a
	g++ test.o -o test -lhashset -llinkedlist -L. -L lib/build/lib/release
	mkdir -p build/bin/release
	mkdir -p build/lib/release
	mkdir -p build/objects
	mv *.o build/objects
	mv *.a build/lib/release
	mv test build/bin/release
