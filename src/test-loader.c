#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

#include "particule.h"
#include "event.h"
#include "heap.h"

#include "disc.h"
#include "simulation.h"

#define SIZE 900


int main() {
	
    FILE *p_file = NULL;

    p_file = fopen("data/two-particles-simple.txt", "r");

    if (p_file == NULL) {
        fprintf(stderr, "Cannot read file %s!\n", "data/two-particles-simple.txt");
        exit(EXIT_FAILURE);
    }


    int line_nb       = 1;
    double first_float = 0;
    double second_float= 0;
	double third_float = 0;
	double fourth_float= 0;
	double fifth_float = 0;
	double sixth_float = 0;
    int fscanf_result = 0;
    int size = 0;


	char header_buffer[1024];
	fgets(header_buffer, 1024, p_file);
	
	fscanf(p_file,"%d",&size);
	
	printf("%d\n\n",size);
	
	partic* array[size]; //contiendra des pointeurs vers des particules. Il y aura autant de pointeurs que de particules. Au début, toutes les particules ont 0 collisions.

	for (int i = 0;i<size;i++) {
		array[i] = malloc(sizeof(partic));
	}

    fscanf_result = fscanf(p_file, "%lf,%lf,%lf,%lf,%lf,%lf", &first_float, &second_float, &third_float, &fourth_float, &fifth_float, &sixth_float);
	int j = 0;
    while (fscanf_result != EOF) {
        if (fscanf_result != 6) {
            fprintf(stderr, "Line number %d is not syntactically correct!\n",
                     line_nb);
            exit(EXIT_FAILURE);
        }
		
		array[j]->x = first_float;
		array[j]->y = second_float;;
		array[j]->vx = third_float;
		array[j]->vy = fourth_float;
		array[j]->m = fifth_float;
		array[j]->r = sixth_float;
		array[j]->nb_collisions = 0;

		j++;
        line_nb = line_nb + 1;
		fscanf_result = fscanf(p_file, "%lf,%lf,%lf,%lf,%lf,%lf", &first_float, &second_float, &third_float, &fourth_float, &fifth_float, &sixth_float);
    }

    fclose(p_file);

    p_file = NULL;

	for (int i = 0;i<size;i++) {
		printf("%lf\n", array[i]->x);
		printf("%lf\n",array[i]->y);
		printf("%lf\n",array[i]->vx);
		printf("%lf\n",array[i]->vy);
		printf("%lf\n",array[i]->m);
		printf("%lf\n",array[i]->r);
		printf("%d\n\n\n",array[i]->nb_collisions);
	}

	for (int i = 0;i<size;i++) {
		free(array[i]);
	}
	
	return 0;
}
	
