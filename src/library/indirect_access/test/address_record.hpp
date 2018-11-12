
#ifndef ADDRESS_RECORD_HPP
#define ADDRESS_RECORD_HPP


#include <string>
#include "celma/indirect_access/indirect_access.hpp"


#define  ADDRESS_RECORD_FIELDS(FIELD) \
   FIELD( std::string, Name) \
   FIELD( std::string, FirstName) \
   FIELD( int,         PostalCode)


INDIRECT_ACCESS( AddressRecord, ADDRESS_RECORD_FIELDS);


#endif   // ADDRESS_RECORD_HPP
