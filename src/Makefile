CC = clang
CFLAGS = -g -Wall
LDFLAGS = 
LDLIBS = -lm
OBJS = main.o libmysvg.o
SRCS = main.c libmysvg.c
EXEC = main
SAMPLE = sample.svg
$(EXEC) : $(OBJS)

$(SAMPLE): $(EXEC)
	./$(EXEC) > $@

format: $(SRCS)
	clang-format -i $^

clean: 
	rm -f $(OBJS) $(EXEC) $(SAMPLE)
