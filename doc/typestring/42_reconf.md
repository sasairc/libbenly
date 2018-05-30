## 名前

reconf - STRING 構造体の再設定を行う

## 書式

```c
#include <benly/typestring.h>

int s->reconf(STRING** self, size_t n);
```

## 説明

メンバ関数`reconf()`は、`self`の指す STRING 構造体の再設定を行う。

メンバ変数`string`や、メンバ関数`c_str()`の戻り値は C/C++ における文字列表現 *char\** であるため、直接操作が可能である。
しかし、文字列の操作やメモリ領域の操作を直接行った場合、 STRING 構造体の管理パラメータと異なってしまう。
本関数は、操作後の文字列サイズの計算、ならびにメモリ管理に関する値の再設定を提供する。

`n`は手動で確保した場合の領域サイズを指定する。 0 を指定した場合、`capacity()`の値がそのまま用いられる。

## 戻り値

再計算後の`size()`の戻り値。

## エラー

本関数は失敗しない。

## 例

```c
#include <benly/typestring.h>
#include <stdio.h>
#include <stdlib.h> /* malloc(), free() */
#include <string.h> /* mem*() */

int main(void)
{
    STRING* s   = new_string("hello world");

    fprintf(stdout, "size() = %zu, capacity() = %zu\n",
            s->size(s), s->capacity(s));

    /* 領域を解放 */
    free(s->c_str(s));
    /* 領域を 64byte 確保 */
    s->string = (char*)malloc(sizeof(char) * 64);

    /* s->string を 直接操作 */
    memset(s->string, '\0', 64);
    memcpy(s->string, "ぼくドラえもんです\0", 28);
    memmove(s->string + 18, s->string, 28);
    memcpy(s->string, "こんにちは、", 18);

    /* 再設定 */
    s->reconf(&s, 64);
    fprintf(stdout, "%s\n",
            s->c_str(s));
    fprintf(stdout, "size() = %zu, capacity() = %zu\n",
            s->size(s), s->capacity(s));

    /* 何要素か足してみる */
    size_t  i   = 0;
    while (i < 64) {
        s->push_back(&s, '.');
        i++;
    }

    /* 最終的な結果 */
    fprintf(stdout, "%s\n",
            s->c_str(s));
    fprintf(stdout, "size() = %zu, capacity() = %zu\n",
            s->size(s), s->capacity(s));

    s->release(s);

    return 0;
}
```

### 出力

```
size() = 11, capacity() = 1024
こんにちは、ぼくドラえもんです
size() = 45, capacity() = 64
こんにちは、ぼくドラえもんです................................................................
size() = 109, capacity() = 1088
```
