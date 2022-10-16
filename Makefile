#Luke Kaplan
#sjd7wr
#10-12-22
#Makefile

CXX=clang++ $(CXXFLAGS)
CXXFLAGS=-Wall
DEBUG=-g

a.out: AVLNode.o AVLPathTest.o AVLTree.o
	$(CXX) $(DEBUG) AVLNode.o AVLPathTest.o AVLTree.o -o a.out

AVLNode.o: AVLNode.cpp AVLNode.h
AVLPathTest.o: AVLPathTest.cpp AVLTree.h AVLNode.h
AVLTree.o: AVLTree.cpp AVLNode.h AVLTree.h

.PHONY: clean
clean:
	-rm -f *.o *~ a.out

