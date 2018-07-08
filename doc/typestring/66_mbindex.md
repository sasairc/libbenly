## 名前

mbindex - STRING から部分文字列の開始位置を取得する

## 書式

```c
#include <benly/typestring.h>

int s->mbindex(STRING* self, char* const str, size_t pos, size_t* idx);
```

## 説明

メンバ関数`mbindex()`は、`self`が管理する文字列から任意の部分文字列`str`の開始位置を検索し、`idx`の指す領域へその値を格納する。
`pos > 0`を指定すると、その任意位置から検索を開始する。本関数での位置とは、バイト数ではなく実文字である。

指定位置`pos`として有効な値は、現在の実文字数に限られる。
従って、`self->mblen(self)`を超えてはならない。

## 戻り値

成功した場合は 0 を返す。
エラーが発生した場合は負の整数を返し、`string_errno`にエラー原因を示す値を設定する。

## エラー

### ESTRISEMPTY

`self`が管理する文字列が存在しない、またはサイズが 0 だった。

### EARGISNULPTR

`str`または`idx`が NULL だった。

### EINVALIDCHAR

不正なマルチバイト列を検出した。

### ESTRNOTFOUND

`self`が管理する文字列内に部分文字列`str`が存在しなかった。

## 例

```c
#include <benly/typestring.h>
#include <stdio.h>

int main(void)
{
    size_t  idx     = 0;

    STRING* s       = new_string("神戸県神戸市");

    s->mbindex(s, "戸", 0, &idx);
    fprintf(stdout, "%zu\n",
            idx);

    s->mbindex(s, "戸", 2, &idx);
    fprintf(stdout, "%zu\n",
            idx);

    s->release(s);

    return 0;
}
```

### 出力

```
1
5
```
