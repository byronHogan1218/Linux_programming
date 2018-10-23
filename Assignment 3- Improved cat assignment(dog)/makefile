#
# PROGRAM:    assign2
# PROGRAMMER: Byron Hogan
# LOGON ID:   Z1825194
# DATE DUE:   9-26-17
#

# Compiler variables
CCFLAGS =  -std=c++11
#add -Wall
# Rule to link object code files to create executable file
assign3: assign3.o dog.o
	g++ $(CCFLAGS) -o assign3 assign3.o dog.o

# Rules to compile source code file to object code
assign3.o: assign3.cpp
	g++ $(CCFLAGS) -c assign3.cpp

dog.o:dog.cpp dog.h
	g++ $(CCFLAGS) -c dog.cpp

# Pseudo-target to remove object code and executable files
clean:
	-rm *.o assign3
