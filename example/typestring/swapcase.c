#include <typestring.h>
#include <stdio.h>

int main(void)
{
    STRING* s   = new_string("HELLO WORLD");

    s->downcase(&s);
    fprintf(stdout, "%s\n",
            s->c_str(s));
    s->release(s);

    return 0;
}
