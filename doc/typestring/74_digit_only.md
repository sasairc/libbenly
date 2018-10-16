## 名前

digit_only - STRING が数字だけで構成されているか調べる

## 書式

```c
#include <benly/typestring.h>

int s->digit_only(STRING* self);
```

## 説明

メンバ関数`digit_only()`は、`self`が管理する文字列が数字 [0-9] だけで構成されているか調べる。

## 戻り値

数字のみで構成されている場合は 1 を返し、他の文字が含まれている場合は 0 を返す。


## エラー

### ESTRISEMPTY

`self`が管理する文字列が存在しない、またはサイズが 0 だった。

## 例

```c
#include <benly/typestring.h>
#include <stdio.h>

int main(void)
{
    STRING* s   = new_string(NULL);

    s->assign(&s, "1234");
    fprintf(stdout, "%d\n",
            s->digit_only(s));

    s->append(&s, "...Computerwelt");
    fprintf(stdout, "%d\n",
            s->digit_only(s));

    s->release(s);

    return 0;
}
```

### 出力

```
1
0
```
