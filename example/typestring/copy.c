#include <typestring.h>
#include <stdio.h>

int main(void)
{
    STRING* s1  = new_string(NULL),
          * s2  = NULL;

    s1->reserve(&s1, 32);
    s1->assign(&s1, "hello world");
    s1->copy(s1, &s2);
    fprintf(stdout, "s1->c_str() = %s\ns2->c_str() = %s\n",
            s1->c_str(s1), s2->c_str(s2));
    fprintf(stdout, "s1->capacity() = %zu\ns2->capacity() = %zu\n",
            s1->capacity(s1), s2->capacity(s2));
    s1->release(s1);
    s2->release(s2);

    return 0;
}
