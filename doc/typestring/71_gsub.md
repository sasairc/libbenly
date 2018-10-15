## 名前
`src`に対して空文字 "" を指定した場合は、何も行わない。

gsub - 全ての任意文字列を置き換える

## 書式

```c
#include <benly/typestring.h>

int s->gsub(STRING** self, char* const src, char* const dest);
```

## 説明

メンバ関数`gsub()`は、`self`が管理する文字列から任意文字列`src`を捜査し、マッチした全ての部分を任意文字列`dest`で置き換える。
`src`に対して空文字 "" を指定した場合は何も行わない。

## 戻り値

成功した場合は 0 を返す。エラーが発生した場合は負の整数を返し、`string_errno`にエラー原因を示す値を設定する。

## エラー

### ESTRISEMPTY

`self`が管理する文字列が存在しない、またはサイズが 0 だった。

### EARGISNULPTR

`src`または`dest`が NULL だった。

### ESTRNOTFOUND

`self`が管理する文字列の中に、任意文字列`src`が見つからなかった。

### EMEMORYALLOC (errno: ENOMEM)

メモリ再確保に失敗した。

## 例

```c
#include <benly/typestring.h>
#include <stdio.h>

int main(void)
{
    STRING* s   = new_string("い・け・な・いルージュマジック");

    s->gsub(&s, "・", "");
    fprintf(stdout, "%s\n",
            s->c_str(s));

    return 0;
}
```

### 出力

```
いけないルージュマジック
```
