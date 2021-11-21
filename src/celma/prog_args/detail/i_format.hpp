
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2016-2021 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
--*/


/// @file
/// See documentation of class celma::prog_args::detail::IFormat.


#pragma once


#include <string>


namespace celma::prog_args::detail {


/// Base class for value formatters.
///
/// @since  0.2, 10.04.2016
class IFormat
{
public:
   /// Empty, virtual destructor.
   ///
   /// @since  0.2, 10.04.2016
   virtual ~IFormat() = default;

   /// The method that must be implemented by the derived classes: May change
   /// the formatting of the passed value, e.g. change capitalization etc.
   ///
   /// @param[in,out]  val  The value to change the formatting of.
   /// @since  0.2, 10.04.2016
   virtual void formatValue( std::string& val) const = 0;

   /// Returns the description/name of the formatter.
   ///
   /// @return
   ///    The description or name of the formatter as given to the constructor.
   /// @since  1.33.0, 05.11.2019
   const std::string& desc() const;

protected:
   /// Constructor, stores the name of the formatter.
   ///
   /// @param[in]  desc  The description/name of the formatter.
   /// @since  1.33.0, 05.11.2019
   explicit IFormat( const std::string& desc);

private:
   /// The name or description of the formatter.
   const std::string  mDescription;

}; // IFormat


// inlined methods
// ===============


inline const std::string& IFormat::desc() const
{
   return mDescription;
} // IFormat::desc


} // namespace celma::prog_args::detail


// =====  END OF i_format.hpp  =====

