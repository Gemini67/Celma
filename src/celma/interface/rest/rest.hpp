
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2023 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
--*/


/// @file
/// See documentation of class celma::interface::rest::@@@.


#pragma once


#include <boost/asio.hpp>
#include <boost/beast.hpp>

#include <iostream>


namespace celma::interface::rest {


using namespace boost::asio;
using namespace boost::beast;
using tcp = boost::asio::ip::tcp;


void handle_request( http::request< http::string_body>& request,
   tcp::socket& socket)
{

   // implement the logic for each API endpoint
   if ((request.method() == http::verb::get) && (request.target() == "/hello"))
   {
      http::response< http::string_body>  response{ http::status::ok, request.version()};
 
      response.set(http::field::server, BOOST_BEAST_VERSION_STRING);
      response.set(http::field::content_type, "text/plain");
      response.keep_alive(request.keep_alive());
      response.body() = "Hello, world!";
      response.prepare_payload();
      http::write(socket, response);
   }
}


void handle_connection( tcp::socket&& socket)
{

   http::request_parser< http::string_body>  parser;
   flat_buffer buffer;

std::cerr << "read request from socket" << std::endl;
   http::read(socket, buffer, parser);
std::cerr << "handle request" << std::endl;
   handle_request(parser.get(), socket);
std::cerr << "shutdown connection" << std::endl;
   socket.shutdown(tcp::socket::shutdown_send);
   socket.close();

}


void rest()
{

   io_context     io_context;
   tcp::acceptor  acceptor( io_context, tcp::endpoint(tcp::v4(), 8080));

   for (;;)
   {
      tcp::socket  socket( io_context);
      acceptor.accept(socket);
std::cerr << "connected!" << std::endl;
      boost::asio::post( io_context, [&]
      {
         std::cerr << "call handle connection" << std::endl;
         handle_connection( std::move( socket));
      });
   }

}


} // namespace celma::interface::rest


// =====  END OF rest.hpp  =====

