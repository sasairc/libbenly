#include <typestring.h>
#include <stdio.h>

int main(void)
{
    STRING* s   = NULL;

    s = new_string("hello world");
    fprintf(stdout, "s->size() = %zu\n",
            s->size(s));
    s->release(s);

    return 0;
}
