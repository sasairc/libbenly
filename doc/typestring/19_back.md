## 名前

back - STRING の末尾要素へのポインタを取得する

## 書式

```c
#include <benly/typestring.h>

char* s->back(STRING* self);
```

## 説明

メンバ関数`back()`は、`self`が管理する文字列の末尾要素へのポインタを返却する。

## 戻り値

成功した場合は末尾要素へのポインタを返す。
エラーが発生した場合は NULL を返し、`string_errno`にエラー原因を示す値を設定する。

## エラー

### ESTRISEMPTY

`self`が管理する文字列が存在しない、またはサイズが 0 だった。

## 例

```c
#include <benly/typestring.h>
#include <stdio.h>

int main(void)
{
    STRING* s   = new_string("doraemon");

    if (s->back(s) != NULL)
        fprintf(stdout, "%c\n",
                *s->back(s));
    s->release(s);

    return 0;
}
```

### 出力

```
n
```
