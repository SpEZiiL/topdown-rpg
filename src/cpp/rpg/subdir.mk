# src/cpp/rpg/subdir.mk

OBJECTS += $(BIN)/$(CXXSRC)/rpg/entity.o

$(BIN)/$(CXX_SRC)/rpg/%.o: $(SRC)/$(CXX_SRC)/rpg/%.$(EXT)
	@if [ ! -d $(shell dirname '$@') ]; then $(MKDIR) $(shell dirname '$@'); fi
	$(info )
	$(info Building object file '$@' ...)
	@$(TIME) $(C) $(FLAGS) -D_INSTALL='$(INSTALL)' -D_DEPLOY='$(DEPLOY)' -c '$<' -o '$@'
#$(BIN)/$(CXX_SRC)/rpg/%.o

$(SRC)/$(CXX_SRC)/rpg/%.$(EXT):
	$(error File '$@' not found)
#$(SRC)/$(CXX_SRC)/rpg/%.$(EXT)
