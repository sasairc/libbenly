## 名前

append - STRING へ文字列を連結する

## 書式

```c
#include <benly/typestring.h>

int s->append(STRING** self, char* const str);
```

## 説明

メンバ関数`append()`は、`self`が管理する文字列へ文字列`str`を連結する。
その際、末尾のNULL文字 ('\0') は上書きされ、連結後の文字列へ新たに付与される。

`append()`は`self`が文字列を管理していなくても構わない。その場合、処理は違えど`assign()`と同様の結果が得られる。

## 戻り値

成功した場合は 0 を返す。エラーが発生した場合は負の整数を返し、`errno`並びに`string_errno`にエラー原因を示す値を設定する。

## エラー

### EARGISNULPTR

`str`の値が文字列ではなく`NULL`であった。

### EMEMORYALLOC (errno: ENOMEM)

メモリ再確保に失敗した。

## 例

```c
#include <benly/typestring.h>
#include <stdio.h>

int main(void)
{
    STRING* s   = new_string(NULL);

    s->append(&s, "やすなちゃん");  /* assign() と等価 */
    s->append(&s, "はウザおバカわいい");
    s->append(&s, "！");
    fprintf(stdout, "%s\n",
            s->c_str(s));

    s->release(s);

    return 0;
}
```

### 出力

```
やすなちゃんはウザおバカわいい！
```
