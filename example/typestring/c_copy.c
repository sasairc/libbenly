#include <typestring.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    char*   p   = NULL;

    STRING* s   = new_string("hello world");

    fprintf(stdout, "%zu\n",
            s->c_copy(s, &p));
    fprintf(stdout, "%s\n",
            p);

    free(p);
    s->release(s);

    return 0;
}
