## 名前

assign - STRING へ文字列を代入する

## 書式

```c
#include <benly/typestring.h>

int s->assign(STRING** self, char* const str);
```

## 説明

メンバ関数`assign()`は、`self`のメンバ変数`self->string`に対して、文字列`str`を代入する。この際、終端にNULL文字 ('\0') が追加される。
既に`self`が文字列を管理していた場合、そのメモリ領域を解放した上で新たにメモリを確保し、上記の代入を行う。
いずれにせよ、元の文字列が残留する事は無い。

## 戻り値

成功した場合は 0 を返す。エラーが発生した場合は負の整数を返し、`errno`並びに`string_errno`にエラー原因を示す値を設定する。

## エラー

### EARGISNULPTR

`str`の値が文字列ではなく`NULL`であった。

### EMEMORYALLOC (errno: ENOMEM)

代入先のメモリ確保に失敗した。

## 例

```c
#include <benly/typestring.h>
#include <stdio.h>

int main(void)
{
    STRING* s   = new_string(NULL);

    s->assign(&s, "こんにちは");
    fprintf(stdout, "%s\n",
            s->c_str(s));

    s->assign(&s, "ぼく");
    fprintf(stdout, "%s\n",
            s->c_str(s));

    s->assign(&s, "ドラえもんです");
    fprintf(stdout, "%s\n",
            s->c_str(s));

    s->release(s);

    return 0;
}
```

### 出力

```
こんにちは
ぼく
ドラえもんです
```
