
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2021 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
--*/


/// @file
/// See documentation of class celma::container::Segment and template classes
/// - celma::container::SharedList<>
/// - celma::container::SharedMap<>
/// - celma::container::SharedMultiMap<>
/// - celma::container::SharedMultiSet<>
/// - celma::container::SharedSet<>
/// - celma::container::SharedUnorderedMap<>
/// - celma::container::SharedVector<>


// module headerfile include
#include "celma/container/shared_container.hpp"


namespace celma::container {



/// Constructor.
/// Tries to access an existing segment with the given name, if that fails
/// tries to open/create a new segment.
/// @param[in]  name  The symbolic name of the shared memory segment.
/// @param[in]  size  The initial size of the shared memory segment. Only
///                   used if the shared memory segment does not exist yet.
/// @throws  boost::interprocess::bad_alloc if memory allocation failed.
/// @since  x.y.z, 31.03.2021
Segment::Segment( const char* name, size_t size) noexcept( false):
   boost::interprocess::managed_shared_memory()
{

   namespace bi = boost::interprocess;

   try
   {
      static_cast< bi::managed_shared_memory&>( *this)
         = bi::managed_shared_memory( bi::open_only, name);
   } catch (...)
   {
      static_cast< bi::managed_shared_memory&>( *this)
         = bi::managed_shared_memory( boost::interprocess::create_only, name, size);
      mWasCreated = true;
   } // end try

} // Segment::Segment



} // namespace celma::container


// =====  END OF shared_container.cpp  =====

