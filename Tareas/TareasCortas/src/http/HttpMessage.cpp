// Copyright 2021 Luis Eduardo Rojas. Universidad de Costa Rica. CC BY 4.0

#include "HttpMessage.hpp"

HttpMessage::HttpMessage() {
  httpVersion = "";
  method = "";
}

HttpMessage::~HttpMessage() {
}

std::string HttpMessage::findMap(std::string key) {
  std::map <std::string, std::string>::iterator it;
  std::string valor = "";
  it = mapa.find(key);
  if (it != mapa.end()) {
    valor = it->second;
  }
  return valor;
}

void HttpMessage:: addData(std::string key, std::string value) {
  mapa.insert(std::pair<std::string, std::string>(key, value));
}

void HttpMessage::setHttpVersion(std::string httpVersion) {
  this->httpVersion = httpVersion;
}

void HttpMessage::setMethod(std::string method) {
  this->method = method;
}

std::string HttpMessage::getHttpVersion() {
  return httpVersion;
}

std::string HttpMessage::getMethod() {
  return method;
}

void HttpMessage::addBody(std::string cadena) {
  this->body << cadena;
}

std::string HttpMessage::getBody() {
  return body.str();
}

void HttpMessage::print() {
  std::cout << body.str() <<std::endl;
}

void HttpMessage::cleanBody() {
  body.str("");
}
