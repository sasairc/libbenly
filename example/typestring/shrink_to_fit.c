#include <typestring.h>
#include <stdio.h>

int main(void)
{
    STRING* s   = new_string("hello world");

    fprintf(stdout, "capacity = %zu\n",
            s->capacity(s));
    s->shrink_to_fit(&s);
    fprintf(stdout, "capacity = %zu\n",
            s->capacity(s));

    s->release(s);

    return 0;
}
