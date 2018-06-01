#include <typestring.h>
#include <stdio.h>

int main(void)
{
    STRING*     s   = new_string("hello");

    s->resize(&s, 10, '?');
    fprintf(stdout, "%s\n",
            s->c_str(s));

    s->resize(&s, 2, 'A');
    fprintf(stdout, "%s\n",
            s->c_str(s));

    s->release(s);

    return 0;
}
