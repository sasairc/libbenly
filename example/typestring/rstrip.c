#include <typestring.h>
#include <stdio.h>

int main(void)
{
    STRING* s   = new_string("やすなちゃん！    \r \n");

    fprintf(stdout, "rstrip() = %zu\n",
            s->rstrip(&s));
    fprintf(stdout, "size() = %zu, c_str() = \"%s\"\n",
            s->size(s), s->c_str(s));

    s->release(s);

    return 0;
}
