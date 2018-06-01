#include <typestring.h>
#include <stdio.h>

int main(void)
{
    STRING* s   = new_string(NULL);

    s->append(&s, "やすなちゃん");  /* assign() と等価 */
    s->append(&s, "はウザおバカわいい");
    s->append(&s, "！");
    fprintf(stdout, "%s\n",
            s->c_str(s));

    s->release(s);

    return 0;
}
