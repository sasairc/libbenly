## 名前

each_char - STRING から1文字ずつ取り出す

## 書式

```c
#include <benly/typestring.h>

int s->each_char(STRING* self, void (*fn)(char*));
```

## 説明

メンバ関数`each_char()`は、`self`が管理する文字列から1文字ずつ取り出し、関数`fn`の引数として繰り返し実行する。
本関数はマルチバイト文字をサポートしており、マルチバイト列で構成される文字も正常に扱える。

実装上、範囲ベースではないため、 C++ における *std::for_each()* と機能的には等価である。

## 戻り値

成功した場合は 0 を返す。
エラーが発生した場合は負の整数を返し、`errno`並びに`string_errno`へエラー原因を示す値を設定する。

## エラー

### ESTRISEMPTY

`self`が管理する文字列が存在しない、またはサイズが 0 だった。

### EARGISNULPTR

`fn`の値が NULL だった。

### EINVALIDCHAR

不正なマルチバイト列を検出した。

### EMEMORYALLOC (errno: ENOMEM)

メモリ確保に失敗した。

## 例

```c
#include <benly/typestring.h>
#include <stdio.h>

void sub(char* c)
{
    fprintf(stdout, "%s ",
            c);

    return;
}

int main(void)
{
    STRING* s   = new_string("やすなちゃんKawaii!!");

    s->each_char(s, &sub);
    putchar('\n');
    s->release(s);

    return 0;
}
```

### 出力

```
や す な ち ゃ ん K a w a i i ! ! 
```
