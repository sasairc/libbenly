## 名前

front - STRING の先頭要素を取得する

## 書式

```c
#include <benly/typestring.h>

char s->front(STRING* self);
```

## 説明

メンバ関数`front()`は、`self`が管理する文字列の先頭要素を取得する。
返却する値は要素の複製であり、要素への参照でない。

## 戻り値

先頭要素を返す。文字列が空の場合の戻り値は、必然的にNULL文字 ('\0') である。

## エラー

本関数は失敗しない。

## 例

```c
#include <benly/typestring.h>
#include <stdio.h>

int main(void)
{
    STRING* s   = new_string("hello world");

    fprintf(stdout, "%c\n",
            s->front(s));

    s->release(s);

    return 0;
}
```

### 出力

```
h
```
