
##
##    ####   ######  #       #    #   ####
##   #    #  #       #       ##  ##  #    #
##   #       ###     #       # ## #  ######    (C) 2016 Rene Eng
##   #    #  #       #       #    #  #    #        LGPL
##    ####   ######  ######  #    #  #    #
##

cmake_minimum_required( VERSION 2.8 )

add_definitions( -DBOOST_TEST_DYN_LINK)

celma_add_celma_boost_testprogram( test_argh_callables )
celma_add_celma_boost_testprogram( test_argh_cardinality )
celma_add_celma_boost_testprogram( test_argh_checks )
celma_add_celma_boost_testprogram( test_argh_constraints )
celma_add_celma_boost_testprogram( test_argh_custom_convert )
celma_add_celma_boost_testprogram( test_argh_custom_type )
celma_add_celma_boost_testprogram( test_argh_longarg_abbr )
celma_add_celma_boost_testprogram( test_argh_range )
celma_add_celma_boost_testprogram( test_argh_separate_values )
celma_add_celma_boost_testprogram( test_arg_list_parser )
celma_add_celma_boost_testprogram( test_argument_groups )
celma_add_celma_boost_testprogram( test_argument_handler )
celma_add_celma_boost_testprogram( test_argument_key )
celma_add_celma_boost_testprogram( test_argument_sub_groups )
celma_add_celma_boost_testprogram( test_constraint_container )

# test-programs for output
add_executable( test_arg_groups_usage           test_arg_groups_usage.cpp )
add_executable( test_argh_hidden_output         test_argh_hidden_output )
add_executable( test_argh_list_arg_vars_output  test_argh_list_arg_vars_output.cpp )
add_executable( test_argh_print_def             test_argh_print_def.cpp )
add_executable( test_argh_verbose_output        test_argh_verbose_output )
add_executable( test_groups_sub_groups_usage    test_groups_sub_groups_usage.cpp )
add_executable( test_long_arg_desc              test_long_arg_desc.cpp )
add_executable( test_sub_groups_usage           test_sub_groups_usage.cpp )

target_link_libraries( test_arg_groups_usage             celma ${Boost_Test_Link_Libs} )
target_link_libraries( test_argh_hidden_output           celma ${Boost_Test_Link_Libs} )
target_link_libraries( test_argh_list_arg_vars_output    celma ${Boost_Test_Link_Libs} )
target_link_libraries( test_argh_print_def               celma ${Boost_Test_Link_Libs} )
target_link_libraries( test_argh_verbose_output          celma ${Boost_Test_Link_Libs} )
target_link_libraries( test_groups_sub_groups_usage      celma ${Boost_Test_Link_Libs} )
target_link_libraries( test_long_arg_desc                celma ${Boost_Test_Link_Libs} )
target_link_libraries( test_sub_groups_usage             celma ${Boost_Test_Link_Libs} )

add_test( test_arg_groups_usage                ${CMAKE_CURRENT_BINARY_DIR}/test_arg_groups_usage -h )
add_test( test_argh_hidden_output              ${CMAKE_CURRENT_BINARY_DIR}/test_argh_hidden_output -h )
add_test( test_argh_list_arg_vars_output       ${CMAKE_CURRENT_BINARY_DIR}/test_argh_list_arg_vars_output )
add_test( test_argh_print_def                  ${CMAKE_CURRENT_BINARY_DIR}/test_argh_print_def -h )
add_test( test_argh_verbose_output             ${CMAKE_CURRENT_BINARY_DIR}/test_argh_verbose_output -f -i 36 -s myname )
add_test( test_groups_sub_groups_usage_input   ${CMAKE_CURRENT_BINARY_DIR}/test_groups_sub_groups_usage -ih )
add_test( test_groups_sub_groups_usage_main    ${CMAKE_CURRENT_BINARY_DIR}/test_groups_sub_groups_usage -h )
add_test( test_groups_sub_groups_usage_output  ${CMAKE_CURRENT_BINARY_DIR}/test_groups_sub_groups_usage -o -h )
add_test( test_long_arg_desc_long_desc         ${CMAKE_CURRENT_BINARY_DIR}/test_long_arg_desc 1 )
add_test( test_long_arg_desc_long_name         ${CMAKE_CURRENT_BINARY_DIR}/test_long_arg_desc 2 )
add_test( test_long_arg_desc_long_name_desc    ${CMAKE_CURRENT_BINARY_DIR}/test_long_arg_desc 3 )
add_test( test_long_arg_desc_long_name_4       ${CMAKE_CURRENT_BINARY_DIR}/test_long_arg_desc 4 )
add_test( test_long_arg_desc_main              ${CMAKE_CURRENT_BINARY_DIR}/test_long_arg_desc )
add_test( test_sub_groups_usage_input          ${CMAKE_CURRENT_BINARY_DIR}/test_sub_groups_usage -i -h )
add_test( test_sub_groups_usage_main           ${CMAKE_CURRENT_BINARY_DIR}/test_sub_groups_usage -h )
add_test( test_sub_groups_usage_output         ${CMAKE_CURRENT_BINARY_DIR}/test_sub_groups_usage -oh )

