## 名前

front - STRING の先頭要素へのポインタを取得する

## 書式

```c
#include <benly/typestring.h>

char* s->front(STRING* self);
```

## 説明

メンバ関数`front()`は、`self`が管理する文字列の先頭要素へのポインタを返却する。

## 戻り値

成功した場合は先頭要素へのポインタを返す。
エラーが発生した場合は NULL を返し、`string_errno`にエラー原因を示す値を設定する。

## エラー

### ESTRISEMPTY

`self`が管理する文字列が存在しない、またはサイズが 0 だった。

## 例

```c
#include <benly/typestring.h>
#include <stdio.h>

int main(void)
{
    STRING* s   = new_string("doraemon");

    if (s->front(s) != NULL)
        fprintf(stdout, "%c\n",
                *s->front(s));
    s->release(s);

    return 0;
}
```

### 出力

```
d
```
