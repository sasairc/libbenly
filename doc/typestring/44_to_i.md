## 名前

to_i - STRING を int に変換する

## 書式

```c
#include <benly/typestring.h>

int s->to_i(STRING* self, int base);
```

## 説明

メンバ関数`to_i()`は、`self`が管理する文字列の有効な範囲を、`base`を基数として int に変換する。
`base`に対して 0 を指定した場合は 10 と等価となる。また、任意の基数は 2 から 36 までの値でなければならない。

## 戻り値

成功した場合は、変換後の値を返す。
オーバーフローにより失敗した場合は定数 LONG_MAX を返し、アンダーフローの場合は定数 LONG_MIN を返す。
また、失敗時は`errno`にエラー原因を示す値を設定する。

## エラー

### EINVAL (errno)

基数`base`の値が無効だった。

### ERANGE (errno)

アンダーフローまたはオーバーフローが発生した。

## 例

```c
#include <benly/typestring.h>
#include <stdio.h>

int main(void)
{
    STRING* s   = new_string("1024ですよ");

    fprintf(stdout, "%d\n",
            s->to_i(s, 0));

    s->assign(&s, "0xFFかもね");
    fprintf(stdout, "%d\n",
            s->to_i(s, 16));

    s->release(s);

    return 0;
}
```

### 出力

```
1024
255
```
