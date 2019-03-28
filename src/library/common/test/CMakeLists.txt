
##
##    ####   ######  #       #    #   ####
##   #    #  #       #       ##  ##  #    #
##   #       ###     #       # ## #  ######    (C) 2016-2019 Rene Eng
##   #    #  #       #       #    #  #    #        LGPL
##    ####   ######  ######  #    #  #    #
##

cmake_minimum_required( VERSION 3.5 )

add_definitions( -DBOOST_TEST_DYN_LINK)

celma_add_boost_testprogram( test_adjust )
celma_add_boost_testprogram( test_any_type_base )
celma_add_boost_testprogram( test_bitset_iterator )
celma_add_boost_testprogram( test_clear_container )
celma_add_boost_testprogram( test_constexpr_string_concat )
celma_add_boost_testprogram( test_constexpr_string_from )
celma_add_boost_testprogram( test_contains )
celma_add_boost_testprogram( test_current_total )
celma_add_boost_testprogram( test_enum_array )
celma_add_boost_testprogram( test_enum_flags )
celma_add_boost_testprogram( test_find_sequence )
celma_add_boost_testprogram( test_first_pass )
celma_add_boost_testprogram( test_lazy_ptr )
celma_add_boost_testprogram( test_manipulator )
celma_add_boost_testprogram( test_merge_sorted_cont )
celma_add_boost_testprogram( test_multiline_string_compare )
celma_add_boost_testprogram( test_object_counted_enumerated )
celma_add_boost_testprogram( test_object_counter )
celma_add_boost_testprogram( test_object_enumerator )
celma_add_boost_testprogram( test_read_buffer )
celma_add_boost_testprogram( test_rel_ops_from_compare )
celma_add_boost_testprogram( test_rel_ops_from_less )
celma_add_boost_testprogram( test_reset_at_exit )
celma_add_boost_testprogram( test_string_util )
celma_add_boost_testprogram( test_text_file )
celma_add_boost_testprogram( test_tokenizer )
celma_add_boost_testprogram( test_tokenizer_base )
celma_add_boost_testprogram( test_transform_call )
celma_add_boost_testprogram( test_type_name )
celma_add_boost_testprogram( test_value_result )
celma_add_boost_testprogram( test_write_buffer )

celma_add_boost_mt_testprogram( test_managed_thread )
celma_add_boost_mt_testprogram( test_sleep_on_error )

celma_add_celma_boost_testprogram( test_exception )
celma_add_celma_boost_testprogram( test_extract_funcname )
celma_add_celma_boost_testprogram( test_file_info )
celma_add_celma_boost_testprogram( test_file_operations )
celma_add_celma_boost_testprogram( test_range_dest )
celma_add_celma_boost_testprogram( test_range_expression )
celma_add_celma_boost_testprogram( test_range_generator )
celma_add_celma_boost_testprogram( test_range_string )
celma_add_celma_boost_testprogram( test_singleton )
celma_add_celma_boost_testprogram( test_tuple_at_index )
celma_add_celma_boost_testprogram( test_tuple_length )
celma_add_celma_boost_testprogram( test_version_info )
