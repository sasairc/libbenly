## 名前

compare - 他の STRING 構造体と比較する

## 書式

```c
#include <benly/typestring.h>

int s->compare(STRING* self, STRING* opp);
```

## 説明

メンバ関数`compare()`は、`self`が管理する文字列と`opp`が管理する文字列を比較する。

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
    STRING* s1  = new_string("abc"),
          * s2  = new_string("abc"),
          * s3  = new_string("qwerty");

    fprintf(stdout, "compare = %d\n",
            s1->compare(s1, s2));
    fprintf(stdout, "compare = %d\n",
            s1->compare(s1, s3));

    s1->release(s1);
    s2->release(s2);
    s3->release(s3);

    return 0;
}
```

### 出力

```
compare = 0
compare = 1
```
