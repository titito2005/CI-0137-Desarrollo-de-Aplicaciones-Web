// Copyright 2021 Luis Eduardo Rojas. Universidad de Costa Rica. CC BY 4.0

#include "HttpAplication.hpp"

HttpAplication:: HttpAplication() {
}

HttpAplication::~HttpAplication() {
}

void HttpAplication::initMap() {
  addItemMap("css", "text/css");
  addItemMap("csv", "text/csv");
  addItemMap("gif", "image/gif");
  addItemMap("htm ", "text/html");
  addItemMap("html", "text/html");
  addItemMap("xhtml", "application/xhtml+xml");
  addItemMap("jpeg", "image/jpeg");
  addItemMap("jpg", "image/jpeg");
  addItemMap("png", "image/png");
  addItemMap("txt", "text/plain");
  addItemMap("cpp", "text/plain");
  addItemMap("hpp", "text/plain");
}

// AGREGA UN ITEM AL MAPA.
void HttpAplication::addItemMap(std::string key, std::string value) {
  mapa.insert(std::pair<std::string, std::string>(key, value));
}

// BUSCA EN EL MAPA.
std::string HttpAplication::searchMime(std::string key) {
  std::map <std::string, std::string>::iterator it;
  std::string valor = "text/plain";
  it = mapa.find(key);
  if (it != mapa.end()) {
    valor = it->second;
  }
  return valor;
}
