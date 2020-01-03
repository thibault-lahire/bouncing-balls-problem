/**
 * @file simulation.h
 * @brief Draw particles with SDL
 *
 * This module exposes a function that makes it possible to draw particles.
 *
 * @author Thibault Lahire
 * @date 13 Mar 2018
 */ 

#ifndef SIMULATION_H
#define SIMULATION_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

#include "particule.h"
#include "event.h"
#include "heap.h"
#include "disc.h"


/**
 * @brief Draw particles in the GUI
 *
 * @param nb is the number of particles.
 * @param cloud[nb] is a list of pointers to particles.
 */
void draw_particles(int nb, partic* cloud[nb]);


#endif
