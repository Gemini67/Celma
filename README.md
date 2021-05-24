# Celma

## C++ Extension Library Modules for Application

Version: 1.45.0

[![Quality Gate Status](https://sonarcloud.io/api/project_badges/measure?project=Gemini67_Celma&metric=alert_status)](https://sonarcloud.io/dashboard?id=Gemini67_Celma)

This library offers a collection of modules that are often needed in developping applications on UNIX.
The main modules are:

- [Argument Handler](doc/argument_handler.md)

  Command line argument parsing, store the values directly in the destination variables.

- Logging

  Easy to use logging library.

- [Type name](doc/type_name.md)

  Gives the type name as string.

- Indirect access

  Create a data structure and an object that allows to access members of the structure by name or id.

- Formatting

  Various functions and modules for formatting purposes, e.g. text-block formatting, fast integer to string conversion etc.

Requirements:
- Boost library
- C++ 17 compliant compiler


## Building

### Requirements

To build the software, the following components are required: 
- Boost Development: Libraries and headerfiles.
- CMake
- g++ compiler

To build the documentation, doxygen is required.<br>
To run the coverage analysis, lcov is needed additionally.

### Compile

There is a makefile in the top-level directory that supports all build targets:
- make debug<br>Builds the debug version with the lowest C++ version that is currently supported, e.g. C++ 17.
- make release<br>Builds the release version (optimised) with the lowest C++ version that is currently supported, e.g. C++ 17.
- make debug-<C++ version>/make release-<C++ version><br>Builds the debug or release version with the specified C++ version.
- make doxgen<br>Creates the HTML documentation from the source code using doxygen.

The steps for building are:
- Check if the build/<target> directory exists.
- If not:
- Create the directory.
 
