
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
/// See documentation of class celma::prog_args::IUsageText.


#ifndef CELMA_PROG_ARGS_I_USAGE_TEXT_HPP
#define CELMA_PROG_ARGS_I_USAGE_TEXT_HPP


#include "celma/prog_args/handler.hpp"


namespace celma { namespace prog_args {


/// Base class for classes that print additional information for the usage.<br>
/// Together with the following macro UsageText(), the additional usage output
/// can be created very easily.<br>
/// Example:<br>
/// - Define the text to print before the list of arguments:
///   <pre>
///      UsageText( PreArgText,
///                 "Additional text to print before the arguments"
///               );
///   </pre>
/// - Pass the information like this:<br>
///   <pre>
///      ArgumentHandler::evalArguments( argc, argv,
///                                      ArgumentHandler::upBeforeArgs,
///                                      PreArgText);
///   </pre>
///
/// @since  0.2, 10.04.2016
class IUsageText
{
public:
   /// Constructor.
   /// @param[in]  up  The position of the text, provided by this object, in the
   ///                 usage.
   /// @since  0.2, 10.04.2016
   IUsageText( Handler::UsagePos up):
      mUsagePos( up)
   {
   } // end IUsageText::IUsageText

   /// Empty, virtual destructor.
   /// @since  0.2, 10.04.2016
   virtual ~IUsageText() = default;

   /// Defines the interface function.
   /// @param[out]  os  The stream to write the output to.
   /// @since  0.2, 10.04.2016
   virtual void print( std::ostream& os) const = 0;

   /// Returns the position of the text in the usage as specified in the
   /// constructor.
   /// @return  The defined position for the text.
   /// @since  0.2, 10.04.2016
   Handler::UsagePos usagePos() const
   {
      return mUsagePos;
   } // end IUsageText::usagePos

   /// Prints the contents of the class/object derived from this base class.
   /// @param[out]  os    The stream to write to.
   /// @param[in]   pObj  Pointer to the object to dumpt the contents of.
   /// @return  The stream as passed as parameter.
   /// @since  0.2, 10.04.2016
   friend std::ostream& operator <<( std::ostream& os, IUsageText* pObj)
   {
      pObj->print( os);
      return os;
   } // end ostream& operator <<

private:
   /// The position of the text in the usage.
   const Handler::UsagePos  mUsagePos;

}; // end IUsageText


} // namespace prog_args
} // namespace celma


/// Macro to easily define the output function.<br>
/// Actually creates a class called \<c\>_class which contains the required
/// print() method, as well a static, global variable called c (of type
/// \<c\>_class) which can then be passed to evalArguments().
/// @param  c  The name of the class/object to create.
/// @param  p  The position of the text in the usage (see enum UsagePos in class
///            ArgumentHandler)
/// @param  t  The text to print.
/// @since  0.2, 10.04.2016
#define UsageText( c, p, t) \
   class c ## _class : public celma::prog_args::IUsageText \
   { \
   public: \
      c ## _class( celma::prog_args::Handler::UsagePos up): \
         celma::prog_args::IUsageText( up) { } \
      virtual void print( std::ostream& os) const \
      { \
         os << t; \
      } \
   }; \
   static c ## _class*  c = new c ## _class ( celma::prog_args::Handler:: p)


#endif   // CELMA_PROG_ARGS_I_USAGE_TEXT_HPP


// =========================  END OF i_usage_text.hpp  =========================

