## 名前

c_partition - STRING から部分文字列の前後を分割する

## 書式

```c
#include <benly/typestring.h>

int s->c_partition(STRING* self, char* const str, char*** dest);
```

## 説明

メンバ関数`c_partition()`は、`self`が管理する文字列から、任意の文字列`str`を以て前後に分割を行う。
分割後の文字列は、新たに確保された領域に格納され、これらを指すポインタ配列の先頭アドレスを`dest`へセットする。

呼び出し側は、`dest`とそれに含まれる要素を解放すべきである。

## 戻り値

成功した場合は 0 を返す。
エラーが発生した場合は負の整数を返し、`errno`並びに`string_errno`にエラー原因を示す値を設定する。

## エラー

### ESTRISEMPTY

`self`が管理する文字列が存在しない、またはサイズが 0 だった。

### EARGISNULPTR

`str`が NULL だった。

### EOUTOFRANGE

`str`の長さが`self`を超過していた。

### ESTRNOTFOUND

`self`が管理する文字列内に部分文字列`str`が存在しなかった。

### EMEMORYALLOC (errno: ENOMEM)

メモリ確保に失敗した。

## 例

```c
#include <benly/typestring.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    STRING*     src     = new_string("ぼくドラえもん");

    char**      dest    = {NULL};

    src->c_partition(src, "ドラ", &dest);
    fprintf(stdout, "%s%s\n",
            dest[0], dest[1]);

    release_char_arr(NULL, 2, dest);
    src->release(src);

    return 0;
}
```

### 出力

```
ぼくえもん
```
