# Compiler to use
CC = gcc

# Compiler flags
# -I specifies the include directories for header files
# NOTE: These paths are checked by the compiler by default and hence can be omitted.
# CFLAGS = -I/usr/local/include -I/usr/local/include/glad

# Linker flags
# -L specifies the library directory, and -l links against the specified libraries
# NOTE: /usr/local/lib is checked by the compiler by default and hence can be omitted.
# LDFLAGS = -L/usr/local/lib -lglfw -lm -ldl
LDFLAGS = -lglfw -lm -ldl

# Source files
# This lists the source files to compile. glad.c is expected to be located in /usr/local/lib.
SOURCES = /usr/local/lib/glad.c src/main.c src/block_renderer.c src/shader.c

# Name of the output executable
TARGET = tetris

# Default target to build
all: $(TARGET)

# Rule to create the target executable
# This line specifies that the target (executable) depends on the source files.
$(TARGET): $(SOURCES)
	# Compile the source files into the target executable
	# $(CC) invokes the compiler, $(CFLAGS) adds include directories,
	# $(SOURCES) specifies the source files, -o specifies the output file,
	# and $(LDFLAGS) links the necessary libraries.
	$(CC) $(CFLAGS) $(SOURCES) -o $(TARGET) $(LDFLAGS)

# Rule to clean up generated files
clean:
	# Remove the target executable file
	rm -f $(TARGET)
