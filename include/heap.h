/**
 * @file heap.h
 * @brief Define heaps and operations involving heaps
 *
 * This module exposes the structures and the fonctions helping the management of heaps.
 *
 * @author Thibault Lahire
 * @date 13 Mar 2018
 */ 


#ifndef HEAP_H
#define HEAP_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

#include "particule.h"
#include "event.h"


/**
 * @brief An alias for the structure representing the nodes of heaps
 */
typedef struct heap_double_node heap_double_node;


/**
 * @brief The structure representing a node of a heap
 */
struct heap_double_node {
	/** the event that has to be stored */
	event ev;
	/** a pointer to the first son of the node */
	heap_double_node * p_node_son_a;
	/** a pointer to the second son of the node */
	heap_double_node * p_node_son_b;
	/** a pointer to the father of the node */
	heap_double_node * p_node_father;
};


/**
 * @brief An alias for the structure representing the heaps
 */
typedef struct heap_double heap_double;


/**
 * @brief The structure representing a heap
 */
struct heap_double {
	/** a pointer to the first node of the heap */
	heap_double_node * root;
	/** the number of nodes in the heap */
	int size;
};


/**
 * @brief Create an empty heap
 *
 * @return an empty heap
 */
heap_double nil();


/**
 * @brief Tell us if the heap considered is empty or not
 *
 * @param p_heap is a pointer to a heap
 *
 * @return true if the heap is empty, false otherwise 
 */
bool is_empty(heap_double * p_heap);


/**
 * @brief Prints the heap under the node number 'level'
 *
 * @param p_node is a pointer to a node in the heap
 * @param level is the number of the node concerned 
 */
void print_level(heap_double_node *p_node, int level);


/**
 * @brief Prints the binary heap.
 *
 * @param p_heap is a pointer to the binary heap to be printed
 *
 * @pre `p_heap` is not `NULL`
 *
 * @post After the call, the binary heap is printed.
 */
void print_heap(heap_double * p_heap);


/**
 * @brief Gives a pointer to the father of the node considered
 *
 * @param p_heap is a pointer to the binary heap to be printed
 * @param n is the number of the node which father is searched
 * 
 * @return a pointer to a node, which is the father of the node considered
 */
heap_double_node *go_to_father_node(heap_double * p_heap, int n);


/**
 * @brief Insert a new event in the binary heap. The
 *        worst-case execution time of this function
 *        is guaranteed to be in \f$\log n\f$ where
 *        \f$n\f$ is the size of the binary heap.
 *
 * @param p_heap is a pointer to the heap in which the event is to be inserted
 * @param eve is the event to be inserted
 *
 * @post After the call, `p_heap` will point to a binary heap
 *       in which the event `eve` has been inserted.
 */
void insert(heap_double * p_heap, event eve);


/**
 * @brief Serve the extract_min function : If the event related to the node considered has an 
 * associated time less than the associated time of one of the two node sons, 
 * the function 'swap' swaps the two events concerned and actualizes the pointer to the node.   
 *
 * @param p is a pointer to a node in a heap
 *
 * @return a pointer to a node 
 */
heap_double_node* swap( heap_double_node * p );


/**
 * @brief Extract the next event, ie the event with the minimum 
 *        associated time in the binary heap. The
 *        worst-case execution time of this function
 *        is guaranteed to be in \f$\log n\f$ where \f$n\f$ is
 *        the size of the binary heap.
 *
 * @param p_heap is a pointer to the heap from which the event is to be extracted
 *
 * @return the event at the top in the binary heap
 *
 * @pre `p_heap` is not `NULL` and the binary heap is not empty
 */
event extract_min(heap_double *p_heap);


/**
 * @brief Deallocate the binary heap.
 *
 * @param p_heap is a pointer to the binary heap to be deallocated
 *
 * @pre `p_heap` is not `NULL`
 *
 * @post After the call, all memory regions used for the nodes
 *       are deallocated.
 */
void deallocate_heap(heap_double *p_heap);

#endif



