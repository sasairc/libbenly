## 名前

c_concat - STRING へ文字列を連結する

## 書式

```c
#include <benly/typestring.h>

int s->c_concat(STRING** self, char* const s, ...);
```

## 説明

メンバ関数`c_concat()`は、`self`が管理する文字列の末尾へ、任意の数の文字列`s`を連結する。
その際、末尾のNULL文字 ('\0') は上書きされ、連結後の文字列へ新たに付与される。

本関数の引数は可変長であるため、末尾を NULL で終端しなければならない。

## 戻り値

成功した場合は 0 を返す。
エラーが発生した場合は負の整数を返し、`errno`並びに`string_errno`にエラー原因を示す値を設定する。

## エラー

### EMEMORYALLOC (errno: ENOMEM)

メモリ再確保に失敗した。

## 例

```c
#include <benly/typestring.h>
#include <stdio.h>

int main(void)
{
    STRING* s   = new_string("やすなちゃんの");

    s->c_concat(&s, "もちもち", "ほっぺ！", NULL);
    fprintf(stdout, "%s\n",
            s->c_str(s));
    s->release(s);

    return 0;
}
```

### 出力

```
やすなちゃんのもちもちほっぺ！
```
