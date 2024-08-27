This project is a C++ library for handling and manipulating graphs using adjacency matrices. It includes a variety of algorithms for graph analysis and manipulation, making it a powerful tool for anyone needing to work with graphs programmatically.

 ## Features

 - **Graph Representation**: The `Graph` class represents graphs using adjacency matrices, allowing for efficient graph manipulation and storage.
 - **Algorithms**: The `Algorithms` class provides several useful algorithms for graph analysis, such as connectivity checks.
 - **Operator Overloading**: Overloaded operators for intuitive graph manipulation, including printing graphs and matrix multiplication.
 - **Customizable and Extensible**: Easily extend the functionality of graphs and algorithms by adding new methods or modifying existing ones.

 ## Prerequisites

 Before you begin, ensure you have met the following requirements:

 - **C++ Compiler**: A C++14-compatible compiler (`clang++` recommended).
 - **Make**: A build tool for compiling the project.
 - **Valgrind**: For memory leak detection (optional but recommended).
 - **clang-tidy**: For static code analysis (optional).

 ## Installation

 ### Step 1: Clone the Repository
 Clone the project repository to your local machine:
 git clone <repository_url>
 cd <project_directory_name>

 ### Step 2: Install Dependencies
 Ensure all required dependencies are installed on your system:
 - For **Ubuntu**:
   sudo apt-get update
   sudo apt-get install clang++ make valgrind clang-tidy
 - For **MacOS**:
   brew update
   brew install llvm make valgrind
  

 ### Step 3: Compile the Project
 Compile the project using the provided `Makefile`:
 make
 This command will build the project and generate two executables: `demo` and `test`.
 ## Usage

 ### Running the Demo
 To run the demo application and see the graph functionalities in action:
 ./demo

 ### Running the Tests
 To run the unit tests and verify the functionality of the project:
 make test
 ./test

 ## Project Structure
 The project directory includes the following files:
 .
 ├── src
 │   ├── Algorithms.cpp
 │   ├── Graph.cpp
 ├── include
 │   ├── Algorithms.hpp
 │   ├── Graph.hpp
 ├── test
 │   ├── Test.cpp
 │   ├── TestCounter.cpp
 │   ├── my_test.cpp
 ├── Makefile
 ├── doctest.h
 └── README.md
 ```

 - **`src/`**: Contains source code for the project.
 - **`include/`**: Contains header files for the project.
 - **`test/`**: Contains test files for unit testing and validation.
 - **`Makefile`**: A script for compiling and building the project.
 - **`doctest.h`**: The Doctest library header file for unit testing.
 - **`README.md`**: This README file.

 ## Contributing
 Contributions are always welcome! Here’s how you can contribute:
 1. Fork the repository.
 2. Create a new branch (`git checkout -b feature-new-feature`).
 3. Make your changes and commit them (`git commit -m 'Add a new feature'`).
 4. Push to the branch (`git push origin feature-new-feature`).
 5. Open a Pull Request.

 ## Troubleshooting

 - **Compilation Errors**: Ensure your compiler is set to use C++14 or later. Double-check your environment setup and make sure all dependencies are installed.
 - **Memory Leaks**: Use Valgrind to check for memory leaks by running `valgrind ./demo` or `valgrind ./test`.
 - **Static Analysis**: Use `clang-tidy` for static code analysis to catch potential bugs and improve code quality.

 ## License

 This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.
