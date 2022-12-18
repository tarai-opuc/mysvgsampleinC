CC = clang
CFLAGS = -Wall
LDFLAGS = 
LDLIBS = -lm
OBJS = main.o 
SRCS = main.c
EXEC = main
SAMPLE = sample.svg
$(EXEC) : $(OBJS)

sample: $(EXEC)
	./$(EXEC) > $(SAMPLE)

format: $(SRCS)
	clang-format -i $^

clean: 
	rm -f $(OBJS) $(EXEC) $(SAMPLE)
