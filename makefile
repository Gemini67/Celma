
PATH := $(shell pwd)/scripts:$(PATH)
CPUS := $(shell lscpu -p | fgrep -v '\#' | wc -l)


all:	debug release release-dbg debug-20 release-20

debug:
	+if [ ! -d build/debug ]; then \
	   mkdir -p build/debug; \
	   cd build/debug; \
	   cmake -DCMAKE_INSTALL_PREFIX=${PWD} \
	         -DBOOST_VERSION=${BOOST_VERSION} \
	         -DCMAKE_BUILD_TYPE=Debug \
	         ../..; \
	   cd -; \
	fi; \
	cd build/debug; \
	make -j${CPUS}; \
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
	make -j${CPUS}; \
	make install

debug-20:
	+if [ ! -d build/debug-20 ]; then \
	   mkdir -p build/debug-20; \
	   cd build/debug-20; \
	   cmake -DCMAKE_INSTALL_PREFIX=${PWD} \
	         -DBOOST_VERSION=${BOOST_VERSION} \
	         -DCMAKE_BUILD_TYPE=Debug \
	         -DCPP_VERSION=20 \
	         ../..; \
	   cd -; \
	fi; \
	cd build/debug-20; \
	make -j${CPUS}; \
	make install

release-20:
	@+if [ ! -d build/release-20 ]; then \
	   mkdir -p build/release-20; \
	   cd build/release-20; \
	   cmake -DCMAKE_INSTALL_PREFIX=${PWD} \
	         -DBOOST_VERSION=${BOOST_VERSION} \
	         -DCMAKE_BUILD_TYPE=Release \
	         -DCPP_VERSION=20 \
	         ../..; \
	   cd -; \
	fi; \
	cd build/release-20; \
	make -j${CPUS}; \
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
	make -j${CPUS}; \
	make install

analyze:
	@if [ ! -d build/analyze ]; then \
	   mkdir -p build/analyze; \
	   cd build/analyze; \
	   export CC=clang; \
	   export CXX=clang++; \
	   cmake -DCMAKE_INSTALL_PREFIX=${PWD} \
	         -DBOOST_VERSION=${BOOST_VERSION} \
	         -DCMAKE_BUILD_TYPE=Debug \
	         -D__LLVM_ANALYZE__=1 \
	         ../..; \
	   cd -; \
	fi; \
	cd build/analyze; \
	make -j${CPUS};

cppcheck:
	cppcheck --enable=all --quiet --inline-suppr --force --std=c++11 -I src src

test:	test-release test-debug test-release-20 test-debug-20

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

test-debug-20:
	@if [ -d build/debug-20 ]; then \
	   cd build/debug-20; \
	   make test; \
	else \
	   echo "*** Error: build/debug-20 does not exist!" >&2; \
	fi

test-release-20:
	@if [ -d build/release-20 ]; then \
	   cd build/release-20; \
	   make test; \
	else \
	   echo "*** Error: build/release-20 does not exist!" >&2; \
	fi


doxygen:
	doxygen celma.doxy


coverage:
	@if [ ! -d build/coverage ]; then \
	   mkdir -p build/coverage; \
	   cd build/coverage; \
	   cmake -DCMAKE_INSTALL_PREFIX=${PWD} \
	         -DBOOST_VERSION=${BOOST_VERSION} \
	         -DCMAKE_BUILD_TYPE=Coverage \
	         ../..; \
	   cd -; \
	fi; \
	cd build/coverage; \
	/usr/bin/time --format="-- Build Duration: %E" make -j${CPUS} install; \
	/usr/bin/time --format="-- Build Duration: %E" make Celma_coverage

sonar:
	@if [ ! -d build/sonar ]; then \
	   mkdir -p build/sonar; \
	   cd build/sonar; \
	   cmake -DCMAKE_INSTALL_PREFIX=${PWD} \
	         -DBOOST_VERSION=${BOOST_VERSION} \
                 -DCMAKE_BUILD_TYPE=Debug \
	         ../..; \
	   cd -; \
	fi; \
	cd build/sonar; \
	build-wrapper-linux-x86-64 --out-dir bw-output make -j4; \
	cd -; \
	sonar-scanner -Dsonar.login=$(SONAR_LOGIN)

edit-release:
	nedit doc/main_page.txt CMakeLists.txt README.md celma.doxy sonar-project.properties &

