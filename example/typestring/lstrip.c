#include <typestring.h>
#include <stdio.h>

int main(void)
{
    STRING* s   = new_string("    やすなちゃん！");

    fprintf(stdout, "lstrip() = %zu\n",
            s->lstrip(&s));
    fprintf(stdout, "size() = %zu, c_str() = \"%s\"\n",
            s->size(s), s->c_str(s));

    s->release(s);

    return 0;
}
