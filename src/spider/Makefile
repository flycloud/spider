
main: spider.o thread.o task.o
	g++ -g -std=c++0x -o main spider.o thread.o task.o -lpthread

spider.o: spider/spider.cpp
	g++ -g -std=c++0x -c spider/spider.cpp -I. -lpthread

task.o: spider/core/src/task.cpp
	g++ -g -std=c++0x -c spider/core/src/task.cpp -I.

thread.o: spider/core/src/thread.cpp
	g++ -g -std=c++0x -c spider/core/src/thread.cpp -I. -lpthread

clean:
	rm main spider.o thread.o task.o
