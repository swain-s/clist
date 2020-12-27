#ifndef STR_LIST_H
#define STR_LIST_H

#include <stdio.h>

typedef struct Node{
    char *str_val;
    struct Node *next;
} Node;

typedef struct List{
    int node_cnt;
    Node *first_node;
} List;

extern List *str_list(void);
extern void free_list(List *list);

extern size_t len(List *list);
extern char *val(List *list, int list_pos);
extern int pos(List *list, const char *str_val);
extern char** arr(List *list);
extern void print(List *list);

extern void append(List *list, const char *str_val);
extern void insert(List *list, const char *str_val, int list_pos);
extern void pop(List *list);
extern void del(List *list, int list_pos);
extern void cat(List *base_list, List *extra_list);
extern List *sublist(List *list, int begin_pos, int end_pos); /* common node */

#endif /* STR_LIST_H */
