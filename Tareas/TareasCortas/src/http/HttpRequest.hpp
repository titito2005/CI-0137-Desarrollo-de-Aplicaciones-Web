// Copyright 2021 Luis Eduardo Rojas. Universidad de Costa Rica. CC BY 4.0

#ifndef HTTPREQUEST_H
#define HTTPREQUEST_H

#include <stdio.h>
#include <string.h>

#include <cstdint>
#include <iostream>
#include <map>
#include <string>
#include <sstream>

#include "HttpMessage.hpp"
#include "Socket.hpp"

class HttpRequest : public HttpMessage {
  DISABLE_COPY(HttpRequest);

 public:
  HttpRequest();
  ~HttpRequest();
  void load(Socket);
  void setUri(std::string);
  std::string getUri();
  enum codes{OK_200 = 200, NOT_FOUND_404 = 404};

 private:
  std::string uri;
};
#endif
