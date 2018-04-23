
CXX=icpc
CXXFLAGS=-O3 -qopt-zmm-usage=high -qopt-report=5 -xCORE-AVX512 -std=c++11


cbench: cache_bench.cpp
	$(CXX) -o $@ $^ $(CXXFLAGS)

clean:
	rm cbench
