#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

#include "particule.h"
#include "event.h"
#include "heap.h"

#include "disc.h"
#include "simulation.h"



int main () {
	
	heap_double queue = nil();
	heap_double* p_queue = &queue;

	for (double i = 1.0;i<51.0;i++) {
		event event_for_test;
		event_for_test.temps = i;
		event_for_test.nb_collisions_for_a = 0;
		event_for_test.nb_collisions_for_b = 0;
		event_for_test.p_particle_a = NULL;
		event_for_test.p_particle_b = NULL;			
		insert(p_queue,event_for_test);
	}
	
	print_heap(p_queue);
	
	while (is_empty(p_queue) == 0) {
		event evenement = extract_min(p_queue);
		printf("%lf\n",evenement.temps);
	}
	
	print_heap(p_queue);
	
	deallocate_heap(p_queue);
	
	return 0;
}

