clink_wrap.cxx:
	swig -I/usr/include -I/usr/local/include -javascript -node -c++ clink.i

build/:
	node-gyp clean configure build

.phony:clean

clean:
	rm -rf build/ clink_wrap.cxx

.phony:all


all: clink_wrap.cxx build/
