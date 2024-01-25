main: *.cpp	*.h
	g++ -std=c++98 *.cpp *.h -o main

run: main
	./main

clean:
	-rm main -f *.o *.out

all:
	g++ -g -std=c++98 *.cpp -o main && ./main