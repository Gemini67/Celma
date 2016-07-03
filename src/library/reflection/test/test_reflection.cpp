
#include "address_record.hpp"

#include <iostream>


int main()
{

   AddressRecord           addr1;
   ReflectedAddressRecord  r_addr1( addr1);

   r_addr1.set( std::string( "Name"), std::string( "Eng"));
   r_addr1.set( std::string( "FirstName"), std::string( "Rene"));
   r_addr1.set( std::string( "PostalCode"), 5037);

   std::cout << "Name = " << r_addr1.get< std::string>( std::string( "Name"))
             << std::endl << std::endl;

   for (uint16_t i = 0; i < r_addr1.size(); ++i)
   {
      std::cout << r_addr1.getFieldNameReflected( i) << " = "
                << r_addr1.getFieldValueString( i) << " ["
                << r_addr1.getFieldTypeString( i)  << "]" << std::endl;
   } // end for

}
