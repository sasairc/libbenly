#include <typestring.h>
#include <stdio.h>

int main(void)
{
    STRING* s1  = new_string("ソーニャ 折部やすな 呉織あぎり"),
          * s2  = NULL;

    s1->substr(s1, 13, 15, &s2);
    fprintf(stdout, "%s\n",
            s2->c_str(s2));

    s1->release(s1);
    s2->release(s2);

    return 0;
}
