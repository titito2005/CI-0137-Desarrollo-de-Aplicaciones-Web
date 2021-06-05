// Copyright 2021 Luis Eduardo Rojas. Universidad de Costa Rica. CC BY 4.0

#ifndef HTTPAPLICATION_H
#define HTTPAPLICATION_H

#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include <fstream>
#include <iostream>
#include <map>
#include <streambuf>
#include <string>
#include <utility>


#include "HttpMessage.hpp"
#include "HttpRequest.hpp"
#include "HttpResponse.hpp"
#include "Socket.hpp"

class HttpAplication {
  DISABLE_COPY(HttpAplication);

 public:
  HttpAplication();
  ~HttpAplication();
  // Método para verificar pertenencia del request.
  virtual bool verifyRequest(HttpRequest*, HttpResponse*) = 0;
  // Método para generar la respuesta.
  virtual void makeResponse(HttpRequest*, HttpResponse*) = 0;
  void initMap();
  void addItemMap(std::string, std::string);
  std::string searchMime(std::string);

 private:
  std::map <std::string, std::string> mapa;
};
#endif
