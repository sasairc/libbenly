#include <typestring.h>
#include <stdio.h>

int main(void)
{
    STRING* s1  = new_string("没キャラ");

    s1->clear(&s1);
    if (s1->empty(s1)) {
        fprintf(stdout, "%s\n",
                s1->c_str(s1));
        fprintf(stdout, "size = %zu\n",
                s1->size(s1));
        fprintf(stdout, "capacity = %zu\n",
                s1->capacity(s1));
    }
    s1->release(s1);

    return 0;
}
