#include <stdio.h>
#include "list/str_list.h"

List *a_list()
{
    List *list = NULL;
    list = str_list();
    append(list, "a");
    append(list, "b");
    append(list, "c");
    append(list, "d");
    append(list, "e");
    append(list, "f");
    append(list, "g");
    return list;
}

void test_pop()
{
    List *list = a_list();
    pop(list);
    pop(list);
    pop(list);
    pop(list);
    pop(list);
    pop(list);
    append(list, "d");
    pop(list); print(list);
    free_list(list);
}

void test_del()
{
    List *list = a_list(); print(list);
    del(list, 1); print(list);
    del(list, 3); print(list);
    del(list, -1); print(list);
    del(list, -1); print(list);
    del(list, 0); print(list);
    free_list(list);
}

void test_insert()
{
    List *list = a_list(); print(list);
    insert(list, "1", 1); print(list);
    insert(list, "2", 2); print(list);
    insert(list, "0", 0); print(list);
    insert(list, "10", 9); print(list);
    free_list(list);
}

void test_val()
{
    List *list = a_list(); print(list);
    printf("%s %s %s %s\n", val(list, 0), val(list, 5), val(list, 6), val(list, 2));
    printf("%s\n", val(list, -1));
    free_list(list);
}

void test_pos()
{
    List *list = a_list(); print(list);
    printf("%d %d %d %d\n", pos(list, "a"), pos(list, "f"), pos(list, "g"), pos(list, "  "));
    printf("%d\n", pos(list, "c"));
    free_list(list);
}

int main(int argc, const char * argv[]) {
    List *alist = a_list();
    print(alist);
    char *val2 = val(alist, 2);
    printf("%s\n", val2);
    
    
    strcpy(val2, "aaaaaaaaa");
    print(alist);
    
    val2 = "zzzzz";
    printf("%s\n", val2);
    print(alist);
    
    return 0;
}
