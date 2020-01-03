/**
 * @file particule.h
 * @brief Define particles and operations involving particles
 *
 * This module exposes the structure and the fonctions helping the management of particles.
 *
 * @author Thibault Lahire
 * @date 13 Mar 2018
 */ 


#ifndef PARTICULE_H
#define PARTICULE_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>


/**
 * @brief An alias for the structure representing the particles
 */
typedef struct partic partic;


/**
 * @brief The structure representing the particles
 */
struct partic {
	/** the position of the particle on the x-axis */
	double x;
	/** the position of the particle on the y-axis */
	double y;
	/** the speed of the particle in the x-direction */
	double vx;
	/** the speed of the particle in the y-direction */
	double vy;
	/** the mass of the particle */
	double m;
	/** the radius of the particle */
	double r;
	/** the number of collisions of the particle */
	int nb_collisions;
};


/**
 * @brief Prints the properties of a particle
 *
 * @param p_particle is a pointer to the particle concerned
 */
void print_particle(partic * p_particle);


/**
 * @brief Update the particle position after a certain period of time
 *
 * @param p_particle is a pointer to the particle concerned
 * @param period is the time separating the present and the realization of the event
 * @param grav is an integer that makes it possible to know if gravity is taken into account
 */
void update_particle_position(partic * p_particle, double period, int grav);


/**
 * @brief Calculate the time for a collision between a particle and a vertical wall
 *
 * @param p_particle is a pointer to the particle concerned
 *
 * @return the duration between now and the collision of the particle with one of the two vertical walls 
 */
double collision_vertical(partic * p_particle);


/**
 * @brief Calculate the time for a collision between a particle and an horizontal wall
 *
 * @param p_particle is a pointer to the particle concerned
 *
 * @return the duration between now and the collision of the particle with one of the two horizontal walls 
 */
double collision_horizontal(partic * p_particle, int grav);


/**
 * @brief Update the particle velocity after a choc with a vertical wall
 *
 * @param p_particle is a pointer to the particle concerned
 */
void update_particle_velocity_after_vertical(partic * p_particle);


/**
 * @brief Update the particle velocity after a choc with an horizontal wall
 *
 * @param p_particle is a pointer to the particle concerned
 */
void update_particle_velocity_after_horizontal(partic * p_particle);


/**
 * @brief Calculate the time for a collision between two particles
 *
 * @param p_p1 is a pointer to the first particle concerned
 * @param p_p2 is a pointer to the second particle concerned
 *
 * @return the duration between now and the collision of the two particles
 */
double collision_between_two_particles(partic * p_p1,partic * p_p2);


/**
 * @brief Update the velocity of the two particles after the collision 
 *
 * @param p_p1 is a pointer to the first particle concerned
 * @param p_p2 is a pointer to the second particle concerned
 */
void update_particle_velocity_after_choc(partic * p_p1,partic * p_p2);

#endif

