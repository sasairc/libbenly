#include <typestring.h>
#include <stdio.h>

int main(void)
{
    STRING* s1  = new_string("abc"),
          * s2  = new_string("abc"),
          * s3  = new_string("qwerty");

    fprintf(stdout, "compare = %d\n",
            s1->compare(s1, s2));
    fprintf(stdout, "compare = %d\n",
            s1->compare(s1, s3));

    s1->release(s1);
    s2->release(s2);
    s3->release(s3);

    return 0;
}
