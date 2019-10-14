#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "LinkedList.h"

#define L1_MAX  3
#define L2_MAX  3

circular_double_list(test);

typedef struct _test_t{
    list_head list;
    int test_i;
    float test_f;
    char * test_c;
}test_t;

test_t test_1;


int main(){
    time_t tm;
    time(&tm);
    char * t;
    t = ctime(&tm);
    list_head * p = (list_head *) malloc(sizeof(list_head));
    circular_singly_list_ptr(p);

    printf("%s\n", t);
    printf("test address 0x%08x\n", &test);
    printf("test next is 0x%08x\n", test.next);
    printf("test prev is 0x%08x\n", test.prev);

    printf("test address 0x%08x\n", p);
    printf("test next is 0x%08x\n", p->next);
    printf("test prev is 0x%08x\n", p->prev);

    printf("offset of ptr 0x%016x 0x%016x 0x%016x 0x%016x\n", (unsigned long)(&((test_t *)0)->list), (unsigned long)(&((test_t *)0)->test_i), (unsigned long)(&((test_t *)0)->test_f), (unsigned long)(&((test_t *)0)->test_c));
    printf("offset of ptr 0x%016x 0x%016x 0x%016x 0x%016x 0x%016x\n", (unsigned long)&test_1, (unsigned long)&test_1.list, (unsigned long)&test_1.test_i, (unsigned long)&test_1.test_f, (unsigned long)&test_1.test_c);

    printf("test address is 0x%016x\n", list_entry(&test_1.test_i, test_t, test_i));
}

