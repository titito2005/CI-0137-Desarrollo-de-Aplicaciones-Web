// Copyright 2021 Luis Eduardo Rojas. Universidad de Costa Rica. CC BY 4.0

#include "HttpRequest.hpp"

HttpRequest::HttpRequest() {
}

HttpRequest::~HttpRequest() {
}

void HttpRequest::load(Socket sock) {
  char request[1000];
  sock.readAvailable(request, 1000);
  std::istringstream input;
  input.str(request);
  std::string token;

  getline(input, token, '\n');

  std::istringstream header;
  header.str(token);
  std::string token2;
  for (int i = 0; i < 3; i++) {
    getline(header, token2, ' ');
    if (i == 0) {
      setMethod(token2);
    }
    if (i == 1) {
      setUri(token2);
    }
    if (i == 2) {
      setHttpVersion(token2);
    }
  }

  while (getline(input, token, '\n')) {
    if (token.size() > 2) {
      std::istringstream header2;
      header2.str(token);
      std::string token2;
      getline(header2, token2, ' ');
      token2 = token2.substr(0, token2.length()-1);
      std::string llave = token2;
      getline(header2, token2, '\n');
      addData(llave, token2);
    }
  }
}

void HttpRequest::setUri(std::string uri) {
  this->uri = uri;
}

std::string HttpRequest::getUri() {
  return uri;
}

