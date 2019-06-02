
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2016-2019 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
--*/


/// @file
/// See documentation of templates celma::common::MultiSetter2<> and
/// celma::common::MultiSetter3<>.


#ifndef CELMA_COMMON_MULTI_SETTER_HPP
#define CELMA_COMMON_MULTI_SETTER_HPP


#include <string>
#include <boost/lexical_cast.hpp>


namespace celma { namespace common {


namespace detail {


/// All that's needed to store a reference with the value to assign.
/// @tparam  T  The type of the variable to handle.
/// @since  0.2, 10.04.2016
template< typename T> class DestVarHolder
{
public:
   /// Constructor.
   /// @param[in]  dest   The variable to set the value on.
   /// @param[in]  vname  The name of the variable (for error reporting).
   /// @param[in]  value  The value to set in assign().
   /// @since  0.2, 10.04.2016
   DestVarHolder( T& dest, const std::string vname, const T& value):
      mDestVar( dest),
      mVarName( vname),
      mValue( value)
   {
   } // end DestVarHolder< T>::DestVarHolder

#if __cplusplus >= 201103L
   DestVarHolder( const DestVarHolder< T>&) = default;
   ~DestVarHolder() = default;
#endif

   /// Assigns the value defined in the constructor to the variable.
   /// @since  0.2, 10.04.2016
   void assign()
   {
      mDestVar = boost::lexical_cast< T>( mValue);
   } // end DestVarHolder< T>::assign

private:
   /// Reference of the destination variable to store the value in.
   T&                 mDestVar;
   /// The name of the variable to store the second value in.
   const std::string  mVarName;
   /// The value to set in the second variable.<br>
   /// Must be copied when the object is created, otherwise we risk keeping a
   /// reference to a temporary value/variable.
   const T            mValue;

}; // DestVarHolder< T>


} // namespace detail


/// Template to use together with the class celma::prog_args::Handler:<br>
/// When assign is called, sets the passed value on the first variable, and sets
/// the value specified in the constructor on the second variable.
/// @tparam  T1  The type of the first variable.
/// @tparam  T2  The type of the second variable.
/// @since  0.2, 10.04.2016
template< typename T1, typename T2> class MultiSetter2
{
public:
   /// Constructor.
   /// @param[in]  dest1   The first variable to set a value on.
   /// @param[in]  vname1  The name of the first variable.
   /// @param[in]  dest2   The second variable to set a value on.
   /// @param[in]  vname2  The name of the second variable.
   /// @param[in]  value2  The value to set on the second variable.
   /// @since  0.2, 10.04.2016
   MultiSetter2( T1& dest1, const std::string vname1,
                 T2& dest2, const std::string vname2, const T2& value2):
      mDestVar1( dest1),
      mVarName1( vname1),
      mDestVar2( dest2, vname2, value2)
   {
   } // end MultiSetter2< T1, T2>::MultiSetter2

   MultiSetter2( const MultiSetter2< T1, T2>&) = default;
   ~MultiSetter2() = default;

   /// Assigns the specified value to the first variable, and the value
   /// specified in the constructor to the second variable.
   /// @param[in]  value1
   ///    The value to assign.
   /// @param[in]  inverted
   ///    Ignored.
   /// @since  1.27.0, 27.05.2019
   ///    (added parameter inverted)
   /// @since  0.2, 10.04.2016
   void assign( const std::string& value1, bool /* inverted */)
   {
      mDestVar1 = boost::lexical_cast< T1>( value1);
      mDestVar2.assign();
   } // end MultiSetter2< T1, T2>::assign

private:
   /// Reference of the destination variable to store the value in.
   T1&                         mDestVar1;
   /// The name of the variable to store the second value in.
   const std::string           mVarName1;
   /// Reference of the destination variable to store the value in.
   detail::DestVarHolder< T2>  mDestVar2;

}; // MultiSetter2< T1, T2>


/// Template to use together with the class celma::prog_args::Handler:<br>
/// When assign is called, sets the passed value on the first variable, and sets
/// the values specified in the constructor on the second and third variable.
/// @tparam  T1  The type of the first variable.
/// @tparam  T2  The type of the second variable.
/// @tparam  T3  The type of the third variable.
/// @since  0.2, 10.04.2016
template< typename T1, typename T2, typename T3> class MultiSetter3:
   private MultiSetter2< T1, T2>
{
public:
   /// Constructor.
   /// @param[in]  dest1   The first variable to set a value on.
   /// @param[in]  vname1  The name of the first variable.
   /// @param[in]  dest2   The second variable to set a value on.
   /// @param[in]  vname2  The name of the second variable.
   /// @param[in]  value2  The value to set on the second variable.
   /// @param[in]  dest3   The third variable to set a value on.
   /// @param[in]  vname3  The name of the third variable.
   /// @param[in]  value3  The value to set on the third variable.
   /// @since  0.2, 10.04.2016
   MultiSetter3( T1& dest1, const std::string vname1,
                 T2& dest2, const std::string vname2, const T2& value2,
                 T3& dest3, const std::string vname3, const T3& value3):
      MultiSetter2< T1, T2>( dest1, vname1, dest2, vname2, value2),
      mDestVar3( dest3, vname3, value3)
   {
   } // end MultiSetter3< T1, T2, T3>::MultiSetter3

   MultiSetter3( const MultiSetter3< T1, T2, T3>&) = default;
   ~MultiSetter3() = default;

   /// Assigns the specified value to the first variable, and the values
   /// specified in the constructor to the second and third variable.
   /// @param[in]  value1
   ///    The value to assign.
   /// @param[in]  inverted
   ///    Ignored.
   /// @since  1.27.0, 27.05.2019
   ///    (added parameter inverted)
   /// @since  0.2, 10.04.2016
   void assign( const std::string& value1, bool /* inverted */)
   {
      MultiSetter2< T1, T2>::assign( value1, false);
      mDestVar3.assign();
   } // end MultiSetter3< T1, T2, T3>::assign

private:
   /// Reference of the third destination variable to store the value in.
   detail::DestVarHolder< T3>  mDestVar3;

}; // MultiSetter3< T1, T2, T3>


} // namespace common
} // namespace selma


#define DEST_MULTI_SETTER2( dv1, dv2, val2)  dv1, #dv1, dv2, #dv2, val2
#define DEST_MULTI_SETTER3( dv1, dv2, val2, dv3, val3)  \
   dv1, #dv1, dv2, #dv2, val2, dv3, #dv3, val3


#endif   // CELMA_COMMON_MULTI_SETTER_HPP


// =====  END OF multi_setter.hpp  =====

