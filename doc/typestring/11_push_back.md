## 名前

push_back - 文字列の末尾に要素を追加する

## 書式

```c
#include <benly/typestring.h>

int s->push_back(STRING** self, char const c);
```

## 説明

メンバ関数`push_back()`は、`self`が管理する文字列の末尾へ要素`c`を追加する。
その際、末尾のNULL文字 ('\0') は上書きされ、追加後の文字列へ新たに付与される。

## 戻り値

成功した場合は 0 を返す。エラーが発生した場合は負の整数を返し、`errno`並びに`string_errno`にエラー原因を示す値を設定する。

## エラー

### EMEMORYALLOC (errno: ENOMEM)

メモリ再確保に失敗した。

## 例

```c
#include <benly/typestring.h>
#include <stdio.h>

int main(void)
{
    STRING* s   = new_string("hello");

    s->push_back(&s, '?');
    fprintf(stdout, "%s\n",
            s->c_str(s));

    s->release(s);

    return 0;
}
```

## 出力

```
hello?
```
