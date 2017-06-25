########################################################################
# COSC1076 - Advanced Programming Techniques
# Semester 2 2014 Assignment #2
# Full Name        : Neil D'Souza
# Student Number   : s3600251
# Course Code      : COOSC1076
# Program Code     : BP096
# Start up code provided by Paul Miller
########################################################################

SOURCES=ppd_main.c ppd_menu.c ppd_options.c ppd_utility.c ppd_stock.c \
ppd_coin.c
HEADERS=ppd_main.h ppd_menu.h ppd_options.h ppd_utility.h ppd_stock.h \
ppd_coin.h ppd_shared.h
README=ppd_readme
MAKEFILE=Makefile

########################################################################
# Move this target to the end of the Makefile to zip up your code 
# when submitting. Do not submit your .dat files, or directories. 
# We only want the files that are part of your implementation.
########################################################################


CC = gcc
DEBUG = -g
CFLAGS = -Wall -ansi -pedantic $(DEBUG)	
PROG = ppd
OBJS = ppd_main.o ppd_coin.o ppd_stock.o ppd_utility.o ppd_options.o ppd_menu.o

all: $(OBJS)
	$(CC) $(CFLAGS) -o $(PROG) $(OBJS)

%.o: %.c 
	@echo “compiling ...” 
	$(CC) $(CFLAGS) -c -o $@ $^

# compile corresponding .c and .h files to .o files	
# $@ - output .o files
# $^ - input .c files

clean:
	@echo “cleaning ...”
	rm -f *.o $(PROG)

archive:
	zip $(USER)-a2 $(SOURCES) $(HEADERS) $(README) $(MAKEFILE)
