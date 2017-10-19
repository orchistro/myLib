###############################################################################
#
# Requires gnu make
#
###############################################################################

.PHONY: clean gcov

EXEC_NAME = heaptest
OBJECTS   = $(patsubst %.c,%.o,$(wildcard *.c))
CC        = gcc
LD        = gcc
CFLAGS   += -Wall -g
GCOVOPT   = -fprofile-arcs -ftest-coverage

# Default target
all: $(EXEC_NAME)

$(EXEC_NAME) : $(OBJECTS)
	$(CC) $(LDFLAGS) -o $@ $^

$(OBJECTS) : %.o : %.c 
	$(CC) $(CFLAGS) -o $@ -c $<

# Generating dependency files
%.d : %.c
	@$(CC) -MM $< > $@

# Include dependency file to have gcc recompile necessary sources
-include $(patsubst %.c,%.d,$(wildcard *.c))

clean:
	rm -f *.o *.d core $(EXEC_NAME) *.gcda *.gcno *.gcov

gcov:
	make clean all LDFLAGS='$(GCOVOPT)' CFLAGS='$(GCOVOPT)'
