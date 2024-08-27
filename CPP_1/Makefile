CXX = clang++
CXXFLAGS = -std=c++14 -Werror
VALGRIND_FLAGS = -v --leak-check=full --show-leak-kinds=all --error-exitcode=99

SOURCES = Graph.cpp Algorithms.cpp Demo.cpp Test.cpp TestCounter.cpp
OBJECTS = $(subst .cpp,.o,$(SOURCES))

# La règle all construira tout : demo et test
.PHONY: all clean tidy valgrind run

all: demo test
	@echo "Build completed successfully."

run: demo
	@echo "Running demo..."
	./demo

demo: Demo.o Graph.o Algorithms.o
	$(CXX) $(CXXFLAGS) Demo.o Graph.o Algorithms.o -o demo
	@echo "Demo executable built."

test: TestCounter.o Test.o Graph.o Algorithms.o
	$(CXX) $(CXXFLAGS) TestCounter.o Test.o Graph.o Algorithms.o -o test
	@echo "Test executable built."

tidy:
	@echo "Running clang-tidy..."
	clang-tidy $(SOURCES) -checks=bugprone-*,clang-analyzer-*,cppcoreguidelines-*,performance-*,portability-*,readability-*,-cppcoreguidelines-pro-bounds-pointer-arithmetic,-cppcoreguidelines-owning-memory --warnings-as-errors=-* --
	@echo "Clang-tidy completed."

valgrind: demo test
	@echo "Running Valgrind on demo..."
	valgrind --tool=memcheck $(VALGRIND_FLAGS) ./demo
	@echo "Running Valgrind on test..."
	valgrind --tool=memcheck $(VALGRIND_FLAGS) ./test
	@echo "Valgrind checks completed."

%.o: %.cpp %.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	@echo "Cleaning up..."
	rm -f *.o demo test
	@echo "Cleanup completed."