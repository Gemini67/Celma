
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2017-2019 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
--*/


/// @file
/// See documentation of class celma::prog_args::ValueHandler.


#ifndef CELMA_PROG_ARGS_VALUE_HANDLER_HPP
#define CELMA_PROG_ARGS_VALUE_HANDLER_HPP


#include <map>
#include <memory>
#include <stdexcept>
#include <string>
#include "celma/prog_args.hpp"
#include "celma/prog_args/detail/argument_value.hpp"


namespace celma { namespace prog_args {


/// Extension of the Handler class that creates and stores the destination
/// variables itself.
/// Use this class e.g. in a library module that wants to support setting values
/// through command line arguments, but does not have a global object that
/// persists. Then, create an object of this value handler class in the
/// prog_args::Groups, specify the arguments with the type of the destination
/// variables, and that's it. Later, when the values from the command line
/// arguments are required, retrieve the value handler object again from the
/// Groups, and extract the values.<br>
/// This class seems to offer some types less than the original Handler class,
/// but actually most types can (here) be handled by the simple template
/// parameter type \c T.<br>
/// In a value handler object, all arguments must be set to use a destination
/// variable in this object, tho ensure that the corresponding methods of the
/// base Handler class are hidden here.
///
/// @since  0.14.0, 09.02.2017
class ValueHandler: public Handler
{
public:
   /// Constructor.
   ///
   /// @param[in]  flagSet
   ///    The set of flags. See enum HandleFlags for a list of possible values.
   /// @param[in]  txt1
   ///    Optional pointer to the object to provide additional text for the
   ///    usage.
   /// @param[in]  txt2
   ///    Optional pointer to the object to provide additional text for the
   ///    usage.
   /// @since  0.14.0, 09.02.2017
   explicit ValueHandler( int flagSet = Handler::hfHelpShort | Handler::hfHelpLong,
      IUsageText* txt1 = nullptr, IUsageText* txt2 = nullptr);

   /// Constructor that allows to specify the output streams to write to.
   ///
   /// @param[in]  os
   ///    The stream to write normal output to.
   /// @param[in]  error_os
   ///    The stream to write error output to.
   /// @param[in]  flag_set
   ///    The set of flags. See enum HandleFlags for a list of possible values.
   /// @param[in]  txt1
   ///    Optional pointer to the object to provide additional text for the
   ///    usage.
   /// @param[in]  txt2
   ///    Optional pointer to the object to provide additional text for the
   ///    usage.
   /// @since  0.14.0, 09.02.2017
   ValueHandler( std::ostream& os, std::ostream& error_os,
      int flag_set = Handler::hfHelpShort | Handler::hfHelpLong,
      IUsageText* txt1 = nullptr,
      IUsageText* txt2 = nullptr);

   // default destructor will do just fine
   virtual ~ValueHandler() = default;

   // don't want to allow copying nor assignment
   ValueHandler( const ValueHandler&) = delete;
   ValueHandler& operator =( const ValueHandler&) = delete;

   /// Add an argument to the argument handler, where the destination variable
   /// is managed by this class.
   /// This method is used for single-value-types like PODs, std::string etc.
   ///
   /// @tparam  T  The type of the argument value to handle.
   /// @param[in]  args
   ///    The arguments on the command line for this argument.
   /// @param[in]  desc
   ///    The description of this argument for the usage.
   /// @return
   ///    The object managing this argument, may be used to apply further
   ///    settings.
   /// @since  0.14.0, 10.02.2017
   template< typename T>
      typename std::enable_if< !detail::ContainerAdapter< T>::HasAdapter,
         detail::TypedArgBase*>::type
      addValueArgument( const std::string& args, const std::string& desc)
         noexcept( false)
   {

      auto  value = std::make_shared< detail::ArgumentValue< T>>();

      mValues.insert( container_t::value_type( detail::ArgumentKey( args), value));
      return Handler::addArgument(
         args, new detail::TypedArg< T>( (*value)(), "unnamed"), desc);
   } // ValueHandler::addValueArgument

   /// Add an argument to the argument handler, where the destination variable
   /// is managed by this class.
   /// This method is used for types that can store multiple values.
   ///
   /// @tparam  T  The type of the argument value to handle.
   /// @param[in]  args
   ///    The arguments on the command line for this argument.
   /// @param[in]  desc
   ///    The description of this argument for the usage.
   /// @return
   ///    The object managing this argument, may be used to apply further
   ///    settings.
   /// @since  x.y., 29.11.2019
   template< typename T>
      typename std::enable_if< detail::ContainerAdapter< T>::HasAdapter,
         detail::TypedArgBase*>::type
      addValueArgument( const std::string& args, const std::string& desc)
         noexcept( false)
   {

      auto  value = std::make_shared< detail::ArgumentValue< T>>();

      mValues.insert( container_t::value_type( detail::ArgumentKey( args), value));
      detail::ContainerAdapter< T>  wrapper( (*value)());
      return Handler::addArgument(
         args, new detail::TypedArg< detail::ContainerAdapter< T>>( wrapper,
         "unnamed"), desc);
   } // ValueHandler::addValueArgument

   /// Add a free argument to the argument handler, where the destination
   /// variable is managed by this class.
   ///
   /// @tparam  T  The type of the argument value to handle.
   /// @param[in]  desc  The description of this argument for the usage.
   /// @return
   ///    The object managing this argument, may be used to apply further
   ///    settings.
   /// @since  0.14.0, 10.02.2017
   template< typename T>
      detail::TypedArgBase* addValueArgument( const std::string& desc)
         noexcept( false);

