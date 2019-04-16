
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2019 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
--*/


/// @file
/// See documentation of class celma::prog_args::detail::@@@.


#ifndef CELMA_PROG_ARGS_DETAIL_EVAL_ARGUMENTS_ERROR_EXIT_HPP
#define CELMA_PROG_ARGS_DETAIL_EVAL_ARGUMENTS_ERROR_EXIT_HPP


#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <string>
#include <boost/lexical_cast.hpp>


namespace celma { namespace prog_args { namespace detail {


/// Unified evaluation of program arguments and error handling for single
/// argument handlers as well as argument groups.<br>
/// Calls evalArguments() of the given object, handles and repoerts all errors
/// (exceptions) and exits in case of an error.
///
/// @tparam  T  The type of the object to call evalArguments() on.
/// @param[in]  arg_obj
///    The object to call evalArguments() on.
/// @param[in]  err_out
///    The stream to write error messages to.
/// @param[in]  argc
///    Number of arguments passed to the program.
/// @param[in]  argv
///    List of argument strings.
/// @param[in]  prefix
///    Prefix to print before the error messages.
/// @since
///    x.y.z, 16.04.2019  (extracted from handler)
template< typename T>
   void evalArgumentsErrorExit( T& arg_obj, std::ostream& err_out, int argc,
      char* argv[], const std::string& prefix)
{

   try
   {

      arg_obj.evalArguments( argc, argv);
      return;   // return here, easier error exit below

   } catch (const std::invalid_argument& ia)
   {
      err_out << prefix << "Caught 'invalid argument' exception: " << ia.what()
         << "!" << std::endl;
   } catch (const std::out_of_range& re)
   {
      err_out << prefix << "Caught 'range error' exception: " << re.what()
         << "!" << std::endl;
   } catch (const std::logic_error& le)
   {
      err_out << prefix << "Caught 'logic error' exception: " << le.what()
         << "!" << std::endl;
   } catch (const std::overflow_error& oe)
   {
      err_out << prefix << "Caught 'overflow' exception: " << oe.what() << "!"
         << std::endl;
   } catch (const std::underflow_error& ue)
   {
      err_out << prefix << "Caught 'underflow' exception: " << ue.what() << "!"
         << std::endl;
   } catch (const std::runtime_error& rte)
   {
      err_out << prefix << "Caught 'runtime error' exception: " << rte.what()
         << "!" << std::endl;
   } catch (const boost::bad_lexical_cast& blc)
   {
      err_out << prefix << "Caught boost " << blc.what() << "!" << std::endl;
   } catch (const std::exception& e)
   {
      err_out << prefix << "Caught unspecific std::exception: " << e.what()
         << "!" << std::endl;
   } catch (...)
   {
      err_out << prefix << "Caught unknown exception!" << std::endl;
   } // end try

   ::exit( EXIT_FAILURE);
} // evalArgumentsErrorExit


} // namespace detail
} // namespace prog_args
} // namespace celma


#endif   // CELMA_PROG_ARGS_DETAIL_EVAL_ARGUMENTS_ERROR_EXIT_HPP


// =====  END OF eval_arguments_error_exit.hpp  =====

