## 名前

chomp - STRING 末尾の改行文字を削除する

## 書式

```c
#include <benly/typestring.h>

size_t s->chomp(STRING** self);
```

## 説明

メンバ関数`chomp()`は、`self`が管理する文字列末尾に存在する改行文字を削除する。
改行文字は *\r* および *\n* を指し、連続して複数存在する場合は全て取り除く。

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
    STRING* s   = new_string("hello\n");

    fprintf(stdout, "size() = %zu\n",
            s->size(s));
    fprintf(stdout, "chomp() = %zu\n",
            s->chomp(&s));
    fprintf(stdout, "size() = %zu, c_str() = %s\n\n",
            s->size(s), s->c_str(s));

    s->assign(&s, "hello\r");
    fprintf(stdout, "size() = %zu\n",
            s->size(s));
    fprintf(stdout, "chomp() = %zu\n",
            s->chomp(&s));
    fprintf(stdout, "size() = %zu, c_str() = %s\n\n",
            s->size(s), s->c_str(s));

    s->assign(&s, "hello\r\n");
    fprintf(stdout, "size() = %zu\n",
            s->size(s));
    fprintf(stdout, "chomp() = %zu\n",
            s->chomp(&s));
    fprintf(stdout, "size() = %zu, c_str() = %s\n\n",
            s->size(s), s->c_str(s));

    s->assign(&s, "hello\r\n\r\n\n");
    fprintf(stdout, "size() = %zu\n",
            s->size(s));
    fprintf(stdout, "chomp() = %zu\n",
            s->chomp(&s));
    fprintf(stdout, "size() = %zu, c_str() = %s\n",
            s->size(s), s->c_str(s));

    s->release(s);

    return 0;
}
```

### 出力

```
size() = 6
chomp() = 1
size() = 5, c_str() = hello

size() = 6
chomp() = 1
size() = 5, c_str() = hello

size() = 7
chomp() = 2
size() = 5, c_str() = hello

size() = 10
chomp() = 5
size() = 5, c_str() = hello
```
