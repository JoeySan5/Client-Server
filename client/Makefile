client: libpack109.a main.o
	g++ build/objects/main.o -o client -lpack109 -Lbuild/lib -std=c++11
	mkdir -p build/bin
	mv client build/bin

libpack109.a:
	g++ src/packlib.cpp -c -Iinclude -std=c++11
	ar rs libpack109.a packlib.o 
	mkdir -p build/lib
	mkdir -p build/objects
	mv *.o build/objects
	mv libpack109.a build/lib

main.o:
	g++ src/bin/main.cpp -c -lpack109 -Lbuild/lib -Iinclude -std=c++11
	mkdir -p build/objects
	mv main.o build/objects

clean:
	rm -f *.a
	rm -f *.o
	rm -rf build