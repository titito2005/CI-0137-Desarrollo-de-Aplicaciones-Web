// Copyright 2021 Luis Eduardo Rojas. Universidad de Costa Rica. CC BY 4.0

#ifndef HTTPRESPONSE_H
#define HTTPRESPONSE_H

#include <iostream>
#include <map>
#include <sstream>
#include <string>

#include "HttpMessage.hpp"
#include "Socket.hpp"

class HttpResponse : public HttpMessage {
  DISABLE_COPY(HttpResponse);

 public:
  HttpResponse();
  ~HttpResponse();
  void setStatusCode(int, std::string);
  void send(Socket);

 private:
  int statusCode;
  std::string reason;
};
#endif
