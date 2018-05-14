## 名前

capacity - メモリを再確保せずに格納できる最大のバイト数を取得する

## 書式

```c
#include <benly/typestring.h>

size_t s->capacity(STRING* self);
```

## 概要

メンバ関数`capacity()`は、`self`がメモリを再確保せずに文字列を格納できる最大のバイト数を返す。

## 戻り値

`capacity()`は、`self`がメモリを再確保せずに文字列を格納できる最大のバイト数を返す。
この値はメモリ上に確保されているバイト数であり、文字列のバイト数を差し引いていない事に注意すること。

## エラー

本関数は失敗しない。

## 例

```c
#include <benly/typestring.h>
#include <stdio.h>

int main(void)
{
    size_t  i       = 0,
            capa    = 0;


    STRING* s       = NULL;

    s = new_string("");
    fprintf(stdout, "s->capacity() = %zu\n",
            capa = s->capacity(s));

    /*
     * 末尾に要素 'o' を capa 個加える
     */
    for (i = 0; i < capa; i++)
        s->push_back(&s, 'o');
    fprintf(stdout, "s->capacity() = %zu\n",
            s->capacity(s));

    s->release(s);

    return 0;
}
```

### 出力

```
s->capacity() = 1024
s->capacity() = 2048
```

## 追加情報

`capacity()`はメンバ変数`s->alloc_size`の値を返す。従って、結果は`s->alloc_size`の参照と等価である。
