## 名前

c_casecmp - 大文字と小文字を区別せず文字列を比較する

## 書式

```c
#include <benly/typestring.h>

int s->c_casecmp(STRING* self, char* const s);
```

## 説明

メンバ関数`c_casecmp()`は、`self`が管理する文字列と任意の文字列`s`を、大文字と小文字を区別せず比較する。
区別しないのは ASCII 文字のみであり、その他の文字の差異は区別される。

## 戻り値

同じなら 0 を返し、異なる場合は 1 を返す。
エラーが発生した場合は負の整数を返し、`errno`並びに`string_errno`へエラー原因を示す値を設定する。

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
    STRING* s   = new_string("BoKuドラえもんDeSu");

    fprintf(stdout, "c_casecmp() = %d\n",
            s->c_casecmp(s, "bOkUドラえもんdesu"));

    fprintf(stdout, "c_casecmp() = %d\n",
            s->c_casecmp(s, "私はドラえもんではありません"));

    s->release(s);

    return 0;
}
```

### 出力

```
c_casecmp() = 0
c_casecmp() = 1
```
