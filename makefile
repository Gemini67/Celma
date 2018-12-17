
PATH := $(shell pwd)/scripts:$(PATH)
CPUS := $(shell lscpu -p | fgrep -v '\#' | wc -l)


all:	debug release release-dbg

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
	make -j${CPUS};

cppcheck:
	cppcheck --enable=all --quiet --inline-suppr --force --std=c++11 -I src src

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
	sonar-scanner \
	   -Dsonar.projectKey=Gemini67_Celma \
	   -Dsonar.organization=gemini67-github \
	   -Dsonar.sources=. \
	   -Dsonar.cfamily.build-wrapper-output=bw-output \
	   -Dsonar.host.url=https://sonarcloud.io \
	   -Dsonar.login=4ab969e5c744a5b2f2e7e31f290d2576d532e8a4

