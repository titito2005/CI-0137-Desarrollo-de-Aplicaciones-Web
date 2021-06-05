// Copyright 2021 Luis Eduardo Rojas. Universidad de Costa Rica. CC BY 4.0

#ifndef HTTPSERVER_H
#define HTTPSERVER_H

#include <vector>

#include "HttpAplication.hpp"
#include "Queue.hpp"
#include "Socket.hpp"
#include "TcpServer.hpp"

class HttpServer : public TcpServer {
  DISABLE_COPY(HttpServer);
 protected:
  HttpServer();
  ~HttpServer();
  void handleClientConnection(Socket& client) override;

 public:
  void addWebAplication(HttpAplication*);
  static HttpServer& getInstance();
  void start(const char*);
  void stop();

 private:
  Queue <Socket> cola;
  std::vector<HttpAplication*> webAplications;
  int cantidadHilos;
};
#endif
