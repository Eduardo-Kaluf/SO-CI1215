// PingPongOS - PingPong Operating System
// EDUARDO KALUF - GRR20241770

#include <stdlib.h>
#include <stdio.h>

#include "queue.h"

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
    if (!queue)
        return ERROR;

    struct node_t *node = queue->head;
    for (int i = 0; i < queue->n; i++) {
        queue->head = queue->head->next;

        free(node);

        node = queue->head;
    }

    free(queue);

    return NOERROR;
}

int queue_add(struct queue_t *queue, void *item) {
    if (!queue)
        return ERROR;

    struct node_t *node = malloc(sizeof(struct node_t));

    if (!node)
        return ERROR;

    node->next = NULL;
    node->item = item;

    if (queue_size(queue) == 0) {
        queue->head = node;
        queue->iterator = node;
    } else {
        queue->tail->next = node;
    }

    queue->tail = node;
    queue->n++;

    return NOERROR;
}

int queue_del(struct queue_t *queue, void *item) {
    if (!queue || queue_size(queue) == 0)
        return ERROR;

    struct node_t *node = NULL;
    struct node_t *aux = queue->head;

    for (int i = 0; i < queue_size(queue); i++) {
        if (aux->item == item) {
            if (queue->iterator->item == item)
                queue->iterator = queue->iterator->next;

            if (node == NULL)
                queue->head = aux->next;
            else
                node->next = aux->next;

            if (aux == queue->tail)
                queue->tail = node;

            free(aux);

            queue->n--;

            return NOERROR;
        }

        node = aux;
        aux = aux->next;
    }

    return ERROR;
}

bool queue_has(struct queue_t *queue, void *item) {
    if (!queue)
        return false;

    const struct node_t *node = queue->head;
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
    if (!queue || queue_size(queue) == 0)
        return NULL;

    queue->iterator = queue->head;

    return queue->iterator->item;
}

void *queue_next(struct queue_t *queue) {
    if (!queue || queue_size(queue) == 0)
        return NULL;

    queue->iterator = queue->iterator->next;

    if (!queue->iterator)
        return NULL;

    return queue->iterator->item;
}

void *queue_item(struct queue_t *queue) {
    if (!queue || queue_size(queue) == 0 || !queue->iterator)
        return NULL;

    return queue->iterator->item;
}

void queue_print(char *name, struct queue_t *queue, void (func)(void *)) {
    printf("%s: ", name);

    if (!queue) {
        printf("undef\n");
        return;
    }

    const struct node_t *node = queue->head;

    printf("[ ");

    for (int i = 0; i < queue_size(queue); i++) {
        if (!node->item | !func) {
            printf("undef ");
        } else {
            func(node->item);
            printf(" ");
        }

        node = node->next;
    }

    printf("] (%d items)\n", queue_size(queue));
}
