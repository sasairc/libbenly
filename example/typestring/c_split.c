#include <typestring.h>
#include <stdio.h>

int main(void)
{
    size_t      i       = 0,
                idx     = 0;

    char**      dest    = NULL;

    STRING*     src     = new_string("foo,bar,baz");

    idx = src->c_split(src, ",", &dest);
    src->release(src);
    while (i < idx) {
        fprintf(stdout, "%s\n",
                dest[i]);
        i++;
    }
    release_char_arr(NULL, idx, dest);

    return 0;
}
