main.exe: main.cpp Utility.o Exercise.o Menu.o 
	g++ -o main main.cpp Exercise.o Menu.o Utility.o

Exercise.o: Exercise.cpp
	g++ -c Exercise.cpp

Menu.o: Menu.cpp
	g++ -c Menu.cpp

Utility.o: Utility.cpp
	g++ -c Utility.cpp
