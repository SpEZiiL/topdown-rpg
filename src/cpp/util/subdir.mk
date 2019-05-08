# src/cpp/util/subdir.mk

OBJECTS += \
$(BIN)/$(CXXSRC)/util/logger.o \
$(BIN)/$(CXXSRC)/util/utils.o \

$(BIN)/$(CXXSRC)/util/%.o: $(SRC)/$(CXXSRC)/util/%.$(EXT)
	@if [ ! -d $(shell dirname '$@') ]; then $(MKDIR) $(shell dirname '$@'); fi
	$(info )
	$(info Building object file '$@' ...)
	@$(TIME) $(C) $(FLAGS) -D_INSTALL='$(INSTALL)' -D_DEPLOY='$(DEPLOY)' -c '$<' -o '$@'
#$(BIN)/$(CXXSRC)/util/%.o

$(SRC)/$(CXXSRC)/util/%.$(EXT):
	$(error File '$@' not found)
#$(SRC)/$(CXXSRC)/util/%.$(EXT)
