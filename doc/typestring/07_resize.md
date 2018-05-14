## 名前

resize - 文字列の長さを変更する

## 書式

```c
#include <benly/typestring.h>

int s->resize(STRING** self, size_t n, char const c);
```

## 説明

メンバ関数`resize()`は、`self`が管理する文字列の長さを変更する。
`n > size()`の場合、拡張する長さだけ要素`c`を付け加え、終端にNULL文字 ('\0') を付与する。
また、`n <= size()`の場合は`self`が管理する文字列のはじめ`n`要素を残し、残りはNULL文字 ('\0') で初期化する。

## 戻り値

成功した場合は 0 を返す。エラーが発生した場合は負の整数を返し、`errno`並びに`string_errno`にエラー原因を示す値を設定する。

## エラー

### EMEMORYALLOC (errno: ENOMEM)

文字列の拡張時、メモリ確保に失敗した。

## 例

```c
#include <benly/typestring.h>
#include <stdio.h>

int main(void)
{
    STRING*     s   = new_string("hello");

    s->resize(&s, 10, '?');
    fprintf(stdout, "%s\n",
            s->c_str(s));

    s->resize(&s, 2, 'A');
    fprintf(stdout, "%s\n",
            s->c_str(s));

    s->release(s);

    return 0;
}
```

### 出力

```
hello?????
he
```
