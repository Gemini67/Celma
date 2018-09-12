
##
##    ####   ######  #       #    #   ####
##   #    #  #       #       ##  ##  #    #
##   #       ###     #       # ## #  ######    (C) 2017-2018 Rene Eng
##   #    #  #       #       #    #  #    #        LGPL
##    ####   ######  ######  #    #  #    #
##

cmake_minimum_required( VERSION 3.5 )

add_definitions( -DBOOST_TEST_DYN_LINK)

celma_add_celma_boost_testprogram( test_arg_string_2_array )
celma_add_celma_boost_testprogram( test_project_path )
celma_add_celma_boost_testprogram( test_project_root )
