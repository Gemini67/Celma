
##
##    ####   ######  #       #    #   ####
##   #    #  #       #       ##  ##  #    #
##   #       ###     #       # ## #  ######    (C) 2016 Rene Eng
##   #    #  #       #       #    #  #    #        LGPL
##    ####   ######  ######  #    #  #    #
##

cmake_minimum_required( VERSION 2.8 )

add_definitions( -DBOOST_TEST_DYN_LINK)

celma_add_celma_boost_testprogram( test_arg_list_element )
celma_add_celma_boost_testprogram( test_arg_list_parser )
celma_add_celma_boost_testprogram( test_argument_key )
