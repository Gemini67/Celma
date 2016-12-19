
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
/// See description of class celma::indirect_access::detail::IIndirectAccess.


#ifndef CELMA_INDIRECT_ACCESS_DETAIL_I_INDIRECT_ACCESS_FIELD_HPP
#define CELMA_INDIRECT_ACCESS_DETAIL_I_INDIRECT_ACCESS_FIELD_HPP


#include <string>


namespace celma { namespace indirect_access { namespace detail {


/// Base class for accessing fields in a structure. Handles some shared
/// information and defines the methods needed by the interface.<br>
/// This class should not used directly by an application, the corresponding
/// usage is generate
/// @since  0.5, 03.11.2016  (renamed to 'indirect access')
/// @since  0.4, 02.05.2016
class IIndirectAccess
{
public:
   /// Constructor.
   /// @param[in]  name       The name of the field == the variable in the
   ///                        structure.
   /// @param[in]  type_name  The name of the type.
   /// @since  0.4, 02.05.2016
   IIndirectAccess( const std::string& name, const std::string& type_name);

   /// Default destructor is fine.
   virtual ~IIndirectAccess() = default;

   /// Returns the name of the field/variable.
   /// @return  The name as passed to the constructor.
   /// @since  0.4, 02.07.2016
   const std::string& fieldName() const noexcept( true);

   /// Returns the type of the field as text.
   /// @return  The type of the variable.
   /// @since  0.4, 02.05.2016
   const std::string& typeName() const noexcept( true);

   /// In the derived classes, should return the value stored in the variable as
   /// string.
   /// @return  The value of the field as string.
   /// @since  0.4, 02.07.2016
   virtual const std::string str() const noexcept( false) = 0;

protected:
   /// The name of the field/variable.
   const std::string  mName;
   /// The type as string.
   const std::string  mTypeName;

}; // IIndirectAccess


// inlined methods
// ===============


inline IIndirectAccess::IIndirectAccess( const std::string& name,
                                         const std::string& type_name):
   mName( name),
   mTypeName( type_name)
{
} // end IIndirectAccess::IIndirectAccess


inline const std::string& IIndirectAccess::fieldName() const noexcept( true)
{
   return mName;
} // end IIndirectAccess::fieldName


inline const std::string& IIndirectAccess::typeName() const noexcept( true)
{
   return mTypeName;
} // end IIndirectAccess::typeName


} // namespace detail
} // namespace indirect_access
} // namespace celma


#endif   // CELMA_INDIRECT_ACCESS_DETAIL_I_INDIRECT_ACCESS_FIELD_HPP


// ======================  END OF i_indirect_access.hpp  ======================

