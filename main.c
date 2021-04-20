#include <stdio.h>
#include "interface.h"

void print_list(const LList* list);

int main(int argc, char* argv[])
{
    LList* list = create_list();
    int* a = (int*) calloc(1, sizeof(int));
    void* data;
    
    if (initialize_list(&list) == 0)
    {
        for (int i = 0; i < 10; i++)
        {
            a = (int*) calloc(1, sizeof(int));
            *a = i;

            insert_first(&list, (void*) a);
        }

        print_list(list);

        delete_first(&list, &data);
        printf("%d\n", *((int*) data));
        print_list(list);
    }

    return 0;
}

/* ================================================================ */

void print_list(const LList* list)
{
    printf("List size: %zu\n", list->size);
    printf("(");

    if (list->size > 0)
    {
        Node* t = list->head;

        while (t)
        {
            printf("%d", *((int*) t->data));

            if (t->next != NULL)
                printf(", ");

            t = t->next;
        }
    }

    printf(")\n");
}