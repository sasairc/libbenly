#include <typestring.h>
#include <stdio.h>

int main(void)
{
    STRING* s   = new_string("hello world");

    fprintf(stdout, "%c\n",
            s->back(s));

    s->release(s);

    return 0;
}
