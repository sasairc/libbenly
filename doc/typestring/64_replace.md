## 名前

replace - STRING の部分文字列を置き換える

## 書式

```c
#include <benly/typestring.h>

int s->replace(STRING** self, size_t pos, size_t n, char* const str);
```

## 説明

メンバ関数`replace()`は、`self`が管理する文字列の指定位置`pos`番目から`n`要素を、文字列`str`で置き換える。
`n`に対して 0 が与えられた場合、文字列の末尾まで要素の置き換えを行う。

指定位置`pos`として有効な値は、現在の領域内に限られる。
従って、`self->size(self)`を超えてはならないし、必然的に 0 以上の整数値である。

## 戻り値

成功した場合は 0 を返す。
エラーが発生した場合は負の整数を返し、`errno`並びに`string_errno`にエラー原因を示す値を設定する。

## エラー

### EOUTOFRANGE

`pos` (`n`) が無効な指定位置 (領域外) であった。

### EARGISNULPTR

`str`が NULL だった。

### EMEMORYALLOC (errno: ENOMEM)

メモリ再確保に失敗した。

## 例

```c
#include <benly/typestring.h>
#include <stdio.h>

int main(void)
{
    STRING* s   = new_string("日本国兵庫県神戸市");

    s->replace(&s, 9, 6, "神戸");
    fprintf(stdout, "%s\n",
            s->c_str(s));
    s->release(s);

    return 0;
}
```

### 出力

```
日本国神戸県神戸市
```
