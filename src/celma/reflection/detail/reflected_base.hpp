
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
/// See description of class celma::reflection::detail::ReflectedBase.


#ifndef CELMA_REFLECTION_DETAIL_REFLECTED_BASE_HPP
#define CELMA_REFLECTION_DETAIL_REFLECTED_BASE_HPP


#include <memory>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <vector>


#include "celma/reflection/detail/i_reflected_field.hpp"
#include "celma/reflection/detail/reflected_field.hpp"


namespace celma {

/// Namespace for the classes used to provide reflection-like access to the
/// member variables of a structure.
namespace reflection {
/// Reflection detail namespace, used for classes etc. that should not be
/// directly accessed by an application.
namespace detail {


/// Base class for a class that provides reflection-like access to its member
/// variables.
/// @since  0.4, 02.05.2016
class ReflectedBase
{
public:
   /// Assigns a new value.
   /// @tparam  T  The type of the value.
   /// @param[in]  id        The id/number of the field/variable to assign the
   ///                       value to.
   /// @param[in]  newValue  The new value to assign.
   /// @since  0.4, 02.05.2016
   template< typename T> void set( uint16_t id, const T& newValue)
                                 noexcept( false);

   /// Returns the current value of the specified variable/field.
   /// @tparam  T  The type of the value.
   /// @param[in]  id  The id/number of the field/variable to return the value of.
   /// @return  The current value of the specified variable.
   /// @since  0.4, 02.05.2016
   template< typename T> const T& get( uint16_t id) const noexcept( false);

   /// Assigns a new value.
   /// @tparam  T  The type of the value.
   /// @param[in]  name       The name of the field/variable to assign the value
   ///                        to.
   /// @param[in]  new_value  The new value to assign.
   /// @since  0.4, 02.05.2016
   template< typename T> void set( const std::string& name, const T& new_value)
                                 noexcept( false);

   /// Returns the current value of the specified variable/field.
   /// @tparam  T  The type of the value.
   /// @param[in]  name  The name of the field/variable to return the value of.
   /// @return  The current value of the specified variable.
   /// @since  0.4, 02.05.2016
   template< typename T> const T& get( const std::string& name) const
                                     noexcept( false);

   /// Returns the name of the field/variable with the specified id.
   /// @param[in]  id  The id of the field to return the name of.
   /// @return  The name of the field with the given id.
   /// @since  0.4, 02.05.2016
   const std::string& getFieldNameReflected( uint16_t id) const noexcept( false);

   /// Returns the current value of the specified field/variable as string.
   /// @param[in]  id  The id of the field to return the value of.
   /// @return  The current value of the variable as string.
   /// @since  0.4, 02.07.2016
   const std::string getFieldValueString( uint16_t id) const noexcept( false);

   /// Returns the type of the field/variable as string.
   /// @param[in]  id  The id of the field to return the value of.
   /// @return  The type of the value as string.
   /// @since  0.4, 02.07.2016
   const std::string& getFieldTypeString( uint16_t id) const noexcept( false);

   /// Returns the number of fields stored here.
   /// @return  The number of fields stored by this reflection container.
   /// @since  0.4, 02.07.2016
   uint16_t size() const noexcept( true);

protected:
   /// Constructor.
   /// @since  0.4, 02.05.2016
   ReflectedBase();

   /// Default destructor.
   virtual ~ReflectedBase() = default;

   /// Adds a new field.
   /// @tparam  T  The type of the value/variable.
   /// @param[in]  name   The name of the field/variable.
   /// @param[in]  value  The variable itself.
   /// @since  0.4, 02.05.2016
   template< typename T> void addField( const std::string& name, T& value)
                                      noexcept( false);

private:
   /// Shared pointer type to store.
   typedef std::shared_ptr< IReflectedField>            field_ptr;
   /// Vector type for storing the fields and access them by id.
   typedef std::vector< field_ptr>                      id_cont_t;
   /// Container type for accessing the fields by name.
   typedef std::unordered_map< std::string, field_ptr>  name_cont_t;

