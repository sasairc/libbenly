#include <typestring.h>

int main(void)
{
    STRING* s1  = new_string("没キャラ");

    s1->release(s1);

    return 0;
}
