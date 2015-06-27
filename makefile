home    = /home/courses/cop4530p/LIB
cpp     = $(home)/cpp
tcpp    = $(home)/tcpp
tests   = $(home)/tests
proj    = .
incpath = -I$(proj) -I$(cpp) -I$(tcpp)
#CC      = g++ -std=c++11 -Wall -Wextra
CC      = clang++ -std=c++11 -Wall -Wextra

project: wb.x

wb.x:   main_wb.o xstring.o wordbench.o
	$(CC) -o wb.x main_wb.o xstring.o wordbench.o

main_wb.o: $(proj)/wordbench.h $(proj)/main_wb.cpp
	$(CC) $(incpath)  -c $(proj)/main_wb.cpp

wordbench.o: $(proj)/wordbench.h $(proj)/wordbench.cpp $(proj)/wordify.cpp
	$(CC) $(incpath)  -c $(proj)/wordbench.cpp

xstring.o: $(cpp)/xstring.h $(cpp)/xstring.cpp
	$(CC) $(incpath)  -c $(cpp)/xstring.cpp

