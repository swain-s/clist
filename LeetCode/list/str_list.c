#include "str_list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void handle_err()
{
    printf("ERROR: \n"); /* TODO : I am lazy */
    exit(1);
}

List *str_list(void)
{
    List *new_list = NULL;
    
    new_list = (List *)malloc(sizeof(List));
    if (new_list == NULL) {
        handle_err();
    }
    
    new_list->node_cnt = 0;
    new_list->first_node = NULL;
    return new_list;
}

void free_list(List *list)
{
    Node *cur_node = NULL;
    Node *to_free = NULL;
    
    if (list == NULL){
        return;
    }
    
    cur_node = list->first_node;
    while(cur_node != NULL){
        to_free = cur_node;
        cur_node = cur_node->next;
        free(to_free->str_val);
        free(to_free);
    }
    
    free(list);
}

size_t len(List *list)
{
    return list->node_cnt;
}

char *val(List *list, int list_pos)
{
    Node *target_node = NULL;
    
    if (list_pos == -1) {
        list_pos = list->node_cnt - 1;
    }
    
    if (list_pos < 0 || list_pos >= list->node_cnt) {
        handle_err();
    }
    
    target_node = list->first_node;
    for (size_t i = 0; i < list_pos; i++) {
        target_node = target_node->next;
    }
    
    return target_node->str_val;
}

int pos(List *list, const char *str_val)
{
    Node *target_node = NULL;
    
    if (list->node_cnt < 1) {
        return -1; /* -1 means : cannot find str_val in list */
    }
    
    target_node = list->first_node;
    for (int i = 0; i < list->node_cnt; i++) {
        if (strcmp(target_node->str_val, str_val) == 0) {
            return i;
        }
        target_node = target_node->next;
    }
    
    return -1;
}

char** arr(List *list)
{
    return NULL; /* TODO */
}

void print(List *list)
{
    Node *cur_node = NULL;
    
    printf("(%d)[", list->node_cnt);
    
    cur_node = list->first_node;
    for (size_t i = 0; i < list->node_cnt; i++) {
        if (i != list->node_cnt - 1) {
            printf("'%s', ", cur_node->str_val);
        } else {
            /* print the last node */
            printf("'%s'", cur_node->str_val);
        }
        cur_node = cur_node->next;
    }
    
    printf("]\n");
}

void append(List *list, const char *str_val)
{
    /* last_node -> next = new_node */
    Node *last_node = NULL;
    Node *new_node = NULL;
    char *new_node_str_val = NULL;
    
    new_node_str_val = (char *)malloc(strlen(str_val));
    if (new_node_str_val == NULL) {
        handle_err();
    }
    
    new_node = (Node *)malloc(sizeof(Node));
    if (new_node == NULL) {
        handle_err();
    }
    strcpy(new_node_str_val, str_val);
    new_node->str_val = new_node_str_val;
    new_node->next = NULL;
    
    if (list->first_node == NULL) {
        list->first_node = new_node;
    } else {
        last_node = list->first_node;
        for (int i = 0; i < (list->node_cnt - 1); i++) {
            last_node = last_node->next;
        }
        last_node->next = new_node;
    }
    
    list->node_cnt ++;
}

void insert(List *list, const char *str_val, int list_pos)
{
    Node *new_node = NULL;
    Node *pre_new_node = NULL;
    char *new_node_str_val = NULL;
    
    if (list_pos < 0 || list_pos >= list->node_cnt) {
        handle_err();
    }
    
    new_node_str_val = (char *)malloc(strlen(str_val));
    if (new_node_str_val == NULL) {
        handle_err();
    }
    
    new_node = (Node *)malloc(sizeof(Node));
    if (new_node == NULL) {
        handle_err();
    }
    strcpy(new_node_str_val, str_val);
    new_node->str_val = new_node_str_val;
    
    if (list_pos == 0) {
        new_node->next = list->first_node;
        list->first_node = new_node;
    } else {
        pre_new_node = list->first_node;
        for (int i = 0; i < (list_pos - 1); i++) {
            pre_new_node = pre_new_node->next;
        }
        new_node->next = pre_new_node->next;
        pre_new_node->next = new_node;
    }
    
    list->node_cnt ++;
}

void pop(List *list)
{
    Node *last_node = NULL;
    Node *pre_last_node = NULL;
    
    if (list->first_node == 0) {
        return;
    } else if (list->node_cnt == 1) {
        last_node = list->first_node;
        list->first_node = NULL;
    } else {
        pre_last_node = list->first_node;
        for (int i = 0; i < (list->node_cnt - 2); i++) {
            pre_last_node = pre_last_node->next;
        }
        last_node = pre_last_node->next;
        pre_last_node->next = NULL;
    }
    
    free(last_node->str_val);
    free(last_node);
    list->node_cnt --;
}

void del(List *list, int list_pos)
{
    Node *target_node = NULL;
    Node *pre_target_node = NULL;
    
    if (list_pos == -1) {
        list_pos = list->node_cnt - 1;
    }
    
    if (list_pos == 0) {
        target_node = list->first_node;
        list->first_node = list->first_node->next;
    } else if (list_pos > 0 && list_pos < list->node_cnt) {
        pre_target_node = list->first_node;
        for (int i = 0; i < list_pos - 1; i++) {
            pre_target_node = pre_target_node->next;
        }
        target_node = pre_target_node->next;
        pre_target_node->next = target_node->next;
    } else {
        handle_err();
    }
    
    free(target_node->str_val);
    free(target_node);
    list->node_cnt --;
}

void cat(List *base_list, List *extra_list)
{
    Node *last_node = NULL;
    
    if (base_list->node_cnt == 0) {
        base_list->first_node = extra_list->first_node;
        base_list->node_cnt += extra_list->node_cnt;
        return;
    } else {
        last_node = base_list->first_node;
        for (int i = 0; i < (base_list->node_cnt - 1); i++) {
            last_node = last_node->next;
        }
        last_node->next = extra_list->first_node;
        base_list->node_cnt += extra_list->node_cnt;
    }
}

List *sublist(List *list, int begin_pos, int end_pos)
{
    List *new_list = NULL;
    Node *cur_node = NULL;
    int list_pos = 0;
    
    if (end_pos == -1) {
        end_pos = list->node_cnt + 1;
    }
    
    if (begin_pos < end_pos || begin_pos < 0 || begin_pos >= list->node_cnt || end_pos < 0 || end_pos >= list->node_cnt) {
        return NULL;
    }
    
    new_list = (List *)malloc(sizeof(List));
    if (new_list == NULL) {
        handle_err();
    }
    
    cur_node = list->first_node;
    for (; list_pos < begin_pos; list_pos++) {
        cur_node = cur_node->next;
    }
    new_list->first_node = cur_node;
    
    for(;list_pos < end_pos - 1; list_pos++) {
        cur_node = cur_node->next;
    }
    cur_node->next = NULL;
    
    new_list->node_cnt = end_pos - begin_pos;
    return new_list;
}
