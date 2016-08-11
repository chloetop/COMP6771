##
## Makefile for WordLadder
##

CPPFLAGS = -g -Wall -Werror -O2 -std=c++14

CXX=g++
LDFLAGS = 

# Add your own cpp files below
CLASS = genlib.cpp lexicon.cpp strutils.cpp
CLASS_H = $(SRCS:.cpp=.h)
SRCS = WordLadder.cpp $(CLASS)
OBJS = $(SRCS:.cpp=.o)
PROGS = wl

default : $(PROGS) 

$(PROGS) : depend $(OBJS)
	$(CXX) -o $@ $(OBJS)   $(LDFLAGS) 

# The dependencies below make use of make's default rules,
# under which a .o automatically depends on its .cpp and
# the action taken uses the $(CC) and $(CFLAGS) variables.
# These lines describe a few extra dependencies involved.

depend:: Makefile.dependencies $(SRCS) $(HDRS)

Makefile.dependencies:: $(SRCS) $(HDRS)
	$(CXX) $(CPPFLAGS) -MM $(SRCS) > Makefile.dependencies

-include Makefile.dependencies

clean : 
	/bin/rm -f *.o a.out core $(PROGS) Makefile.dependencies

TAGS : $(SRCS) $(HDRS)
	etags -t $(SRCS) $(HDRS)
