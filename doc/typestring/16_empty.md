## 名前

empty - STRING が空か判定する

## 書式

```c
#include <benly/typestring.h>

int s->empty(STRING* self);
```

## 説明

メンバ関数`empty()`は、`self`が管理する文字列が空であるか判定を行う。本関数は`size() == 0`の判定と等価である。

## 戻り値

空であれば 1 を返し、空でなければ 0 を返す。

## エラー

本関数は失敗しない。

## 例

```c
#include <benly/typestring.h>
#include <stdio.h>

int main(void)
{
    STRING* s   = new_string("hello world");

    fprintf(stdout, "empty? = %d\n",
            s->empty(s));

    s->clear(&s);
    fprintf(stdout, "empty? = %d\n",
            s->empty(s));

    s->release(s);

    return 0;
}
```

### 出力

```
empty? = 0
empty? = 1
```
