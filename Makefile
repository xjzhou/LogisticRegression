CC=g++
C_OPTS=-O2
#LIBS=-lrt -lpthread

all:
	$(CC) $(C_OPTS) $(LIBS) LinearRegression.cpp -o linreg
	$(CC) $(C_OPTS) $(LIBS) main.cpp LogisticRegression.cpp -o logreg

run:
	rm linreg
	rm logreg

clean:
	rm -f *.o
	rm -f lr
