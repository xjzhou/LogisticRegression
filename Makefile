CC=g++
C_OPTS=-O2
#LIBS=-lrt -lpthread

all:
	$(CC) $(C_OPTS) $(LIBS) main.cpp LogisticRegression.cpp -o lr

run:
	./lr

clean:
	rm -f *.o
	rm -f lr
