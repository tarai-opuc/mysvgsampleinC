CC = gcc
CFLAGS = -Wall
LDFLAGS = 
LDLIBS = -lm
OBJS = main.o 
EXEC = main
SAMPLE = sample.svg
$(EXEC) : $(OBJS)

$(SAMPLE): $(EXEC)
	./$(EXEC) > $@

clean: 
	rm -f $(OBJS) $(EXEC) $(SAMPLE)
