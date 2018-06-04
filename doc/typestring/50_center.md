## 名前

center - STRING を中央に寄せる

## 書式

```c
#include <benly/typestring.h>

int s->center(STRING** self, size_t s, char c);
```

## 説明

メンバ関数`center()`は、`self`が管理する文字列を`s`を長さとし、`c`を埋めて中央に寄せる。
`c`に対して NULL 文字 ('\0') を与えた場合は、既定値として半角スペースが用いられる。
また、`s <= size()`の場合は何も行わない。

## 戻り値

成功した場合は 0 を返す。
エラーが発生した場合は負の整数を返し、`errno`並びに`string_errno`へエラー原因を示す値を設定する。

## エラー

### ESTRISEMPTY

`self`が管理する文字列が存在しない、またはサイズが 0 だった。

### EMEMORYALLOC (errno: ENOMEM)

メモリ再確保に失敗した。

## 例

```c
#include <benly/typestring.h>
#include <stdio.h>

int main(void)
{
    STRING* s   = new_string("foo");

    s->center(&s, 10, '*');
    fprintf(stdout, "%s\n",
            s->c_str(s));

    s->assign(&s, "bar");
    s->center(&s, 11, '#');
    fprintf(stdout, "%s\n",
            s->c_str(s));

    s->release(s);

    return 0;
}
```

### 出力

```
***foo****
####bar####
```
