#include <typestring.h>
#include <stdio.h>

int main(void)
{
    STRING* s1  = new_string("weekly ascii"),
          * s2  = new_string("週刊アスキー");

    fprintf(stdout, "ascii_only = %d\n",
            s1->ascii_only(s1));
    fprintf(stdout, "ascii_only = %d\n",
            s2->ascii_only(s2));

    s1->release(s1);
    s2->release(s2);

    return 0;
}
