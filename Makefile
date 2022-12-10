server: libpack109.a main.o liblinkedlist.a 
	g++ build/objects/main.o -o client -lpack109 -Lbuild/lib/release -std=c++11
	mkdir -p build/bin
	mv client build/bin

test: libpack109.a main.o
	g++ build/objects/main.o -o client -lpack109 -Lbuild/lib/release -std=c++11
	mkdir -p build/bin
	mv client build/bin


libpack109.a:
	g++ src/packlib.cpp -c -Iinclude -I hashlib -std=c++11
	ar rs libpack109.a packlib.o 
	mkdir -p build/lib/release
	mkdir -p build/objects
	mv *.o build/objects
	mv libpack109.a build/lib/release

liblinkedlist.a:
	$(MAKE) -C linkedlib/ static


main.o:
	g++ src/bin/main.cpp -c -l pack109 -L build/lib/release -Iinclude -Ihashlib -std=c++11
	mkdir -p build/objects
	mv main.o build/objects
	

clean:
	rm -f *.a
	rm -f *.o
	rm -rf build/lib
	rm -rf build/objects
	rm -rf build/out