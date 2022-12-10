server: main.o libpack109.a liblinkedlist.a libhashset.a
	g++ build/objects/main.o -o server -lpack109 -Lbuild/lib/release -lhashset -Lhashlib/build/lib/release -llinkedlist -L linkedlib/build/lib/release -std=c++11
	mkdir -p build/bin
	mv server build/bin

test: main.o
	g++ build/objects/main.o -o server -lpack109 -Lbuild/lib/release -lhashset -Lhashlib/build/lib/release -llinkedlist -L linkedlib/build/lib/release -std=c++11
	mkdir -p build/bin	
	mv server build/bin


libpack109.a:
	g++ src/packlib.cpp -c -Iinclude -I hashlib -Ilinkedlib -std=c++11
	ar rs libpack109.a packlib.o 
	mkdir -p build/lib/release
	mkdir -p build/objects
	mv *.o build/objects
	mv libpack109.a build/lib/release

liblinkedlist.a:
	$(MAKE) -C linkedlib/ static

libhashset.a:
	$(MAKE) -C hashlib/ static


main.o:
	g++ src/bin/main.cpp -c  -Iinclude -Ihashlib -std=c++11
	mkdir -p build/objects
	mv main.o build/objects
	

clean:
	rm -f *.a
	rm -f *.o
	rm -rf build/lib
	rm -rf build/objects
	rm -rf build/out