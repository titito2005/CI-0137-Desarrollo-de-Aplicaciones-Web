// Copyright 2021 Luis Eduardo Rojas. Universidad de Costa Rica. CC BY 4.0

#include <iostream>

#include "HttpServer.hpp"
#include "HttpThreadHandler.hpp"

HttpServer::HttpServer() {
}

HttpServer::~HttpServer() {
}

void HttpServer::start(const char* cantHilos) {
  cantidadHilos = atoi(cantHilos);  // VERIFICAR INPUT
  for (int i = 0; i < cantidadHilos; i++) {
    HttpThreadHandler* hilo = new HttpThreadHandler(&webAplications);
    hilo->setConsumingQueue(&cola);
    hilo->startThread();
  }
}

void HttpServer::stop() {
  std::cout << "Server stopped" << std::endl;
  this->stopListening();
}

HttpServer& HttpServer::getInstance() {
  static HttpServer server;
  return server;
}

void HttpServer::handleClientConnection(Socket& client) {
  cola.push(client);
}

void HttpServer::addWebAplication(HttpAplication *app) {
  webAplications.push_back(app);
}


