# Sources
TARGET     = gpio
INCLUDES   = $(TARGET).h
SOURCES    = $(TARGET).c
LIBS       = 

# files
LIB        = lib$(TARGET).a
DEPS       = $(SOURCES:.c=.h)
OBJS       = $(SOURCES:.c=.o)

# library test files
TEST_TGT   = $(TARGET)_test
TEST_SRC   = $(TEST_TGT).c
TEST_OBJ   = $(TEST_TGT).o

# compiler options
STANDARD   = -std=gnu11
#TEMPS      = -save-temps
#DEBUG      = -g
#DEBUG      = -D DEBUG
#OPTIMIZE   = -O2
INC_DIRS   = -I../../include
LIB_DIRS   = -L../../lib
C_FLAGS    = $(STANDARD) $(INC_DIRS) $(DEBUG) $(OPTIMIZE) $(TEMPS)\
		-W -Wall -pedantic \
		-Wformat-nonliteral -Wcast-align  \
		-Wpointer-arith -Wbad-function-cast \
		-Wstrict-prototypes -Winline -Wundef \
		-Wnested-externs -Wcast-qual -Wshadow \
		-Wconversion -Wwrite-strings \
		-ffloat-store
L_FLAGS    = $(LIB_DIRS) $(LIBS)

# compiler commands
COMPILE    = gcc $(C_FLAGS)

# symbolic targets
all:	$(LIB)

lib:	$(LIB)

test: $(OBJS)
	$(COMPILE) -D TEST -c $(TEST_SRC) -o $(TEST_OBJ)
	$(COMPILE) -o $(TEST_TGT) $(OBJS) $(TEST_OBJ) $(L_FLAGS)

# command targets
install: $(LIB)
	cp $(TARGET).h ../../include
	cp $(LIB)      ../../lib

clean:
	rm -f $(LIB) $(OBJS) $(TEST_TGT) $(TEST_OBJ)

# file targets
$(LIB): $(OBJS) $(DEPS)
	ar rcs ${LIB} ${OBJS}

%.o: %.c $(INCLUDES)
	$(COMPILE) -c $< -o $@

%.s: %.c
	$(COMPILE) -S $< -o $@

.PHONY: install lib clean test