# test_arg_groups_usage
# ---------------------

set( test_arg_groups_usage_result
     "^Usage:\n"
     "\n"
     "Program Arguments:\n"
     "Mandatory:\n"
     "   --mandatory_int   mandatory integer value\n"
     "\n"
     "Optional:\n"
     "   -q                be quiet\n"
     "   --debug_mode      set to activate the debug mode\n"
     "\n"
     "\n"
     "Standard Arguments:\n"
     "Optional:\n"
     "   -h,--help         Prints the program usage\n"
     "   --version         prints version information\n"
     "   --modlist         prints module list\n"
     "\n"
     "\n$"
)

celma_add_test_output_check( test_arg_groups_usage  test_arg_groups_usage_result )


# test_argh_print_def
# -------------------

set( test_argh_print_def_result
     "^Usage:\n"
     "Mandatory arguments:\n"
     "   -m,--mandatory         Mandatory integer argument, no default\n"
     "\n"
     "Optional arguments:\n"
     "   -h,--help              Prints the program usage\n"
     "   -f,--flag              Boolean flag, no default\n"
     "   -o,--optional          Optional integer argument, \\*with\\* default\n"
     "                          Default value: 4711\n"
     "   -p,--optional-string   Optional string argument, \\*with\\* default\n"
     "                          Default value: hello world\n"
     "   -l,--list              Optional vector argument, don't print default\n"
     "   -c,--checked           Optional integer argument, using CheckAssign<>, \\*with\\*\n"
     "                          default\n"
     "\n$"
)

celma_add_test_output_check( test_argh_print_def  test_argh_print_def_result )


# test_argh_verbose_output
# ------------------------

set( test_argh_verbose_output_result
     "flagArg: is set\n"
     "intArg: value '36' is assigned\n"
     "stringArg: value 'myname' is assigned\n$"
)

celma_add_test_output_check( test_argh_verbose_output  test_argh_verbose_output_result )


# test_groups_sub_groups_usage_input
# ----------------------------------

set( test_groups_sub_groups_usage_input_result
   "^Usage:\n"
   "Optional arguments:\n"
   "   -h,--help   Prints the program usage\n"
   "   -f          specifies to read from a file\n"
   "   -q          specifies to read from a queue\n"
   "\n$"
)

celma_add_test_output_check( test_groups_sub_groups_usage_input  test_groups_sub_groups_usage_input_result )


# test_groups_sub_groups_usage_main
# ---------------------------------

set( test_groups_sub_groups_usage_main_result
   "^Usage:\n"
   "\n"
   "Program Arguments:\n"
   "Mandatory:\n"
   "   --mandatory_int   mandatory integer value\n"
   "\n"
   "Optional:\n"
   "   -q                be quiet\n"
   "   --debug_mode      set to activate the debug mode\n"
   "   -i                input arguments\n"
   "   -o                output arguments\n"
   "\n"
   "\n"
   "Standard Arguments:\n"
   "Optional:\n"
   "   -h,--help         Prints the program usage\n"
   "   --version         prints version information\n"
   "   --modlist         prints module list\n"
   "\n"
   "\n$"
)

celma_add_test_output_check( test_groups_sub_groups_usage_main  test_groups_sub_groups_usage_main_result )


# test_groups_sub_groups_usage_output
# -----------------------------------

set( test_groups_sub_groups_usage_output_result
   "^Usage:\n"
   "Optional arguments:\n"
   "   -h,--help   Prints the program usage\n"
   "   -f          specifies to write into a file\n"
   "   -q          specifies to write into a queue\n"
   "\n$"
)

