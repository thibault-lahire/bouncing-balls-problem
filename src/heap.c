#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

#include "particule.h"
#include "event.h"
#include "heap.h"

heap_double nil() {
	heap_double aux;
	aux.root = NULL;
	aux.size = 0;
	return aux;
}

bool is_empty(heap_double * p_heap) {
	if (p_heap->root == NULL)
	{
		return (true);
	}
	else
	{
		return (false);
	}

}

void print_level(heap_double_node *p_node, int level) {
    for (int i = 0; i < level - 1; i++) {
        printf("   ");
    }

    if (p_node == NULL) {
        printf("%snil\n", level == 0 ? "" : " +-");
        return;
    }

    printf("%s(%lf)\n", level == 0 ? "" : " +-", p_node->ev.temps);
    print_level(p_node->p_node_son_a, level + 1);
    print_level(p_node->p_node_son_b, level + 1);
}

void print_heap(heap_double * p_heap) {
	print_level(p_heap->root, 0);
}

heap_double_node *go_to_father_node(heap_double * p_heap, int n) {
    char carray[ sizeof(int) * 8 + 1 ];
	int level = 0;
	
	do {
		carray[level] = ( n & 1 ) == 1 ? 'r':'l';
		level++;
		n = n>>1;
	} while ( n != 0 );
	
	heap_double_node * p_father_node = p_heap->root;
	
	for ( int i = level - 2 ; i>0;i--){
		if ( carray[i] == 'l' ){
			p_father_node = p_father_node->p_node_son_a;
		} else {
			p_father_node = p_father_node->p_node_son_b;
		}
	}
	return p_father_node;
}






void deallocate_heap(heap_double *p_heap) {
	int n = p_heap->size;
	if (n>0) {
		while (n!=1) {
			heap_double_node* father_of_the_last = go_to_father_node(p_heap,n);
			heap_double_node* pointer_to_the_last;
			if (father_of_the_last->p_node_son_b == NULL) {
				pointer_to_the_last = father_of_the_last->p_node_son_a;
				free(pointer_to_the_last);
				father_of_the_last->p_node_son_a = NULL;
				n--;
			} else {
				pointer_to_the_last = father_of_the_last->p_node_son_b;
				free(pointer_to_the_last);
				father_of_the_last->p_node_son_b = NULL;
				n--;
			}
		}
		free(p_heap->root);
		p_heap->root = NULL;
		p_heap->size = 0;
	} else {
	}
}




heap_double_node* swap( heap_double_node * p ) {
	if (p->p_node_son_a == NULL) {
		return NULL;
	} else {
		if (p->p_node_son_b == NULL) {
			double k = p->p_node_son_a->ev.temps;
			if (k <= p->ev.temps) {
				event tmp = p->ev;
				p->ev = p->p_node_son_a->ev;
				p->p_node_son_a->ev = tmp;
				return p->p_node_son_a;
			} else { 
				return NULL; 
			}
		} else {
			double i = p->p_node_son_a->ev.temps;
			double j = p->p_node_son_b->ev.temps;
			if (i<j) {
				if (p->ev.temps > i) {
					event tmp1 = p->ev;
					p->ev = p->p_node_son_a->ev;
					p->p_node_son_a->ev = tmp1;
					return p->p_node_son_a;
				} else {
					return NULL;
				}
			} else {
				if (p->ev.temps > j) {
					event tmp2 = p->ev;
					p->ev = p->p_node_son_b->ev;
					p->p_node_son_b->ev = tmp2;
					return p->p_node_son_b;
				} else {
					return NULL;
				}
			}
		}	
	}
}


event extract_min(heap_double *p_heap) {
	event res = p_heap->root->ev;
	int n = p_heap->size;
	if (n==1) {
		free(p_heap->root);
		p_heap->root = NULL;
		p_heap->size--;
		return res;
	} else {
		heap_double_node* father_of_the_last = go_to_father_node(p_heap,n);
		heap_double_node* pointer_to_the_last;
		if (father_of_the_last->p_node_son_b == NULL) {
			pointer_to_the_last = father_of_the_last->p_node_son_a;
			event event_of_the_last = pointer_to_the_last->ev;
			p_heap->root->ev = event_of_the_last;
			p_heap->size--;
			free(pointer_to_the_last);
			father_of_the_last->p_node_son_a = NULL;
		} else {
			pointer_to_the_last = father_of_the_last->p_node_son_b;
			event event_of_the_last = pointer_to_the_last->ev;
			p_heap->root->ev = event_of_the_last;
			p_heap->size--;
			free(pointer_to_the_last);
			father_of_the_last->p_node_son_b = NULL;
		}
	
		heap_double_node* p_current_node = p_heap->root;
	
		while (p_current_node != NULL) {
			p_current_node = swap(p_current_node);
		}
	
		return res;
	}

}



void insert(heap_double * p_heap, event eve)
{

	if ( p_heap->size == 0 ) {
		p_heap->size = 1;
		p_heap->root = (heap_double_node*)malloc( sizeof(heap_double_node) );
		p_heap->root->ev = eve;
		p_heap->root->p_node_father = NULL;
		p_heap->root->p_node_son_a = NULL;
		p_heap->root->p_node_son_b = NULL;
	} else {
		heap_double_node * p_father_node = go_to_father_node( p_heap, p_heap->size + 1);
		heap_double_node * p_new_node = (heap_double_node*)malloc( sizeof(heap_double_node) );
		
		p_new_node->ev = eve;
		p_new_node->p_node_son_a = NULL;
		p_new_node->p_node_son_b = NULL;
		p_new_node->p_node_father = p_father_node;
		
		if (p_father_node->p_node_son_a == NULL)
		{
			p_father_node->p_node_son_a = p_new_node;
		} else {
			p_father_node->p_node_son_b = p_new_node;
		}
		
		bool finished = false;
		heap_double_node * p_current_node = p_new_node;
		while (!finished ) {
			if ( p_current_node->p_node_father == NULL ){
				finished = true;
			} else if ( p_current_node->p_node_father->ev.temps > p_current_node->ev.temps ){
				event tmp = p_current_node->ev;
				p_current_node->ev = p_current_node->p_node_father->ev;
				p_current_node->p_node_father->ev = tmp;
			} else {
				finished = true;
			}
			p_current_node = p_current_node->p_node_father;
		}
		p_heap->size++;
	}
}







