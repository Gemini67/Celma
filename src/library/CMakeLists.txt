
##
##    ####   ######  #       #    #   ####
##   #    #  #       #       ##  ##  #    #
##   #       ###     #       # ## #  ######    (C) 2016-2017 Rene Eng
##   #    #  #       #       #    #  #    #        LGPL
##    ####   ######  ######  #    #  #    #
##

cmake_minimum_required( VERSION 2.8 )

add_subdirectory( appl )
get_directory_property( appl_sources DIRECTORY ./appl
   DEFINITION appl_sources
)

add_subdirectory( common )
get_directory_property( common_sources DIRECTORY ./common
   DEFINITION common_sources
)

add_subdirectory( format )
get_directory_property( format_sources DIRECTORY ./format
   DEFINITION format_sources
)

add_subdirectory( log )
get_directory_property( log_sources DIRECTORY ./log
   DEFINITION log_sources
)

add_subdirectory( prog_args )
get_directory_property( prog_args_sources DIRECTORY ./prog_args
   DEFINITION prog_args_sources
)

add_subdirectory( indirect_access )
get_directory_property( indirect_access_sources DIRECTORY ./indirect_access
   DEFINITION indirect_access_sources
)

set( celma_lib_sources
   ${appl_sources}
   ${common_sources}
   ${format_sources}
   ${log_sources}
   ${prog_args_sources}
   ${indirect_access_sources}
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

