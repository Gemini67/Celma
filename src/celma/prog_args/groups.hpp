
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2016 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
--*/


/// @file
/// See documentation of class celma::prog_args::Groups.


#ifndef CELMA_PROG_ARGS_GROUPS_HPP
#define CELMA_PROG_ARGS_GROUPS_HPP


#include <string>
#include <vector>
#include <memory>
#include "celma/common/singleton.hpp"
#include "celma/prog_args/handler.hpp"


namespace celma { namespace prog_args {


class Handler;


/// Allows to combine multiple argument groups.<br>
/// A possible use case could be when a program uses a library that takes some
/// parameters from the command line. Then the program would initialise its
/// argument handler and add its program specific arguments, the library would
/// create its own argument handler and add its (library specific) arguments,
/// and both add their argument handlers to the argument groups instance.<br>
/// Afterwards, evalArguments() of the Groups object must be called.
/// @since  0.2, 10.04.2016
/// @todo  Add method evalArgumentsErrorExit() like in Handler class.
class Groups: public common::Singleton< Groups>
{

   friend class common::detail::StaticSingletonCreator< Groups>;

public:
   /// The type used to store an argument handler object.
   typedef std::shared_ptr< Handler>  SharedArgHndl;

   /// Adds an argument handler to the internal list.<br>
   /// All arguments that this handler supports should already be set, so the
   /// class can check that there are no duplicates.
   /// @param[in]  grpName  The symbolic name of this handler, used for
   ///                      identification and printing the usage.
   /// @param[in]  ah       The argument handler to add.
   /// @since  0.2, 10.04.2016
   void addArgHandler( const std::string& grpName, SharedArgHndl ah);

   /// Returns the handler stored with the given symbolic name.
   /// @param[in]  grpName  The name of the handler.
   /// @return  Pointer to the handler object, NULL if no object with this name
   ///          was found.
   /// @since  0.2, 10.04.2016
   SharedArgHndl getHandler( const std::string& grpName) const;

   /// Iterates over the list of arguments and passes the elemnts to the
   /// internally stored argument handlers.<br>
   /// After all arguments were processed successfully, the function checks for
   /// missing, mandatory arguments.
   /// @param[in]  argc    Number of arguments passed to the process.
   /// @param[in]  argv[]  List of argument strings.
   /// @since  0.2, 10.04.2016
   void evalArguments( int argc, char* argv[]);

   /// Needed for testing purposes, but may be used in 'normal' programs too:
   /// Removes a previously added argument handler object.
   /// @param[in]  grpName  The symbolic name of the argument handler to remove.
   /// @since  0.2, 10.04.2016
   void removeArgHandler( const std::string& grpName);

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

protected:
   /// Constructor.
   /// @since  0.2, 10.04.2016
   Groups();

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
      ~Storage() = default;
      Storage& operator =( const Storage&) = default;

      /// The symbolic name of the argument handler.
      std::string    mName;
      /// Pointer to the argument handler object.
      SharedArgHndl  mpArgHandler;

   }; // Storage

   /// Container to store the argument handlers.
   typedef std::vector< Storage>  ArgHandlerCont;

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
} // end Groups::evaluatedByArgGroups


inline void Groups::setUsageLineLength( int useLen)
{
   mUsageLineLength = useLen;
} // end Groups::setUsageLineLength


} // namespace prog_args
} // namespace celma


#endif   // CELMA_PROG_ARGS_GROUPS_HPP


// =========================  END OF groups.hpp  =========================

