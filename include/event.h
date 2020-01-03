/**
 * @file event.h
 * @brief Define events and create them
 *
 * This module exposes a function that makes it possible to create the event you want.
 *
 * @author Thibault Lahire
 * @date 13 Mar 2018
 */ 


#ifndef EVENT_H
#define EVENT_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

#include "particule.h"


/**
 * @brief An alias for the structure representing the events
 */
typedef struct event event;


/**
 * @brief The structure representing the events
 */
struct event {
	/** the date of the event */
	double temps;
	/** the first particle concerned */
	partic * p_particle_a;
	/** the second particle concerned */
	partic * p_particle_b;
	/** the number of collisions in which the first particle was involved at the creation of the event */
	int nb_collisions_for_a;
	/** the number of collisions in which the second particle was involved at the creation of the event */
	int nb_collisions_for_b;
};



#endif

