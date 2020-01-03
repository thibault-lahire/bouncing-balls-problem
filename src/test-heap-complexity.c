#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <time.h>

#include "particule.h"
#include "event.h"
#include "heap.h"

#include "disc.h"
#include "simulation.h"

#define SIZE 900


int main() {
	
	heap_double Q = nil();

	heap_double* p_Q = &Q;
	
	FILE *p_file = NULL;
	
	p_file = fopen("scripts/data_complexity_heap.csv", "w");
	
	if (p_file == NULL) {
		fprintf(stderr, "Cannot write to file fact.txt!\n");
		exit(EXIT_FAILURE);
	}
	
	int N = 200000;
	for (int n = 20;n<N;n=2*n) {
		event* my_array[n];
		event my_array2[n];
		for (int i = 0;i<n;i++) {
			my_array[i] = malloc(sizeof(event));
			my_array[i]->temps = (double)rand() / (double)RAND_MAX;;
			my_array[i]->p_particle_a = NULL;
			my_array[i]->p_particle_b = NULL;
			my_array[i]->nb_collisions_for_a = 0;
			my_array[i]->nb_collisions_for_b = 0;
		}
	
		
		
		clock_t start = clock();
		for (int i = 0;i<n;i++) {
			insert(p_Q,*my_array[i]);
		}
		clock_t end = clock();
		double elapsed_time = (double) (end - start)/CLOCKS_PER_SEC;
	
		clock_t start2 = clock();
		for (int i = 0;i<n;i++) {
			my_array2[i] = extract_min(p_Q);
		}	
		clock_t end2 = clock();
		double elapsed_time2 = (double) (end2 - start2)/CLOCKS_PER_SEC;
	
		fprintf(p_file, "%d, %lf, %lf\n", n, elapsed_time, elapsed_time2);
	
		for (int i = 0;i<n;i++) {
			free(my_array[i]);
		}
		
		// Si je ne mets pas la ligne suivante, il met un warning
		double aux = 0.0;
		for (int i = 0;i<n;i++) {
			aux = aux + my_array2[i].temps;
		}
		printf("%lf\n",aux);
		
	}
	
	
	
	fclose(p_file);
	p_file = NULL;

	deallocate_heap(p_Q);

	
	return 0;
}

