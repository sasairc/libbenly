## 名前

reverse - STRING の要素を反転する

## 書式

```c
#include <benly/typestring.h>

int s->reverse(STRING** self);
```

## 説明

メンバ関数`reverse()`は、`self`が管理する文字列の要素の順番を反転する。

## 戻り値

成功した場合は 0 を返す。
エラーが発生した場合は負の整数を返し、`errno`並びに`string_errno`にエラー原因を示す値を設定する。

## エラー

### ESTRISEMPTY

`self`が管理する文字列が存在しない、またはサイズが 0 だった。

### EINVALIDCHAR

不正なマルチバイト列を検出した。

### EMEMORYALLOC (errno: ENOMEM)

メモリ確保に失敗した。

## 例

```c
#include <benly/typestring.h>
#include <stdio.h>

int main(void)
{
    STRING* s   = new_string("doraemon");

    s->reverse(&s);
    fprintf(stdout, "%s\n",
            s->c_str(s));

    s->assign(&s, "ドラえもん");
    s->reverse(&s);
    fprintf(stdout, "%s\n",
            s->c_str(s));

    s->release(s);

    return 0;
}
```

### 出力

```
nomearod
んもえラド
```

## 余談

"doraemon" を reverse() した "nomearod" のコレジャナイ感がすごい。　
