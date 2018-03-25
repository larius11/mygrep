FILES :=                                 \
    mygrep.c		                     \
    mypattern.c		                     \
    myfilter.c

CXX      		:= gcc
ALLO			:= mygrep.o mypattern.o myfilter.o

all: clean mygrep

mygrep: $(ALLO)
	$(CXX) $(ALLO) -o mygrep

mygrep.o:
	$(CXX) -c mygrep.c 

mypattern.o:
	$(CXX) -c mypattern.c 

myfilter.o:
	$(CXX) -c myfilter.c 

test: mygrep
	@echo 'Testing'

clean:
	rm -f *.o
	rm -f mygrep