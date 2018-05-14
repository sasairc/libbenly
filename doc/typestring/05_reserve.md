## 名前

reserve - 前もってメモリを確保する

## 書式

```c
#include <benly/typestring.h>

int s->reserve(STRING** self, size_t s);
```

## 説明

メンバ関数`reserve()`は、前もって任意のサイズ`s`バイトぶんのメモリを確保する。
この際、NULL文字 ('\0') を格納するため、`s`バイトより 1 バイト多く確保される事に注意。

既定の領域サイズは、定数`T_STRING_DEFAULT_ALLOC_SIZE`にて定義している。しかし、事前に十分なサイズを把握しているのなら、本関数は効果的である。

## 戻り値

成功した場合は 0 を返す。エラーが発生した場合は負の整数を返し、`errno`並びに`string_errno`にエラー原因を示す値を設定する。

## エラー

### EOUTOFRANGE

`n`の値が 0 だった。

### EMEMORYALLOC 

メモリ確保に失敗。

## 例

```c
#include <benly/typestring.h>
#include <stdio.h>

int main(void)
{
    STRING* s   = new_string(NULL);

    s->reserve(&s, 3);
    s->push_back(&s, 'A');
    s->push_back(&s, 'B');
    s->push_back(&s, 'C');
    fprintf(stdout, "%s\n",
            s->c_str(s));
    fprintf(stdout, "capacity = %zu, size = %zu\n",
            s->capacity(s), s->size(s));

    s->push_back(&s, 'D');
    fprintf(stdout, "%s\n",
            s->c_str(s));
    fprintf(stdout, "capacity = %zu, size = %zu\n",
            s->capacity(s), s->size(s));

    s->release(s);

    return 0;
}
```

### 出力

```
ABC
capacity = 4, size = 3
ABCD
capacity = 1028, size = 4
```
