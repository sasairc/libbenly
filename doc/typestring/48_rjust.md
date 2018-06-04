## 名前

rjust - STRING を右寄せにする

## 書式

```c
#include <benly/typestring.h>

int s->rjust(STRING** self, size_t s, char c);
```

## 説明

メンバ関数`rjust()`は、`self`が管理する文字列を`s`を長さとし、`c`を埋めて右寄せにする。
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

    s->rjust(&s, 8, '\0');
    fprintf(stdout, "%s\n",
            s->c_str(s));

    s->assign(&s, "bar");
    s->rjust(&s, 10, '*');
    fprintf(stdout, "%s\n",
            s->c_str(s));

    s->release(s);

    return 0;
}
```

### 出力

```
     foo
*******bar
```
