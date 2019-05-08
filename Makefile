# Targets:
#
# test
#     Defines the DEPLOY macro to 0 and calls the 'all' target.
#
# retest
#     Calls the 'clean' and then the 'test' target.
#
# deploy
#     Defines the DEPLOY macro to 1 and calls the 'clean' and then the 'all' target.
#     If missing, creates a new 'deploy' directory.
#     Puts the 'assets' and 'src/python' directories and the executable into an
#     tar.gz archive that is saved under the 'deploy' directory.
#
# all
#     If missing, creates a new 'bin' directory.
#     Compiles all missing or changed source files into the 'bin' directory as
#     object files.
#     Links all object files with libraries and builds the executable into the
#     'bin' directory.
#
# clean
#     Removes the 'bin' and 'deploy' directories with all their contents, if
#     they exist.

-include init.mk

WINAPI_INCLUDES ?= -I/usr/share/mingw-w64/include
PYTHON_INCLUDES ?= -I/usr/include/python3.6 -I/usr/include/python3.6m

override LANG := cpp
LANG_STD ?= 11

override DEFAULT_OS := gnu_linux
ifndef OS
 $(info INFO: OS macro is not defined or is empty; defaulting to operating system '$(DEFAULT_OS)')
 override OS := $(DEFAULT_OS)
endif
ifeq ($(OS), gnu_linux)
 CC ?= gcc
 CXX ?= g++
else #elif
 ifeq ($(OS), win_i686)
  CC ?= i686-w64-mingw32-gcc
  CXX ?= i686-w64-mingw32-g++
 else #elif
  ifeq ($(OS), win_x86_64)
   CC ?= x86_64-w64-mingw32-gcc
   CXX ?= x86_64-w64-mingw32-g++
  else
   $(error Unsupported or unknown operating system '$(OS)')
  endif
 endif
endif

CEXT ?= c
CXXEXT ?= cpp
override WARNINGS := -W -Wall -Wno-implicit-fallthrough -Wno-expansion-to-defined $(WARNINGS)
override INCLUDES := -Isrc/cpp/include $(PYTHON_INCLUDES) $(INCLUDES)
override MACROS := $(MACROS)
override FLAGS := $(WARNINGS) $(INCLUDES) $(MACROS) $(FLAGS)
override LINKS := -lpython3.6m -lpthread -ldl -lutil -lm -fPIC $(LINKS)

ifeq ($(LANG), c)
 override C := $(CC)
 override EXT := $(CEXT)
 override FLAGS := -std=c$(LANG_STD) $(FLAGS)
else #elif
 ifeq ($(LANG), cpp)
  override C := $(CXX)
  override EXT := $(CXXEXT)
  override FLAGS := -std=c++$(LANG_STD) $(FLAGS)
 else
  $(error Invalid language '$(LANG)')
 endif
endif

TIME ?= time -f'Elapsed time: ~%E'
override RM := rm -rf
override MKDIR := mkdir -p
INST ?= install

SRC ?= src
CXXSRC ?= cpp
PYSRC ?= python
BIN ?= bin
DEP ?= deploy
TMP ?= tmp
ASSETS ?= assets

OBJECTS =

ifeq ($(OS), gnu_linux)
 TARGET ?= rpg-game_gnu_linux
 PREFIX ?= /usr/local/bin
 ASSET_PREFIX ?= /usr/local/share/rpg-game
 ARCHIVE ?= rpg-game_gnu_linux.tar.gz
else #elif
 ifeq ($(OS), win_i686)
  TARGET ?= rpg-game_win_i686.exe
  PREFIX ?= $(warning win_i686 PREFIX)
  ASSET_PREFIX ?= $(warning win_i686 ASSET_PREFIX)
  ARCHIVE ?= rpg-game_win_i686.zip
 else #elif
  ifeq ($(OS), win_x86_64)
   TARGET ?= rpg-game_win_x86_64.exe
   PREFIX ?= $(warning win_x86_64 PREFIX)
   ASSET_PREFIX ?= $(warning win_x86_64 ASSET_PREFIX)
   ARCHIVE ?= rpg-game_win_x86_64.zip
  endif
 endif
endif

include $(SRC)/$(CXXSRC)/subdir.mk
include $(SRC)/$(CXXSRC)/rpg/subdir.mk
include $(SRC)/$(CXXSRC)/util/subdir.mk

test: INSTALL = 0
test: DEPLOY = 0
test: all
#test

retest: clean test
#retest

install: INSTALL = 1
install: DEPLOY = 0
install: clean all
	$(info )
	$(info Installing...)
	$(warning TODO: install)
#install

uninstall:
	$(info )
	$(info Uninstalling...)
	$(warning TODO: uninstall)
#uninstall

deinstall: uninstall
#deinstall

deploy: INSTALL = 0
deploy: DEPLOY = 1
deploy: clean all
	$(info )
	$(info Deploying...)
	@if [ '$(OS)' == gnu_linux]; then \
	    $(TIME) tar -czvf $(DEP)/$(ARCHIVE) --exclude=__pycache__ \
	                      $(ASSETS) \
	        -C $(BIN)     $(TARGET) \
	        -C ../$(SRC)  $(PYSRC)  \
	elif [ '$(OS)' == win_i686 ]; then \
	    echo 'TODO: win_i686: deploy' \
	elif [ '$(OS)' == win_x86_64 ]; then \
	    echo 'TODO: win_x86_64: deploy' \
	fi
#deploy

all: $(OBJECTS)
	$(info )
	$(info Building executable '$(BIN)/$(TARGET)' ...)
	@$(TIME) $(C) $(FLAGS) $(OBJECTS) -o '$(BIN)/$(TARGET)' $(LINKS)
#all

clean:
	$(info )
	$(info Cleaning...)
	@$(TIME) $(RM) -v '$(BIN)' '$(DEP)' '$(TMP)'
#clean

.PHONY: test retest install uninstall deinstall deploy all clean
