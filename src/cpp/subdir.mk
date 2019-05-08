# src/cpp/subdir.mk

OBJECTS += \
$(BIN)/$(CXXSRC)/main.o \
$(BIN)/$(CXXSRC)/mod.o

$(BIN)/$(CXXSRC)/%.o: $(SRC)/$(CXXSRC)/%.$(EXT)
	@if [ ! -d $(shell dirname '$@') ]; then $(MKDIR) $(shell dirname '$@'); fi
	$(info )
	$(info Building object file '$@' ...)
	@$(TIME) $(C) $(FLAGS) -D_INSTALL='$(INSTALL)' -D_DEPLOY='$(DEPLOY)' -c '$<' -o '$@'
#$(BIN)/$(CXXSRC)/%.o

$(SRC)/$(CXXSRC)/%.$(EXT):
	$(error File '$@' not found)
#$(SRC)/$(CXXSRC)/%.$(EXT)
