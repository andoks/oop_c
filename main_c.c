
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

typedef void* context;

typedef bool status;
const status status_fail = false;
const status status_ok = true;

#define UNUSED(x) (void)(x)

typedef struct{
    context ctx;
    status (*dispatch)(context);
    void (*destroy)(context);
} super;

typedef struct {
    char* bytes;
} T1;

status T1_dispatch(context ctx)
{
    T1* t1 = (T1*) ctx;
    printf("%s", t1->bytes);

    return status_ok;
}

context T1_make_ctx(char* str)
{
    size_t len = strlen(str);
    T1* t1 = malloc(sizeof(T1));
    t1->bytes = malloc(len+1);
    strcpy(t1->bytes, str);
    t1->bytes[len] = '\0';

    return (context) t1;
}

void T1_destroy(context ctx)
{
    T1* t1 = (T1*)ctx;
    free(t1->bytes);
    free(t1);
}

super T1_make(char* str)
{
    super s;
    s.ctx = T1_make_ctx(str);
    s.dispatch = T1_dispatch;
    s.destroy = T1_destroy;

    return s;
}

typedef struct {
    int id;
} T2;

status T2_dispatch(context ctx)
{
    T2* t2 = (T2*) ctx;
    printf("%d\n", t2->id);

    return status_fail;
}

context T2_make_ctx(int id)
{
    T2* t2 = malloc(sizeof(T2));
    t2->id = id;

    return (context) t2;
}

void T2_destroy(context ctx)
{
    T2* t2 = (T2*)ctx;
    free(t2);
}

super T2_make(int id)
{
    super s;
    s.ctx = T2_make_ctx(id);
    s.dispatch = T2_dispatch;
    s.destroy = T2_destroy;

    return s;
}

int main(int argc, char** argv)
{
    UNUSED(argc);
    UNUSED(argv);

    super objs[2];
    objs[0] = T1_make("Hello there\n");
    objs[1] = T2_make(42);
    
    for(int i = 0; i < 2; ++i)
    {
        super val = objs[i];
        status s = val.dispatch(val.ctx);
        printf("obj %d dispatch was %s\n", i, (s ? "ok" : "error"));
        val.destroy(val.ctx);
    }

    return EXIT_SUCCESS;
}
