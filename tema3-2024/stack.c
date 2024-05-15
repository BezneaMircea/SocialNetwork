/*
 * Copyright (c) 2024, <> Beznea Mircea <bezneamirceaandrei21@gmail.com>
 *                        Ghenescu Stefan <stefan.ghenescu2005@gmail.com>
 */


#include "structuri.h"

stack_t *init_stack(unsigned int data_size) {
	stack_t *stack = malloc(sizeof(stack_t));
	DIE(!stack, "Eroare la alocare\n");

	stack->list = ll_create(data_size);

	return stack;
}

/** @param stack: Stiva a carei dimensiune vrem sa o aflam.
 *  @return Returneaza dimensiunea stivei, -1 la eroare. 
 */
int get_size_stack(stack_t *stack) {
	if (!stack)
		return -1;

	if (!stack->list)
		return -1;

	return stack->list->size;
}

/** @param stack: Stiva
 *  @brief Verifica daca stiva e goala sau nu
 *  @return Intoarce 1 daca stiva e goala, 0 daca nu e goala si -1 la eroare
 */
int is_empty_stack(stack_t *stack) {
	if (!stack)
		return -1;

	if (!stack->list)
		return -1;

	if (stack->list->size == 0)
		return 1;
	
	return 0;
}


/** @brief Functia intoarce informatia din varful stivei
 *  @param stack: Stiva
 *  @return Informatia din varful stivei, NULL in caz contrar
 */
void* peek_stack(stack_t *stack) {
	if (!stack)
		return NULL;

	if (!stack->list)
		return NULL;

	if (!stack->list->size)
		return NULL;

	return stack->list->head->data;
}

/** @brief Functia sterge nodul din varful stivei si elibereaza memoria
 *  @param stack: Stiva
 */
void pop_stack(stack_t *stack) {
	if (!stack)
		return;

	if (!stack->list)
		return;

	if (stack->list->size == 0)
		return;
	
	ll_node_t *nod = ll_remove_nth_node(stack->list, 0);
	free(nod->data);
	free(nod);
}

/** @param stack: Stiva
 *  @param new_data: Noua informatie de adaugat in varful stivei
 *  @brief Functia adauga un nou nod continand new_data in varful stivei
 */
void push_stack(stack_t *stack, void *new_data) {
	if (!stack)
		return;

	if (!stack->list)
		return;
	ll_add_nth_node(stack->list, 0, new_data);
}

/** @brief Iti goleste stiva
 *  @param stack: stiva 
 */
void clear_stack(stack_t *stack) {
	for (int i = 0; i < stack->list->size; i++)
		pop_stack(stack);
}

/** @brief Iti elibereaza memoria utilizata pentru tot continutul stivei
 *         si elibereaza memoria folosita pentru aceasta. Facand ca stack
 * 		   sa pointeze spre NULL.
 *  @param stack: Stiva
 */
void purge_stack(stack_t **stack) {
	stack_t *stack_to_free = *stack;

	ll_free(&stack_to_free->list);
	free(stack_to_free);

	*stack = NULL;
}
