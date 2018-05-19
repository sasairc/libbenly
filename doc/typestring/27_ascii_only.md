## 名前

ascii_only - STRING が ASCII 文字だけで構成されているか調べる

## 書式

```c
#include <benly/typestring.h>

int s->ascii_only(STRING* self);
```

## 説明

メンバ関数`ascii_only()`は、`self`が管理する文字列が ASCII 文字だけで構成されているか調べる。

## 戻り値

ASCII 文字のみで構成されているなら 1 を返し、他の文字が含まれる場合は 0 を返す。

## エラー

本関数はエラーを設定しない。

## 例

```c
#include <benly/typestring.h>
#include <stdio.h>

int main(void)
{
    STRING* s1  = new_string("weekly ascii"),
          * s2  = new_string("週刊アスキー");

    fprintf(stdout, "ascii_only = %d\n",
            s1->ascii_only(s1));
    fprintf(stdout, "ascii_only = %d\n",
            s2->ascii_only(s2));

    s1->release(s1);
    s2->release(s2);

    return 0;
}
```

### 出力

```
ascii_only = 1
ascii_only = 0
```
