
##
##    ####   ######  #       #    #   ####
##   #    #  #       #       ##  ##  #    #
##   #       ###     #       # ## #  ######    (C) 2016 Rene Eng
##   #    #  #       #       #    #  #    #        LGPL
##    ####   ######  ######  #    #  #    #
##
##
##   Description:
##      Macro definitions for adding a test program.
##


# define a test program that doesn't need any libraries
macro( celma_add_testprogram  filename )
   add_executable( ${filename}  ${filename}.cpp )
   add_test(       ${filename}  ${CMAKE_CURRENT_BINARY_DIR}/${filename} )
endmacro( celma_add_testprogram )


# define a test program that uses Boost.Test
macro( celma_add_boost_testprogram  filename )
   add_executable(        ${filename}  ${filename}.cpp )
   target_link_libraries( ${filename}  ${Boost_Test_Link_Libs} )
   add_test(              ${filename}  ${CMAKE_CURRENT_BINARY_DIR}/${filename} )
endmacro( celma_add_boost_testprogram )


# define a test program that needs to link the foundation library
macro( celma_add_celma_testprogram  filename )
   add_executable(        ${filename}  ${filename}.cpp )
   target_link_libraries( ${filename}  celma ${Boost_Link_Libs} )
   add_test(              ${filename}  ${CMAKE_CURRENT_BINARY_DIR}/${filename} )
endmacro( celma_add_celma_testprogram )


# define a test program that needs to link the foundation and the Boost.Test
# libraries
macro( celma_add_celma_boost_testprogram  filename )
   add_executable(        ${filename}  ${filename}.cpp )
   target_link_libraries( ${filename}  celma ${Boost_Test_Link_Libs} )
   add_test(              ${filename}  ${CMAKE_CURRENT_BINARY_DIR}/${filename} )
endmacro( celma_add_celma_boost_testprogram )
