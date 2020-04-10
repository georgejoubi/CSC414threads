CC=cl
RM=del
example: example.cpp
	$(CC) example.cpp
readerswriters: readersWriters.cpp
	$(CC) readersWriters.cpp

waitForOthers: waitForOthers.cpp
	$(CC) waitForOthers.cpp
all: example readerswriters waitForOthers
	.
.PHONY:clean
clean:
	$(RM) *.obj *.exe *.vcx* *.sln

