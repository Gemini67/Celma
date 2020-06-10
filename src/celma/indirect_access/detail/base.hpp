
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2016-2019 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
--*/


/// @file
/// See description of class celma::indirect_access::detail::Base.


#ifndef CELMA_INDIRECT_ACCESS_DETAIL_BASE_HPP
#define CELMA_INDIRECT_ACCESS_DETAIL_BASE_HPP


#include <iosfwd>
#include <memory>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <vector>


#include "celma/indirect_access/detail/i_field.hpp"
#include "celma/indirect_access/detail/field.hpp"


namespace celma {

/// Namespace for the classes used to provide indirect access to the member
/// variables of a structure.
namespace indirect_access {
/// Indirect access detail namespace, used for classes etc. that should not be
/// directly accessed by an application.
namespace detail {


/// Base class for a class that provides indirect access to its member variables.
///
/// @since  1.2.1, 08.01.2018
///    (renamed to Base)
/// @since  0.5, 03.11.2016
///    (feature renamed to 'indirect access')
/// @since  0.4, 02.05.2016
class Base
{
public:
   /// Copying of objects of this class is not allowed.
   Base( const Base&) = delete;
   /// Assignment of another object is also not allowed.
   Base& operator =( const Base&) = delete;

   /// Assigns a new value.
   ///
   /// @tparam  T  The type of the value.
   /// @param[in]  id
   ///    The id/number of the field/variable to assign the value to.
   /// @param[in]  newValue
   ///    The new value to assign.
   /// @throw
   ///    std::runtime_error when the id is unknown or the type of the value
   ///    does not match the type of the variable.
   /// @since  0.4, 02.05.2016
   template< typename T>
      void set( uint16_t id, const T& newValue) noexcept( false);

   /// Returns the current value of the specified variable/field.
   ///
   /// @tparam  T  The type of the value.
   /// @param[in]  id
   ///    The id/number of the field/variable to return the value of.
   /// @return  The current value of the specified variable.
   /// @throw
   ///    std::runtime_error when the id is unknown or the type of the value
   ///    does not match the return type.
   /// @since  0.4, 02.05.2016
   template< typename T> const T& get( uint16_t id) const noexcept( false);

   /// Assigns a new value.
   ///
   /// @tparam  T  The type of the value.
   /// @param[in]  name
   ///    The name of the field/variable to assign the value to.
   /// @param[in]  new_value
   ///    The new value to assign.
   /// @throw
   ///    std::runtime_error when the name is unknown or the type of the value
   ///    does not match the type of the variable.
   /// @since  0.4, 02.05.2016
   template< typename T>
      void set( const std::string& name, const T& new_value) noexcept( false);

   /// Returns the current value of the specified variable/field.
   ///
   /// @tparam  T  The type of the value.
   /// @param[in]  name  The name of the field/variable to return the value of.
   /// @return  The current value of the specified variable.
   /// @throw
   ///    std::runtime_error when the name is unknown or the type of the value
   ///    does not match the return type.
   /// @since  0.4, 02.05.2016
   template< typename T>
      const T& get( const std::string& name) const noexcept( false);

   /// Returns the name of the field/variable with the specified id.
   ///
   /// @param[in]  id  The id of the field to return the name of.
   /// @return  The name of the field with the given id.
   /// @throw  std::runtime_error when the id is unknown.
   /// @since  0.4, 02.05.2016
   const std::string& getFieldName( uint16_t id) const noexcept( false);

   /// Returns the current value of the specified field/variable as string.
   ///
   /// @param[in]  id  The id of the field to return the value of.
   /// @return  The current value of the variable as string.
   /// @throw  std::runtime_error when the id is unknown.
   /// @since  0.4, 02.07.2016
   const std::string getFieldValueString( uint16_t id) const noexcept( false);

   /// Returns the type of the field/variable as string.
   ///
   /// @param[in]  id  The id of the field to return the value of.
   /// @return  The type of the value as string.
   /// @throw  std::runtime_error when the id is unknown.
   /// @since  0.4, 02.07.2016
   const std::string& getFieldTypeString( uint16_t id) const noexcept( false);

