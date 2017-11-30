
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

typedef void* context;

typedef bool status;
const status status_fail = false;
const status status_ok = true;

typedef struct{
    context ctx;
    status (*dispatch)(context);
} Base;

typedef struct {
    char bytes[10];
} T1;

status T1_dispatch(context ctx)
{
    T1* t1 = (T1*) ctx;
    printf("%s", t1->bytes);

    return status_ok;
}

context T1_make(char* str)
{
    printf("%s", "Hello World!");
    printf("sizeof T1: %ldu ", sizeof(T1));
    T1* t1 = malloc(sizeof(T1));
    memcpy(str, t1->bytes, 9);
    t1->bytes[9] = '\0';

    return (context) t1;
}

void T1_destroy(context ctx)
{
    free((T1*)ctx);
}

int main (int argc, char** argv)
{
    context something = T1_make("Hi there");
    T1_dispatch(something);
    T1_destroy(something);

    printf("%s", "Hello World!");
    return EXIT_SUCCESS;
}
