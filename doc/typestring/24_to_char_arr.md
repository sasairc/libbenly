## 名前

to_char_arr - STRING から一文字ずつ分割する

## 書式

```c
#include <benly/typestring.h>

int s->to_char_arr(STRING* self, char*** dest);
```

## 説明

メンバ関数`to_char_arr()`は、`self`が管理する文字列を一文字ずつ配列の要素として複製し、その配列の先頭アドレスを`dest`へ割り当てる。
本関数は`mblen()`と同様にマルチバイト文字を精査しており、ロケールに依存はするものの、正常にマルチバイト文字を扱う事ができる。また、配列の各要素は NULL文字 ('\0') で終端される。

呼び出し側は、返された領域を`free()`すべきである。また、簡略化のため`release_char_arr()`を利用可能。

## 戻り値

成功した場合は 0 を返す。エラーが発生した場合は負の整数を返し、`errno`並びに`string_errno`にエラー原因を示す値を設定する。

## エラー

### EINVALIDCHAR

不正なマルチバイト列を検出した。

### EMEMORYALLOC (errno: ENOMEM)

メモリ確保に失敗した。

## 例

```c
#include <benly/typestring.h>
#include <stdio.h>

int main(void)
{
    size_t      i       = 0;

    char**      dest    = NULL;

    STRING*     s       = new_string("abcぼくドラえもんです");

    s->to_char_arr(s, &dest);
    while (i < s->mblen(s)) {
        fprintf(stdout, "%s\n",
                *(dest + i));
        i++;
    }
    release_char_arr(s, 0, dest);
    s->release(s);

    return 0;
}
```

### 出力

```
a
b
c
ぼ
く
ド
ラ
え
も
ん
で
す
```
