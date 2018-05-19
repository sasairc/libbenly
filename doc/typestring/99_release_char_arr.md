## 名前

release_char_arr - おまけ

## 書式

```c
#include <benly/typestring.h>

void release_char_arr(STRING* self, size_t n, char** arr);
```

## 説明

関数`release_char_arr()`は、`to_char_arr()`によって確保された二次元配列のメモリ領域を解放する。
`self`へ STRING 構造体へのポインタを渡した場合は、`arr`から`self->mblen()`個の要素を解放し、`arr`の指すメモリ領域も解放する。
また、`self`へ NULL ポインタを渡し、`n`へ直接要素数を指定する事もできる。

（でもこれくらい自分でやればいいと思います）

## 例

下に示すコードは全て等価。

```c
#include <benly/typestring.h>

int main(void)
{
    char**  arr = NULL;

    STRING* s   = new_string("こんにちは");

    s->to_char_arr(s, &arr);
    release_char_arr(s, 0, arr);
    s->release(s);

    return 0;
}
```

```c
#include <benly/typestring.h>

int main(void)
{
    char**  arr = NULL;

    STRING* s   = new_string("こんにちは");

    s->to_char_arr(s, &arr);
    release_char_arr(NULL, s->mblen(s), arr);
    s->release(s);

    return 0;
}
```

```c
#include <benly/typestring.h>
#include <stdlib.h>

int main(void)
{
    size_t  i   = 0;

    char**  arr = NULL;

    STRING* s   = new_string("こんにちは");

    s->to_char_arr(s, &arr);
    while (i < s->mblen(s)) {
        free(*(arr + i));
        i++;
    }
    free(arr);
    s->release(s);

    return 0;
}
```
