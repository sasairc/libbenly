## 名前

split - STRING から文字列を分割する

## 書式

```c
#include <benly/typestring.h>

size_t s->split(STRING* self, char* const delim, STRING*** dest);
```

## 説明

メンバ関数`split()`は、`self`が管理する文字列から、文字列`delim`を区切り文字と見なし分割を行う。
分割後の文字列は、新たな STRING 構造体に格納され、これらを指すポインタ配列の先頭アドレスを`dest`へセットする。
呼び出し側は、メンバ関数`release()`を用いて分割された構造体を解放すべきである。

## 戻り値

STRING 構造体へのポインタ配列の要素数を返す。
エラーが発生した場合は 0 を返し、`errno`並びに`string_errno`にエラー原因を示す値を設定する。

## エラー

### EARGISNULPTR

`delim`の値が文字列ではなく`NULL`であった。

### ESTRISEMPTY

`self`が管理する文字列が存在しない、またはサイズが 0 だった。

### EMEMORYALLOC (errno: ENOMEM)

メモリ確保に失敗した。

## 例

### 例.1

```c
#include <benly/typestring.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    size_t      i       = 0,
                idx     = 0;

    STRING*     src     = new_string("foo,bar,baz"),
          **    dest    = NULL;

    idx = src->split(src, ",", &dest);
    src->release(src);
    while (i < idx) {
        fprintf(stdout, "%s\n",
                dest[i]->c_str(dest[i]));
        dest[i]->release(dest[i]);
        i++;
    }
    free(dest);

    return 0;
}
```

#### 例.1 - 出力

```
foo
bar
baz
```

### 例.2

```c
#include <benly/typestring.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    size_t      i       = 0,
                idx     = 0;

    STRING*     src     = new_string("こんばんは"),
          **    dest    = NULL;

    idx = src->split(src, "ん", &dest);
    src->release(src);
    while (i < idx) {
        fprintf(stdout, "%s\n",
                dest[i]->c_str(dest[i]));
        dest[i]->release(dest[i]);
        i++;
    }
    free(dest);

    return 0;
}
```

#### 例.2 - 出力
```
こ
ば
は
```

### 例.3

```c
#include <benly/typestring.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    size_t      i       = 0,
                idx     = 0;

    STRING*     src     = new_string("志布志市志布町志布志の志布志市役所志布志支所"),
          **    dest    = NULL;

    idx = src->split(src, "志布志", &dest);
    src->release(src);
    while (i < idx) {
        fprintf(stdout, "%s\n",
                dest[i]->c_str(dest[i]));
        dest[i]->release(dest[i]);
        i++;
    }
    free(dest);

    return 0;
}
```

#### 例.3 - 出力

```

市志布町
の
市役所
支所
```
