SDL3_GFX_DIR = /Users/ethansampson/"Physics Engine"/SDL3_gfx

# Compiler and flags
CC = clang
CFLAGS = -Wall -Wextra -std=c99
PROJECT_INCLUDE = -I./include
PKG_CONFIG_PATH := $(SDL3_GFX_DIR)/build:$$PKG_CONFIG_PATH
INCLUDES = $(shell PKG_CONFIG_PATH=$(PKG_CONFIG_PATH) pkg-config --cflags sdl3-gfx)
LIBS = $(shell PKG_CONFIG_PATH=$(PKG_CONFIG_PATH) pkg-config --libs sdl3-gfx)
LIBDIRS = -L$(SDL3_GFX_DIR)/build/SDL3_gfx_Shared

# Your program
TARGET = window
SOURCES = $(wildcard *.c src/*.c)

LDFLAGS = -Wl,-rpath,$(SDL3_GFX_DIR)/build/SDL3_gfx_Shared

# Build rule
$(TARGET): $(SOURCES)
	PKG_CONFIG_PATH=$(PKG_CONFIG_PATH) $(CC) $(CFLAGS) $(PROJECT_INCLUDE) $(INCLUDES) $(SOURCES) $(LIBS) -o $(TARGET)

run: $(TARGET)
	DYLD_LIBRARY_PATH=$(SDL3_GFX_DIR)/build/SDL3_gfx_Shared:$$DYLD_LIBRARY_PATH ./$(TARGET)

# Clean rule
clean:
	rm -f $(TARGET)

# Phony targets
.PHONY: clean

