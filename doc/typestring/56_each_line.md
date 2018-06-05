## 名前

each_line - STRING から改行文字で分割し、1行ずつ取り出す

## 書式

```c
#include <benly/typestring.h>

int s->each_line(STRING* self, char* const delim, void (*fn)(STRING*));
```

## 説明

メンバ関数`each_line()`は、`self`が管理する文字列を区切り文字`delim`で分割し、分割後の各 STRING\* を関数`fn`の引数として、要素終端まで繰り返し実行する。
`delim`に対して NULL が与えられた場合、既定として ('\n') が用いられる。
注意点として、本関数は`split()`の応用であるため、分割後の文字列に改行文字 ('\n') は含まれない。
分割は本関数内で行われており、よって、分割後の各 STRING は明示的に解放する必要は無い。

実装上、範囲ベースではないため、 C++ における *std::for_each()* と機能的には等価である。

## 戻り値

成功した場合は 0 を返す。
エラーが発生した場合は負の整数を返し、`errno`並びに`string_errno`へエラー原因を示す値を設定する。

## エラー

### ESTRISEMPTY

`self`が管理する文字列が存在しない、またはサイズが 0 だった。

### EARGISNULPTR

`fn`の値が NULL だった。

### EMEMORYALLOC (errno: ENOMEM)

メモリ確保に失敗した。

## 例

```c
#include <benly/typestring.h>

/*
 * グローバル変数は滅ぼせ
 */
int     i       = 0;

STRING* s2[3]   = {NULL};

void sub2(STRING* line)
{
    line->mbcenter(&line, 16, '*');
    line->push_back(&line, '\n');
    fputline(stdout, line);

    return;
}

void sub1(STRING* line)
{
    line->copy(line, &s2[i]);
    i++;

    return;
}

int main(void)
{
    STRING* s1  = new_string("ソーニャ\nやすな\nあぎり");

    s1->each_line(s1, NULL, &sub1);
    s1->each_line(s1, NULL, &sub2);

    fprintf(stdout, "%s\n%s\n%s\n",
            s2[0]->c_str(s2[0]),
            s2[1]->c_str(s2[1]),
            s2[2]->c_str(s2[2]));

    s2[0]->release(s2[0]);
    s2[1]->release(s2[1]);
    s2[2]->release(s2[2]);
    s1->release(s1);

    return 0;
}
```

### 出力

```
****ソーニャ****
*****やすな*****
*****あぎり*****
ソーニャ
やすな
あぎり
```
