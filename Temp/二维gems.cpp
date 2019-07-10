#include<stdio.h>
#include<algorithm>
#include<string.h>
#include<math.h>
using namespace std;
typedef long long ll;
#define INF 0x3f3f3f3f
int sum[20010]; 
int dp[20002][202];
//解释在后面 
int main()
{
	int T;
	scanf("%d",&T);
	while(T--)
	{
		int n;
		memset(dp,0,sizeof(dp));
		scanf("%d",&n);
//		int ret=-199999999;
//		for(int i=0;i<20010;i++)
//			for(int j=0;j<202;j++)
//				dp[i][j]=ret;
		for(int i=1;i<=n;i++)
		{
			scanf("%d",&sum[i]);
			sum[i]=sum[i]+sum[i-1];//前缀和 
		}
		memset(dp,0,sizeof(dp));
		for(int i=n;i>0;i--)
		{
			for(int j=min(200,n-i+1);j>0;j--)
			{
				dp[i][j]=sum[i+j-1]-sum[i-1];
				int t=dp[i+j][j];
				if(i+j+j+1-1<=n) t=max(t,dp[i+j][j+1]);
				dp[i][j]-=t;
				if(i<=1&&j<=2) //必须要在这里随时比较 
				{
					if(dp[i][j]>ret) ret=dp[i][j];
				} 
			}
		} 
		printf("%d\n",ret);
	}
}
// 二维开dp[20000][200]能过，但是longlong不能过 必须是int 
/*
一个想要差值绝对值尽可能大，一个想要尽可能的小，等价于两人都想最大化自己与另一个人差值，
因为A-B>0 B-A<0 正数增大是增大，负数向0靠拢也是增大 
dp[i][j]表示当前从位置i取数,取j个,产生的最大差值；
转移方程为dp[i][j]=sum[i+j-1]-sum[i-1]-max(dp[i+j][j],dp[i+j][j+1])；
因为不管当前i怎么选，后面的人一定会尽量让这个差值变大，因此我们就在后面可能的情形里找一个最大的即可
然后两者相减就是目前的差值 
题解中所说的 "考虑后者的情况，显然是取max，即最坏情况；"后者也就是指的后面那个人 
最后取dp[1][1]和dp[1][2]的最大值即可； 
关于为什么要随时都要比较结果值是因为: 比如1 -1这个样例应该输出-1，此时dp[1][2]是没有定义的 
max(dp[1][1],dp[1][2])的结果是0，解决方案可以将dp初始化为-INF 实验成功  

*/ 
