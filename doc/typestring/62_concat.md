## 名前

concat - STRING へ文字列を連結する

## 書式

```c
#include <benly/typestring.h>

int s->concat(STRING** self, STRING* opp, ...);
```

## 説明

メンバ関数`concat()`は、`self`が管理する文字列の末尾へ、任意の数の STRING `opp`を連結する。
その際、末尾のNULL文字 ('\0') は上書きされ、連結後の文字列へ新たに付与される。

本関数の引数は可変長であるため、末尾を NULL で終端しなければならない。

## 戻り値

成功した場合は 0 を返す。
エラーが発生した場合は負の整数を返し、`errno`並びに`string_errno`にエラー原因を示す値を設定する。

## エラー

### ESTRISEMPTY

`opp`が管理する文字列が存在しなかった。
このエラーは`opp->string == NULL`の場合のみ発生する。

### EMEMORYALLOC (errno: ENOMEM)

メモリ再確保に失敗した。

## 例

```c
#include <benly/typestring.h>
#include <stdio.h>

int main(void)
{
    STRING* s1  = new_string("こんにちは、"),
          * s2  = new_string("ぼく"),
          * s3  = new_string("ドラえもん"),
          * s4  = new_string("ですか？");

    s1->concat(&s1, s2, s3, s4, NULL);
    fprintf(stdout, "%s\n",
            s1->c_str(s1));

    s1->release(s1);
    s2->release(s2);
    s3->release(s3);
    s4->release(s4);

    return 0;
}
```

### 出力

```
こんにちは、ぼくドラえもんですか？
```
