#include <typestring.h>
#include <stdio.h>

int main(void)
{
    STRING* s   = new_string("hello\n");

    fprintf(stdout, "size() = %zu\n",
            s->size(s));
    fprintf(stdout, "chomp() = %zu\n",
            s->chomp(&s));
    fprintf(stdout, "size() = %zu, c_str() = %s\n\n",
            s->size(s), s->c_str(s));

    s->assign(&s, "hello\r");
    fprintf(stdout, "size() = %zu\n",
            s->size(s));
    fprintf(stdout, "chomp() = %zu\n",
            s->chomp(&s));
    fprintf(stdout, "size() = %zu, c_str() = %s\n\n",
            s->size(s), s->c_str(s));

    s->assign(&s, "hello\r\n");
    fprintf(stdout, "size() = %zu\n",
            s->size(s));
    fprintf(stdout, "chomp() = %zu\n",
            s->chomp(&s));
    fprintf(stdout, "size() = %zu, c_str() = %s\n\n",
            s->size(s), s->c_str(s));

    s->assign(&s, "hello\r\n\r\n\n");
    fprintf(stdout, "size() = %zu\n",
            s->size(s));
    fprintf(stdout, "chomp() = %zu\n",
            s->chomp(&s));
    fprintf(stdout, "size() = %zu, c_str() = %s\n",
            s->size(s), s->c_str(s));

    s->release(s);

    return 0;
}
