// Copyright 2021 Luis Eduardo Rojas. Universidad de Costa Rica. CC BY 4.0

#include "IndexApp.hpp"

IndexApp::IndexApp() {
  SERVER_NAME = "IndexApp";
  initMap();
  fullrequest = "";
}

IndexApp::~IndexApp() {
  delete SERVER_NAME;
}

bool IndexApp::getFullPath() {
  memset(cwd, 0, PATH_MAX);
  bool getPath = true;
  if (getcwd(cwd, sizeof(cwd)) != NULL) {
  } else {
    perror("getcwd() error");
    getPath = false;
  }
  return getPath;
}

bool IndexApp::verifyRequest(HttpRequest* request, HttpResponse* response) {
  bool verify = true;
  std::string uri = request->getUri();
  std::istringstream input;
  input.str(uri);
  std::string token;

  getline(input, token, '/');
  getline(input, token, '/');

  if (token == "index") {
    verify = true;
    char lastCharacter = uri.back();
    if (lastCharacter != '/') {
      uri.push_back('/');
      request->setUri(uri);
    }
  } else {
    request->setUri("/index/");
    verify = true;
  }

  bool hiddenDirectory = checkHiddenDirectory(uri);
  if (hiddenDirectory) {
    body.str("");
    body.clear();
    head.str("");
    head.clear();
    errorCode(404, "FORBIDDEN");
    response->addBody(head.str());
    response->addBody(body.str());
  } else {
    makeResponse(request, response);
  }
  return verify;
}

bool IndexApp::checkHiddenDirectory(std::string path) {
  getFullPath();
  std::istringstream input;
  input.str(path);
  std::string token;
  bool found = false;
  char fullpath[PATH_MAX];
  int cont = snprintf(fullpath, PATH_MAX, "%s", cwd);

  while (getline(input, token, *"/") && (found == false)) {
    if (token != "") {
      const char *path = token.c_str();
      cont += snprintf(fullpath+cont, PATH_MAX-cont, "%s", "/");
      cont += snprintf(fullpath+cont, PATH_MAX-cont, "%s", path);
      if (token.at(0) == '.') {
        DIR *dir;
        if ((dir = opendir(fullpath)) != NULL) {
          found = true;
          closedir(dir);
        } else {
          std::ifstream ifs(path, std::ifstream::binary);
          if (ifs.is_open()) {
            found = true;
          }
          ifs.close();
        }
      }
    }
  }
  return found;
}

void IndexApp::makeResponse(HttpRequest* request, HttpResponse* response) {
  body.str("");
  body.clear();
  head.str("");
  head.clear();
  fullrequest = request->getUri();
  getResponse();
  response->addBody(head.str());
  response->addBody(body.str());
}

std::string IndexApp::getFileCreationTime(char *fullpath) {
  struct stat attr;
  stat(fullpath, &attr);
  char buf[100];
  ctime_r(&attr.st_mtime, buf);
  std::string time(buf);
  return time;
}

int IndexApp::getFileSize(char *fullpath) {
  struct stat sb{};
  int tam = 0;
  if (!stat(fullpath, &sb)) {
    tam = sb.st_size;
  } else {
    perror("stat");
  }
  return tam;
}

void IndexApp::getResponse() {
  getFullPath();
  std::istringstream input;
  input.str(fullrequest);
  std::string token;
  getline(input, token, '/');
  getline(input, token, '/');
  while (getline(input, token, '/')) {
    int tam = strlen(cwd);
    tam += snprintf(cwd+tam, PATH_MAX-tam, "%s", "/");
    char *val = new char[token.length()+1];
    snprintf(val, token.length()+1, "%s", token.c_str());
    tam += snprintf(cwd+tam, PATH_MAX-tam, "%s", val);
    free(val);
  }
  if (verifyIndexDocument(cwd)) {
      openIndex(cwd);
  } else {
    // Intenta abrir el directorio.
    bool openDirectory = generateTableDirectory(cwd);

    if (!openDirectory) {
      bool open = readBinaryFile(cwd);
      if (!open) {
        errorCode(404, "NOT_FOUND");
      }
    }
  }
}

// Abre archivos index.html ó index.xhtml
void IndexApp::openIndex(char* path) {
  std::ifstream file(path);
  std::string str;
  std::ostringstream text;

  while (std::getline(file, str)) {
    text << str;
  }
  std::string extension = getExtension(path);
  body << text.str();
  headerGenerator(extension, body.str().length());
}

bool IndexApp::verifyIndexDocument(char* path) {
  DIR *dir2 = NULL;
  struct dirent *ent2 = NULL;
  bool found = false;
  if ((dir2 = opendir(path)) != NULL) {
    while ((ent2 = readdir(dir2)) != NULL && !found) {
      if (!strcmp(ent2->d_name, ".") || !strcmp(ent2->d_name, "..")) {
        // NO hace nada.
      } else {
        if (strcmp(ent2->d_name, "index.html") == 0) {
        found = true;
          int tam = strlen(path);
          tam+= snprintf(path+tam, PATH_MAX-tam, "%s", "/");
          tam += snprintf(path+tam, PATH_MAX-tam, "%s", "index.html");
        }
        if (strcmp(ent2->d_name, "index.xhtml") == 0) {
          found = true;
          int tam = strlen(path);
          tam+= snprintf(path+tam, PATH_MAX-tam, "%s", "/");
          tam += snprintf(path+tam, PATH_MAX-tam, "%s", "index.xhtml");
        }
      }
    }
  }
  closedir(dir2);
  return found;
}

