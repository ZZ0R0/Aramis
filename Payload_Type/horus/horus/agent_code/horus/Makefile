# -----------------------------
# Compiler Definitions
# -----------------------------

# C++ Compiler
CXX := x86_64-w64-mingw32-g++

# -----------------------------
# Compiler Flags
# -----------------------------

# Automatically find all directories containing .h or .hpp files within 'core' and 'commands'
HEADER_DIRS := $(shell find core commands -type f \( -name "*.h" -o -name "*.hpp" \) -exec dirname {} \; | sort -u)

# Convert directories to compiler include flags
INCLUDE := $(addprefix -I, $(HEADER_DIRS))

# C++ Compiler Flags
CXXFLAGS := -mwindows -g -O0 -e WinMain -fexceptions -m64
CXXFLAGS += -ffunction-sections -falign-jumps=1
CXXFLAGS += -falign-labels=1 -fPIC
CXXFLAGS += $(INCLUDE)

# Linker Flags
LDFLAGS := -Wl,-s,--enable-stdcall-fixup -m64

# Libraries to Link Against
LIBS := -lwinhttp -liphlpapi -lnetapi32 -lshlwapi

# -----------------------------
# Build Directory
# -----------------------------

BUILD := ./build

# -----------------------------
# Source Files
# -----------------------------

# Find all .cpp files excluding those in the build directory
CPP_SOURCES := $(shell find . -type f -name "*.cpp" | grep -v "^./$(BUILD)")

# -----------------------------
# Object Files
# -----------------------------

# Convert .cpp source files to their corresponding object file paths
OBJ_CPP := $(patsubst %.cpp,$(BUILD)/%.o,$(CPP_SOURCES))

# Combined all object files
ALL_OBJ := $(OBJ_CPP)

# -----------------------------
# Targets
# -----------------------------

# Default Target
all: exe dll

# Executable Target
exe: $(ALL_OBJ)
	@echo "[*] Compiling x64 executable"
	@mkdir -p $(BUILD)
	$(CXX) $(CXXFLAGS) $(ALL_OBJ) $(LDFLAGS) $(LIBS) -o $(BUILD)/horus.exe

# DLL Target
dll: $(ALL_OBJ)
	@echo "[*] Compiling x64 DLL"
	@mkdir -p $(BUILD)
	$(CXX) $(CXXFLAGS) $(ALL_OBJ) $(LDFLAGS) $(LIBS) -shared -e DllMain -o $(BUILD)/horus.dll -DDLL -DSLEEP -DPROTOCOL -DSYSCALL

# -----------------------------
# Compilation Rules
# -----------------------------

# Rule for C++ files
$(BUILD)/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# -----------------------------
# Clean Target
# -----------------------------

clean:
	@echo "[*] Cleaning build directory"
	@rm -rf $(BUILD)

# -----------------------------
# Phony Targets
# -----------------------------

.PHONY: all exe dll clean
