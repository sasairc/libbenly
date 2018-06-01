#include <typestring.h>
#include <stdio.h>

int main(void)
{
    STRING* s   = new_string("hello world");

    fprintf(stdout, "%zu\n",
            s->count(s, "l"));
    fprintf(stdout, "%zu\n",
            s->count(s, "lo"));

    s->assign(&s, "志布志市志布町志布志の志布志市役所志布志支所");
    fprintf(stdout, "%zu\n",
            s->count(s, "志布志"));

    s->release(s);

    return 0;
}
