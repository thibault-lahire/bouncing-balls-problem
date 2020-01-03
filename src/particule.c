#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

#include "particule.h"

#define G 0.0000001

void print_particle(partic * p_particle) {
	printf("%lf\n",p_particle->x);
	printf("%lf\n",p_particle->y);
	printf("%lf\n",p_particle->vx);
	printf("%lf\n",p_particle->vy);
	printf("%lf\n",p_particle->m);
	printf("%lf\n",p_particle->r);
	printf("%d\n",p_particle->nb_collisions);
}



void update_particle_position(partic * p_particle, double period, int grav) {
	if (grav == 0) {
		p_particle->x = p_particle->x + period*(p_particle->vx);
		p_particle->y = p_particle->y + period*(p_particle->vy);	
	} else {
		p_particle->x = p_particle->x + period*(p_particle->vx);
		p_particle->y = p_particle->y + period*(p_particle->vy) - G*period*period*0.5 ;
		p_particle->vy = p_particle->vy - period*G;
	}
}


double inf = INFINITY;

double collision_vertical(partic * p_particle) {
	if ( p_particle->vx > 0.0 ) {
		return (1.0 - p_particle->x - p_particle->r)/p_particle->vx;
	}
	if ( p_particle->vx < 0.0 ) {
		return (p_particle->r - p_particle->x)/p_particle->vx;
	}
	else {
		return inf;
	}
}

double collision_horizontal(partic * p_particle, int grav) {
	if (grav == 0) {
		if ( p_particle->vy > 0.0 ) {
			return (1.0 - p_particle->y - p_particle->r)/p_particle->vy;
		}
		if ( p_particle->vy < 0.0 ) {
			return (p_particle->r - p_particle->y)/p_particle->vy;
		}
		else {
			return inf;
		}
	} else {
		if ( p_particle->vy > pow(2*G*(1 - p_particle->y),0.5) ) {
			return (p_particle->vy - pow((p_particle->vy)*(p_particle->vy) - 2.0*G*(1 - p_particle->y - p_particle->r),0.5))/G;
		} else {
			return (p_particle->vy + pow(p_particle->vy*p_particle->vy + 2.0*G*p_particle->y,0.5))/G;
		}
	}
}



void update_particle_velocity_after_vertical(partic * p_particle) {
	p_particle->vx = - p_particle->vx;
}

void update_particle_velocity_after_horizontal(partic * p_particle) {
	p_particle->vy = - p_particle->vy;
}


double collision_between_two_particles(partic * p_p1,partic * p_p2) {
	double delta_v_scal_delta_v = pow((p_p2->vx - p_p1->vx),2) + pow((p_p2->vy - p_p1->vy),2);
	double delta_p_scal_delta_p = pow(((p_p2->x) - (p_p1->x)),2) + pow(((p_p2->y) - (p_p1->y)),2); 
	double delta_p_scal_delta_v = ((p_p2->x) - (p_p1->x))*(p_p2->vx - p_p1->vx) + ((p_p2->y) - (p_p1->y))*(p_p2->vy - p_p1->vy);
	double k = pow(p_p1->r+p_p2->r,2);
	if (pow(delta_p_scal_delta_v,2) - delta_v_scal_delta_v*(delta_p_scal_delta_p - k) >= 0) {
		double res = -(delta_p_scal_delta_v + pow(pow(delta_p_scal_delta_v,2) - delta_v_scal_delta_v*(delta_p_scal_delta_p - k),0.5))/delta_v_scal_delta_v;
		if (res > 0) {
			return res;
		} else {
			return inf;
		}
	} else {
		return inf;
	}
}



void update_particle_velocity_after_choc(partic * p_p1,partic * p_p2) {
	double delta_p_scal_delta_v = ((p_p2->x) - (p_p1->x))*(p_p2->vx - p_p1->vx) + ((p_p2->y) - (p_p1->y))*(p_p2->vy - p_p1->vy);
	double k = pow(p_p1->r+p_p2->r,2);
	
	p_p1->vx = p_p1->vx + 2*(p_p2->m)*delta_p_scal_delta_v*(p_p2->x - p_p1->x)/((p_p1->m+p_p2->m)*k);
	p_p1->vy = p_p1->vy + 2*(p_p2->m)*delta_p_scal_delta_v*(p_p2->y - p_p1->y)/((p_p1->m+p_p2->m)*k);	
	
	p_p2->vx = p_p2->vx - 2*(p_p1->m)*delta_p_scal_delta_v*(p_p2->x - p_p1->x)/((p_p1->m+p_p2->m)*k);
	p_p2->vy = p_p2->vy - 2*(p_p2->m)*delta_p_scal_delta_v*(p_p2->y - p_p1->y)/((p_p1->m+p_p2->m)*k);
}