bool IndexApp::readBinaryFile(char* path) {
  std::string extension = getExtension(path);
  std::ostringstream binaryFile;
  std::ifstream ifs(path, std::ifstream::binary);
  bool open = true;
  if (ifs.is_open()) {
    char binaryData = ifs.get();
    while (ifs.good()) {
      body << binaryData;
      binaryData = ifs.get();
    }
    headerGenerator(extension, body.str().length());
  } else {
    open = false;
  }
  ifs.close();
  return open;
}

// Muestra la extensión del archivo para el mimeType.
std::string IndexApp::getExtension(char* path) {
  char completePath[PATH_MAX];
  std::string extension = "";
  snprintf(completePath, PATH_MAX, "%s", path);
  char *token;
  char *saveptr;
  token = strtok_r(completePath, ".", &saveptr);
  std::string lastToken = "txt";
  while (token != NULL) {
    token = strtok_r(NULL, ".", &saveptr);
    if (token != NULL) {
      lastToken = token;
    }
  }
  extension = lastToken;
  return extension;
}

// Generador de Headers positivos.
void IndexApp::headerGenerator(std::string extension, int length) {
  head << "HTTP/1.0 200 0K\r\n";
  head << "Server: " << SERVER_NAME << "\r\n";
  head << "Content-Type: " << searchMime(extension) << ";charset=ascii\r\n";
  head << "Content-Length: " << length << "\r\n";
  head << "\r\n";
}

std::string IndexApp::getFatherDirectory(std::string path) {
  std::string fatherPath = path;
  if (fatherPath != "/index/") {
    fatherPath.pop_back();
    char lastCharacter = fatherPath.back();
    while (lastCharacter != '/') {
      fatherPath.pop_back();
      lastCharacter = fatherPath.back();
    }
  }
  return fatherPath;
}

bool IndexApp::generateTableDirectory(char* path) {
DIR *dir = NULL;
struct dirent *ent = NULL;
bool openDirectory = true;
if ((dir = opendir(path)) != NULL) {
  int numberFiles = 0;
  int64_t sizeFiles = 0;
  body << "<!DOCTYPE html><html lang=\"es\"><meta charset=\"utf-8\"/>";
  body << "<title>IndexApp</title><h1>Welcome!</h1>";
  body << "<hr><p>Generated by " << SERVER_NAME << "</p>";
  body << "<table style= width:50%>";
  body << "<caption>" << "File Browser" << "</caption>";
  body << "<thead>";
  body << "<tr>";
  body << "<td> NAME </td>";
  body << "<td> SIZE </td>";
  body << "<td> LAST MODIFIED </td>";
  body << "</tr>";
  body << "</thead>";
  body << "<tbody>";
  while ((ent = readdir(dir)) != NULL) {
    if (!strcmp(ent->d_name, ".") || !strcmp(ent->d_name, "..") ||
    (ent->d_name[0] == '.') ) {
    // No hace nada.
    } else {
      numberFiles++;
      int size = 0;
      body << "<tr>";
      char full_text[PATH_MAX];
      int tam = snprintf(full_text, PATH_MAX, "%s", path);
      tam += snprintf(full_text+tam, PATH_MAX-tam, "%s", "/");
      tam += snprintf(full_text+tam, PATH_MAX-tam, "%s", ent->d_name);
      size = getFileSize(full_text);
      body << "<td>" << "<a href= " << fullrequest << ent->d_name << "/" << ">";
      body << ent->d_name << "</a>" << "</td>";
      body << "<td>" << size << " bytes" << "</td>";
      body << "<td>" << getFileCreationTime(full_text) <<"</td>";
      body << "</tr>";
      sizeFiles += size;
    }
  }
  body << "</tbody>";
  body << "<tfoot>";
  body << "<tr>";
  body << "<td>" << "<a href= " << getFatherDirectory(fullrequest) << ">";
  body << "Return" << "</a>" << "</td>";
  body << "<td>" << "Total size: " << sizeFiles << " bytes" << "</td>";
  body << "<td>" << "Total files: "<< numberFiles << "</td>";
  body << "</tr>";
  body << "</tfoot>";
  body << "</table>";
  body << "</html>";
  closedir(dir);
  headerGenerator("html", body.str().length());
  } else {
    openDirectory = false;
  }
delete ent;
return openDirectory;
}

void IndexApp::errorCode(int code, std::string error) {
  body << "<!DOCTYPE html><html lang=\"es\"><meta charset=\"utf-8\"/>";
  body << "<title>IndexApp</title>";
  body << "<h1>Error</h1>";
  body << "<h1>" << code << " " << error << "</h1>";
  body << "<hr>";
  body << "<p>Generated by " << SERVER_NAME << "</p>";
  body << "</html>";
  head << "HTTP/1.0 " << code << " " << error << "\r\n";
  head << "Server: " << SERVER_NAME << "\r\n";
  head << "Content-Type: " << searchMime("html") << ";charset=ascii\r\n";
  head << "Content-Length: " << body.str().length() << "\r\n";
  head << "\r\n";
}
