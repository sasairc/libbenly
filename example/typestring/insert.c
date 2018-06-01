#include <typestring.h>
#include <stdio.h>

int main(void)
{
    STRING* s   = new_string("ぼくです");

    /* "ぼく" は 6byte */
    s->insert(&s, 6, "ドラえもん");
    fprintf(stdout, "%s\n",
            s->c_str(s));

    s->release(s);

    return 0;
}
