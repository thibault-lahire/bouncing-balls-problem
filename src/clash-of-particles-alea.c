#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

#include "particule.h"
#include "event.h"
#include "heap.h"

#include "disc.h"
#include "simulation.h"

#define SIZE 600

int main() {
	
	// Définition d'une constante utile pour la suite
	double inf = INFINITY;
	
	// On demande à l'utilisateur le nombre de particules qu'il souhaite
    int size;
    printf("Combien de particules souhaitez-vous ?\n");
    scanf("%d",&size);
    
	partic* array[size]; // array contiendra des pointeurs vers des particules. 
	// Il y aura autant de pointeurs que de particules. 

	for (int i = 0;i<size;i++) {
		array[i] = malloc(sizeof(partic));
		array[i]->x = (double)rand() / (double)RAND_MAX;
		array[i]->y = (double)rand() / (double)RAND_MAX;
		array[i]->vx = ((double)rand() / (double)RAND_MAX)*0.001 - 0.0005;
		array[i]->vy = ((double)rand() / (double)RAND_MAX)*0.001 - 0.0005;
		array[i]->m = 0.5;
		array[i]->r = 0.01;
	}
    
	// On demande à l'utilisateur la durée totale de la simulation
	double limit_time;
	printf("Temps limite pour la simulation ?\n");
	scanf("%lf",&limit_time);
	
	// On demande à l'utilisateur la période d'insertion des événements de rafraichissement
	double raf;
	printf("Période de rafraichissement -2.0 fonctionne bien- ?\n");
	scanf("%lf",&raf);
	
	// On demande à l'utilisateur s'il souhaite rajouter la gravité
	int gravity;
	printf("Doit-on prendre en compte la gravité ? Oui:1 Non:0\n");
	scanf("%d",&gravity);
	
	// Création de l'arbre
	heap_double Q = nil();
	heap_double* p_Q = &Q;

	// On fait l'initialisation : Pour chaque particule, on insère ses prochaines collisions potentielles uniquement si elles ont
	// un temps inférieur au temps limite de simlation.
	for (int i = 0; i<size ; i++) {
		
		// On s'intéresse au cas d'une collision avec un mur vertical
		if (collision_vertical(array[i]) > limit_time) {
		} else {
			event event_for_ver;
			event_for_ver.temps = collision_vertical(array[i]);
			event_for_ver.nb_collisions_for_a = 0;
			event_for_ver.nb_collisions_for_b = 0;
			event_for_ver.p_particle_a = NULL;
			event_for_ver.p_particle_b = array[i];			
			insert(p_Q,event_for_ver);
		}
		
		// On s'intéresse au cas d'une collision avec un mur horizontal
		if (collision_horizontal(array[i],gravity) > limit_time) {
		} else {
			event event_for_hor;
			event_for_hor.temps = collision_horizontal(array[i],gravity);
			event_for_hor.nb_collisions_for_a = 0;
			event_for_hor.nb_collisions_for_b = 0;
			event_for_hor.p_particle_a = array[i];
			event_for_hor.p_particle_b = NULL;
			insert(p_Q,event_for_hor);
		}

		// On s'intéresse au cas d'une collision avec une autre particule
		// La boucle commence à i+1 : il est inutile de considérer le choc de la particule a avec la particule b et le choc
		// de la particule b avec la particule a : c'est le même événement ! 
		for (int j = i+1; j<size ; j++) {
			if (collision_between_two_particles(array[i],array[j]) > limit_time) {
			} else {
				event event_for_col;
				event_for_col.temps = collision_between_two_particles(array[i],array[j]);
				event_for_col.nb_collisions_for_a = 0;
				event_for_col.nb_collisions_for_b = 0;
				event_for_col.p_particle_a = array[i];
				event_for_col.p_particle_b = array[j];
				insert(p_Q,event_for_col);
			}
		}
		
	}
	
	// On initialise trois variables qui vont servir pour la simulation.
	double time = 0.0;
	double time2 = 0.0;
	double refresh = 0.0;
	
	// On insert un événement de rafraichissement au temps 0.
	event event_for_refr;
	event_for_refr.temps = refresh;
	event_for_refr.nb_collisions_for_a = 0;
	event_for_refr.nb_collisions_for_b = 0;
	event_for_refr.p_particle_a = NULL;
	event_for_refr.p_particle_b = NULL;			
	insert(p_Q,event_for_refr);

	// On ouvre la fenêtre graphique.
	CreateWindow("Boules blanches sur fond noir", SIZE, SIZE);
	
	// On définit trois variables qui vont être utiles.
	event evenement;
	event valid_event;
	double delta_t;
	
	// Entrons dans la boucle principale
	while (p_Q->size != 0) {
		// On stocke dans la variable evenement le prochaine événement. 
		evenement = extract_min(p_Q);

		// On crée d'une certaine manière la variable valid_event.
		// valid_event s'apparente à un événement de rafraichissement qui a un temps infini.
		valid_event.temps = inf;
		valid_event.p_particle_a = NULL;
		valid_event.p_particle_b = NULL;
		valid_event.nb_collisions_for_a = 0;
		valid_event.nb_collisions_for_b = 0;
		
		// valid_event deviendra evenement si l'événement est jugé valide d'après les tests ci-dessous.
		// La définition précédente de valid_event sera donc remplacée.
		if ((evenement.p_particle_a == NULL) && (evenement.p_particle_b == NULL)) {
			// c'est le cas d'un rafraichissement : l'événement est nécessairement valide.
			valid_event = evenement;
		} else if ((evenement.p_particle_a != NULL) && (evenement.p_particle_b == NULL)) {
			// c'est le cas d'une collision avec un mur horizontal : s'il y a coincidence sur le nombre de collisions de la particule
			// concernée, alors l'événement est valide. Si l'événement n'est pas valide, alors la variable valid_event n'est pas
			// actualisée, le tour dans le while s'arrête ici car evenement n'est pas réutilisé plus tard.  
			if (evenement.p_particle_a->nb_collisions == evenement.nb_collisions_for_a) {
				valid_event = evenement;
			} else {
			}
		} else if ((evenement.p_particle_a == NULL) && (evenement.p_particle_b != NULL)) {
			// Idem avec mur vertical
			if (evenement.p_particle_b->nb_collisions == evenement.nb_collisions_for_b) {
				valid_event = evenement;
			} else {
			}
		} else {
			// Idem pour une collision entre deux particules
			if ((evenement.nb_collisions_for_a == evenement.p_particle_a->nb_collisions) && (evenement.nb_collisions_for_b == evenement.p_particle_b->nb_collisions)) { 
				valid_event = evenement;
			} else {
			}
		}

		// On souhaite savoir, à ce stade du programme, si valid_event est resté l'événement infini qui ne correspond à rien
		// défini au début ou s'il est devenu un "véritable" événement.
		int indic;
		if (valid_event.temps != inf) {
			indic = 1;
		} else {
			indic = 0;
		}


		// Quand on insère un événement dans l'arbre, on l'insère au temps actuel + la durée calculée pour la collision.
		if (indic == 1) {		
			// time2 est la date de l'événement qui va être traité.
			time2 = valid_event.temps;
			// time est resté "à l'étape d'avant". En soustrayant la date de l'événement qui va être traité à la date du dernier
			// événement traité, on obtient la durée qui va nous permettre d'actualiser la position des particules.
			delta_t = time2 - time;
			time = valid_event.temps;
		} else {
		// On ne fait rien ! Il ne faudrait pas actualiser les temps avec de l'infini...
		}
		
		if ((valid_event.p_particle_a == NULL) && (valid_event.p_particle_b == NULL)) {
			// C'est le cas d'un rafraichissement.
			if (indic == 1) {
				// Il faut actualiser sinon on se pourrait se retrouver avec un ancien delta_t
				for (int i = 0;i<size;i++) {
					update_particle_position(array[i],delta_t,gravity);
				}
			}
			// On affiche les particules.
			draw_particles(size,array);
			
			// On insère un événement de rafraichissement à la valeur choisie par l'utilisateur au début.
			event event_for_refresh;
			refresh = refresh + raf;
			event_for_refresh.temps = refresh;
			event_for_refresh.nb_collisions_for_a = 0;
			event_for_refresh.nb_collisions_for_b = 0;
			event_for_refresh.p_particle_a = NULL;
			event_for_refresh.p_particle_b = NULL;			
			insert(p_Q,event_for_refresh);
			
		} else if ((valid_event.p_particle_a != NULL) && (valid_event.p_particle_b == NULL)) {
			// C'est le cas d'une collision avec un mur horizontal.

			for (int i = 0;i<size;i++) {
				update_particle_position(array[i],delta_t,gravity);
			}
			
			// On actualise les paramètres de la particule concernée.	
			update_particle_velocity_after_horizontal(valid_event.p_particle_a);
			valid_event.p_particle_a->nb_collisions++;

			// On regarde à présent les collisions potentielles futures de la particule impliquée dans le choc avec le mur horizontal.
			// Si l'événement doit se produire au-delà de la simlation, on ne l'insère pas dans l'arbre.
			if (collision_vertical(valid_event.p_particle_a) > limit_time) {
			} else {
				event event_for_ver3;
				event_for_ver3.temps = time + collision_vertical(valid_event.p_particle_a);
				event_for_ver3.nb_collisions_for_a = 0;
				event_for_ver3.nb_collisions_for_b = valid_event.p_particle_a->nb_collisions;
				event_for_ver3.p_particle_a = NULL;
				event_for_ver3.p_particle_b = valid_event.p_particle_a;			
				insert(p_Q,event_for_ver3);
			}
		
			if (collision_horizontal(valid_event.p_particle_a,gravity) > limit_time) {
			} else {
				event event_for_hor3;
				event_for_hor3.temps = time + collision_horizontal(valid_event.p_particle_a,gravity);
				event_for_hor3.nb_collisions_for_a = valid_event.p_particle_a->nb_collisions;
				event_for_hor3.nb_collisions_for_b = 0;
				event_for_hor3.p_particle_a = valid_event.p_particle_a;
				event_for_hor3.p_particle_b = NULL;				
				insert(p_Q,event_for_hor3);
			}

			for (int j = 0; j<size ; j++) {
				if (array[j] == valid_event.p_particle_a){
					// On ne fait rien, on comparerait un choc de la particule avec elle-même.
				} else {
					if (collision_between_two_particles(valid_event.p_particle_a,array[j]) > limit_time) {
					} else {
						event event_for_col3;
						event_for_col3.temps = time + collision_between_two_particles(valid_event.p_particle_a,array[j]);
						event_for_col3.nb_collisions_for_a = valid_event.p_particle_a->nb_collisions;
						event_for_col3.nb_collisions_for_b = array[j]->nb_collisions;
						event_for_col3.p_particle_a = valid_event.p_particle_a;
						event_for_col3.p_particle_b = array[j];
						insert(p_Q,event_for_col3);
					}
				}
			}
		} else if ((valid_event.p_particle_a == NULL) && (valid_event.p_particle_b != NULL)) {
			// C'est le cas d'une collision avec un mur vertical.

			for (int i = 0;i<size;i++) {
				update_particle_position(array[i],delta_t,gravity);
			}

			// On actualise les paramètres de la particule concernée.
			update_particle_velocity_after_vertical(valid_event.p_particle_b);
			valid_event.p_particle_b->nb_collisions++;

			// On regarde à présent les collisions potentielles futures de la particule impliquée dans le choc avec le mur vertical.
			// Si l'événement doit se produire au-delà de la simulation, on ne l'insère pas dans l'arbre.
			if ( collision_vertical(valid_event.p_particle_b) > limit_time ) {
			} else {
				event event_for_ver2;
				event_for_ver2.temps = time + collision_vertical(valid_event.p_particle_b);
				event_for_ver2.nb_collisions_for_a = 0;
				event_for_ver2.nb_collisions_for_b = valid_event.p_particle_b->nb_collisions;
				event_for_ver2.p_particle_a = NULL;
				event_for_ver2.p_particle_b = valid_event.p_particle_b;			
				insert(p_Q,event_for_ver2);
			}
	
			if (collision_horizontal(valid_event.p_particle_b,gravity) > limit_time) {
			} else {
				event event_for_hor2;
				event_for_hor2.temps = time + collision_horizontal(valid_event.p_particle_b,gravity);
				event_for_hor2.nb_collisions_for_a = valid_event.p_particle_b->nb_collisions;
				event_for_hor2.nb_collisions_for_b = 0;
				event_for_hor2.p_particle_a = valid_event.p_particle_b;
				event_for_hor2.p_particle_b = NULL;
				insert(p_Q,event_for_hor2);
			}
			
			for (int j = 0; j<size ; j++) {
				if (array[j] == valid_event.p_particle_b){
					// On ne fait rien, on comparerait un choc de la particule avec elle-même.
				} else {
					if (collision_between_two_particles(valid_event.p_particle_b,array[j]) > limit_time) {
					} else {
						event event_for_col2;
						event_for_col2.temps = time + collision_between_two_particles(valid_event.p_particle_b,array[j]);
						event_for_col2.nb_collisions_for_a = valid_event.p_particle_b->nb_collisions;
						event_for_col2.nb_collisions_for_b = array[j]->nb_collisions;
						event_for_col2.p_particle_a = valid_event.p_particle_b;
						event_for_col2.p_particle_b = array[j];
						insert(p_Q,event_for_col2);
					}
				}
			}
		} else {
			// C'est le cas d'un choc entre deux particules.
			for (int i = 0;i<size;i++) {
				update_particle_position(array[i],delta_t,gravity);
			}

			// On actualise les paramètres des particules concernées.
			update_particle_velocity_after_choc(valid_event.p_particle_a,valid_event.p_particle_b);
			valid_event.p_particle_a->nb_collisions++;
			valid_event.p_particle_b->nb_collisions++;
				
			// On regarde à présent les collisions potentielles futures des particules impliquées dans le choc.
			// Si l'événement doit se produire à l'infini, on ne l'insère pas dans l'arbre.
			if (collision_vertical(valid_event.p_particle_b) > limit_time) {
			} else {
				event event_for_ver4;
				event_for_ver4.temps = time + collision_vertical(valid_event.p_particle_b);
				event_for_ver4.nb_collisions_for_a = 0;
				event_for_ver4.nb_collisions_for_b = valid_event.p_particle_b->nb_collisions;
				event_for_ver4.p_particle_a = NULL;
				event_for_ver4.p_particle_b = valid_event.p_particle_b;			
				insert(p_Q,event_for_ver4);
			}
		
			if (collision_horizontal(valid_event.p_particle_b,gravity) > limit_time) {
			} else {
				event event_for_hor4;
				event_for_hor4.temps = time + collision_horizontal(valid_event.p_particle_b,gravity);
				event_for_hor4.nb_collisions_for_a = valid_event.p_particle_b->nb_collisions;
				event_for_hor4.nb_collisions_for_b = 0;
				event_for_hor4.p_particle_a = valid_event.p_particle_b;
				event_for_hor4.p_particle_b = NULL;
				insert(p_Q,event_for_hor4);
			}
			
			for (int j = 0; j<size ; j++) {
				if ((array[j] == valid_event.p_particle_b) || (array[j] == valid_event.p_particle_a)) {
						// On ne considère pas les événements consistant en un choc de la particule avec elle-même ou de 
						// celle qu'elle vient juste de percuter.
				} else {
					if (collision_between_two_particles(valid_event.p_particle_b,array[j]) > limit_time) {
					} else {
						event event_for_col4;
						event_for_col4.temps = time + collision_between_two_particles(valid_event.p_particle_b,array[j]);
						event_for_col4.nb_collisions_for_a = valid_event.p_particle_b->nb_collisions;
						event_for_col4.nb_collisions_for_b = array[j]->nb_collisions;
						event_for_col4.p_particle_a = valid_event.p_particle_b;
						event_for_col4.p_particle_b = array[j];
						insert(p_Q,event_for_col4);
					}
				}
			}
				
			// On fait de même pour l'autre particule.
			if (collision_vertical(valid_event.p_particle_a) > limit_time) {
			} else {
				event event_for_ver5;
				event_for_ver5.temps = time + collision_vertical(valid_event.p_particle_a);
				event_for_ver5.nb_collisions_for_a = 0;
				event_for_ver5.nb_collisions_for_b = valid_event.p_particle_a->nb_collisions;
				event_for_ver5.p_particle_a = NULL;
				event_for_ver5.p_particle_b = valid_event.p_particle_a;			
				insert(p_Q,event_for_ver5);
			}
				
			if (collision_horizontal(valid_event.p_particle_a,gravity) > limit_time) {
			} else {
				event event_for_hor5;
				event_for_hor5.temps = time + collision_horizontal(valid_event.p_particle_a,gravity);
				event_for_hor5.nb_collisions_for_a = valid_event.p_particle_a->nb_collisions;
				event_for_hor5.nb_collisions_for_b = 0;
				event_for_hor5.p_particle_a = valid_event.p_particle_a;
				event_for_hor5.p_particle_b = NULL;
				insert(p_Q,event_for_hor5);
			}

			for (int j = 0; j<size ; j++) {
				if ((array[j] == valid_event.p_particle_a) || (array[j] == valid_event.p_particle_b)) {
						// Même commentaire
				} else {
					if (collision_between_two_particles(valid_event.p_particle_a,array[j]) > limit_time) {
					} else {
						event event_for_col5;
						event_for_col5.temps = time + collision_between_two_particles(valid_event.p_particle_a,array[j]);
						event_for_col5.nb_collisions_for_a = valid_event.p_particle_a->nb_collisions;
						event_for_col5.nb_collisions_for_b = array[j]->nb_collisions;
						event_for_col5.p_particle_a = valid_event.p_particle_a;
						event_for_col5.p_particle_b = array[j];
						insert(p_Q,event_for_col5);
					}
				}
			}
		}
		
		// On utilise le temps défini par l'utilisateur pour arrêter la simulation.
		if (refresh > limit_time) {
			break;
		}
	
	}
	
	// On ferme l'affichage graphique et on libère l'espace que l'on avait alloué pour la simulation.
	CloseWindow();
	
	for (int i = 0;i<size;i++) {
		free(array[i]);
	}
	deallocate_heap(p_Q);
	
	
	return 0;
}
