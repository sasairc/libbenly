#include <typestring.h>
#include <stdio.h>
#include <stdlib.h> /* malloc(), free() */
#include <string.h>

int main(void)
{
    STRING* s   = new_string("hello world");

    fprintf(stdout, "size() = %zu, capacity() = %zu\n",
            s->size(s), s->capacity(s));

    free(s->c_str(s));
    s->string = (char*)malloc(sizeof(char) * 64);

    memset(s->string, '\0', 64);
    memcpy(s->string, "ぼくドラえもんです\0", 28);
    memmove(s->string + 18, s->string, 28);
    memcpy(s->string, "こんにちは、", 18);

    s->reconf(&s, 64);
    fprintf(stdout, "%s\n",
            s->c_str(s));
    fprintf(stdout, "size() = %zu, capacity() = %zu\n",
            s->size(s), s->capacity(s));

    size_t  i   = 0;
    while (i < 64) {
        s->push_back(&s, '.');
        i++;
    }

    fprintf(stdout, "%s\n",
            s->c_str(s));
    fprintf(stdout, "size() = %zu, capacity() = %zu\n",
            s->size(s), s->capacity(s));

    s->release(s);

    return 0;
}
