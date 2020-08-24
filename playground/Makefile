LLVM_CONFIG?=llvm-config
ifndef VERBOSE
QUIET:=@
endif

SRC_DIR?=$(PWD)
TARGET_DIR?=$(PWD)
COMMON_FLAGS=-O3
CXX=clang++
CXXFLAGS+=$(COMMON_FLAGS) $(shell $(LLVM_CONFIG) --cxxflags)
LDFLAGS+=$(shell $(LLVM_CONFIG) --ldflags --libs) -lpthread -lncurses

PROJECT=play
PROJECT_OBJECTS=play.o
default: $(PROJECT)

%.o : $(SRC_DIR)/%.cpp
	@echo Compiling $*.cpp
	$(CXX) -c $(CXXFLAGS) $<

$(PROJECT) : $(PROJECT_OBJECTS)
	@echo Linking $@
	$(CXX) -o $@ $(LDFLAGS) $^

clean::
	$(QUIET)rm -f $(PROJECT) $(PROJECT_OBJECTS)