## 名前

c_substr - STRING から部分文字列の複製を行う

## 書式

```c
#include <benly/typestring.h>

int s->c_substr(STRING* self, size_t pos, size_t n, char** dest);
```

## 説明

メンバ関数`c_substr()`は、`self`が管理する文字列の指定位置`pos`番目から`n`要素を`dest`へ複製する、その際、末尾はNULL文字 ('\0') で終端される。
`n`に対して 0 が与えられた場合、文字列の末尾まで複製を行う。

`c_substr()`は、必要な大きさの配列を動的に確保し、その先頭アドレスを`dest`へ割り当てる。
呼び出し側は、返されたバッファを`free()`すべきである。

指定位置`pos`として有効な値は、現在の領域内に限られる。
従って、`self->size(self)`を超えてはならないし、必然的に 0 以上の整数値である。

## 戻り値

成功した場合は 0 を返す。エラーが発生した場合は負の整数を返し、`errno`並びに`string_errno`にエラー原因を示す値を設定する。

### ESTRISEMPTY

`self`が管理する文字列が存在しない、またはサイズが 0 だった。

### EMEMORYALLOC (errno: ENOMEM)

複製先のメモリ確保に失敗した。
