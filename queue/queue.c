// PingPongOS - PingPong Operating System
// EDUARDO KALUF - GRR20241770

#include "queue.h"
#include <stdlib.h>
#include <stdio.h>



struct node_t {
    struct node_t *next;
    void *item;
};

struct queue_t {
    int n;
    struct node_t *head;
    struct node_t *tail;
    struct node_t *iterator;
};

struct queue_t *queue_create() {
    struct queue_t *queue = malloc(sizeof(struct queue_t));

    if (!queue)
	return NULL;

    queue->n = 0;
    queue->head = NULL;
    queue->tail = NULL;
    queue->iterator = NULL;

    return queue;
}

int queue_destroy(struct queue_t *queue) {
     if (queue)
         return NOERROR
    
    // Do not use iterator
     queue->iterator = queue->tail;
     for (int i = 0; i < queue->n; i++) {
         queue->tail = queue->tail->next;
        
         free(queue->iterator);
     }


     return NOERROR	
 }

int queue_add(struct queue_t *queue, void *item) {

	if (!queue)
	    return ERROR;

	struct node_t node = malloc(sizeof(struct node_t));

	if (!node)
		return ERROR;

	node->next = tail;
	node->item = item;

	if (queue->n == 1) {
		queue->head = node;  
    }
}

int queue_del(struct queue_t *queue, void *item) {
    
    struct node_t node = queue->tail;

    for (int i = 0; i < queue_size(queue); i++) {

        if (node->item == item) {
            
        }

    }


}

bool queue_has(struct queue_t *queue, void *item) {

    struct node_t node = queue->tail;
    for (int i = 0; i < queue_size(queue); i++) {
        
        if (node->item == item)
            return true;

        node = node->next;
    }

    return false;
}
int queue_size(struct queue_t *queue) {
    if (!queue)
	return ERROR;

    return queue->n;
}

void *queue_head(struct queue_t *queue) {

    if (!queue)
        return ERROR

    return queue->head->item;
}

void *queue_next(struct queue_t *queue) {
    if (!queue)
        return ERROR

    return queue->iterator->next->item;
}

void *queue_item(struct queue_t *queue) {
    if (!queue)
        return ERROR

    return queue->iterator->item;
}

void queue_print(char *name, struct queue_t *queue, void(func)(void *)) {
    
	printf("%s: ", name);

	if (!queue) {
	    printf("undef");
	    return;
	}
	
	printf("[ ");

	for (int i = 0; i <= queue_size(queue); i++) {
	
		if (!queue->iterator->item) {
			printf("undef ");
		}
		else {
			func(queue->iterator->item);
			printf(" ");		
		}
	
	}

	printf("] (%d items)\n", queue_size(queue));
}

