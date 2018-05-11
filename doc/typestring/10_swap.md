## 名前

swap - STRING 構造体を入れ替える

## 書式

```c
#include <benly/typestring.h>

void s->swap(STRING** s1, STRING** s2);
```

## 説明

メンバ関数`swap()`は、`s1`と`s2`が指す STRING 構造体へのアドレスを入れ替える。

## 戻り値

本関数に戻り値は存在しない。

## エラー

本関数は失敗しない。

## 例

```c
#include <benly/typestring.h>
#include <stdio.h>

int main(void)
{
    STRING* s1  = new_string("world"),
          * s2  = new_string("hello");

    s1->swap(&s1, &s2);
    fprintf(stdout, "%s %s\n",
            s1->c_str(s1), s2->c_str(s2));

    s1->release(s1);
    s2->release(s2);

    return 0;
}
```

## 出力

```
hello world
```
