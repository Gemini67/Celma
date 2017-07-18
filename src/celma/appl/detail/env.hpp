
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
/// See documentation of class celma::appl::detail::@@@.


#ifndef CELMA_APPL_DETAIL_ENV_HPP
#define CELMA_APPL_DETAIL_ENV_HPP


#include <string>


namespace celma { namespace appl { namespace detail {


/// @since  x.y.z, 12.12.2016
class env
{
public:
   /// Constructor. Stores the name of the property.
   /// @param[in]  name  The name of the property.
   /// @since  x.y.z, 12.12.2016
   explicit env( const std::string& var_name):
      mEnvVarName( var_name)
   {
   } // 

   /// Returns the internally stored name of the custom property.
   /// @return  The name of the property.
   /// @since  x.y.z, 12.12.2016
   const std::string& getVarName() const
   {
      return mEnvVarName;
   } // 
   
private:
   /// The name of the property.
   const std::string  mEnvVarName;
   
}; // env



} // namespace detail
} // namespace appl
} // namespace celma


#endif   // CELMA_APPL_DETAIL_ENV_HPP


// =============================  END OF env.hpp  =============================

