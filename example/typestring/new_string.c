#include <typestring.h>
#include <stdio.h>

int main(void)
{
    STRING* s   = NULL;

    s = new_string("hello world");
    fprintf(stdout, "s->string = \"%s\", s->length = %zu, s->alloc_size = %zu\n",
            s->c_str(s), s->length, s->alloc_size);
    s->release(s);

    s = new_string("");
    fprintf(stdout, "s->string = \"%s\", s->length = %zu, s->alloc_size = %zu\n",
            s->c_str(s), s->length, s->alloc_size);
    s->release(s);

    s = new_string(NULL);
    fprintf(stdout, "s->string = \"%s\", s->length = %zu, s->alloc_size = %zu\n",
            s->c_str(s), s->length, s->alloc_size);
    s->release(s);

    return 0;
}
