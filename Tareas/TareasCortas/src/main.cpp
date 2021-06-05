// Copyright 2021 Luis Eduardo Rojas. Universidad de Costa Rica. CC BY 4.0

#include <signal.h>

#include <iostream>
#include <sstream>

#include "HttpAplication.hpp"
#include "EchoApp.hpp"
#include "IndexApp.hpp"
#include "HttpServer.hpp"
#include "HttpThreadHandler.hpp"
#include "HttpMessage.hpp"
#include "HttpRequest.hpp"
#include "HttpResponse.hpp"
#include "TcpServer.hpp"
#include "Socket.hpp"
#include "Queue.hpp"

void handleSignal(int signal) {
  HttpServer::getInstance().stop();
  std::cout << "Signal: " << signal << std::endl;
}

int main(int argc, char* argv[]) {
  if (argc >= 3) {
    HttpServer::getInstance().addWebAplication(new EchoApp());
    HttpServer::getInstance().addWebAplication(new IndexApp());
    HttpServer::getInstance().start(argv[2]);
    ::signal(SIGINT, ::handleSignal);
    ::signal(SIGTERM, ::handleSignal);
    try {
      HttpServer::getInstance().listenForever(argv[1]);
    } catch(std::runtime_error& error) {
      std::cout << "Error server" << std::endl;
    }
  } else {
    std::cout << "Faltan parámetros" << std::endl;
    std::cout << "Ejecute bin/[AppName] [port] [threads]" << std::endl;
  }
  return 0;
}
