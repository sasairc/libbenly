## 名前

each_codepoint - STRING から1文字ずつコードポイントを取得する

## 書式

```c
#include <benly/typestring.h>

int s->each_codepoint(STRING* self, void (*fn)(gunichar))
```

## 説明

メンバ関数`each_codepoint()`は、`self`が管理する文字列から1文字ずつコードポイントを取り出し、関数`fn`の引数として繰り返し実行する。

実装上、範囲ベースではないため、 C++ における *std::for_each()* と機能的には等価である。

## 戻り値

成功した場合は 0 を返す。
エラーが発生した場合は負の整数を返し、`string_errno`へエラー原因を示す値を設定する。

## エラー

### ESTRISEMPTY

`self`が管理する文字列が存在しない、またはサイズが 0 だった。

### EINVALIDCHAR

不正なマルチバイト列を検出した。

## 例

```c
#include <benly/typestring.h>
#include <stdio.h>
#include <glib.h>

void sub(gunichar cp)
{
    fprintf(stdout, "%x\n",
            cp);

    return;
}

int main(void)
{
    STRING* s   = new_string("BTRON超漢字");

    s->each_codepoint(s, &sub);
    s->release(s);

    return 0;
}
```

### 出力

```
42
54
52
4f
4e
8d85
6f22
5b57
```
