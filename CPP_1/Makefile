# Compiler and flags
CXX = clang++
CXXFLAGS = -std=c++14 -Werror
DEBUG_FLAGS = -g -O0
VALGRIND_FLAGS = -v --leak-check=full --show-leak-kinds=all --error-exitcode=99

# Source and object files
SOURCES = Graph.cpp Algorithms.cpp Demo.cpp Test.cpp TestCounter.cpp
HEADERS = Graph.hpp Algorithms.hpp
OBJECTS = $(SOURCES:.cpp=.o)

# Executables
DEMO_EXEC = demo
TEST_EXEC = test

# Default rule
.PHONY: all clean tidy valgrind run debug

all: $(DEMO_EXEC) $(TEST_EXEC)
	@echo "Build completed successfully."

# Rule to run demo
run: $(DEMO_EXEC)
	@echo "Running demo..."
	./$(DEMO_EXEC)

# Rule to build demo executable
$(DEMO_EXEC): Demo.o Graph.o Algorithms.o
	$(CXX) $(CXXFLAGS) $^ -o $@
	@echo "Demo executable built."

# Rule to build test executable
$(TEST_EXEC): TestCounter.o Test.o Graph.o Algorithms.o
	$(CXX) $(CXXFLAGS) $^ -o $@
	@echo "Test executable built."

# Rule to run clang-tidy
tidy:
	@echo "Running clang-tidy..."
	clang-tidy $(SOURCES) -checks=bugprone-*,clang-analyzer-*,cppcoreguidelines-*,performance-*,portability-*,readability-*,-cppcoreguidelines-pro-bounds-pointer-arithmetic,-cppcoreguidelines-owning-memory --warnings-as-errors=-* --
	@echo "Clang-tidy completed."

# Rule to run valgrind
valgrind: $(DEMO_EXEC) $(TEST_EXEC)
	@echo "Running Valgrind on demo..."
	valgrind --tool=memcheck $(VALGRIND_FLAGS) ./$(DEMO_EXEC)
	@echo "Running Valgrind on test..."
	valgrind --tool=memcheck $(VALGRIND_FLAGS) ./$(TEST_EXEC)
	@echo "Valgrind checks completed."

# Debug build rule
debug: CXXFLAGS += $(DEBUG_FLAGS)
debug: $(DEMO_EXEC) $(TEST_EXEC)
	@echo "Debug build completed."

# Pattern rule for object files
%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean rule to remove all build artifacts
clean:
	@echo "Cleaning up..."
	rm -f $(OBJECTS) $(DEMO_EXEC) $(TEST_EXEC)
	@echo "Cleanup completed."