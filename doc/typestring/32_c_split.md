## 名前

c_split - STRING から文字列を分割する

## 書式

```c
#include <benly/typestring.h>

size_t s->c_split(STRING* self, char* const delim, char*** dest);
```

## 説明

メンバ関数`c_split()`は、`self`が管理する文字列から、文字列`delim`を区切り文字と見なし分割を行う。
分割後の文字列は、新たなメモリ領域に複製され、これらを指すポインタ配列の先頭アドレスを`dest`へセットする。
呼び出し側は、返された領域を`free()`すべきである。

## 戻り値

配列の要素数を返す。
エラーが発生した場合は 0 を返し、`errno`並びに`string_errno`にエラー原因を示す値を設定する。

## エラー

### EARGISNULPTR

`delim`の値が文字列ではなく`NULL`であった。

### ESTRISEMPTY

`self`が管理する文字列が存在しない、またはサイズが 0 だった。

### EMEMORYALLOC (errno: ENOMEM)

メモリ確保に失敗した。

## 例

詳しくは`split()`の例も参照されたい。

```c
#include <benly/typestring.h>
#include <stdio.h>

int main(void)
{
    size_t      i       = 0,
                idx     = 0;

    char**      dest    = NULL;

    STRING*     src     = new_string("foo,bar,baz");

    idx = src->c_split(src, ",", &dest);
    src->release(src);
    while (i < idx) {
        fprintf(stdout, "%s\n",
                dest[i]);
        i++;
    }
    release_char_arr(NULL, idx, dest);

    return 0;
}
```

### 出力

```
foo
bar
baz
```
