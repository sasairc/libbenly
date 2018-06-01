## 名前

to_f - STRING を float に変換する

## 書式

```c
#include <benly/typestring.h>

float s->to_f(STRING* self);
```

## 説明

メンバ関数`to_f()`は、`self`が管理する文字列の有効な範囲を float に変換する。

## 戻り値

変換後の値を返す。

## エラー

本関数はエラーを設定しない。

## 例

```c
#include <benly/typestring.h>
#include <stdio.h>

int main(void)
{
    STRING* s   = new_string("3.141592");

    fprintf(stdout, "%f\n",
            s->to_f(s));

    s->assign(&s, "-1.2e-3");
    fprintf(stdout, "%f\n",
            s->to_f(s));

    s->release(s);

    return 0;
}
```

### 出力

```
3.141592
-0.001200
```
