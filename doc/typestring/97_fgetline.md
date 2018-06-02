## 名前

fgetline - ファイルから一行読み込む

## 書式

```c
#include <benly/typestring.h>

int fgetline(FILE* fp, STRING** s);
```

## 説明

関数`fgetline()`は、読み込み可能なファイルストリーム`fp`から一行全てを読み込み、その文字列を格納した STRING 構造体へのポインタを`s`へセットする。
この際、文字列の終端にNULL文字列 ('\0') が追加される。
呼び出し側は、メンバ関数`release()`を用いてこの構造体を解放すべきである。

## 戻り値

成功した場合は 0 を返す。また、ファイルの終端に達した場合は EOF を返す。
エラーが発生した場合は負の整数を返し、`errno`並びに`string_errno`にエラー原因を示す値を設定する。

## エラー

### EMEMORYALLOC (errno: ENOMEM)

内部バッファ、もしくは STRING 構造体のメモリ確保に失敗した。

## 例

```c
#include <benly/typestring.h>
#include <stdio.h>

int main(void)
{
    STRING* s   = NULL;

    FILE*   fp  = NULL;

    fp = fopen("/usr/lib/os-release", "r");
    while (fgetline(fp, &s) != EOF) {
        fprintf(stdout, "%s",
                s->c_str(s));
        s->release(s);
    }
    fclose(fp);

    return 0;
}
```

### 出力

```
PRETTY_NAME="Debian GNU/Linux 9 (stretch)"
NAME="Debian GNU/Linux"
VERSION_ID="9"
VERSION="9 (stretch)"
ID=debian
HOME_URL="https://www.debian.org/"
SUPPORT_URL="https://www.debian.org/support"
BUG_REPORT_URL="https://bugs.debian.org/"
```
