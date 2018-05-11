## 名前

c_str - STRING から文字列表現を取得する

## 書式

```c
#include <benly/typestring.h>

char* s->c_str(STRING* self);
```

## 説明

メンバ関数`c_str()`は、`self`から文字列表現を取得する。これは、`self->string`への操作と等価である。

## 戻り値

NULL文字 ('\0') で終端された文字列へのポインタ。

## エラー

本関数は失敗しない。

## 例

```c
#include <benly/typestring.h>
#include <stdio.h>

int main(void)
{
    STRING* s   = new_string("ソーニャ 折部やすな 呉織あぎり");

    fprintf(stdout, "%.*s\n",
            15, s->c_str(s) + 13);

    s->release(s);

    return 0;
}
```

### 出力

```
折部やすな
```
