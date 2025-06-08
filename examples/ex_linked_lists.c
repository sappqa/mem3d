#include <stdlib.h>
#include <stdio.h>

#define D if (0)


typedef struct ll_node {
    int value;
    struct ll_node* next;
} ll_node;

ll_node* lln_create(const int value, ll_node* const next) {
    ll_node* n = (ll_node*)malloc(sizeof(ll_node));
    if (!n) return NULL;

    n->value = value;
    n->next = next;
    return n;
}

void ll_print(const ll_node* ll_head) {
    int i = 0;
    while (ll_head != NULL) {
        D printf("node%d @ %p: %d\n", i, ll_head, ll_head->value);
        ll_head = ll_head->next;
        i++;
    }
}

ll_node* ll_alloc(unsigned int n) {
    ll_node* head = lln_create(0, NULL);
    ll_node* current = head;
    for (int i = 1; i < n; i++) {
        ll_node* next = lln_create(i, NULL);
        current->next = next;
        current = current->next;
    }
    return head;
}

void ll_dealloc(ll_node* ll_head) {
    while (ll_head != NULL) {
        ll_node* ptr = ll_head;
        ll_head = ll_head->next;
        free(ptr);
    }
}

void main() {
    ll_node* list = ll_alloc(400);
    ll_print(list);
    ll_dealloc(list);
    list = NULL;
}