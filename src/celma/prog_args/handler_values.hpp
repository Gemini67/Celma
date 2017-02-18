
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2017 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
--*/


/// @file
/// See documentation of class celma::prog_args::@@@.


#ifndef CELMA_PROG_ARGS_HANDLER_VALUES_HPP
#define CELMA_PROG_ARGS_HANDLER_VALUES_HPP


#include <map>
#include <memory>
#include <stdexcept>
#include <string>
#include "celma/prog_args/handler.hpp"
#include "celma/prog_args/detail/value_storage.hpp"
#include "celma/prog_args/detail/argument_value.hpp"


namespace celma { namespace prog_args {


/// @since  x.y.z, 09.02.2017
class HandlerValues: private Handler
{
public:
   explicit HandlerValues( int flagSet = Handler::hfHelpShort | Handler::hfHelpLong,
                           IUsageText* txt1 = nullptr,
                           IUsageText* txt2 = nullptr);

   HandlerValues( std::ostream& os, std::ostream& error_os,
                  int flag_set = Handler::hfHelpShort | Handler::hfHelpLong,
                  IUsageText* txt1 = nullptr,
                  IUsageText* txt2 = nullptr);

   ~HandlerValues() = default;
   HandlerValues( const HandlerValues&) = delete;
   HandlerValues& operator =( const HandlerValues&) = delete;

   template< typename T>
      detail::TypedArgBase* addValueArgument( const std::string& args,
                                              const std::string desc)
                                            noexcept( false);

   /// @since  x.y.z, 10.02.2017
   template< typename T>
      detail::TypedArgBase* addValueArgument( const std::string desc)
                                            noexcept( false);

   /// Iterates over the list of arguments and their values and stores the
   /// values in the corresponding destination variables.<br>
   /// The function also checks for missing, mandatory arguments, arguments
   /// wrongly used without a value etc. If an invalid value is passed for an
   /// argument, or if a mandatory argument is missing etc., an exception is
   /// thrown.
   /// @param[in]  argc    Number of arguments passed to the process.
   /// @param[in]  argv[]  List of argument strings.
   /// @throw  Exception as described above.
   /// @since  x.y.z, 09.02.2017
   void evalArguments( int argc, char* argv[]) noexcept( false);

   /// Same as evalArguments(). Difference is that this method catches
   /// exceptions, reports them on stderr and then exits the program.<br>
   /// In other words: If the function returns, all argument requirements and
   /// constraints were met.
   /// @param[in]  argc    Number of arguments passed to the process.
   /// @param[in]  argv    List of argument strings.
   /// @param[in]  prefix  Prefix text to print before the error message.<br>
   ///                     The prefix may be an empty string. If not, add a
   ///                     space at the end as separator to the following text.
   /// @since  x.y.z, 09.02.2017
   void evalArgumentsErrorExit( int argc, char* argv[],
                                const std::string& prefix);

   template< typename T>
      void getValue( T& dest, const std::string& args) const noexcept( false);

   /// @since  x.y.z, 10.02.2017
   template< typename T> void getValue( T& dest) const noexcept( false);

private:
   typedef std::shared_ptr< detail::ValueStorage>  shared_value_storage_t;
   typedef std::map< detail::ArgumentKey, shared_value_storage_t>  container_t;

   container_t  mValues;

}; // HandlerValues


// inlined methods
// ===============


template< typename T>
   detail::TypedArgBase* HandlerValues::addValueArgument( const std::string& args,
                                                          const std::string desc)
                                                        noexcept( false)
{

   auto  value = std::make_shared< detail::ArgumentValue< T>>();

   mValues.insert( container_t::value_type( detail::ArgumentKey( args), value));
   return addArgument( args, (*value)(), "unnamed", desc);
}


template< typename T>
   detail::TypedArgBase* HandlerValues::addValueArgument( const std::string desc)
                                                        noexcept( false)
{
   return addValueArgument< T>( "-", desc);
}


template< typename T>
   void HandlerValues::getValue( T& dest, const std::string& args) const
                               noexcept( false)
{

   auto  value_iter = mValues.find( detail::ArgumentKey( args));

   if (value_iter == mValues.end())
      throw std::invalid_argument( "unknown argument '" + args + "'");
   if (!value_iter->second->isSameType( type< T>::name()))
      throw std::invalid_argument( "type mismatch");

   detail::ValueStorage*       storage = value_iter->second.get();
   detail::ArgumentValue< T>*  value_obj = reinterpret_cast< detail::ArgumentValue< T>*>( storage);
   dest = (*value_obj)();

}


template< typename T> void HandlerValues::getValue( T& dest) const noexcept( false)
{
   getValue( dest, "-");
}


} // namespace prog_args
} // namespace celma


#endif   // CELMA_PROG_ARGS_HANDLER_VALUES_HPP


// ========================  END OF handler_values.hpp  ========================

