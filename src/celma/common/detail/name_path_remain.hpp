
/*==
**
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
/// See documentation of class celma::common::detail::NamePathRemain.


#ifndef CELMA_COMMON_DETAIL_NAME_PATH_REMAIN_HPP
#define CELMA_COMMON_DETAIL_NAME_PATH_REMAIN_HPP


#include <string>


namespace celma { namespace common { namespace detail {


/// Helper class used to split a property path into the first name and the
/// remaining path.
///
/// @since  1.22.0, 19.10.2016
class NamePathRemain
{
public:
   /// Returns if the specified string contains a separator, making it a path.
   ///
   /// @param[in]  name
   ///    The name to check for the separator.
   /// @param[in]  separator
   ///    The separator character to check for.
   /// @return  \c true if \a name contains the \a separator.
   /// @since  1.22.0, 19.10.2016
   static bool nameHasSeparator( const std::string& name, char separator);

   /// Constructor.<br>
   /// Tries to split the \a name into the first name and the remaining path.
   ///
   /// @param[in]  name
   ///    The property path to handle.
   /// @param[in]  separator
   ///    The separator character.
   /// @since  1.22.0, 19.10.2016
   NamePathRemain( const std::string& name, char separator);

   /// Should not be needed, but when, the default is okay.
   NamePathRemain( const NamePathRemain&) = default;
   /// Should not be needed, but when, the default is okay.
   NamePathRemain& operator =( const NamePathRemain&) = default;
   /// Default destructor is fine.
   ~NamePathRemain() = default;

   /// Returns the first name as extracted in the constructor.
   ///
   /// @return  The first name.
   /// @since  1.2, 19.10.2016
   const std::string& firstName() const;

   /// Returns the remaining path as extracted in the constructor.
   ///
   /// @return  The remaining path.
   /// @since  1.2, 19.10.2016
   const std::string& remain() const;

private:
   /// The first name found in the path.
   std::string  mFirstName;
   /// The remaining path.
   std::string  mRemain;

}; // NamePathRemain


// inlined methods
// ===============


inline bool NamePathRemain::nameHasSeparator( const std::string& name,
                                              char separator)
{
   return name.find( separator) != std::string::npos;
} // NamePathRemain::nameHasSeparator


inline const std::string& NamePathRemain::firstName() const
{
   return mFirstName;
} // NamePathRemain::firstName


inline const std::string& NamePathRemain::remain() const
{
   return mRemain;
} // NamePathRemain::remain


} // namespace detail
} // namespace common
} // namespace celma


#endif   // CELMA_COMMON_DETAIL_NAME_PATH_REMAIN_HPP


// =====  END OF name_path_remain.hpp  =====

