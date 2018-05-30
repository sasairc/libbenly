## 名前

substr - STRING から部分文字列の複製を行う

## 書式

```c
#include <benly/typestring.h>

int s->substr(STRING* self, size_t pos, size_t n, STRING** dest);
```

## 説明

メンバ関数`substr()`は、`self`が管理する文字列の指定位置`pos`番目から`n`要素を部分文字列として複製を行い、部分文字列を格納した新たな STRING 構造体へのポインタを`dest`へセットする。
`n`に対して 0 が与えられた場合、文字列の末尾まで複製を行う。

指定位置`pos`として有効な値は、現在の領域内に限られる。
従って、`self->size(self)`を超えてはならないし、必然的に 0 以上の整数値である。

呼び出し側は、メンバ関数`release()`を用いて返却された構造体を解放すべきである。

## 戻り値

成功した場合は 0 を返す。
エラーが発生した場合は負の整数を返し、`errno`並びに`string_errno`にエラー原因を示す値を設定する。

## エラー

### EOUTOFRANGE

`pos` (`n`) が無効な指定位置 (領域外) であった。

### EMEMORYALLOC (errno: ENOMEM)

メモリ確保に失敗した。

## 例

```c
#include <benly/typestring.h>
#include <stdio.h>

int main(void)
{
    STRING* s1  = new_string("ソーニャ 折部やすな 呉織あぎり"),
          * s2  = NULL;

    s1->substr(s1, 13, 15, &s2);
    fprintf(stdout, "%s\n",
            s2->c_str(s2));

    s1->release(s1);
    s2->release(s2);

    return 0;
}
```

### 出力

```
折部やすな
```
