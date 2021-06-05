// Copyright 2021 Luis Eduardo Rojas. Universidad de Costa Rica. CC BY 4.0

#ifndef HTTPMESSAGE_H
#define HTTPMESSAGE_H

#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <utility>

#include "Socket.hpp"

class HttpMessage {
  DISABLE_COPY(HttpMessage);

 public:
  HttpMessage();
  ~HttpMessage();
  std::string findMap(std::string);
  void addBody(std::string);
  std::string getBody();
  void addData(std::string, std::string);
  void setHttpVersion(std::string);
  void setMethod(std::string);
  std::string getHttpVersion();
  std::string getMethod();
  void print();
  void cleanBody();

 private:
  std::string httpVersion;
  std::string method;
  std::stringstream body;
  std::map <std::string, std::string> mapa;
};
#endif