celma_add_test_output_check( test_groups_sub_groups_usage_output  test_groups_sub_groups_usage_output_result )


# test_sub_groups_usage_input
# ---------------------------

set( test_sub_groups_usage_input_result
   "^Usage:\n"
   "Optional arguments:\n"
   "   -h,--help   Prints the program usage\n"
   "   -f          specifies to read from a file\n"
   "   -q          specifies to read from a queue\n"
   "\n$"
)

celma_add_test_output_check( test_sub_groups_usage_input  test_sub_groups_usage_input_result )


# test_sub_groups_usage_main_result
# ---------------------------------

set( test_sub_groups_usage_main_result
   "^Usage:\n"
   "Mandatory arguments:\n"
   "   --mandatory_int   mandatory integer value\n"
   "\n"
   "Optional arguments:\n"
   "   -h,--help         Prints the program usage\n"
   "   -q                be quiet\n"
   "   --debug_mode      set to activate the debug mode\n"
   "   -i                input arguments\n"
   "   -o                output arguments\n"
   "\n$"
)

celma_add_test_output_check( test_sub_groups_usage_main  test_sub_groups_usage_main_result )


# test_sub_groups_usage_output_result
# -----------------------------------

set( test_sub_groups_usage_output_result
   "^Usage:\n"
   "Optional arguments:\n"
   "   -h,--help   Prints the program usage\n"
   "   -f          specifies to write into a file\n"
   "   -q          specifies to write into a queue\n"
   "\n$"
)

celma_add_test_output_check( test_sub_groups_usage_output  test_sub_groups_usage_output_result )


# test_long_arg_desc_main
# -----------------------

set( test_long_arg_desc_main_output_result
   "^Need exactly one argument:\n"
   "   1  for test of parameter with long description\n"
   "   2  for test of parameter with long name\n"
   "   3  for test of parameter with long name and long description\n"
   "\n$"
)

celma_add_test_output_check( test_long_arg_desc_main  test_long_arg_desc_main_output_result )


# test_long_arg_desc_long_desc
# ----------------------------

set( test_long_arg_desc_long_desc_output_result
   "^Usage:\n"
   "Optional arguments:\n"
   "   -h,--help      Prints the program usage\n"
   "   -i,--include   Now here we have a parameter with a very long, long,\n"
   "                  description.\n"
   "                  This description spawns multiple lines by itself, and contains\n"
   "                  lines that are so long that they must be split unto multiple\n"
   "                  lines in order to get a decent output.\n"
   "                  Default value:\n"
   "\n$"
)

celma_add_test_output_check( test_long_arg_desc_long_desc  test_long_arg_desc_long_desc_output_result )


# test_long_arg_desc_long_name
# ----------------------------

set( test_long_arg_desc_long_name_output_result
   "^Usage:\n"
   "Optional arguments:\n"
   "   -h,--help\n"
   "      Prints the program usage\n"
   "   -i,--include-from-this-absolute-directory-path\n"
   "      Long parameter\n"
   "      Default value:\n"
   "\n$"
)

celma_add_test_output_check( test_long_arg_desc_long_name  test_long_arg_desc_long_name_output_result )


# test_long_arg_desc_long_name_desc
# ---------------------------------

set( test_long_arg_desc_long_name_desc_output_result
   "^Usage:\n"
   "Optional arguments:\n"
   "   -h,--help\n"
   "      Prints the program usage\n"
   "   -i,--include-from-this-absolute-directory-path\n"
   "      Now here we have a long parameter with a very long, long, description.\n"
   "      This description spawns multiple lines by itself, and contains lines that\n"
   "      are so long that they must be split unto multiple lines in order to get a\n"
   "      decent output.\n"
   "      Default value:\n"
   "\n$"
)

celma_add_test_output_check( test_long_arg_desc_long_name_desc  test_long_arg_desc_long_name_desc_output_result )


# test_long_arg_desc_long_name_4
# ------------------------------

set( test_long_arg_desc_long_name_4_output_result
   "^Usage:\n"
   "Optional arguments:\n"
   "   -h,--help\n"
   "      Prints the program usage\n"
   "   -i,--include-from-this-absolute-directory-path\n"
   "      Now here we have a long parameter with a very long, long,\n"
   "      description.\n"
   "      This description spawns multiple lines by itself, and\n"
   "      contains lines that are so long that they must be split\n"
   "      unto multiple lines in order to get a decent output.\n"
   "      Default value:\n"
   "\n$"
)

