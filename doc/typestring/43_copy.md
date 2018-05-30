## 名前

copy - STRING 構造体をコピーする

## 書式

```c
#include <benly/typestring.h>

int s->copy(STRING* self, STRING** dest);
```

メンバ関数`copy()`は、`self`が管理する文字列を新たな STRING 構造体へ複製し、そのポインタを`dest`へセットする。
この際、複製元となる`self`の領域サイズおよび、管理のための`capacity()`等も引き継がれる。
呼び出し側は、メンバ関数`release()`を用いて複製された構造体を解放すべきである。

## 戻り値

成功した場合は 0 を返す。エラーが発生した場合は負の整数を返し、`errno`並びに`string_errno`にエラー原因を示す値を設定する。

## エラー

### EMEMORYALLOC (errno: ENOMEM)

メモリ確保に失敗した。

## 例

```c
#include <benly/typestring.h>
#include <stdio.h>

int main(void)
{
    STRING* s1  = new_string(NULL),
          * s2  = NULL;

    s1->reserve(&s1, 32);
    s1->assign(&s1, "hello world");
    s1->copy(s1, &s2);
    fprintf(stdout, "s1->c_str() = %s\ns2->c_str() = %s\n",
            s1->c_str(s1), s2->c_str(s2));
    fprintf(stdout, "s1->capacity() = %zu\ns2->capacity() = %zu\n",
            s1->capacity(s1), s2->capacity(s2));
    s1->release(s1);
    s2->release(s2);

    return 0;
}
```

### 出力

```
s1->c_str() = hello world
s2->c_str() = hello world
s1->capacity() = 33
s2->capacity() = 33
```
