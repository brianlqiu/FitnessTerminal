main.exe: main.cpp utility.o exercise.o menu.o workoutday.o workoutplan.o
	g++-9.1.0 -o main main.cpp exercise.o menu.o utility.o workoutday.o workoutplan.o

exercise.o: exercise.cpp
	g++-9.1.0 -c exercise.cpp

menu.o: menu.cpp
	g++-9.1.0 -c menu.cpp

utility.o: utility.cpp
	g++-9.1.0 -c utility.cpp

workoutday.o: workoutday.cpp 
	g++-9.1.0 -c workoutday.cpp

workoutplan.o: workoutplan.cpp
	g++-9.1.0 -c workoutplan.cpp -std=c++17 -lstdc++fs

cleanetxt:
	rm -i *.txt

cleanobj:
	rm -i *.o

fcleanetxt:
	rm *.txt

cleandtxt:
	rm -i ./PPL/*.txt