   /// Copying of objects of this class is not allowed.
   ReflectedBase( const ReflectedBase&) = delete;
   /// Assignment of another object is also not allowed.
   ReflectedBase& operator =( const ReflectedBase&) = delete;

   /// Primary container, access by field id.
   id_cont_t    mId2Field;
   /// Second container for access by name.
   name_cont_t  mName2Field;

}; // ReflectedBase


// inlined methods
// ===============


template< typename T> void ReflectedBase::set( uint16_t id, const T& newValue)
                                             noexcept( false)
{
   if (id >= mId2Field.size())
      throw std::runtime_error( "invalid field id");
   if (mId2Field[ id]->typeName() != type< T>::name())
      throw std::runtime_error( "cannot assign value with different type");
   auto  my_obj = static_cast< ReflectedField< T>*>( mId2Field[ id].get());
   my_obj->set( newValue);
} // end ReflectedBase::set


template< typename T> const T& ReflectedBase::get( uint16_t id) const
                                                  noexcept( false)
{
   if (id >= mId2Field.size())
      throw std::runtime_error( "invalid field id");
   if (mId2Field[ id]->typeName() != type< T>::name())
      throw std::runtime_error( "cannot return value with different type");
   auto  my_obj = static_cast< ReflectedField< T>*>( mId2Field[ id].get());
   return my_obj->get();
} // end ReflectedBase::get


template< typename T> void ReflectedBase::set( const std::string& name,
                                               const T& new_value)
                                             noexcept( false)
{
   auto  it = mName2Field.find( name);
   if (it == mName2Field.end())
      throw std::runtime_error( "invalid field name");
   if (it->second->typeName() != type< T>::name())
      throw std::runtime_error( "cannot assign value with different type");
   auto  my_obj = static_cast< ReflectedField< T>*>( it->second.get());
   my_obj->set( new_value);
} // end ReflectedBase::set


template< typename T> const T& ReflectedBase::get( const std::string& name) const
                                                 noexcept( false)
{
   auto  it = mName2Field.find( name);
   if (it == mName2Field.end())
      throw std::runtime_error( "invalid field name");
   if (it->second->typeName() != type< T>::name())
      throw std::runtime_error( "cannot return value with different type");
   auto  my_obj = static_cast< ReflectedField< T>*>( it->second.get());
   return my_obj->get();
} // end ReflectedBase::get


const std::string& ReflectedBase::getFieldNameReflected( uint16_t id) const
                                                       noexcept( false)
{
   if (id >= mId2Field.size())
      throw std::runtime_error( "invalid field id");
   return mId2Field[ id]->fieldName();
} // end ReflectedBase::getFieldNameReflected


const std::string ReflectedBase::getFieldValueString( uint16_t id) const
                                                    noexcept( false)
{
   if (id >= mId2Field.size())
      throw std::runtime_error( "invalid field id");
   return mId2Field[ id]->str();
} // end ReflectedBase::getFieldValueString


const std::string& ReflectedBase::getFieldTypeString( uint16_t id) const
                                                    noexcept( false)
{
   if (id >= mId2Field.size())
      throw std::runtime_error( "invalid field id");
   return mId2Field[ id]->typeName();
} // end ReflectedBase::getFieldTypeString


uint16_t ReflectedBase::size() const noexcept( true)
{
   return static_cast< uint16_t>( mId2Field.size());
} // end ReflectedBase::size


ReflectedBase::ReflectedBase():
   mId2Field(),
   mName2Field()
{
} // end ReflectedBase::ReflectedBase


template< typename T>
   void ReflectedBase::addField( const std::string& name, T& value)
                               noexcept( false)
{
   if (mName2Field.find( name) != mName2Field.end())
      throw std::runtime_error( "field with this name already exists");

   field_ptr  new_field( new ReflectedField< T>( name, value));

   mId2Field.push_back( new_field);
   mName2Field.insert( name_cont_t::value_type( name, new_field));
} // end ReflectedBase::addField


} // namespace detail
} // namespace reflection
} // namespace celma


#endif   // CELMA_REFLECTION_DETAIL_REFLECTED_BASE_HPP


// ========================  END OF reflected_base.hpp  ========================

