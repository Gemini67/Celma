
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
/// See description of class celma::reflection::detail::IReflectedField.


#ifndef CELMA_REFLECTION_DETAIL_I_RELFECTED_FIELD_HPP
#define CELMA_REFLECTION_DETAIL_I_RELFECTED_FIELD_HPP


#include <string>


namespace celma { namespace reflection { namespace detail {


/// Base class for accessing fields in a structure. Handles some shared
/// information and defines the methods needed by the interface.<br>
/// This class should not used directly by an application, the corresponding
/// usage is generate
/// @since  0.4, 02.05.2016
class IReflectedField
{
public:
   /// Constructor.
   /// @param[in]  name       The name of the field == the variable in the
   ///                        structure.
   /// @param[in]  type_name  The name of the type.
   /// @since  0.4, 02.05.2016
   IReflectedField( const std::string& name, const std::string& type_name);

   /// Default destructor is fine.
   virtual ~IReflectedField() = default;

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

}; // IReflectedField


// inlined methods
// ===============


inline IReflectedField::IReflectedField( const std::string& name,
                                         const std::string& type_name):
   mName( name),
   mTypeName( type_name)
{
} // end IReflectedField::IReflectedField


inline const std::string& IReflectedField::fieldName() const noexcept( true)
{
   return mName;
} // end IReflectedField::fieldName


inline const std::string& IReflectedField::typeName() const noexcept( true)
{
   return mTypeName;
} // end IReflectedField::typeName


} // namespace detail
} // namespace reflection
} // namespace celma


#endif   // CELMA_REFLECTION_DETAIL_I_RELFECTED_FIELD_HPP


// ======================  END OF i_reflected_field.hpp  ======================