celma_add_test_output_check( test_long_arg_desc_long_name_4  test_long_arg_desc_long_name_4_output_result )


# test_argh_hidden_output
# -----------------------

set( test_argh_hidden_output_result
   "^Usage:\n"
   "Mandatory arguments:\n"
   "   --int-man             integer mandatory\n"
   "   --string-man          string mandatory\n"
   "\n"
   "Optional arguments:\n"
   "   -h                    Prints the program usage\n"
   "   --print-hidden        Also print hidden arguments in the usage.\n"
   "   --flag                flag\n"
   "   --int-opt             integer optional\n"
   "                         Default value: 0\n"
   "   --string-opt          string optional\n"
   "                         Default value:\n"
   "\n"
   "\n"
   "--------------------------------------------------------------------------------\n"
   "\n"
   "Usage:\n"
   "Mandatory arguments:\n"
   "   --int-man             integer mandatory\n"
   "   --string-man          string mandatory\n"
   "   --hidden-int-man      hidden integer mandatory\n"
   "   --hidden-string-man   hidden string mandatory\n"
   "\n"
   "Optional arguments:\n"
   "   -h                    Prints the program usage\n"
   "   --flag                flag\n"
   "   --int-opt             integer optional\n"
   "                         Default value: 0\n"
   "   --string-opt          string optional\n"
   "                         Default value:\n"
   "   --hidden-flag         hidden flag\n"
   "   --hidden-int-opt      hidden integer optional\n"
   "                         Default value: 0\n"
   "   --hidden-string-opt   hidden string optional\n"
   "                         Default value:\n"
   "\n"
   "\n"
   "--------------------------------------------------------------------------------\n"
   "\n"
   "Usage:\n"
   "Mandatory arguments:\n"
   "   --int-man             integer mandatory\n"
   "   --string-man          string mandatory\n"
   "   --hidden-int-man      hidden integer mandatory\n"
   "   --hidden-string-man   hidden string mandatory\n"
   "\n"
   "Optional arguments:\n"
   "   -h                    Prints the program usage\n"
   "   --print-hidden        Also print hidden arguments in the usage.\n"
   "   --flag                flag\n"
   "   --int-opt             integer optional\n"
   "                         Default value: 0\n"
   "   --string-opt          string optional\n"
   "                         Default value:\n"
   "   --hidden-flag         hidden flag\n"
   "   --hidden-int-opt      hidden integer optional\n"
   "                         Default value: 0\n"
   "   --hidden-string-opt   hidden string optional\n"
   "                         Default value:\n"
   "\n$"
)

celma_add_test_output_check( test_argh_hidden_output  test_argh_hidden_output_result )


# test_argh_list_arg_vars_output
# ------------------------------

