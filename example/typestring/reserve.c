#include <typestring.h>
#include <stdio.h>

int main(void)
{
    STRING* s   = new_string(NULL);

    s->reserve(&s, 3);
    s->push_back(&s, 'A');
    s->push_back(&s, 'B');
    s->push_back(&s, 'C');
    fprintf(stdout, "%s\n",
            s->c_str(s));
    fprintf(stdout, "capacity = %zu, size = %zu\n",
            s->capacity(s), s->size(s));

    s->push_back(&s, 'D');
    fprintf(stdout, "%s\n",
            s->c_str(s));
    fprintf(stdout, "capacity = %zu, size = %zu\n",
            s->capacity(s), s->size(s));

    s->release(s);

    return 0;
}
