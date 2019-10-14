#ifndef _LINKEDLIST_H
#define _LINKEDLIST_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>


#define LIST_WITH_HEADNODE

// typedef struct _list_head_singly{
//     struct _list_head_singly * next;
// }list_head_singly;

// typedef struct _list_head_double{
//     struct _list_head_double * next, * prev;
// }list_head_double;

// #define singly_list(name) list_head_singly (name) = {NULL, NULL}
// #define circular_singly_list(name) list_head_singly (name) = { &(name), &(name)}

// #define double_list(name) list_head_double (name) = {NULL, NULL}
// #define circular_double_list(name) list_head_double (name) = { &(name), &(name) }

typedef struct _list_head{
    struct _list_head * next, * prev;
}list_head;

#define singly_list(name) list_head (name) = {NULL, NULL}
#define circular_singly_list(name) list_head (name) = { &(name), NULL}

#define double_list(name) list_head (name) = {NULL, NULL}
#define circular_double_list(name) list_head (name) = { &(name), &(name) }

#define circular_singly_list_ptr(ptr) do{(ptr)->next = (ptr);}while(0)
#define circular_double_list_ptr(ptr) do{(ptr)->next = (ptr); (ptr)->prev = (ptr); }while(0)

#define list_entry(ptr, type, member) (type *)((unsigned long)(ptr) - (unsigned long)&((type *)0)->member)

#endif