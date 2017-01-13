# Makefile example. Compile all .c files and build execution file
QUIET = @
ECHO  = echo
CC  = gcc
RM = rm -rf
OBJDUMP= objdump -S –l

CFLAGS  = -g
LDFLAGS = -lm -lpthread
TARGET = a.out
OBJS  = $(patsubst %.c,%.o,$(wildcard *.c))
OBJSDUMP_LOG= $(patsubst %.c,%.objdump,$(wildcard *.c))

all: info $(TARGET)

$(TARGET): $(OBJS) #$(OBJSDUMP_LOG)
	$(QUIET)$(ECHO) "Building " $@
	$(QUIET)$(CC) -o $@ $(OBJS) $(LDFLAGS)

%.o: %.c
	$(QUIET)$(ECHO) "Compliling " $<
	$(QUIET)$(CC) $(CFLAGS) -c $< -o $@

%.objdump: %.o
	$(QUIET)$(ECHO) "Objdumping " $<
	$(QUIET)$(OBJDUMP) $< > $@

info:
	$(QUIET)$(ECHO) "CC=$(CC)"
	$(QUIET)$(ECHO) "INFO: CFLAGS=$(CFLAGS)"
	$(QUIET)$(ECHO) "LDFLAGS=$(LDFLAGS)"

clean:
	$(QUIET)$(RM) $(OBJS) $(TARGET)