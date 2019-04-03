
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2016-2018 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
--*/


/// @file
/// See documentation of class celma::log::detail::LogAttributesContainer.


// module header file include
#include "celma/log/detail/log_attributes_container.hpp"


// C++ Standard Library includes
#include <iostream>
#include <thread>


namespace celma { namespace log { namespace detail {


using std::string;



/// Adds an attribute with type string to the internal list of attributes.
///
/// @param[in]  attr_name
///    The name of the attribute.
/// @param[in]  attr_value
///    The value of the attribute.
/// @since  1.15.0, 19.06.2016
void LogAttributesContainer::addAttribute( const string& attr_name,
   const string& attr_value)
{

   mAttributes.push_back( attr_pair_t( attr_name, attr_value));

} // LogAttributesContainer::addAttribute



/// Returns the value for the given attribute.<br>
/// If no attribute with the given name is found, an empty string is
/// returned.<br>
/// If multiple atributes with the same name exist, the value of the last
/// attribute is returned.
///
/// @param[in]  attr_name  The name of the attribute to return the value of.
/// @return
//     The value of the requested attribute, an empty string when not found.
/// @since  1.15.0, 16.03.2018
string LogAttributesContainer::getAttribute( const string& attr_name) const
{

   for (auto attr_rev_iter = mAttributes.rbegin();
        attr_rev_iter != mAttributes.rend(); ++attr_rev_iter)
   {
      if (std::get< 0>( *attr_rev_iter) == attr_name)
         return std::get< 1>( *attr_rev_iter);
   } // end for

   return string();
} // LogAttributesContainer::getAttribute



/// Removes the atribute that was added last.
///
/// @since  1.15.0, 16.03.2018
void LogAttributesContainer::removeAttribute()
{

   // std::cout << "thread " << std::this_thread::get_id() << ", object "
   //           << this << ": remove attribute" << std::endl;

   if (!mAttributes.empty())
      mAttributes.erase( --mAttributes.end());

   // std::cout << "thread " << std::this_thread::get_id() << ", object "
   //           << this << ": attribute removed" << std::endl;

} // LogAttributesContainer::removeAttribute



/// Removes the latest added attribute with the given name.
///
/// @param[in]  attr_name  The name of the attribute to erase.
/// @since  1.15.0, 20.03.2018
void LogAttributesContainer::removeAttribute( const string& attr_name)
{

   if (mAttributes.empty())
      return;

   for (ssize_t idx = mAttributes.size() - 1; idx >= 0; --idx)
   {
      if (std::get< 0>( mAttributes[ idx]) == attr_name)
      {
         mAttributes.erase( mAttributes.begin() + idx);
         break;   // while
      } // end if
   } // end for

} // LogAttributesContainer::removeAttribute



} // namespace detail
} // namespace log
} // namespace celma


// =====  END OF log_attributes_container.cpp  =====

