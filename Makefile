CC = gcc
CFLAGS = -Wall
MAIN = main
TEST = test
SRC=src
OBJS = $(addprefix $(SRC)/, game.o minimax.o utils.o cache.o)

$(MAIN): $(OBJS) $(SRC)/$(MAIN).o
	$(CC) $^ -o $@ $(CFLAGS) $(EXTRA_FLAGS)

$(TEST): $(OBJS) $(SRC)/$(TEST).o
	$(CC) $^ -o $@ $(CFLAGS) $(EXTRA_FLAGS)

%.o: %.c
	$(CC) $? -o $@ -c $(CFLAGS) $(EXTRA_FLAGS)

clean:
	rm -fv $(SRC)/*.o
	rm -fvi $(MAIN) $(TEST)