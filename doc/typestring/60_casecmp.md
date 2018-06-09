## 名前

casecmp - 大文字と小文字を区別せず文字列を比較する

## 書式

```c
#include <benly/typestring.h>

int s->casecmp(STRING* self, STRING* opp);
```

## 説明

メンバ関数`casecmp()`は、`self`が管理する文字列と`opp`が管理する文字列を、大文字と小文字を区別せず比較する。
区別しないのは ASCII 文字のみであり、その他の文字の差異は区別される。

## 戻り値

同じなら 0 を返し、異なる場合は 1 を返す。
エラーが発生した場合は負の整数を返し、`errno`並びに`string_errno`へエラー原因を示す値を設定する。

## エラー

### EARGISNULPTR

`opp`が NULL だった。

### ESTRISEMPTY

`self`または`opp`が管理する文字列が存在しない、またはサイズが 0 だった。

### EMEMORYALLOC (errno: ENOMEM)

メモリ確保に失敗した。

## 例

```c
#include <benly/typestring.h>
#include <stdio.h>

int main(void)
{
    STRING* s1  = new_string("abcdef"),
          * s2  = new_string("aBcDeF");

    fprintf(stdout, "casecmp() = %d\n",
            s1->casecmp(s1, s2));

    s2->assign(&s2, "abcde");
    fprintf(stdout, "casecmp() = %d\n",
            s1->casecmp(s1, s2));

    s1->release(s1);
    s2->release(s2);

    return 0;
}
```

### 出力

```
casecmp() = 0
casecmp() = 1
```
