
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2016-2018 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
--*/


/// @file
/// See description of class celma::indirect_access::detail::IField.


#ifndef CELMA_INDIRECT_ACCESS_DETAIL_I_FIELD_HPP
#define CELMA_INDIRECT_ACCESS_DETAIL_I_FIELD_HPP


#include <string>


namespace celma { namespace indirect_access { namespace detail {


/// Base class for accessing fields in a structure. Handles some shared
/// information and defines the methods needed by the interface.<br>
/// This class should not used directly by an application, the corresponding
/// usage is generated through the "indirect access" macros.
/// @since  1.2.1, 08.01.2018  (renamed to IField)
/// @since  0.5, 03.11.2016  (feature renamed to 'indirect access')
/// @since  0.4, 02.05.2016
class IField
{
public:
   /// Default destructor is fine.
   virtual ~IField() = default;

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
   /// Protected constructor to make sure that this class is always used as base
   /// class.
   /// @param[in]  name       The name of the field == the variable in the
   ///                        structure.
   /// @param[in]  type_name  The name of the type.
   /// @since  0.4, 02.05.2016
   IField( const std::string& name, const std::string& type_name);

   /// The name of the field/variable.
   const std::string  mName;
   /// The type as string.
   const std::string  mTypeName;

}; // IField


// inlined methods
// ===============


inline IField::IField( const std::string& name, const std::string& type_name):
   mName( name),
   mTypeName( type_name)
{
} // IField::IField


inline const std::string& IField::fieldName() const noexcept( true)
{
   return mName;
} // IField::fieldName


inline const std::string& IField::typeName() const noexcept( true)
{
   return mTypeName;
} // IField::typeName


} // namespace detail
} // namespace indirect_access
} // namespace celma


#endif   // CELMA_INDIRECT_ACCESS_DETAIL_I_FIELD_HPP


// =====  END OF i_field.hpp  =====

