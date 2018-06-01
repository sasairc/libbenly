#include <typestring.h>
#include <stdio.h>

int main(void)
{
    STRING* s   = new_string(NULL);

    s->assign(&s, "こんにちは");
    fprintf(stdout, "%s\n",
            s->c_str(s));

    s->assign(&s, "ぼく");
    fprintf(stdout, "%s\n",
            s->c_str(s));

    s->assign(&s, "ドラえもんです");
    fprintf(stdout, "%s\n",
            s->c_str(s));

    s->release(s);

    return 0;
}
