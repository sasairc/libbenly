## 名前

data - STRING が管理するデータを取得する

## 書式

```c
#include <benly/typestring.h>

char* s->data(STRING* self);
```

## 説明

メンバ関数`data()`は、`self`が管理するデータ (文字列) を取得する。このメンバ関数は`c_str()`の別名である。

## エラー

本関数は失敗しない。

## 例

```c
#include <benly/typestring.h>
#include <stdio.h>

int main(void)
{
    STRING* s   = new_string("doraemon");

    fprintf(stdout, "data() = %p\nc_str() = %p\nfront() = %p\n",
            s->data, s->c_str, s->front);
    s->release(s);

    return 0;
}
```

### 出力

```
data() = 0x56199af15527
c_str() = 0x56199af15527
front() = 0x56199af15470
```
