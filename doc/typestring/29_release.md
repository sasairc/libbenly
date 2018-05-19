## 名前

release - STRING を解放する

## 書式

```c
#include <benly/typestring.h>

void s->release(STRING* self);
```

## 説明

メンバ関数`release()`は、`self`が管理している文字列および、 STRING 構造体へのポインタ`self`が指す一連のメモリ領域を開放する。
呼び出し元は、本関数を用いて適宜解放するべきである。

## 戻り値

本関数に戻り値は存在しない。

## エラー

本関数は失敗しない。

## 例

```c
#include <benly/typestring.h>

int main(void)
{
    STRING* s1  = new_string("没キャラ");

    s1->release(s1);
    /* 二重解放を防ぐため NULL を代入する事が望ましい */
    s1 = NULL;

    return 0;
}
```
