# choco install mingw unzip curl

TARGET_EXEC ?= square

CC=gcc
CXX=g++

BIN_DIR ?= ./bin
OBJ_DIR ?= ./obj
SRC_DIR ?= ./src

LIBS := sfml-graphics sfml-window sfml-system
DLLS := $(LIBS:%=$(BIN_DIR)/%-2.dll)
SRCS := $(shell find $(SRC_DIR) -name *.cpp -or -name *.c -or -name *.s)
OBJS := $(SRCS:$(SRC_DIR)/%=$(OBJ_DIR)/%.o)
DEPS := $(OBJS:.o=.d)

INC_DIRS := $(shell find $(SRC_DIR) -type d)
INC_FLAGS := $(addprefix -I,$(INC_DIRS))
INC_FLAGS := $(INC_FLAGS) -Isfml/SFML-2.5.1/include

# LDFLAGS := $(shell pkg-config --libs $(LIBS))
LDFLAGS := -Lsfml/SFML-2.5.1/lib $(addprefix -l,$(LIBS))

CPPFLAGS := $(INC_FLAGS) -g -MMD -MP

$(BIN_DIR)/$(TARGET_EXEC): $(DLLS) sfml $(OBJS)
	$(MKDIR_P) $(dir $@)
	$(CXX) $(OBJS) -o $@ $(LDFLAGS)

$(BIN_DIR)/%.dll: sfml
	$(MKDIR_P) $(dir $@)
	echo $@
	cp sfml/SFML-2.5.1/$@ $@

# assembly
$(OBJ_DIR)/%.s.o: %.s
	$(MKDIR_P) $(dir $@)
	$(AS) $(ASFLAGS) -c $< -o $@

# c source
$(OBJ_DIR)/%.c.o: %.c
	$(MKDIR_P) $(dir $@)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

# c++ source
$(OBJS): $(OBJ_DIR)/%.cpp.o : $(SRC_DIR)/%.cpp
	$(MKDIR_P) $(dir $@)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

sfml: sfml.zip
	unzip -d sfml sfml.zip

sfml.zip:
	curl -Lo sfml.zip https://www.sfml-dev.org/files/SFML-2.5.1-windows-gcc-7.3.0-mingw-64-bit.zip

.PHONY: clean

clean:
	$(RM) -r $(BIN_DIR)

-include $(DEPS)

MKDIR_P ?= mkdir -p