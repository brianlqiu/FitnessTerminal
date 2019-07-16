main.exe: main.cpp utility.o exercise.o menu.o workoutday.o
	g++ -o main main.cpp exercise.o menu.o utility.o workoutday.o

exercise.o: exercise.cpp
	g++ -c exercise.cpp

menu.o: menu.cpp
	g++ -c menu.cpp

utility.o: utility.cpp
	g++ -c utility.cpp

workoutday.o: workoutday.cpp 
	g++ -c workoutday.cpp

clean:
	del /P *.txt