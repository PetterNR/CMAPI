
all: void
	python3 setup.py build
	sudo cp -f build/lib.linux-x86_64-3.10/*.so .
	python3 test.py

void:

install:
	python3 setup.py install

clean:
	python3 -m pip uninstall cmapi
	rm *.txt
	rm *.so