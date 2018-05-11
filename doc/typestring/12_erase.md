## 名前

erase - STRING から要素を削除する

## 書式

```c
#include <benly/typestring.h>

int s->erase(STRING** self, size_t pos, size_t n);
```

## 説明

メンバ関数`erase()`は、`self`のメンバ変数`self->string`の指定位置`pos`から`n`要素を削除する。
`n`に対して 0 が与えられた場合、文字列の末尾まで要素の削除を行う。

指定位置`pos`として有効な値は、現在の領域内に限られる。
従って、`self->size(self)`を超えてはならないし、必然的に 0 以上の整数値である。

## 戻り値

成功した場合は 0 を返す。エラーが発生した場合は負の整数を返し、`string_errno`にエラー原因を示す値を設定する。

## エラー

### EOUTOFRANGE

`pos` (`n`) が無効な指定位置 (領域外) であった。

## 例

```c
#include <benly/typestring.h>
#include <stdio.h>

int main(void)
{
    STRING* s   = new_string("12345");

    s->erase(&s, 1, 2);
    fprintf(stdout, "%s\n",
            s->c_str(s));

    s->release(s);

    return 0;
}
```

### 出力

```
145
```
