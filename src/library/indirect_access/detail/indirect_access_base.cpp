
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2016 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
--*/


/// @file
/// See documentation of class celma::indirect_access::detail::IndirectAccessBase.


// module header file include
#include "celma/indirect_access/detail/indirect_access_base.hpp"


namespace celma { namespace indirect_access { namespace detail {



/// Returns the name of the field/variable with the specified id.
/// @param[in]  id  The id of the field to return the name of.
/// @return  The name of the field with the given id.
/// @since  0.4, 02.05.2016
const std::string& IndirectAccessBase::getFieldName( uint16_t id) const
                                                       noexcept( false)
{
   if (id >= mId2Field.size())
      throw std::runtime_error( "invalid field id");
   return mId2Field[ id]->fieldName();
} // end IndirectAccessBase::getFieldName



/// Returns the current value of the specified field/variable as string.
/// @param[in]  id  The id of the field to return the value of.
/// @return  The current value of the variable as string.
/// @since  0.4, 02.07.2016
const std::string IndirectAccessBase::getFieldValueString( uint16_t id) const
                                                    noexcept( false)
{
   if (id >= mId2Field.size())
      throw std::runtime_error( "invalid field id");
   return mId2Field[ id]->str();
} // end IndirectAccessBase::getFieldValueString



/// Returns the type of the field/variable as string.
/// @param[in]  id  The id of the field to return the value of.
/// @return  The type of the value as string.
/// @since  0.4, 02.07.2016
const std::string& IndirectAccessBase::getFieldTypeString( uint16_t id) const
                                                    noexcept( false)
{
   if (id >= mId2Field.size())
      throw std::runtime_error( "invalid field id");
   return mId2Field[ id]->typeName();
} // end IndirectAccessBase::getFieldTypeString



/// Insertion operator to print the contents of an object using a base class
/// object pointer.
/// @param[out]  os   The stream to insert into.
/// @param[in]   obj  The pointer to the object to print the contents of.
/// @return  The stream as passed in.
/// @since  0.4, 13.07.2016
std::ostream& operator <<( std::ostream& os, const IndirectAccessBase* obj)
{

   for (size_t i = 0; i < obj->mId2Field.size(); ++i)
   {
      if (i > 0)
         os << "\n";

      os << "field idx " << i << ": name='" << obj->mId2Field[ i]->fieldName()
         << "', type='" << obj->mId2Field[ i]->typeName() << "', value='"
         << obj->mId2Field[ i]->str() << "'";
   } // end for
   
   return os;
} // end operator <<



/// Constructor.
/// @since  0.4, 02.05.2016
IndirectAccessBase::IndirectAccessBase():
   mId2Field(),
   mName2Field()
{
} // end IndirectAccessBase::IndirectAccessBase



} // namespace detail
} // namespace indirect_access
} // namespace celma


// =====================  END OF indirect_access_base.cpp  =====================
