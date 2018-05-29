## 名前

lstrip - STRING 先頭の空白を取り除く

## 書式

```c
#include <benly/typestring.h>

size_t s->lstrip(STRING** self);
```

## 説明

メンバ関数`lstrip()`は、`self`が管理する文字列の先頭の空白を取り除く。
この際、端末制御文字 *\t, \n, \v, \f, \r* も取り除くため、必要な場合は注意が必要。

## 戻り値

削除した要素数を返す。

## エラー

本関数は以下の`string_errno`を設定する。ただし影響は少ないだろう。

### ESTRISEMPTY

`self`が管理する文字列が存在しない、またはサイズが 0 だった。

## 例

```c
#include <benly/typestring.h>
#include <stdio.h>

int main(void)
{
    STRING* s   = new_string("    やすなちゃん！");

    fprintf(stdout, "lstrip() = %zu\n",
            s->lstrip(&s));
    fprintf(stdout, "size() = %zu, c_str() = \"%s\"\n",
            s->size(s), s->c_str(s));

    s->release(s);

    return 0;
}
```

### 出力

```
lstrip() = 4
size() = 21, c_str() = "やすなちゃん！"
```
