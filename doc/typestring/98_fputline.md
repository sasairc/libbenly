## 名前

fputline - ファイルへ一行書き込む

## 書式

```c
#include <benly/typestring.h>

int fputline(FILE* fp, STRING* s);
```

## 説明

関数`fputline()`は、書き込み可能なファイルストリーム`fp`に対し、 STRING 構造体`s`の文字列を書き込む。
本関数は`fputs()`のラッパでしかない。従って、改行は出力しない。

## 戻り値

書き込みに成功した場合は負でない整数を返す。失敗した場合 EOF を返す。

## エラー

### EARGISNULPTR

`fp`または`s`が NULL であった。

### EOF

書き込みに失敗した。

## 例

```c
#include <benly/typestring.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    size_t      i       = 0,
                idx     = 0;

    FILE*       fp      = NULL;

    STRING*     s1      = new_string("こんにちは　ぼく　ドラえもん　です"),
          **    s2      = NULL;

    idx = s1->split(s1, "　", &s2);
    s1->release(s1);
    fp = fopen("./out.txt", "w");
    while (i < idx) {
        s2[i]->push_back(&s2[i], '\n');
        fputline(fp, s2[i]);
        s2[i]->release(s2[i]);
        i++;
    }
    fclose(fp);
    free(s2);

    return 0;
}
```

### out.txt

```
こんにちは
ぼく
ドラえもん
です
```
