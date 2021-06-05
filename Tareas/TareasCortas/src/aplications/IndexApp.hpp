// Copyright 2021 Luis Eduardo Rojas. Universidad de Costa Rica. CC BY 4.0

#ifndef INDEXAPP_H
#define INDEXAPP_H

#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include <fstream>
#include <streambuf>
#include <iostream>
#include <string>

#include "HttpAplication.hpp"
#include "HttpMessage.hpp"
#include "HttpRequest.hpp"
#include "HttpResponse.hpp"

class IndexApp : public HttpAplication {
  DISABLE_COPY(IndexApp);

 public:
  IndexApp();
  ~IndexApp();
  // Método para verificar si le corresponde el request.
  bool verifyRequest(HttpRequest*, HttpResponse*) override;
  // Método para generar respuesta.
  void makeResponse(HttpRequest*, HttpResponse*) override;

  std::string getFileCreationTime(char *fullpath);
  int getFileSize(char *fullpath);

  void getResponse();
  bool verifyIndexDocument(char*);
  bool readBinaryFile(char*);
  void headerGenerator(std::string, int);
  std::string getExtension(char*);
  std::string getFatherDirectory(std::string);
  bool generateTableDirectory(char*);
  void openIndex(char*);
  void errorCode(int, std::string);
  bool checkHiddenDirectory(std::string);
  bool getFullPath();

 private:
  std::ostringstream body;
  std::ostringstream head;
  std::string fullrequest;
  const char* SERVER_NAME;
  char cwd[PATH_MAX];
};
#endif
