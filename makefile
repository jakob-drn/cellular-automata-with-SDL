
CC = cc -c 
CFLAGS = -Wall -Wextra -g   
LDLIBS =  -lSDL2 -lGL -lm

VPATH = src
OBJS = main.o ticker.o io.o globals.o linkedlist.o map.o
OBJDIR = bin
OBJ := $(addprefix $(OBJDIR)/,$(OBJS))

$(OBJDIR)/%.o : %.c
	$(CC) $(CFLAGS) $< -o $@

prog : $(OBJ)
	cc $^ -o $@ $(LDLIBS) 

$(OBJ): | $(OBJDIR)
$(OBJDIR) : 
	mkdir $(OBJDIR)

.PHONY : r
r :
	./prog

.PHONY : clean
clean :
	-rm prog $(OBJ)
