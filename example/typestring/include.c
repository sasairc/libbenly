#include <typestring.h>
#include <stdio.h>

int main(void)
{
    STRING* s   = new_string("ソーニャ　折部やすな　呉織あぎり");

    fprintf(stdout, "include? = %d\n",
            s->include(s, "折部やすな"));
    fprintf(stdout, "include? = %d\n",
            s->include(s, "没キャラ"));
    s->release(s);

    return 0;
}
