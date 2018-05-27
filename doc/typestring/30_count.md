## 名前

count - STRING に含まれる要素・文字列の数を返す

## 書式

```c
#include <benly/typestring.h>

size_t s->count(STRING* self, char* const str);
```

## 説明

メンバ関数`count()`は、`self`が管理する文字列から要素・文字列`str`の数をカウントし返す。
エラーが発生した場合、`string_errno`にエラー原因を示す値を設定する。

## 戻り値

STRING に含まれる要素・文字列の数を返す。存在しない場合は 0 である。
注意点として、エラーが発生した場合も 0 を返す。その場合、`string_errno`を参照せよ。

## エラー

### EARGISNULPTR

`str`の値が文字列ではなく`NULL`であった。

### ESTRISEMPTY

`self`が管理する文字列が存在しない、またはサイズが 0 だった。

## 例

```c
#include <benly/typestring.h>
#include <stdio.h>

int main(void)
{
    STRING* s   = new_string("hello world");

    fprintf(stdout, "%zu\n",
            s->count(s, "l"));
    fprintf(stdout, "%zu\n",
            s->count(s, "lo"));

    s->assign(&s, "志布志市志布町志布志の志布志市役所志布志支所");
    fprintf(stdout, "%zu\n",
            s->count(s, "志布志"));

    s->release(s);

    return 0;
}
```

### 出力

```
3
1
4
```
