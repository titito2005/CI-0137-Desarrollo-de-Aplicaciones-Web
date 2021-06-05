CC=cc
CXX=clang++
DEFS=
FLAGS=-g -Wall -Wextra $(DEFS)
CFLAGS=$(FLAGS) -std=gnu11
CXXFLAGS=$(FLAGS) -std=gnu++11
LIBS=-pthread
LINTFILTERS=$\
	-build/c++11,$\
	-build/header_guard,$\
	-build/include_subdir,$\
	-readability/casting,$\
	-runtime/references

APPNAME:=$(shell basename $(shell pwd))
APPARGS=8080
DIRS:=src src/common src/network src/http src/prodcons src/aplications
HEADERS:=$(wildcard $(DIRS:%=%/*.hpp))
SOURCES:=$(wildcard $(DIRS:%=%/*.cpp))
OBJECTS=$(SOURCES:src/%.cpp=build/%.o)
INCLUDES=$(DIRS:%=-I%)

.SECONDEXPANSION:

bin/$(APPNAME): $(OBJECTS) | $$(@D)/.
	$(CXX) $(CXXFLAGS) $(INCLUDES) $^ -o $@ $(LIBS)

build/%.o: src/%.cpp $(HEADERS) | $$(@D)/.
	$(CXX) -c $(CXXFLAGS) $(INCLUDES) $< -o $@ $(LIBS)

.PRECIOUS: %/.
%/.:
	mkdir -p $(dir $@)

all: bin/$(APPNAME) lint memcheck helgrind

.PHONY: lint
lint:
	cpplint --filter=$(LINTFILTERS) $(HEADERS) $(SOURCES)

.PHONY: memcheck
memcheck:
	valgrind --tool=memcheck bin/$(APPNAME) $(APPARGS)

.PHONY: helgrind
helgrind:
	valgrind --quiet --tool=helgrind bin/$(APPNAME) $(APPARGS)

.PHONY: gitignore
gitignore:
	echo bin > .gitignore
	echo build >> .gitignore

.PHONY: clean
clean:
	rm -rf bin build
