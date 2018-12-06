# Argument Handler

## Concepts

The following concepts lead to the design of the argument handler library as it is today:

- Once the command line has been evaluated, everything argument-handling related is done.
- The key of an argument must be specified only once (as opposed to e.g. `getopt()`).
- Reasonable default behaviour depending on the type of the destination variable.

## Features

Here is a list of the features provided by the sub-library for argument handling in Celma:

- Argument handling is (mostly always) done in 3 steps: Define the variables, define the arguments, evaluate the program arguments. Then you're done and the values from the commandline arguments are stored in their destination variables, with the correct type.
- Therefore, argument keys (e.g. `-h`, `--help`) need to be specified only once.
- Supports flags (boolean values), PODs, strings, vectors of values, bitsets, tuples and custom types as destination variables/
  types.<br>
  This means also that some features are turned off or on, depending on the type of the destination variable.
- Values from the command line may be formatted (e.g. to uppercase) or converted automatically (string to destination type) or by
  using custom conversion functions, e.g. to convert the string into an enum value.
- Prints a well-formatted usage, when requested.
- Usage can contain pre- and post-usage text.
- Prints default values in usage, when applicable.<br>
  Can be specifically turned on or off.
- Supports short (e.g. `-h`) and/or long (e.g. `--help`) argument keys.
- The syntax `--` to turn off argument handling for expressions starting with a dash is also supported.
- Of course, positional arguments are supported too.
- With long arguments, abbreviations may be used.
- Values for long arguments may either be specified with an equal sign (`--filename=test.txt`) or separated with a space (`--filename test.txt`).
- Values for multi-value arguments/destination variables may be specified as a list or, when enabled, as multiple, space-separated
  words (e.g. a list of files produced by a globbing pattern).
- Ensures that no argument key conflict exists, i.e. the same argument cannot be defined multiple times.
- An argument may be mandatory or optional.
- An argument may not accept a value at all, may accept a value or not, or need a value.
- Number of values that an argument accepts or expects can be defined.
- For the values of parameters, you can specify a
  - minimum value
  - maximum value
  - range
  - list of acceptable values
- When storing values from the command line in a vector, you can specify that
  - the vector should be cleared before the first value is assigned
  - the values should sorted
  - duplicate values are not allowed
- If the value of a parameter specifies a file system entry, you can add checks if
  - the file exists
  - the given path entry is a directory
  - an absolute path was given
  - the parent directory of the given path exists
- Relations between arguments may be defined.
- Can read arguments from a file, or can store the current arguments in a file for later re-use.
- After evaluating the arguments from the command line, a summary can be printed (list of arguments used and values set).
- Arguments can be grouped and will be shown as a group in the usage.
- Hidden arguments are supported.
- It is possible to set up a global argument handler, that collects all arguments from different modules, libraries etc. and then
  handles all arguments from the command line.
- For library modules, it is also possible to set up a special argument handler that stores the values from the command line and
  retrieve them later.
- The library also supports sub-groups of arguments, i.e. a sub-group started by the argument `-i/--input` followed by the arguments
  for input like `-f/--file` etc. 

## Examples

### Program with "usage" arguments only

The following program accepts no command line arguments, except '-h/--help' to display the usage.
If the program is run with any other argument than these help arguments, an error message is printed and the program stops.

    #include "celma/prog_args.hpp"
    
    int main( int argc, char* argv[])
    {
      celma::prog_args::Handler arg_handler( celma::prog_args::Handler::hfHelpShort | celma::prog_args::Handler::hfHelpLong);
      arg_handler.evalArgumentsErrorExit( argc, argv, "*** Error:");
    } // main

Output when called with argument `--help`:

Output when called with an unknown argument, e.g. `--filename`:
