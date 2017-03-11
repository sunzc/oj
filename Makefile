# compile oj problems

add-without-plus: add_without_plus.c
	gcc add_without_plus.c -o add-without-plus.oj

sort-linklist-in-nlogn: sort_linklist_in_nlogn.c
	gcc sort_linklist_in_nlogn.c -o sort-linklist-in-nlogn.oj

dp-rna: dp_rna_secondary_structure.c
	gcc dp_rna_secondary_structure.c -o dp-rna.oj 

tetra-vol: tetra_vol.cpp
	g++ tetra_vol.cpp -o vol.oj
	
.PHONY: all
all: add-without-plus sort-linklist-in-nlogn dp-rna tetra-vol
	@echo 'compile all the programs'

# Set our own.
.DEFAULT_GOAL := all

$(warning default goal is $(.DEFAULT_GOAL))

.PHONY: clean
clean:
	rm *.oj 
