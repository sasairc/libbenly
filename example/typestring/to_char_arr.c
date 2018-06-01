#include <typestring.h>
#include <stdio.h>

int main(void)
{
    size_t      i       = 0;

    char**      dest    = NULL;

    STRING*     s       = new_string("abcぼくドラえもんです");

    s->to_char_arr(s, &dest);
    while (i < s->mblen(s)) {
        fprintf(stdout, "%s\n",
                *(dest + i));
        i++;
    }
    release_char_arr(s, 0, dest);
    s->release(s);

    return 0;
}
