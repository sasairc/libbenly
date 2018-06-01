#include <typestring.h>
#include <stdio.h>

int main(void)
{
    STRING* s   = new_string("hello world");

    fprintf(stdout, "empty? = %d\n",
            s->empty(s));

    s->clear(&s);
    fprintf(stdout, "empty? = %d\n",
            s->empty(s));

    s->release(s);

    return 0;
}
