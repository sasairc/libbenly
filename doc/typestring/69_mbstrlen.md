## 名前

mbstrlen - 実文字の長さを計算する (おまけ)

## 書式

```c
#include <benly/typestring.h>

size_t s->mbstrlen(char* const str);
```

## 説明

メンバ関数`mbstrlen()`は、名前の通りである。

## 戻り値

成功した場合は、`str`の実文字数を返す。
エラーが発生した場合は 0 を返し、`string_errno`にエラー原因を示す値を設定する。

### EINVALIDCHAR

不正なマルチバイト列を検出した。

## 例

```c
#include <benly/typestring.h>
#include <stdio.h>

int main(void)
{
    STRING*     s   = new_string(NULL);

    fprintf(stdout, "%zu\n",
            s->mbstrlen("こんにちは"));

    s->release(s);

    return 0;
}
```

### 出力

```
5
```

## 与太話

もともと、本関数はライブラリ内部で使用する為に書かれたものです。引数を見てわかる通り、 STRING を操作する関数ではないため、メンバ関数へ含めるべきではありません。
しかし`mbstrlen()`という *ありがちな* 名前である以上、単純にヘッダに書いた場合他のライブラリ (シンボル) とコンフリクトしてしまう。メンバ関数としての実装はその為。
実際、`benly/string.h`には同名同機能の関数の宣言が存在します。なら`mbstrlen()`はそちらを使えば良いと思うでしょう？御もっともですが、ライブラリを利用する上でちと面倒なのです。

なぜなら

```
% gcc -lbenly_typestring -lbenly_string main.c
```

と明示的に`libbenly_string.so`を指定しなければならなくなるから。ライブラリとライブラリの依存は極力排除するに限ります。
