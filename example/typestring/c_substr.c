#include <typestring.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    STRING* s1  = new_string("ソーニャ 折部やすな 呉織あぎり");

    char*   s2  = NULL;

    s1->c_substr(s1, 13, 15, &s2);
    fprintf(stdout, "%s\n",
            s2);

    free(s2);
    s1->release(s1);

    return 0;
}
