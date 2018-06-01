#include <typestring.h>
#include <stdio.h>

int main(void)
{
    STRING* s   = new_string("ソーニャ　折部やすな　呉織あぎり");

    s->append(&s, "没キャラ");
    s->append(&s, "没キャラ");
    s->append(&s, "没キャラ");

    while (s->include(s, "没キャラ"))
        s->slice(&s, "没キャラ");

    fprintf(stdout, "%s\n",
            s->c_str(s));

    s->release(s);

    return 0;
}
