
##
##    ####   ######  #       #    #   ####
##   #    #  #       #       ##  ##  #    #
##   #       ###     #       # ## #  ######    (C) 2016 Rene Eng
##   #    #  #       #       #    #  #    #        LGPL
##    ####   ######  ######  #    #  #    #
##

cmake_minimum_required( VERSION 2.8 )

add_subdirectory( common )
get_directory_property( common_sources DIRECTORY ./common
   DEFINITION common_sources
)

add_subdirectory( format )
get_directory_property( format_sources DIRECTORY ./format
   DEFINITION format_sources
)

add_subdirectory( prog_args )
get_directory_property( prog_args_sources DIRECTORY ./prog_args
   DEFINITION prog_args_sources
)

add_subdirectory( reflection )
get_directory_property( reflection_sources DIRECTORY ./reflection
   DEFINITION reflection_sources
)

set( celma_lib_sources
   ${common_sources}
   ${format_sources}
   ${prog_args_sources}
   ${reflection_sources}
)

add_library( celma SHARED
   ${celma_lib_sources}
)
add_library( celma-static STATIC
   ${celma_lib_sources}
)

set_target_properties( celma
   PROPERTIES VERSION ${MAJORVERSION}.${MINORVERSION}
)
set_target_properties( celma-static
   PROPERTIES OUTPUT_NAME celma
)

install( TARGETS celma celma-static
   RUNTIME DESTINATION bin
   LIBRARY DESTINATION lib64
   ARCHIVE DESTINATION lib64
   COMPONENT LIBRARIES
)

