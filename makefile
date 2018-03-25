CXX      		:= gcc
ALLO			:= mygrep.o mypattern.o myfilter.o isDigit.o set.o range.o otoc.o

all: clean mygrep

mygrep: $(ALLO)
	$(CXX) $(ALLO) -o mygrep

mygrep.o:
	$(CXX) -c mygrep.c 

mypattern.o:
	$(CXX) -c mypattern.c 

myfilter.o:
	$(CXX) -c myfilter.c 

isDigit.o:
	$(CXX) -c isDigit.c

set.o:
	$(CXX) -c set.c

range.o:
	$(CXX) -c range.c

otoc.o:
	$(CXX) -c otoc.c

clean:
	rm -f *.o
	rm -f mygrep