   /// Add an argument that accepts a range string as value.
   ///
   /// @tparam  T
   ///    The type of the values to generate from the range string.
   /// @tparam  C
   ///    The type of the container to store the values in.
   /// @param[in]  args
   ///    The arguments on the command line for this argument.
   /// @param[in]  desc
   ///    The description of this argument for the usage.
   /// @return
   ///    The object managing this argument, may be used to apply further
   ///    settings.
   /// @since  0.14.0, 21.02.2017
   template< typename T, typename C>
      detail::TypedArgBase* addRangeValueArgument( const std::string& args,
                                                   const std::string& desc)
                                                 noexcept( false);

   /// Add a free argument that accepts a range string as value.
   ///
   /// @tparam  T
   ///    The type of the values to generate from the range string.
   /// @tparam  C
   ///    The type of the container to store the values in.
   /// @param[in]  desc  The description of this argument for the usage.
   /// @return
   ///    The object managing this argument, may be used to apply further
   ///    settings.
   /// @since  0.14.0, 21.02.2017
   template< typename T, typename C>
      detail::TypedArgBase* addRangeValueArgument( const std::string& desc)
                                                 noexcept( false);


   /// Adds a sub-group.
   /// Note: Theoretically we could pass the object by reference, but then the
   /// compiler cannot distinguish anymore between this function and the variant
   /// to add an argument resulting in a function call.
   ///
   /// @param[in]  arg_spec
   ///    The arguments on the command line to enter/start the sub-group.
   /// @param[in]  subGroup
   ///    The object to handle the sub-group arguments.
   /// @param[in]  desc
   ///    The description of this sub-group argument.
   /// @return
   ///    The object managing this argument, may be used to apply further
   ///    settings.
   /// @since  0.14.0, 15.03.2017
   detail::TypedArgBase* addArgument( const std::string& arg_spec,
      ValueHandler* subGroup, const std::string& desc);

   /// Use this function to get the value that was set by the argument on the
   /// command line.
   /// To check if a non-mandatory argument was really set, use the
   /// Handler::getArgHandler() method and then check hasValue() from the
   /// (TypedArgBase) pointer returned.
   ///
   /// @tparam  T  The type of the value.
   /// @param[out]  dest
   ///    Returns the value.
   /// @param[in]   args
   ///    The command line argument(s).
   /// @since  0.14.0, 10.02.2017
   template< typename T>
      void getValue( T& dest, const std::string& args) const noexcept( false);

   /// Use this function to get the free value that was set on the command
   /// line.
   /// To check if a non-mandatory, free argument was really set, use the
   /// Handler::getArgHandler() method with '-' as the argument key, and then
   /// check hasValue() from the (TypedArgBase) pointer returned.
   ///
   /// @tparam  T  The type of the value.
   /// @param[out]  dest  Returns the value.
   /// @since  0.14.0, 10.02.2017
   template< typename T> void getValue( T& dest) const noexcept( false);

   /// Returns if this object is a value handler.
   ///
   /// @return  In this class, always \c true.
   /// @since  0.14.0, 21.02.2017
   bool isValueHandler() const override;

   /// Returns this object.
   ///
   /// @return  This object.
   /// @since  0.14.0, 15.03.2017
   ValueHandler* getValueHandlerObj() noexcept( false) override;

private:
   /// Type used to store the destination variables.
   using shared_value_storage_t = std::shared_ptr< common::AnyBase>;
   /// Container used to store the destination variables.
   using container_t = std::map< detail::ArgumentKey, shared_value_storage_t>;

   /// Hidden when value handler is used.
   template< typename T>
      detail::TypedArgBase* addArgument( const std::string&,
                                         T&,
                                         const std::string,
                                         const std::string&);

   /// Hidden when value handler is used.
   detail::TypedArgBase* addArgument( const std::string& arg_spec,
                                      Handler* subGroup,
                                      const std::string& desc);

   /// The container with the destination variables.
   container_t  mValues;

}; // ValueHandler


// inlined methods
// ===============


template< typename T>
   detail::TypedArgBase*
      ValueHandler::addValueArgument( const std::string& desc) noexcept( false)
{
   return addValueArgument< T>( "-", desc);
} // ValueHandler::addValueArgument


template< typename T, typename C>
   detail::TypedArgBase*
      ValueHandler::addRangeValueArgument( const std::string& args,
         const std::string& desc) noexcept( false)
{

   auto  value = std::make_shared< detail::ArgumentValue< C>>();

   mValues.insert( container_t::value_type( detail::ArgumentKey( args), value));
   return Handler::addArgument(
      args,
      new detail::TypedArgRange< T, C>( common::RangeDest< T, C>( (*value)()),
         "unnamed"), desc);
} // ValueHandler::addRangeValueArgument


template< typename T, typename C>
   detail::TypedArgBase*
      ValueHandler::addRangeValueArgument( const std::string& desc)
         noexcept( false)
{
   return addRangeValueArgument< T, C>( "-", desc);
} // ValueHandler::addRangeValueArgument


template< typename T>
   void ValueHandler::getValue( T& dest, const std::string& args) const
      noexcept( false)
{

   auto  value_iter = mValues.find( detail::ArgumentKey( args));

   if (value_iter == mValues.end())
      throw std::invalid_argument( "unknown argument '" + args + "'");

   auto  type_name_access = value_iter->second.get();

   if (type_name_access->getTypeNameBase()->getTypeName() != type< T>::name())
      throw std::invalid_argument( "type mismatch");

   auto  value_obj = static_cast< detail::ArgumentValue< T>*>( type_name_access);
   dest = (*value_obj)();

} // ValueHandler::getValue


template< typename T> void ValueHandler::getValue( T& dest) const noexcept( false)
{
   getValue( dest, "-");
} // ValueHandler::getValue


} // namespace prog_args
} // namespace celma


#endif   // CELMA_PROG_ARGS_VALUE_HANDLER_HPP


// =====  END OF value_handler.hpp  =====

