## 名前

each_byte - STRING から 1 byte ずつ取り出す

## 書式

```c
#include <benly/typestring.h>

int s->each_byte(STRING* self, void (*fn)(char));
```

## 説明

メンバ関数`each_byte()`は、`self`が管理する文字列から 1byte ずつ取り出し、関数`fn`の引数として繰り返し実行する。

実装上、範囲ベースではないため、 C++ における *std::for_each()* と機能的には等価である。

## 戻り値

成功した場合は 0 を返す。
エラーが発生した場合は負の整数を返し、`string_errno`へエラー原因を示す値を設定する。

## エラー

### ESTRISEMPTY

`self`が管理する文字列が存在しない、またはサイズが 0 だった。

### EARGISNULPTR

`fn`の値が NULL だった。

## 例

```c
#include <benly/typestring.h>
#include <stdio.h>

void func(char fixnum)
{
    static int  i    = 0;

    fprintf(stdout, "%X ",
            fixnum & 0x0000FF);

    if (i == 2 && !(i = 0))
        putchar('\n');
    else
        i++;

    return;
}

int main(void)
{
    STRING* s   = new_string("ドラえもん");

    s->each_byte(s, &func);
    s->release(s);

    return 0;
}
```

### 出力

```
E3 83 89 
E3 83 A9 
E3 81 88 
E3 82 82 
E3 82 93 
```
