# Compiler and flags
CXX := clang++
CXXFLAGS := -std=c++2b -Wall -Weffc++ -Wextra -Wconversion -Wsign-conversion
LDFLAGS := -O2

# Directories
SRCDIR := src
INCDIR := include
OBJDIR := target/objects
BINDIR := target

# File patterns
SRCEXT := cpp
OBJEXT := o

# Sources and objects
SOURCES := $(wildcard $(SRCDIR)/*.$(SRCEXT))
OBJECTS := $(patsubst $(SRCDIR)/%.$(SRCEXT),$(OBJDIR)/%.$(OBJEXT),$(SOURCES))

# Target binary
TARGET := $(BINDIR)/chepp

# Rules
all: $(TARGET)

$(TARGET): $(OBJECTS)
	@mkdir -p $(BINDIR)
	$(CXX) $(LDFLAGS) -o $@ $^

$(OBJDIR)/%.$(OBJEXT): $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

run: $(TARGET)
	./$(TARGET)

clean:
	rm -rf $(OBJDIR) $(TARGET)

.PHONY: all clean

