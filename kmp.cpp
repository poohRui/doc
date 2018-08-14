//
//  main.cpp
//  kmp
//
//  Created by yuruilee on 2018/8/14.
//  Copyright © 2018年 小芮神. All rights reserved.
//

#include <iostream>
#include <string>
using namespace std;

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

int KMP(string S,string P){
    int next[P.size()+1];
    getNext(P,next);
    int i = 0,j = 0;
    int len1 = (int)S.size();
    int len2 = (int)P.size();
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

int main() {
    string s = "abcabcabx";
    string p = "abcabx";
    cout<<KMP(s, p)<<endl;
}
