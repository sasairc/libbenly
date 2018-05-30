## 名前

slice - STRING から任意の部分文字列を削除する

## 書式

```c
#include <benly/typestring.h>

int s->slice(STRING** self, char* const str);
```

## 説明

メンバ関数`slice()`は、`self`が管理する文字列のうち、文字列`str`とマッチするものを1つだけ削除する。

## 戻り値

成功した場合は 0 を返す。マッチしなかった場合でも同様である事に注意。
エラーが発生した場合は負の整数を返し、`string_errno`にエラー原因を示す値を設定する。

## エラー

### ESTRISEMPTY

`self`が管理する文字列が存在しない、またはサイズが 0 だった。

### EOUTOFRANGE

`str`のサイズが`self->size()`を超えていた。

## 例

```c
#include <benly/typestring.h>
#include <stdio.h>

int main(void)
{
    STRING* s   = new_string("ソーニャ　折部やすな　呉織あぎり");

    s->append(&s, "没キャラ");
    s->append(&s, "没キャラ");
    s->append(&s, "没キャラ");

    while (s->include(s, "没キャラ"))
        s->slice(&s, "没キャラ");

    fprintf(stdout, "%s\n",
            s->c_str(s));

    s->release(s);

    return 0;
}
```

### 出力

```
ソーニャ　折部やすな　呉織あぎり
```
