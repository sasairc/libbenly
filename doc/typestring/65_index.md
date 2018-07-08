## 名前

index - STRING から部分文字列の開始位置を取得する

## 書式

```c
#include <benly/typestring.h>

int s->index(STRING* self, char* const str, size_t pos, size_t* idx);
```

## 説明

メンバ関数`index()`は、`self`が管理する文字列から任意の部分文字列`str`の開始位置を取得し、`idx`の指す領域へその値を格納する。
`pos > 0`を指定すると、その任意位置から検索を開始する。本関数での位置とはバイト数である。
実文字を扱う場合は`mbindex()`を参照せよ。

指定位置`pos`として有効な値は、現在の領域内に限られる。
従って、`self->size(self)`を超えてはならない。

## 戻り値

成功した場合は 0 を返す。
エラーが発生した場合は負の整数を返し、`string_errno`にエラー原因を示す値を設定する。

## エラー

### ESTRISEMPTY

`self`が管理する文字列が存在しない、またはサイズが 0 だった。

### EARGISNULPTR

`str`または`idx`が NULL だった。

### EOUTOFRANGE

`pos` が無効な指定位置 (領域外) であった。

### ESTRNOTFOUND

`self`が管理する文字列内に部分文字列`str`が存在しなかった。

## 例

```c
#include <benly/typestring.h>
#include <stdio.h>

int main(void)
{
    size_t  idx     = 0;

    STRING* s       = new_string("koubeken-koubeshi");

    s->index(s, "be", 0, &idx);
    fprintf(stdout, "%zu\n",
            idx);

    s->index(s, "be", 5, &idx);
    fprintf(stdout, "%zu\n",
            idx);

    s->release(s);

    return 0;
}
```

### 出力

```
3
12
```
