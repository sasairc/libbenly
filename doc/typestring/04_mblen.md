## 名前

mblen - 実文字数を計算する

## 書式

```c
#include <benly/typestring.h>

size_t s->mblen(STRING* self);
```

## 説明

メンバ関数`mblen()`は、`self`が管理する文字列の実文字数を計算する。
この際、終端のNULL文字 ('\0') のバイト数は含まれない。
エラーが発生した場合、`string_errno`にエラー原因を示す値を設定する。

## 戻り値

`mblen()`は、`self`が管理する文字列の実文字数を返す。

## エラー

### EINVALIDCHAR

不正なマルチバイト列を検出した。

## 例

```c
#include <benly/typestring.h>
#include <stdio.h>

int main(void)
{
    STRING* s   = NULL;

    s = new_string("やすなちゃんkawaii!");
    fprintf(stdout, "s->mblen() = %zu\n",
            s->mblen(s));
    s->release(s);

    return 0;
}
```

### 出力

```
s->mblen() = 13
```

## 注意

`mblen()`の挙動は`LC_CTYPE`カテゴリ情報によって異なる。しかし、この実装でも日本人のみならず、北海道人民には不便しないであろう。
