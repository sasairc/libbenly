#include <typestring.h>
#include <stdio.h>

int main(void)
{
    STRING* s1  = new_string("world"),
          * s2  = new_string("hello");

    s1->swap(&s1, &s2);
    fprintf(stdout, "%s %s\n",
            s1->c_str(s1), s2->c_str(s2));

    s1->release(s1);
    s2->release(s2);

    return 0;
}
