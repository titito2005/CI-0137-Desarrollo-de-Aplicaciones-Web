// Copyright 2021 Luis Eduardo Rojas. Universidad de Costa Rica. CC BY 4.0

#ifndef HTTPTHREADSERVER_H
#define HTTPTHREADSERVER_H

#include <stdlib.h>
#include <unistd.h>

#include <iostream>
#include <vector>

#include "Consumer.hpp"
#include "HttpAplication.hpp"
#include "HttpRequest.hpp"
#include "HttpResponse.hpp"
#include "Socket.hpp"

class HttpThreadHandler:public Consumer<Socket> {
  DISABLE_COPY(HttpThreadHandler);
 public:
  explicit HttpThreadHandler(std::vector <HttpAplication*> *);
  ~HttpThreadHandler();

 private:
  bool findApp(HttpRequest*, HttpResponse*);
  int run() override;
  void consume(Socket sock) override;
  std::vector <HttpAplication*> *apps;
};
#endif
