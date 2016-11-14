
##
##    ####   ######  #       #    #   ####
##   #    #  #       #       ##  ##  #    #
##   #       ###     #       # ## #  ######    (C) 2016 Rene Eng
##   #    #  #       #       #    #  #    #        LGPL
##    ####   ######  ######  #    #  #    #
##

cmake_minimum_required( VERSION 2.8 )

add_definitions( -DBOOST_TEST_DYN_LINK)

celma_add_celma_boost_testprogram( test_ascii_table )
celma_add_celma_boost_testprogram( test_auto_sprintf )
celma_add_celma_boost_testprogram( test_grouped_int2str )
celma_add_celma_boost_testprogram( test_int2str )
celma_add_celma_boost_testprogram( test_text_block )
