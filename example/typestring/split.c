#include <typestring.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    size_t      i       = 0,
                idx     = 0;

    STRING*     src     = new_string("志布志市志布町志布志の志布志市役所志布志支所"),
          **    dest    = NULL;

    idx = src->split(src, "志布志", &dest);
    src->release(src);
    while (i < idx) {
        fprintf(stdout, "%s\n",
                dest[i]->c_str(dest[i]));
        dest[i]->release(dest[i]);
        i++;
    }
    free(dest);

    return 0;
}
