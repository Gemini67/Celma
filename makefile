
all:	debug release release-dbg

debug:
	@+if [ ! -d build/debug ]; then \
	   mkdir -p build/debug; \
	   cd build/debug; \
	   cmake -DCMAKE_INSTALL_PREFIX=${PWD} \
	         -DBOOST_VERSION=${BOOST_VERSION} \
	         -DCMAKE_BUILD_TYPE=Debug \
	         ../..; \
	   cd -; \
	fi; \
	cd build/debug; \
	make -j7; \
	make install

release:
	@+if [ ! -d build/release ]; then \
	   mkdir -p build/release; \
	   cd build/release; \
	   cmake -DCMAKE_INSTALL_PREFIX=${PWD} \
	         -DBOOST_VERSION=${BOOST_VERSION} \
	         -DCMAKE_BUILD_TYPE=Release \
	         ../..; \
	   cd -; \
	fi; \
	cd build/release; \
	make -j7; \
	make install

release-dbg:
	@+if [ ! -d build/release-dbg ]; then \
	   mkdir -p build/release-dbg; \
	   cd build/release-dbg; \
	   cmake -DCMAKE_INSTALL_PREFIX=${PWD} \
	         -DBOOST_VERSION=${BOOST_VERSION} \
	         -DCMAKE_BUILD_TYPE=RelWithDebInfo \
	         ../..; \
	   cd -; \
	fi; \
	cd build/release-dbg; \
	make -j7; \
	make install

analyze:
	@if [ ! -d build/analyze ]; then \
	   mkdir -p build/analyze; \
	   cd build/analyze; \
	   export CC=/usr/bin/clang; \
	   export CXX=/usr/bin/clang++; \
	   cmake -DCMAKE_INSTALL_PREFIX=${PWD} \
	         -DBOOST_VERSION=${BOOST_VERSION} \
	         -DCMAKE_BUILD_TYPE=Debug \
	         -D__LLVM_ANALYZE__=1 \
	         ../..; \
	   cd -; \
	fi; \
	cd build/analyze; \
	make -j7;

test:	test-release test-debug

test-debug:
	@if [ -d build/debug ]; then \
	   cd build/debug; \
	   make test; \
	else \
	   echo "*** Error: build/debug does not exist!" >&2; \
	fi

test-release:
	@if [ -d build/release ]; then \
	   cd build/release; \
	   make test; \
	else \
	   echo "*** Error: build/release does not exist!" >&2; \
	fi

doxygen:
	doxygen celma.doxy

