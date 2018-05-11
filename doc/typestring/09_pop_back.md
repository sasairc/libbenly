## 名前

pop_back - 文字列の末尾から要素を削除する

## 書式

```c
#include <benly/typestring.h>

void s->pop_back(STRING** self);
```

## 説明

メンバ関数`pop_back()`は、`self`のメンバ変数`self->string`の末尾1要素を削除する。

## 戻り値

本関数に対処すべき戻り値は存在しない。

## エラー

### ESTRISEMPTY

範囲外。メンバ変数`s->length`の値が 0 である為、これ以上削除 (後退) できない。

## 例

```c
#include <benly/typestring.h>
#include <stdio.h>

int main(void)
{
    STRING* s   = new_string("helloo");

    s->pop_back(&s);
    fprintf(stdout, "%s\n",
            s->c_str(s));

    s->release(s);

    return 0;
}
```

## 出力

```
hello
```
