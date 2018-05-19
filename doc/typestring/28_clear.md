## 名前

clear - STRING から全ての要素を削除する

## 書式

```c
#include <benly/typestring.h>

void s->clear(STRING** self);
```

## 説明

メンバ関数`clear()`は、`self`が管理している全ての要素を削除する。また、本関数はメモリの解放も行い、関連する各値も初期化される。

## 戻り値

本関数に戻り値は存在しない。

## エラー

本関数は失敗しない。

## 例

```c
#include <benly/typestring.h>
#include <stdio.h>

int main(void)
{
    STRING* s1  = new_string("没キャラ");

    s1->clear(&s1);
    if (s1->empty(s1)) {
        fprintf(stdout, "%s\n",
                s1->c_str(s1));
        fprintf(stdout, "size = %zu\n",
                s1->size(s1));
        fprintf(stdout, "capacity = %zu\n",
                s1->capacity(s1));
    }
    s1->release(s1);

    return 0;
}
```

### 出力

```
(null)
size = 0
capacity = 0
```
