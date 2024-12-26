
#include "celma/appl/appl_main.hpp"

#include <iostream>


class Application final: public celma::appl::ApplBase
{
public:
   void mainLoop() override
   {
      std::cout << "Hello world!" << std::endl;
   }

};



MAIN( Application)

