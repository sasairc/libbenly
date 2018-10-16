## 名前

prepend - STRING の先頭に文字列を追加する

## 書式

```c
#include <benly/typestring.h>

int s->prepend(STRING** self, char* const str);
```

## 説明

メンバ関数`prepend()`は、`self`が管理する文字列の先頭へ任意の文字列`str`を追加する。
その際、末尾のNULL文字 ('\0') は上書きされ、連結後の文字列へ新たに付与される。
`prepend()`は`self`が文字列を管理していなくても構わない。その場合、処理は違えど`assign()`と同様の結果が得られる。

## 戻り値

成功した場合は 0 を返す。
エラーが発生した場合は負の整数を返し、`errno`並びに`string_errno`にエラー原因を示す値を設定する。

## エラー

### EARGISNULPTR

`str`が NULL だった。

### EMEMORYALLOC (errno: ENOMEM)

メモリ再確保に失敗した。

## 例

```c
#include <benly/typestring.h>
#include <stdio.h>

int main(void)
{
    STRING* s   = new_string("かわいい！");

    s->prepend(&s, "やすなちゃん");
    fprintf(stdout, "%s\n",
            s->c_str(s));
    s->release(s);

    return 0;
}
```

### 出力

```
やすなちゃんかわいい！
```
