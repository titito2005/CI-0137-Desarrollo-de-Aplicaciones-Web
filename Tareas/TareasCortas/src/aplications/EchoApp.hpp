// Copyright 2021 Luis Eduardo Rojas. Universidad de Costa Rica. CC BY 4.0

#ifndef ECHOAPP_H
#define ECHOAPP_H

#include <iostream>
#include <string>

#include "HttpAplication.hpp"
#include "HttpMessage.hpp"
#include "HttpRequest.hpp"
#include "HttpResponse.hpp"

class EchoApp : public HttpAplication{
  DISABLE_COPY(EchoApp);

 public:
  EchoApp();
  ~EchoApp();
  bool verifyRequest(HttpRequest*, HttpResponse*) override;
  void makeResponse(HttpRequest*, HttpResponse*) override;
 private:
};
#endif
