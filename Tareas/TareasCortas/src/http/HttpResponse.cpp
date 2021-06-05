// Copyright 2021 Luis Eduardo Rojas. Universidad de Costa Rica. CC BY 4.0

#include "HttpResponse.hpp"

HttpResponse::HttpResponse() {
}

HttpResponse::~HttpResponse() {
}

void HttpResponse::setStatusCode(int code, std::string reason) {
  statusCode = code;
  this->reason = reason;
}

void HttpResponse::send(Socket socket) {
  socket << getBody();
  socket.send();
}