set( test_argh_list_arg_vars_output_result
   "^Short \\(character\\) arguments:\n"
   "'-f' boolean flag, destination 'my_flag', set.\n"
   "   value 'no value' \\(0\\), optional, does not take multiple&separate values, don't print dflt, visible, no checks, no formats\n"
   "'-s' value type 'std::string', destination 'my_string', value not set.\n"
   "   value 'required' \\(2\\), optional, does not take multiple&separate values, print dflt, visible, no checks, no formats\n"
   "\n"
   "Long \\(string\\) arguments:\n"
   "'--integer' value type 'int', destination 'my_int', value not set.\n"
   "   value 'required' \\(2\\), mandatory, does not take multiple&separate values, print dflt, visible, no checks, no formats\n"
   "'--list-arg-vars' calls function/method 'Handler::listArgVars'.\n"
   "   value 'no value' \\(0\\), optional, does not take multiple&separate values, don't print dflt, visible, no checks, no formats\n"
   "'--string' value type 'std::string', destination 'my_string', value not set.\n"
   "   value 'required' \\(2\\), optional, does not take multiple&separate values, print dflt, visible, no checks, no formats\n"
   "\n"
   "--------------------------------------------------------------------------------\n"
   "\n"
   "Short \\(character\\) arguments:\n"
   "'-V' calls function/method 'Handler::listArgVars'.\n"
   "   value 'no value' \\(0\\), optional, does not take multiple&separate values, don't print dflt, visible, no checks, no formats\n"
   "'-f' boolean flag, destination 'my_flag', set.\n"
   "   value 'no value' \\(0\\), optional, does not take multiple&separate values, don't print dflt, visible, no checks, no formats\n"
   "'-s' value type 'std::string', destination 'my_string', value not set.\n"
   "   value 'required' \\(2\\), optional, does not take multiple&separate values, don't print dflt, visible, no checks, no formats\n"
   "\n"
   "Long \\(string\\) arguments:\n"
   "'--call' calls function/method 'callable_function'.\n"
   "   value 'no value' \\(0\\), optional, does not take multiple&separate values, don't print dflt, visible, no checks, no formats\n"
   "'--cas' value type 'std::string', destination 'CheckAssign< my_ca_string>', value not set.\n"
   "   value 'required' \\(2\\), optional, does not take multiple&separate values, don't print dflt, visible, no checks, no formats\n"
   "'--integer' value type 'int', destination 'my_int', value not set.\n"
   "   value 'required' \\(2\\), mandatory, does not take multiple&separate values, print dflt, visible, no checks, no formats\n"
   "'--long' value type 'long', destination 'my_long', value not set.\n"
   "   value 'required' \\(2\\), optional, does not take multiple&separate values, print dflt, hidden, no checks, no formats\n"
   "'--sl' value type 'std::vector<std::string>', destination vector 'my_string_list', currently no values.\n"
   "   value 'required' \\(2\\), optional, does not take multiple&separate values, don't print dflt, visible, no checks, no formats\n"
   "'--string' value type 'std::string', destination 'my_string', value not set.\n"
   "   value 'required' \\(2\\), optional, does not take multiple&separate values, don't print dflt, visible, no checks, no formats\n"
   "'--ulong' value type 'unsigned long', destination 'my_ulong', value not set.\n"
   "   value 'optional' \\(1\\), optional, does not take multiple&separate values, print dflt, visible, no checks, no formats\n"
   "\n"
   "Short \\(character\\) arguments:\n"
   "'-V' calls function/method 'Handler::listArgVars'.\n"
   "   value 'no value' \\(0\\), optional, does not take multiple&separate values, don't print dflt, visible, no checks, no formats\n"
   "'-f' boolean flag, destination 'my_flag', set.\n"
   "   value 'no value' \\(0\\), optional, does not take multiple&separate values, don't print dflt, visible, no checks, no formats\n"
   "'-s' value type 'std::string', destination 'my_string', value not set.\n"
   "   value 'required' \\(2\\), optional, does not take multiple&separate values, don't print dflt, visible, no checks, no formats\n"
   "\n"
   "Long \\(string\\) arguments:\n"
   "'--call' calls function/method 'callable_function'.\n"
   "   value 'no value' \\(0\\), optional, does not take multiple&separate values, don't print dflt, visible, no checks, no formats\n"
   "'--cas' value type 'std::string', destination 'CheckAssign< my_ca_string>', value not set.\n"
   "   value 'required' \\(2\\), optional, does not take multiple&separate values, don't print dflt, visible, no checks, no formats\n"
   "'--integer' value type 'int', destination 'my_int', value = 42.\n"
   "   value 'required' \\(2\\), mandatory, does not take multiple&separate values, print dflt, visible, no checks, no formats\n"
   "'--long' value type 'long', destination 'my_long', value not set.\n"
   "   value 'required' \\(2\\), optional, does not take multiple&separate values, print dflt, hidden, no checks, no formats\n"
   "'--sl' value type 'std::vector<std::string>', destination vector 'my_string_list', currently 1 values.\n"
   "   value 'required' \\(2\\), optional, does not take multiple&separate values, don't print dflt, visible, no checks, no formats\n"
   "'--string' value type 'std::string', destination 'my_string', value not set.\n"
   "   value 'required' \\(2\\), optional, does not take multiple&separate values, don't print dflt, visible, no checks, no formats\n"
   "'--ulong' value type 'unsigned long', destination 'my_ulong', value not set.\n"
   "   value 'optional' \\(1\\), optional, does not take multiple&separate values, print dflt, visible, no checks, no formats\n"
   "\n$"
)

celma_add_test_output_check( test_argh_list_arg_vars_output  test_argh_list_arg_vars_output_result )

