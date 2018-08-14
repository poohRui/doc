# KMP算法及其应用

## KMP算法介绍

> 给定一个字符串S和模式串P，希望找出P在S中出现的位置

像上面说的这种题目，最暴力的方法是使用朴素匹配，即每次发现不匹配时，只将模式串P向后移动一位，具体的若S="abcabcdex"，P="abcdex"，那么暴力匹配的过程为：

```
S： a b c a b c d e x
P： a b c d e x
      a b c d e x
        a b c d e x
          a b c d e x
            a b c d e x
```

当S中的第四位和P中的第四位不匹配时，此时已知S串的前四位（abca），P串的前四位（abcd）。若只将P串只向后移动一位，则需要重新比较P串的第一位和S串的第二位，但是这是没必要的（完全可以根据上一次比较的经验知道这两位不匹配），所以KMP算法就是尽可能大的让模式串P向后跨一步进行匹配，同时避免字符串S的下标向前回溯（固定S中遍历的下标不能变小）。

在上面的例子中，KMP算法的匹配过程如下：

```c++
S： a b c a b c d e x
P： a b c d e x
          a b c d e x
// 在第一次比较中，当S中的第四位和P中的第四位不匹配时，保持S中下标指向第四位不变，将P中下标变为指向第一位后重新比较。
```

现在唯一的变量是，当出现不匹配时，P中的下标需要如何变化，将这个变化规则存储在一个辅助数组中，一般称该数组为next数组。

## next数组

> next数组就是针对模式串P的每一个位置，得到当前对应子串的最长前后缀匹配长度，一般默认取next[0]=-1，不过也有些写法取next[0]=0。

举个例子，若P="abcabx"，对P的第四位来说，其对应子串为"abca"，该子串的最长前后缀匹配长度为1（第一个a，和最后一个a），对P的第五位来说，其对应子串为"abcab"，该子串的最长前后缀匹配长度为2（前两位ab，倒数两位ab）

```
j     0 1 2 3 4 5 6
P       a b c a b x
next -1 0 0 0 1 2 0
```

当出现误匹配时，P的下标变化为最后一位匹配字符对应的next的值。上面的例子中，当P中的第五位出现误匹配，则直接将P的下标变为2，继续匹配。这里next数组有P.size()+1位。

```c++
S： a b c a x a b c a b x
P： a b c a b x        // P中第五位出现误匹配，保持S下标为4不变，
          a b c a b x  // 将P的下标变为1，比较S的第五位和P的第二位
            a b c a b x
              a b c a b x
```

（由于下标一般从0开始计算，指向字符串的第五位，实际上下标为4）

然后问题就变成了如何求next数组，具体代码如下：

```C++ 
//如"abcabx"的next数组求解过程
/*****
i = 0,j = -1
i = 1,j = 0, next[1] = 0
i = 1,j = -1
i = 2, j = 0, next[2] = 0
i = 2, j = -1
i = 3, j= 0, next[3] = 0
i = 4,j = 1, next[4] = 1
i = 5, j= 2, next[5] = 2
i = 5,j = 0
i = 5,j = -1
i = 6,j = 0, next[6] = 0
*******/
// 始终记得next数组和字符串str错了一位。
void getNext(string str,int next[]){
    next[0] = -1;
    int len = (int)str.size();
    int i = 0,j=-1;
    while(i < len){
        if(j == -1 || str[i] == str[j]){
            i++;
            j++;
            next[i] = j; // 更新当前已匹配的next数组的值
        }
        else{
            // 向前找上一个以next[j]作为分界线的最长匹配前缀。
            j = next[j]; 
        }
    }
}
```

## nextval数组

> 上面的next数组虽然能解决问题但还是存在缺陷，提出改进方法，定义nextval数组。

举个例子，之前定义的next数组如下，当P中的第四位出现误匹配时，P的下标需要变为0重新比较，但是对P来说，它的第四位和第一位是一样的，都是'a'，这里没必要再重新比一次，所以nextval数组就是为了去除这种重复比较而被定义的。

```
   j     0 1 2 3 4 5 6
   P       a b c a b x
   next -1 0 0 0 1 2 0
nextval -1 0 0 -1 0 2 0
```

针对这个问题，改进使用nextval数组，对重复情况进行判断，

```C++
//如"abcabx"的nextval数组求解过程
/*****
i = 0,j = -1
i = 1,j = 0, next[1] = 0
i = 1,j = -1
i = 2, j = 0, next[2] = 0
i = 2, j = -1
i = 3, j= 0, next[3] = next[0] = -1
i = 4,j = 1, next[4] = next[1] = 0
i = 5, j= 2, next[5] = 2
i = 5,j = 0
i = 5,j = -1
i = 6,j = 0, next[6] = 0
*******/
void getNext(string str,int next[]){
    next[0] = -1;
    int len = (int)str.size();
    int i = 0,j=-1;
    while(i < len){
        if(j == -1 || str[i] == str[j]){
            i++;
            j++;
            if(str[i] == str[j]){
                next[i] = next[j];
            }
            else{
                next[i] = j;
            }
        }
        else{
            j = next[j];
        }
    }
}
```

## 完整代码

> 给定一个字符串S和模式串P，返回P在S中出现的位置

```c++
void getNext(string str,int next[]){
    // ...和上面一样
}
int KMP(string S,string P){
    int next[P.size()+1];
    getNext(P,next);
    int i = 0,j = 0;
    int len1 = S.size();
    int len2 = P.size();
    while(i < len1 && j < len2){
        if(j == -1 || S[i] == P[j]){
            i++;
            j++;
        }
        else{
            j = next[j]; // 修改P中的下标指向
        }
    }
    if(j == len2){
        return i-j; // 返回出现位置
    }
    else{
        return -1; // S中没有完整的P出现
    }
}
```





KMP的利用：求解从0开始的最长回文子串
