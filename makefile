CC = gcc
MAKE = make

all:
	@echo    "usage: $(MAKE) <target>"
	@echo    ""
	@echo -e "\tclean    remove all extraneous files"
	@echo    ""

%.o: %.c
	gcc -I ../../CoOS/kernel $@

clean:
	rm -rf *.o *.gch
