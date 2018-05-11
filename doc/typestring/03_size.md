## 名前

size - 文字列の長さを返す

## 書式

```c
#include <benly/typestring.h>

size_t s->size(STRING* self);
```

## 説明

メンバ関数`size()`は、`self`が管理する文字列の長さを返す。この際、終端のNULL文字 ('\0') のバイト数は含まれない。

## 戻り値

`size()`は、`self`が管理する文字列のバイト数を返す。

## エラー

本関数は失敗しない。

## 例

```c
#include <benly/typestring.h>
#include <stdio.h>

int main(void)
{
    STRING* s   = NULL;

    s = new_string("hello world");
    fprintf(stdout, "s->size() = %zu\n",
            s->size(s));
    s->release(s);

    return 0;
}
```

### 出力

```
s->size() = 11
```

## 追加情報

`size()`はメンバ変数`s->length`の値を返す。従って、結果は`s->length`の参照と等価である。
また、`strlen(s->string)`並びに`strlen(s->c_str(s))`も同様の結果となる。
