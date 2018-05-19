## 名前

c_compare - 他の文字列と比較する

## 書式

```c
#include <benly/typestring.h>

int s->compare(STRING* self, const char* s);
```

## 説明

メンバ関数`c_compare()`は、`self`が管理する文字列と文字列`s`を比較する。

## 戻り値

同じなら 0 を返し、異なる場合は 1 を返す。

## エラー

本関数はエラーを設定しない。

## 例

```c
#include <benly/typestring.h>
#include <stdio.h>

int main(void)
{
    STRING* s1  = new_string("abc");

    char*   s2  = "abc",
        *   s3  = "qwerty";

    fprintf(stdout, "c_compare = %d\n",
            s1->c_compare(s1, s2));
    fprintf(stdout, "c_compare = %d\n",
            s1->c_compare(s1, s3));

    s1->release(s1);

    return 0;
}
```

### 出力

```
c_compare = 0
c_compare = 1
```
