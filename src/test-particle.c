#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include "particule.h"


int main()
{
	
	partic pa_1;
	pa_1.x=0.25;
	pa_1.y=0.25;
	pa_1.vx=0.5;
	pa_1.vy=0.0;
	pa_1.m=0.5;
	pa_1.r=0.01;
	pa_1.nb_collisions=0;
	
	partic pa_2;
	pa_2.x=0.25;
	pa_2.y=0.25;
	pa_2.vx=-0.5;
	pa_2.vy=0.0;
	pa_2.m=0.5;
	pa_2.r=0.01;
	pa_2.nb_collisions=0;	
	
	partic pa_3;
	pa_3.x=0.25;
	pa_3.y=0.25;
	pa_3.vx=0.0;
	pa_3.vy=0.5;
	pa_3.m=0.5;
	pa_3.r=0.01;
	pa_3.nb_collisions=0;	
	
	partic pa_4;
	pa_4.x=0.25;
	pa_4.y=0.25;
	pa_4.vx=0.0;
	pa_4.vy=-0.5;
	pa_4.m=0.5;
	pa_4.r=0.01;
	pa_4.nb_collisions=0;	
	
	partic pa_5;
	pa_5.x=0.25;
	pa_5.y=0.25;
	pa_5.vx=0.25;
	pa_5.vy=-0.4;
	pa_5.m=0.5;
	pa_5.r=0.01;
	pa_5.nb_collisions=0;	
	
	partic pa_6;
	pa_6.x=0.5;
	pa_6.y=0.25;
	pa_6.vx=0.0;
	pa_6.vy=0.0;
	pa_6.m=0.8;
	pa_6.r=0.005;
	pa_6.nb_collisions=0;	
	
	partic pa_7;
	pa_7.x=0.75;
	pa_7.y=0.25;
	pa_7.vx=-0.25;
	pa_7.vy=0.0;
	pa_7.m=0.5;
	pa_7.r=0.01;
	pa_7.nb_collisions=0;	
	
	partic pa_8;
	pa_8.x=0.6;
	pa_8.y=0.8;
	pa_8.vx=0.25;
	pa_8.vy=-0.4;
	pa_8.m=0.8;
	pa_8.r=0.005;
	pa_8.nb_collisions=0;
	
	partic pa_1_bis = pa_1;
	partic pa_1_ter = pa_1;
	partic pa_1_qua = pa_1;
	
	partic pa_1_pr = pa_1;
	partic pa_2_pr = pa_2;
	partic pa_3_pr = pa_3;
	partic pa_4_pr = pa_4;
	partic pa_5_pr = pa_5;

	
	double i1 = collision_vertical(&pa_1);
	printf("%lf\n",i1);
	printf("\n");
	update_particle_velocity_after_vertical(&pa_1);	
	print_particle(&pa_1);
	printf("\n\n\n");	
	
	double i2 = collision_vertical(&pa_2);
	printf("%lf\n",i2);
	printf("\n");
	update_particle_velocity_after_vertical(&pa_2);	
	print_particle(&pa_2);
	printf("\n\n\n");

	double i3 = collision_vertical(&pa_3);
	printf("%lf\n",i3);	
	printf("\n");
	double i4 = collision_vertical(&pa_4);
	printf("%lf\n",i4);
	printf("\n\n\n");
	
	double i5 = collision_vertical(&pa_5);
	printf("%lf\n",i5);
	printf("\n");
	update_particle_velocity_after_vertical(&pa_5);	
	print_particle(&pa_5);	
	printf("\n\n\n");
	
	double j1 = collision_horizontal(&pa_1_pr,0);
	printf("%lf\n",j1);
	printf("\n");
	double j2 = collision_horizontal(&pa_2_pr,0);
	printf("%lf\n",j2);	
	printf("\n\n\n");
	
	double j3 = collision_horizontal(&pa_3_pr,0);
	printf("%lf\n",j3);
	printf("\n");
	update_particle_velocity_after_horizontal(&pa_3_pr);
	print_particle(&pa_3_pr);
	printf("\n\n\n");
	
	double j4 = collision_horizontal(&pa_4_pr,0);
	printf("%lf\n",j4);
	printf("\n");
	update_particle_velocity_after_horizontal(&pa_4_pr);
	print_particle(&pa_4_pr);
	printf("\n\n\n");
	
	double j5 = collision_horizontal(&pa_5_pr,0);
	printf("%lf\n",j5);
	printf("\n");
	update_particle_velocity_after_horizontal(&pa_5_pr);
	print_particle(&pa_5_pr);
	printf("\n\n\n");
	
	double k1 = collision_between_two_particles(&pa_1_bis,&pa_6);
	printf("%lf\n",k1);
	printf("\n");
	update_particle_position(&pa_1_bis,k1,0);	
	update_particle_position(&pa_6,k1,0);
	update_particle_velocity_after_choc(&pa_1_bis,&pa_6);
	print_particle(&pa_1_bis);
	printf("\n");
	print_particle(&pa_6);
	printf("\n\n\n");
	
	double k2 = collision_between_two_particles(&pa_1_ter,&pa_7);
	printf("%lf\n",k2);
	printf("\n");
	update_particle_position(&pa_1_ter,k2,0);	
	update_particle_position(&pa_7,k2,0);
	update_particle_velocity_after_choc(&pa_1_ter,&pa_7);
	print_particle(&pa_1_ter);
	printf("\n");
	print_particle(&pa_7);
	printf("\n\n\n");	
	
	double k3 = collision_between_two_particles(&pa_1_qua,&pa_8);
	printf("%lf\n",k3);	
	update_particle_position(&pa_1_qua,k3,0);	
	update_particle_position(&pa_8,k3,0);
	update_particle_velocity_after_choc(&pa_1_qua,&pa_8);
	print_particle(&pa_1_qua);
	printf("\n");
	print_particle(&pa_8);
	printf("\n\n\n");

	double k4 = collision_between_two_particles(&pa_7,&pa_8);
	printf("%lf\n",k4);

	return 0;
}

