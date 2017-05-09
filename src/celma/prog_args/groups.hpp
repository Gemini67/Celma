
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2016-2017 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
--*/


/// @file
/// See documentation of class celma::prog_args::Groups.


#ifndef CELMA_PROG_ARGS_GROUPS_HPP
#define CELMA_PROG_ARGS_GROUPS_HPP


#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include "celma/common/singleton.hpp"
#include "celma/prog_args/handler.hpp"
#include "celma/prog_args/value_handler.hpp"


namespace celma { namespace prog_args {


class Handler;


/// Allows to combine multiple argument groups.<br>
/// A possible use case could be when a program uses a library that takes some
/// parameters from the command line. Then the program's main function would get
/// its argument handler from the prog_args::Groups, and add its program
/// specific arguments there. Afterwards the library module would get its own
/// argument handler, and add its (library specific) arguments there.<br>
/// Afterwards, evalArguments() of the Groups object must be called.<br>
/// Of course, all arguments could be added to added to the same group, but if
/// multiple programs use the same library module, it may be better to have the
/// library module parameters shown in a separate block than have them mixed
/// with the program arguments.<br>
/// If special flags or other output channels for verbose and error output
/// should be passed to all handler objects, make sure the group singleton is
/// created first with these special parameters (by calling the instance()
/// method).<br>
/// Last but not least: When using argument groups, be aware that the evaluation
/// of the command line arguments may happen at a later time and/or in another
/// context. That means that the destination variables that are passed to the
/// argument Handler objects may not go out of scope, must be members of an
/// object whose lifetimes lasts at least until evalArguments() was called!
/// @since  0.13.0, 05.02.2017  (redesign to handle special parameters)
/// @since  0.2, 10.04.2016
/// @todo  Add method evalArgumentsErrorExit() like in Handler class.
class Groups: public common::Singleton< Groups>
{

   friend class common::Singleton< Groups>;

public:
   /// The type used to store an argument handler object.
   typedef std::shared_ptr< Handler>  SharedArgHndl;

   /// Set of the flags that may be set on the argument groups object, which
   /// will be passed on to each Handler object that is created afterwards.
   static const int Groups2HandlerFlags = Handler::hfVerboseArgs   |
                                          Handler::hfUsageHidden   |
                                          Handler::hfArgHidden     |
                                          Handler::hfListArgVar    |
                                          Handler::hfEndValues     |
                                          Handler::hfListArgGroups;

   /// Returns the argument handler for the specified group name.<br>
   /// If the argument handler does not exist yet, a new handler object will be
   /// created. If the handler object exists already, it must a 'plain' handler
   /// object, not a value handler.<br>
   /// The output streams will be passed as specified when calling instance()
   /// for this group object, and the flags parameter will be a combination of
   /// this object's flag and the flags passed in \a this_handler_flags.
   /// @param[in]  grpName             The symbolic name of this handler, used
   ///                                 for identification and printing the
   ///                                 usage.
   /// @param[in]  this_handler_flags  Set of flags to pass to the constructor
   ///                                 of the handler object if a new one is
   ///                                 created.
   /// @param[in]  txt1                Optional pointer to the object to provide
   ///                                 additional text for the usage.
   /// @param[in]  txt2                Optional pointer to the object to provide
   ///                                 additional text for the usage.
   /// @since  0.13.0, 05.02.2017  (renamed/merged, added parameters)
   /// @since  0.2, 10.04.2016
   SharedArgHndl getArgHandler( const std::string& grpName, 
                                int this_handler_flags = 0,
                                IUsageText* txt1 = nullptr,
                                IUsageText* txt2 = nullptr) noexcept( false);

   /// Returns the argument value handler for the specified group name.<br>
   /// If the argument handler does not exist yet, a new value handler object
   /// will be created. If the handler object exists already, it must a value
   /// handler object, not a 'plain' handler.<br>
   /// The output streams will be passed as specified when calling instance()
   /// for this group object, and the flags parameter will be a combination of
   /// this object's flag and the flags passed in \a this_handler_flags.
   /// @param[in]  grpName             The symbolic name of this value handler,
   ///                                 used for identification and printing the
   ///                                 usage.
   /// @param[in]  this_handler_flags  Set of flags to pass to the constructor
   ///                                 of the value handler object if a new one
   ///                                 is created.
   /// @param[in]  txt1                Optional pointer to the object to provide
   ///                                 additional text for the usage.
   /// @param[in]  txt2                Optional pointer to the object to provide
   ///                                 additional text for the usage.
   /// @since  0.14.0, 09.02.2017
   SharedArgHndl getArgValueHandler( const std::string& grpName, 
                                     int this_handler_flags = 0,
                                     IUsageText* txt1 = nullptr,
                                     IUsageText* txt2 = nullptr)
                                   noexcept( false);

   /// Iterates over the list of arguments and passes the elemnts to the
   /// internally stored argument handlers.<br>
   /// After all arguments were processed successfully, the function checks for
   /// missing, mandatory arguments.
   /// @param[in]  argc    Number of arguments passed to the process.
   /// @param[in]  argv[]  List of argument strings.
   /// @since  0.2, 10.04.2016
   void evalArguments( int argc, char* argv[]) noexcept( false);

