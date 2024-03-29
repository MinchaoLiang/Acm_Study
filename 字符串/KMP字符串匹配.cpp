#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;

const int maxlen=100;
char str[maxlen],ptr[maxlen];//父串str和子串ptr
int nextt[maxlen];

void getnext()//获取next数组
{
	int i,n,k;
	n=strlen(ptr);
	i = 0;
	k = nextt[i] = -1;
	while(i<n) {
		if(k==-1 || ptr[k]==ptr[i]) {
			i++;k++;
			nextt[i] = k;
		} else {
			k = nextt[k];
		}
		//nextt表示的是“0～i-1”中，“最长前后缀”长度
	}
}

int kmp(char *a,char *b)//匹配ab两串，a为父串
{
	int i=0,j=0;
	int len1=strlen(a);
	int len2=strlen(b);
	getnext();
	while(i<len1&&j<len2) {
		if(j==-1 || a[i]==b[j]) {
			i++;j++;
		} else {
			j=nextt[j];//到前一个匹配点
		}
	}
	if(j>=len2) {
		return i-j;
	} else {
		return -1;
	}
}

int main(){
	while( scanf( "%s%s", str, ptr)) {
		int ans = kmp(str,ptr);
		if(ans>=0) {
			printf( "%d\n", kmp( str,ptr ));
		} else {
			printf("Not find\n");
		}
	}
	return 0;
}
