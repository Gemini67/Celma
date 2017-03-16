
##
##    ####   ######  #       #    #   ####
##   #    #  #       #       ##  ##  #    #
##   #       ###     #       # ## #  ######    (C) 2016-2017 Rene Eng
##   #    #  #       #       #    #  #    #        LGPL
##    ####   ######  ######  #    #  #    #
##

cmake_minimum_required( VERSION 2.8 )

add_definitions( -DBOOST_TEST_DYN_LINK)

celma_add_celma_boost_testprogram( test_ascii_table )
celma_add_celma_boost_testprogram( test_auto_sprintf )
celma_add_celma_boost_testprogram( test_grouped_int16_to_string )
celma_add_celma_boost_testprogram( test_grouped_int2string_16 )
celma_add_celma_boost_testprogram( test_grouped_int2string_32 )
celma_add_celma_boost_testprogram( test_grouped_int2string_64 )
celma_add_celma_boost_testprogram( test_grouped_int2string_8 )
celma_add_celma_boost_testprogram( test_grouped_int32_to_string )
celma_add_celma_boost_testprogram( test_grouped_int64_to_string )
celma_add_celma_boost_testprogram( test_grouped_int8_to_string )
celma_add_celma_boost_testprogram( test_int16_to_string )
celma_add_celma_boost_testprogram( test_int2string_16 )
celma_add_celma_boost_testprogram( test_int2string_32 )
celma_add_celma_boost_testprogram( test_int2string_64 )
celma_add_celma_boost_testprogram( test_int2string_8 )
celma_add_celma_boost_testprogram( test_int32_to_string )
celma_add_celma_boost_testprogram( test_int64_to_string )
celma_add_celma_boost_testprogram( test_int8_to_string )
celma_add_celma_boost_testprogram( test_text_block )

celma_add_celma_boost_testprogram( test_int2str_perf )
