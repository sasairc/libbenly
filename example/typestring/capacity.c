#include <typestring.h>
#include <stdio.h>

int main(void)
{
    size_t  i       = 0,
            capa    = 0;


    STRING* s       = NULL;

    s = new_string("");
    fprintf(stdout, "s->capacity() = %zu\n",
            capa = s->capacity(s));

    /*
     * 末尾に要素 'o' を capa 個加える
     */
    for (i = 0; i < capa; i++)
        s->push_back(&s, 'o');
    fprintf(stdout, "s->capacity() = %zu\n",
            s->capacity(s));

    s->release(s);

    return 0;
}
