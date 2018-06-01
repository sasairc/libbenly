#include <typestring.h>
#include <stdio.h>

int main(void)
{
    STRING* s   = new_string("helloo");

    s->pop_back(&s);
    fprintf(stdout, "%s\n",
            s->c_str(s));

    s->release(s);

    return 0;
}
