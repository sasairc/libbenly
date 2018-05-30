## 名前

upcase - STRING の小文字を大文字へ変換する

## 書式

```c
#include <benly/typestring.h>

int s->upcase(STRING** self);
```

## 説明

メンバ関数`upcase()`は、`self`が管理する文字列のうち、半角 ASCII 文字 [a-z] を全て大文字に変換する。
その他の文字は変換されず、そのままとなる。

## 戻り値

成功した場合は 0 を返す。
エラーが発生した場合は負の整数を返し、`string_errno`にエラー原因を示す値を設定する。

## エラー

### ESTRISEMPTY

`self`が管理する文字列が存在しない、またはサイズが 0 だった。

## 例

```c
#include <benly/typestring.h>
#include <stdio.h>

int main(void)
{
    STRING* s   = new_string("hello world");

    s->upcase(&s);
    fprintf(stdout, "%s\n",
            s->c_str(s));
    s->release(s);

    return 0;
}
```

### 出力

```
HELLO WORLD
```
