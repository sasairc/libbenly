#include <typestring.h>
#include <stdio.h>

int main(void)
{
    STRING* s   = new_string("ソーニャ 折部やすな 呉織あぎり");

    fprintf(stdout, "%.*s\n",
            15, s->c_str(s) + 13);

    s->release(s);

    return 0;
}
