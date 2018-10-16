## 名前

crypt  - 文字列を暗号化する

## 書式

```c
#include <benly/typestring.h>

char* s->crypt(STRING* self, char* const salt);

int s->crypt2(STRING* self, char* const salt, char** dest);
```

メンバ関数`crypt()`および`crypt2()`は、`self`が管理する文字列を鍵として扱い、任意のソルト要素`salt`を用いて暗号化を行う。
`crypt()`の詳細な実装については[crypt (3)](https://linuxjm.osdn.jp/html/LDP_man-pages/man3/crypt.3.html)を参照されたい。

`crypt()`と`crypt2()`の違いは、暗号化された文字列の返却方法の違いのみである。
`crypt()`は、暗号化された文字列へのポインタを戻り値として返却する。その一方で`crypt2()`は、暗号化された文字列へのポインタのアドレスを`dest`へセットする。
一般に、エラー原因の特定が容易な`crypt2()`の利用が推奨される。

## 戻り値

### crypt

成功した場合は暗号化された文字列へのポインタを返す。
エラーが発生した場合は NULL を返し、`errno`並びに`string_errno`にエラー原因を示す値を設定する。

### crypt2

成功した場合は 0 を返す。
エラーが発生した場合は負の整数を返し、`errno`並びに`string_errno`にエラー原因を示す値を設定する。

## エラー

### ESTRISEMPTY

`self`が管理する文字列が存在しない、またはサイズが 0 だった。

### EARGISNULPTR

`salt`が NULL だった。

### EINVAL (errno)

`salt`が間違ったフォーマットである。

### ENOSYS (errno)

`crypt()`関数が実装されていない。多分アメリカの輸出規制のために。

### EPERM (errno)

`/proc/sys/crypto/fips_enabled` が 0 でない値で、 DES などの弱い暗号タイプを利用しようとした。

## 例

以下に`/etc/passwd`を利用するサンプルを示す。
しかし近年のシステムの多くは、ハッシュ化されたパスワードを`/etc/shadow`に保存するため、これは実用的ではないだろう。

```c
#include <benly/typestring.h>
#include <stdio.h>
#include <string.h>
#include <pwd.h>    /* getpwnam() */

int login(STRING* s)
{
    struct passwd*  pw  = NULL;

    /* /etc/passwd から sasai のエントリを取得 */
    pw = getpwnam("sasai");

    /* 照会結果を返却 */
    return strcmp(s->c_str(s), pw->pw_passwd);
}

int main(void)
{
    FILE*   fp  = NULL;

    STRING* s   = new_string(NULL);

    /* パスワードは doraemon */
    s->assign(&s, "doraemon");
    /* 暗号化 */
    s->assign(&s, s->crypt(s, "salt"));
    /* 確認してみる */
    fputline(stdout, s);
    /* 模擬ログイン */
    if (!login(s))
        fprintf(stdout, "\nsuccess\n");
    else
        fprintf(stdout, "\nfailed\n");
    /* 解放 */
    s->release(s);

    return 0;
}
```

### 出力

```
saNRFPJt0jxlM
failed
```
