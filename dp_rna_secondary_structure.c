#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

#define NRNA	4

char RNA_BASE_ELEMENTS[NRNA] = {'A', 'U', 'C', 'G'};

char *RNA_generator(int size);
char *RNA_generator(int size) {
	int i, ran;
	char *rna;

	assert(size>0);

	srand(time(NULL));

	rna = (char *)malloc(size + 1);
	if (rna == NULL) {
		printf("ERROR! malloc failed!\n");
		exit(1);
	}

	for (i = 0; i < size; i++) {
		ran = rand() % NRNA;
		rna[i] = RNA_BASE_ELEMENTS[ran];
	}

	rna[size] = 0;

	return rna;
}

void initialize_opt(int *opt, int size);
void initialize_opt(int *opt, int size) {
	int i;

	for (i = 0; i < size - 4; i++) {
		opt[i * size + i] =  0;
		opt[i * size + i + 1] =  0;
		opt[i * size + i + 2] =  0;
		opt[i * size + i + 3] =  0;
	}

	return;
}

bool match(char a, char b); 
bool match(char a, char b) {
	if (a == 'A' && b == 'U')
		return true;
	else if (a == 'U' && b == 'A')
		return true;
	else if (a == 'C' && b == 'G')
		return true;
	else if (a == 'G' && b == 'C')
		return true;
	else
		return false;
}

void explore_track(int *track, int len, int i, int j);
void explore_track(int *track, int len, int i, int j) {
	int t;

	assert(track != NULL && i >= 0 && j >= 0);

	if (i >= j) {
		printf("%d is not matched\n", i);
		return;
	} else {
		t = track[i * len + j];

		assert(t >= i && t < j);

		if (t == j - 1) {
			printf("%d is not matched\n", j);
			explore_track(track, len, i, j - 1);
		} else {
			printf("%d matches %d\n", t, j);
			explore_track(track, len, i, t - 1);
			explore_track(track, len, t + 1, j - 1);
		}
	}

	return;
}

void print_result(int *track, int len); 
void print_result(int *track, int len) {
	assert(len > 0 && track != NULL);

	printf("matching result for RNA of size %d:\n", len);
	explore_track(track, len, 0, len - 1);
}

int dp_rna_secondary_structure(char *rna);
int dp_rna_secondary_structure(char *rna) {
	int len, i, j, k;
	int a, b, t, max, tmp, loc;
	int *opt;
	int *track;
	int res;

	assert(rna != NULL);

	len = strlen(rna);
	assert(len > 0);

	// simple rna length <= 4, no free energy, return directly
	if (len <= 4)
		return 0;

	// allocate space to store optimal result for subproblems
	opt = (int *)malloc(sizeof(int) * len * len);
	if (opt == NULL) {
		printf("ERROR! malloc failed!\n");
		exit(1);
	}

	// track every choice to recover final match results
	track = (int *)malloc(sizeof(int) * len * len);
	if (track == NULL) {
		printf("ERROR! malloc failed!\n");
		exit(1);
	}

	initialize_opt(opt, len);

	for (k = 5; k < len - 1; k++)
		for (i = 0; i < len - k; i++) {
			j = i + k;

			// opt(i, j) = max(a, b)
			// a record the case when loc j is not matched, a = opt(i, j-1)
			a = opt[i * len + j - 1];

			// b record the result of the subproblem with biggest value
			// b = max(1 + opt(i, t-1) + opt(t+1, j-1))
			max = 0;
			loc = -1;
			for (t = i; t < j - 4; t++) {
				if (match(rna[t], rna[j])) {
					if (t != i) // loc j matches loc t, t != i
						tmp = 1 + opt[i * len + t - 1] + opt[(t + 1) * len + j - 1];
					else // loc j matches loc i, so subproblem opt(i, t-1) == 0, omitted here
						tmp = 1 + opt[(t + 1) * len + j - 1];
				} else
					continue;

				if (tmp > max) {
					max = tmp;
					loc = t;
				}
			} 

			b = max;

			if (a >= b) {
				opt[i * len + j] = a;
				track[i * len + j] = j - 1;
			} else {
				opt[i * len + j] = b;
				track[i * len + j] = loc;
			}
		}

	print_result(track, len);

	res = opt[0 * len + len - 1];

	// free space
	free(opt);
	free(track);

	return res;
}

void print_rna(char *rna);
void print_rna(char *rna) {
	int i, size;

	assert(rna != NULL);

	printf("RNA looks like:\n");
	size = strlen(rna);
	for (i = 0; i < size; i++)
		printf("%c ", rna[i]);

	printf("\n");
}

int main(int argc, char *argv[]) {
	int size, res;
	char *rna;

	size = 0;
	while (size == 0) {
		printf("please input problem size:\n");
		scanf("%d", &size);
		printf("size is %d\n", size);
	}

	rna = RNA_generator(size);

	print_rna(rna);

	res = dp_rna_secondary_structure(rna);

	printf("max free energy is %d\n", res);
}
