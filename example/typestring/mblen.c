#include <typestring.h>
#include <stdio.h>

int main(void)
{
    STRING* s   = NULL;

    s = new_string("やすなちゃんkawaii!");
    fprintf(stdout, "mblen->() = %zu\n",
            s->mblen(s));
    s->release(s);

    return 0;
}
