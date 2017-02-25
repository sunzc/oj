# compile oj problems

add-without-plus: add_without_plus.c
	gcc add_without_plus.c -o add-without-plus.oj

sort-linklist-in-nlogn: sort_linklist_in_nlogn.c
	gcc sort_linklist_in_nlogn.c -o sort-linklist-in-nlogn.oj
	
.PHONY: all
all: add-without-plus sort-linklist-in-nlogn
	@echo 'compile all the programs'

# Set our own.
.DEFAULT_GOAL := all

$(warning default goal is $(.DEFAULT_GOAL))

.PHONY: clean
clean:
	rm *.oj 