   /// Needed for testing purposes, but may be used in 'normal' programs too:
   /// Removes a previously added argument handler object.
   /// @param[in]  grpName  The symbolic name of the argument handler to remove.
   /// @since  0.2, 10.04.2016
   void removeArgHandler( const std::string& grpName);

   /// Needed for testing purposes, but may be used in 'normal' programs too:
   /// Removes all previously added argument handler objects.
   /// @since  0.13.0, 05.02.2017
   void removeAllArgHandler();

   /// Checks if the specified argument is already used by one of the argument
   /// handlers.
   /// @param[in]  argChar  The argument character to check.
   /// @return  \c true if the argument is already in use.
   /// @since  0.2, 10.04.2016
   bool argumentExists( char argChar) const;

   /// Checks if the specified argument is already used by one of the argument
   /// handlers.
   /// @param[in]  argString  The argument string to check.
   /// @return  \c true if the argument is already in use.
   /// @since  0.2, 10.04.2016
   bool argumentExists( const std::string& argString) const;

   /// Returns if the current argument evaluation is controlled by an argument
   /// groups instance or not.
   /// @return  \c true if the current argument evaluation is controlled by
   ///          argument groups.
   /// @since  0.2, 10.04.2016
   bool evaluatedByArgGroups() const;

   /// Specifies the line length to use when printing the usage.
   /// @param[in]  useLen  The new line length to use.<br>
   ///                     The value must be in the range 60 <= useLen < 240.
   /// @since  0.2, 10.04.2016
   void setUsageLineLength( int useLen);

   /// Displays the usage combined from all argument handlers.
   /// @param[in]  txt1  Pointer to the text to display before or after the
   ///                   list of arguments.
   /// @param[in]  txt2  Pointer to the text to display after the list of
   ///                   arguments.
   /// @since  0.2, 10.04.2016
   void displayUsage( IUsageText* txt1, IUsageText* txt2) const;

   /// When argument groups are used, it is necessary to check that the same
   /// argument is only used in one of the handlers.<br>
   /// This is achieved by stting the Handler::hfInGroup flag for each handler
   /// that is created. Then, when an argument is added to the handler, it calls
   /// this method.<br>
   /// Here, since we don't know which argument was the new one, compare each
   /// argument of the handler with all arguments of all the other handlers.<br>
   /// One special point is to mention: When a new Handler object is created,
   /// and a standard argument is set by this handler, this will call this
   /// method, but then the new Handler object is not yet in the internal object
   /// list.
   /// @param[in]  mod_handler  The argument Handler object to which a new
   ///                          argument was added.
   /// @since  0.13.0, 05.02.2017
   void crossCheckArguments( Handler* mod_handler) const noexcept( false);

   /// Lists the names of the argument groups.
   /// @since  013.1, 07.02.2017
   void listArgGroups();

protected:
   /// Constructor.
   /// @param[in]  os        The stream to write normal output to.
   /// @param[in]  error_os  The stream to write error output to.
   /// @param[in]  flag_set  Set of the flags to pass to all handler objects.
   /// @since  0.13.0, 05.02.2017  (added parameters)
   /// @since  0.2, 10.04.2016
   Groups( std::ostream& os = std::cout, std::ostream& error_os = std::cerr,
           int flag_set = 0);

private:
   /// Internal class used to store an argument handler with its symbolic name.
   /// @since  0.2, 10.04.2016
   class Storage
   {
   public:
      /// Constructor
      /// @param[in]  grpName  The symbolic name of the group.
      /// @param[in]  ah       The argument handler.
      /// @since  0.2, 10.04.2016
      Storage( const std::string& grpName, SharedArgHndl ah):
         mName( grpName),
         mpArgHandler( ah)
      {
      } // end Groups::Storage::Storage

      Storage( const Storage&) = default;
      Storage( Storage&&) = default;
      ~Storage() = default;
      Storage& operator =( const Storage&) = default;
      Storage& operator =( Storage&&) = default;

      /// The symbolic name of the argument handler.
      std::string    mName;
      /// Pointer to the argument handler object.
      SharedArgHndl  mpArgHandler;

   }; // Storage

   /// Container to store the argument handlers.
   typedef std::vector< Storage>  ArgHandlerCont;

   /// Stream to write output to.
   std::ostream&   mOutput;
   /// Stream to write error output to.
   std::ostream&   mErrorOutput;
   /// The set of flags to pass on to all handler objects that are created.
   int             mHandlerFlags;
   /// The argument handlers.
   ArgHandlerCont  mArgGroups;
   /// Set to \c true when the method evalArguments() of this class is used.
   bool            mEvaluating;
   /// The line length to use when printing the usage.
   int             mUsageLineLength;

}; // Groups


// inlined methods
// ===============


inline bool Groups::evaluatedByArgGroups() const
{
   return mEvaluating;
} // Groups::evaluatedByArgGroups


inline void Groups::setUsageLineLength( int useLen)
{
   mUsageLineLength = useLen;
} // Groups::setUsageLineLength


} // namespace prog_args
} // namespace celma


#endif   // CELMA_PROG_ARGS_GROUPS_HPP


// ============================  END OF groups.hpp  ============================