   /// Returns the number of fields stored here.
   ///
   /// @return  The number of fields stored by this indirect access container.
   /// @since  0.4, 02.07.2016
   uint16_t size() const noexcept( true);

   /// Insertion operator to print the contents of an object using a base class
   /// object pointer.
   ///
   /// @param[out]  os
   ///    The stream to insert into.
   /// @param[in]   obj
   ///    The pointer to the object to print the contents of.
   /// @return  The stream as passed in.
   /// @since  0.4, 13.07.2016
   friend std::ostream& operator <<( std::ostream& os, const Base* obj);

protected:
   /// Protected constructor to make sure that this class is always used as base
   /// class.
   ///
   /// @since  0.4, 02.05.2016
   Base() = default;

   /// Default destructor.
   virtual ~Base() = default;

   /// Adds a new field.
   ///
   /// @tparam  T  The type of the value/variable.
   /// @param[in]  name
   ///    The name of the field/variable.
   /// @param[in]  value
   ///    The variable itself.
   /// @since  0.4, 02.05.2016
   template< typename T>
      void addField( const std::string& name, T& value) noexcept( false);

private:
   /// Shared pointer type to store.
   using field_ptr = std::shared_ptr< IField>;
   /// Vector type for storing the fields and access them by id.
   using id_cont_t = std::vector< field_ptr>;
   /// Container type for accessing the fields by name.
   using name_cont_t = std::unordered_map< std::string, field_ptr>;

   /// Primary container, access by field id.
   id_cont_t    mId2Field;
   /// Second container for access by name.
   name_cont_t  mName2Field;

}; // Base


// inlined methods
// ===============


template< typename T>
   void Base::set( uint16_t id, const T& newValue) noexcept( false)
{
   if (id >= mId2Field.size())
      throw std::runtime_error( "invalid field id");
   if (mId2Field[ id]->typeName() != type< T>::name())
      throw std::runtime_error( "cannot assign value with different type");
   auto  my_obj = static_cast< Field< T>*>( mId2Field[ id].get());
   my_obj->set( newValue);
} // Base::set


template< typename T>
   const T& Base::get( uint16_t id) const noexcept( false)
{
   if (id >= mId2Field.size())
      throw std::runtime_error( "invalid field id");
   if (mId2Field[ id]->typeName() != type< T>::name())
      throw std::runtime_error( "cannot return value with different type");
   auto  my_obj = static_cast< Field< T>*>( mId2Field[ id].get());
   return my_obj->get();
} // Base::get


template< typename T>
   void Base::set( const std::string& name, const T& new_value) noexcept( false)
{
   auto  it = mName2Field.find( name);
   if (it == mName2Field.end())
      throw std::runtime_error( "invalid field name");
   if (it->second->typeName() != type< T>::name())
      throw std::runtime_error( "cannot assign value with different type");
   auto  my_obj = static_cast< Field< T>*>( it->second.get());
   my_obj->set( new_value);
} // Base::set


template< typename T>
   const T& Base::get( const std::string& name) const noexcept( false)
{
   auto  it = mName2Field.find( name);
   if (it == mName2Field.end())
      throw std::runtime_error( "invalid field name");
   if (it->second->typeName() != type< T>::name())
      throw std::runtime_error( "cannot return value with different type");
   auto  my_obj = static_cast< Field< T>*>( it->second.get());
   return my_obj->get();
} // Base::get


inline uint16_t Base::size() const noexcept( true)
{
   return static_cast< uint16_t>( mId2Field.size());
} // Base::size


template< typename T>
   void Base::addField( const std::string& name, T& value) noexcept( false)
{
   if (mName2Field.find( name) != mName2Field.end())
      throw std::runtime_error( "field with this name already exists");

   field_ptr  new_field( new Field< T>( name, value));

   mId2Field.push_back( new_field);
   mName2Field.insert( name_cont_t::value_type( name, new_field));
} // Base::addField


} // namespace detail
} // namespace indirect_access
} // namespace celma


#endif   // CELMA_INDIRECT_ACCESS_DETAIL_BASE_HPP


// =====  END OF base.hpp  =====

