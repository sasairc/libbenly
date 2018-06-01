#include <typestring.h>
#include <stdio.h>

int main(void)
{
    STRING* s   = new_string("12345");

    s->erase(&s, 1, 2);
    fprintf(stdout, "%s\n",
            s->c_str(s));

    s->release(s);

    return 0;
}
