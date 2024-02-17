# GLOBAL COMPILER
### The compiler you always wanted

Global as the name suggests is a versatile and globalized compiler designed to understand various language syntaxes. Whether you are working with C++, Java, Python, or other programming languages, Global Compiler aims to provide a unified and seamless compilation experience.

## Features
- **Multi-Language Support**: Global Compiler is not bound to a specific programming language. It is designed to handle multiple languages, making it a versatile tool for developers working on diverse projects.

- **Syntax Understanding**: The compiler is equipped with syntax parsers for different languages, allowing it to interpret and compile code from various sources.

- **Ease of Use**: With a simple and intuitive interface, Global Compiler ensures that users can easily compile their code without the hassle of switching between different compilers for different languages.

- **Extensibility**: Global Compiler is designed to be extensible, allowing developers to add support for additional languages or customize existing language modules.


## Getting Started
To get started with Global Compiler, follow these steps:

1. Clone the Repository:

```bash
git clone https://github.com/bisryy/global.git
cd global
```
Build the Compiler:
*For Linux*
```
make
```
*For Windows*
```
mingw32-make
```

Run the Compiler:

```bash
./global <source-file> [options]
```
*Tokenizer*
```bash
./lexer <source-file>
```
##  Usage
Once the compiler is built, you can use it to compile source files in different languages. For example:

```bash
./global tests/test.cpp
```
This command will compile the C++ source file test.cpp.

*Help*
```bash
$ ./global -h

Usage: ./global <filename> [-e] [-w] [-log] [-a] [-l] [-h]
Options:
  -l, --line:    Compile Line by line
  -e, --error:   Compile with errors
  -w, --warning: Show warnings
  -log:          Show logs
  -a, -all:      Show all
  -h, --help:    Show help
```

## Example
```
$ make

$ ./global test.c
$ ./global test.cpp
$ ./global test.py
$ ./global test.js
$ ./global test.rs
$ ./global test.php

...

```
## Language Features
- [x] print statement 
```
print("Hello World")
```
- [x] Variables
    - [x] Variable Declaration
    ```
    var num = 12
    ```
    - [x] Variable Assignment
    ```
    num = 21
    ```
- [x] Data Types
    - [x] Integer
    ```cpp
    int num = 21
    ```
    - [x] String
    ```python
    print("This is string.")
    ```
    - [x] Boolean
    ```js
    let isTrue = true
    ```
    - [ ] Float
    ```rust
    num = 2.34
    ```
- [x] Operators
    - [x] Arithmetic ( +, -, *, /, % )
    ```c
    int x = 4;
    int y = 6;
    int z = 8;

    x = y + z;
    y = x + z;
    z = x + y;

    int a = z + y - (x % y) + (x * z) + (y / 2) * (x - y * z);
    printf(a + x + y + z); // prints -7938

    ```
    - [x] Relational ( <, >, <=, >=, ==, != )
    ```php
    $x = 1;
    $y = 2;

    echo $x < $y; // prints 1
    echo $x > $y; // prints 0
    echo $x <= $y; // prints 1
    echo $x >= $y; // prints 0
    echo $x == $y; // prints 0
    echo $x != $y; // prints 1
    ```
    - [x] Logical ( &&, ||, ! )
    ```cpp
    int x = 1;
    int y = 2;

    cout << (x && y) << endl; // prints 1
    cout << (x || y) << endl; // prints 1
    cout << !x << endl; // prints 0
    ```
    - [x] Assignment  ( = )
    ```python
    x = 1
    y = 2 + x
    z = 3 * y

    print(z) // prints 9
    ```

- [x] Comment ( //, #)
    ```c
    // This is a comment
    ```
    ```python
    # This is also a comment
    ```
- [x] Conditional Statements
    - [x] if
    - [x] else
    ```js
    x = 1

    if x < 0 console.log("x is negative."); else console.log("x is positive") //    prints x is negative.

    if x % 2 console.log("x is odd"); else console.log("x is even") // prints x is odd

    ```
- [ ] Loops
    - [ ] for
    - [ ] while
    - [ ] do while
- [ ] Functions
- [ ] Arrays
- [ ] Classes
- [ ] Structs


## Languages Supported

<!-- checkbox -->
- [x] C++
- [x] C
- [x] Python
- [x] JavaScript
- [x] Rust
- [x] PHP
- [ ] Ruby
- [ ] Go
- [ ] Java
