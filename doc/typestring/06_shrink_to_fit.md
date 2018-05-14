## 名前

shrink_to_fit - メモリサイズを格納文字列まで切り詰める

## 書式

```
#include <benly/typestring.h>

int s->shrink_to_fit(STRING** self);
```

## 説明

メンバ関数`shrink_to_fit()`は、`self`が管理する文字列のサイズまで領域のサイズを切り詰める。
NULL文字 ('\0') を格納するため、厳密には `size() + 1` まで切り詰めを行う。

## 戻り値

成功した場合は 0 を返す。エラーが発生した場合は負の整数を返し、`errno`並びに`string_errno`にエラー原因を示す値を設定する。

## エラー

### ESTRISEMPTY

`self`が管理する文字列が存在しない。

### EMEMORYALLOC (errno: ENOMEM)

メモリ確保に失敗した。

## 例

```c
#include <benly/typestring.h>
#include <stdio.h>

int main(void)
{
    STRING* s   = new_string("hello world");

    fprintf(stdout, "capacity = %zu\n",
            s->capacity(s));
    s->shrink_to_fit(&s);
    fprintf(stdout, "capacity = %zu\n",
            s->capacity(s));

    s->release(s);

    return 0;
}
```

### 出力

```
capacity = 1024
capacity = 12
```
