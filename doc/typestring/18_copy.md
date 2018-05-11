## 名前

copy - STRING から文字列をコピーする

## 書式

```c
#include <benly/typestring.h>

size_t s->copy(STRING* self, char** dest);
```

## 説明

メンバ関数`copy()`は、`self`が管理する文字列を`dest`へ複製する。その際、末尾はNULL文字 ('\0') で終端される。
`copy()`は、必要な大きさの配列を動的に確保し、その先頭アドレスを`dest`へ割り当てる。
呼び出し側は、返されたバッファを`free()`すべきである。

## 戻り値

成功した場合は、複製した文字列のサイズを返す。エラーが発生した場合は 0 を返し、`errno`並びに`string_errno`にエラー原因を示す値を設定する。

## エラー

### ESTRISEMPTY

`self`が管理する文字列が存在しない、またはサイズが 0 だった。

### EMEMORYALLOC (errno: ENOMEM)

複製先のメモリ確保に失敗した。

## 例

```c
#include <benly/typestring.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    char*   p   = NULL;

    STRING* s   = new_string("hello world");

    fprintf(stdout, "%zu\n",
            s->copy(s, &p));
    fprintf(stdout, "%s\n",
            p);

    free(p);
    s->release(s);

    return 0;
}
```

### 出力

```
12
hello world
```
