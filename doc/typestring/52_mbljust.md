## 名前

mbljust - 全角文字を含む STRING を左寄せにする

## 書式

```c
#include <benly/typestring.h>

int s->mbljust(STRING** self, size_t s, char c);
```

## 説明

メンバ関数`mbljust()`は、`self`が管理する文字列を`s`を長さとし、`c`を埋めて左寄せにする。
`c`に対して NULL 文字 ('\0') を与えた場合は、既定値として半角スペースが用いられる。
また、`s`の長さ (表示幅) が操作後と同じになる場合は何も行わない。

## 戻り値

成功した場合は 0 を返す。
エラーが発生した場合は負の整数を返し、`errno`並びに`string_errno`へエラー原因を示す値を設定する。

## エラー

### ESTRISEMPTY

`self`が管理する文字列が存在しない、またはサイズが 0 だった。

### EINVALIDCHAR

不正なマルチバイト列を検出した。

### EMEMORYALLOC (errno: ENOMEM)

メモリ再確保に失敗した。

## 例

```c
#include <benly/typestring.h>
#include <stdio.h>

int main(void)
{
    STRING* s1  = new_string("ソーニャ"),
          * s2  = new_string("折部やすな"), /* 2 (幅) * 5 (文字数) */
          * s3  = new_string("呉織あぎり");

    s1->mbljust(&s1, 16, '*');
    s2->mbljust(&s2, 16, '*');
    s3->mbljust(&s3, 16, '*');
    fprintf(stdout, "%s\n%s\n%s\n",
            s1->c_str(s1), s2->c_str(s2), s3->c_str(s3));

    s1->release(s1);
    s2->release(s2);
    s3->release(s3);

    return 0;
}
```

### 出力

```
ソーニャ********
折部やすな******
呉織あぎり******
```
