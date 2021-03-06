// Copyright 2021 Luis Eduardo Rojas. Universidad de Costa Rica. CC BY 4.0

#include "EchoApp.hpp"

EchoApp::EchoApp() {
}

EchoApp::~EchoApp() {
}

bool EchoApp::verifyRequest(HttpRequest *request, HttpResponse *response) {
  bool verify = false;
  std::string uri = request->getUri();
  std::istringstream input;
  input.str(uri);
  std::string token;

  getline(input, token, '/');
  getline(input, token, '/');

  if (token == "echo") {
    verify = true;
    makeResponse(request, response);
  }
  return verify;
}

void EchoApp::makeResponse(HttpRequest *request, HttpResponse *response) {
  const char* const SERVER_NAME = "EchoApp";
  std::ostringstream message;
  std::ostringstream head;
  message << "<!DOCTYPE html><html lang=\"es\"><meta charset=\"utf-8\"/>";
  message << "<title>Hi!</title>";
  message << "<body>";
  message << "<h1>Welcome!</h1>";
  message << "<hr><p>Generated by " << SERVER_NAME << "</p>";
  message << "<pre>" << "Request Solicitado:" << "</pre>";
  message << "<pre>" << "Host: " << request->findMap("Host");
  message << "</pre>";
  message << "<pre>" << "Accept: " << request->findMap("Accept");
  message << "</pre>";
  message << "<pre>" << "User-Agent: " << request->findMap("User-Agent");
  message << "</pre>";
  message << "<pre>" << "Uri solicitado: " << request->getUri();
  message << "</pre>";
  message << "</body>";
  message << "</html>";
  // Status line
  head << "HTTP/1.0 200 0K\r\n";
  // Response header
  head << "Server: " << SERVER_NAME << "\r\n";
  head << "Content-Type: text/html; charset=ascii\r\n";
  head << "Content-Length: " << message.str().length() << "\r\n";
  head << "\r\n";

  response->cleanBody();
  response->addBody(head.str());
  response->addBody(message.str());
}
