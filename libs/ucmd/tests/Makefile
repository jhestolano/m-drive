PROJ_NAME=ucmd
BUILD_DIR=build
UNITY_DIR=Unity
TEST_DIR=.
SRCS=

# Modules code.
SRCS+=../err.c
SRCS+=../utils.c
SRCS+=../ucmd.c
SRCS+=../line.c

# Tests.
SRCS+=$(TEST_DIR)/test_cmd.c
SRCS+=$(TEST_DIR)/test_utils.c
SRCS+=$(TEST_DIR)/test_line.c
SRCS+=$(TEST_DIR)/test_integration.c
SRCS+=$(TEST_DIR)/main.c

# Unity testing framework.
SRCS+=$(UNITY_DIR)/unity.c

INC_DIRS=.
INC_DIRS+=..
INC_DIRS+=Unity

CC=gcc
OBJCOPY=objcopy
OBJDUMP=objdump
SZ=size

# Any compiler options you need to set
CFLAGS=-ggdb3
CFLAGS+=-Og -Wall -Wextra -Warray-bounds

# Definition used for unit testing.
# Exposes static functions to testing framework.
DEFS=-DUNIT_TEST

INCLUDE = $(addprefix -I,$(INC_DIRS))

.PHONY: $(PROJ_NAME)
$(PROJ_NAME): $(PROJ_NAME).out

%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)

$(PROJ_NAME).out: $(SRCS)
	mkdir -p $(BUILD_DIR)
	$(CC) $(INCLUDE) $(DEFS) $(CFLAGS) $^ -o $(BUILD_DIR)/$@

clean:
	rm -f *.o $(BUILD_DIR)/$(PROJ_NAME).*
