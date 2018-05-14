## 名前

new_string - 新しい STRING 構造体を確保・初期化する

## 書式

```c
#include <benly/typestring.h>

STRING* new_string(char* const str);
```

## 説明

関数`new_string()`は STRING 構造体をメモリ上へ確保・初期化し、割り当てられた構造体へのポインタを返す。
`str`へ`NULL`を渡した場合は、そのまま呼び出し元へ復帰する。
`str`に対して文字列が渡された場合、その文字列を STRING 構造体へ代入・管理する。この際、文字列の終端にNULL文字列 ('\0') が追加される。
呼び出し側は、メンバ関数`release()`を用いてこの構造体を解放すべきである。

## 戻り値

成功した場合はメモリ上に確保・初期化された STRING 構造体へのポインタを返す。エラーが発生した場合には`NULL`を返し、`errno`並びに`string_errno`にエラー原因を示す値を設定する。

## エラー

### EMEMORYALLOC (errno: ENOMEM)

STRING 構造体のメモリ確保に失敗した。

## 例

```c
#include <benly/typestring.h>
#include <stdio.h>

int main(void)
{
    STRING* s   = NULL;

    /* 文字列を代入 */
    s = new_string("hello world");
    fprintf(stdout, "s->string = \"%s\", s->length = %zu, s->alloc_size = %zu\n",
            s->c_str(s), s->length, s->alloc_size);
    s->release(s);

    /* 文字列を代入 (0文字) */
    s = new_string("");
    fprintf(stdout, "s->string = \"%s\", s->length = %zu, s->alloc_size = %zu\n",
            s->c_str(s), s->length, s->alloc_size);
    s->release(s);

    /* 確保・初期化のみ, 代入無し */
    s = new_string(NULL);
    fprintf(stdout, "s->string = \"%s\", s->length = %zu, s->alloc_size = %zu\n",
            s->c_str(s), s->length, s->alloc_size);
    s->release(s);

    return 0;
}
```

### 出力

```
s->string = "hello world", s->length = 11, s->alloc_size = 1024
s->string = "", s->length = 0, s->alloc_size = 1024
s->string = "(null)", s->length = 0, s->alloc_size = 0
```
