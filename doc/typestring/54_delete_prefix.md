## 名前

delete_prefix - STRING から任意の先頭文字列を削除する

## 書式

```c
#include <benly/typestring.h>

int s->delete_prefix(STRING** self, char* const str);
```

## 説明

メンバ関数`delete_prefix()`は、`self`が管理する文字列の先頭から、任意の文字列`str`とマッチする部分を削除する。
削除後、新たに末尾へ NULL 文字 ('\0')が付与される。

## 戻り値

削除をしたら 1 を返す。削除を行わなかった (マッチしなかった) 場合は 0 を返す。
エラーが発生した場合は負の整数を返し、`string_errno`へエラー原因を示す値を設定する。

## エラー

### ESTRISEMPTY

`self`が管理する文字列が存在しない、またはサイズが 0 だった。

## 例

```c
#include <benly/typestring.h>
#include <stdio.h>

int main(void)
{
    STRING* s1  = new_string("hello"),
          * s2  = NULL;
          
    s1->copy(s1, &s2);

    s1->delete_prefix(&s1, "hel");
    s2->delete_prefix(&s2, "llo");
    fprintf(stdout, "%s\n",
            s1->c_str(s1));
    fprintf(stdout, "%s\n",
            s2->c_str(s2));

    s1->release(s1);
    s1->release(s2);

    return 0;
}
```

### 出力

```
lo
hello
```
