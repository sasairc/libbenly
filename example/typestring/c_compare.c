#include <typestring.h>
#include <stdio.h>

int main(void)
{
    STRING* s1  = new_string("abc");

    char*   s2  = "abc",
        *   s3  = "qwerty";

    fprintf(stdout, "c_compare = %d\n",
            s1->c_compare(s1, s2));
    fprintf(stdout, "c_compare = %d\n",
            s1->c_compare(s1, s3));

    s1->release(s1);

    return 0;
}
