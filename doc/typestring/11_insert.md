## 名前

insert - STRING へ文字列を挿入する

## 書式

```c
#include <benly/typestring.h>

int s->insert(STRING** self, size_t pos, char* const str);
```

## 説明

メンバ関数`insert()`は、`self`のメンバ変数`self->string`の指定位置`pos`へ文字列`str`を挿入する。
その際に、`self->string`末尾のNULL文字 ('\0') は上書きされ、挿入後の文字列へ新たに付与される。

指定位置`pos`として有効な値は、現在の領域内に限られる。
従って、`self->size(self)`を超えてはならないし、必然的に 0 以上の整数値である。

## 戻り値

成功した場合は 0 を返す。エラーが発生した場合は負の整数を返し、`errno`並びに`string_errno`にエラー原因を示す値を設定する。

## エラー

### EARGISNULPTR

`str`の値が文字列ではなく`NULL`であった。

### EOUTOFRANGE

`pos`が無効な指定位置 (領域外) であった。

### EMEMORYALLOC (errno: ENOMEM)

メモリ再確保に失敗した。

## 例

```c
#include <benly/typestring.h>
#include <stdio.h>

int main(void)
{
    STRING* s   = new_string("ぼくです");

    /* "ぼく" は 6byte */
    s->insert(&s, 6, "ドラえもん");
    fprintf(stdout, "%s\n",
            s->c_str(s));

    s->release(s);

    return 0;
}
```

### 出力

```
ぼくドラえもんです
```
