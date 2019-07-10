#include<stdio.h>
#include<algorithm>
#include<string.h>
#include<math.h>
using namespace std;
typedef long long ll;
ll sum[20010]; 
ll dp[300][300][2];
//解释在最下面 
int main()
{
	int T;
	scanf("%d",&T);
	while(T--)
	{
		int n;
		memset(dp,0,sizeof(dp));
		scanf("%d",&n);
		for(int i=1;i<=n;i++)
		{
			scanf("%lld",&sum[i]);
			sum[i]=sum[i]+sum[i-1];//前缀和 
		}
		memset(dp,0,sizeof(dp));
		for(int i=n;i>0;i--)
		{
			for(int j=200;j>0;j--)
			{
				if(i+j-1<=n)//如果只满足i+j-1<=n 那么 这一轮就不能取j+1个了 只能取j个
				{
					dp[i%250][j][0]= dp[(i+j)%250][j][1]+(sum[i+j-1]-sum[i-1]);
					dp[i%250][j][1]= dp[(i+j)%250][j][0]-(sum[i+j-1]-sum[i-1]);
					if(i+j<=n)
					{
						dp[i%250][j][0] = max (dp[i%250][j][0], dp[(i+j+1)%250][j+1][1]+(sum[i+j]-sum[i-1]));
						dp[i%250][j][1] = min (dp[i%250][j][1], dp[(i+j+1)%250][j+1][0]-(sum[i+j]-sum[i-1]));						
					}				
				} 
			}
		} 
		printf("%lld\n",dp[1][1][0]);
	}
}
/*
关于滚动数组：
二维数组举例
int i, j, d[100][100];
for(i = 1; i < 100; i++)
    for(j = 0; j < 100; j++)
        d[i][j] = d[i - 1][j] + d[i][j - 1];
上面的d[i][j]只依赖于d[i - 1][j], d[i][j - 1]; 
运用滚动数组
int i, j, d[2][100];
for(i = 1; i < 100; i++)
    for(j = 0; j < 100; j++)
        d[i % 2][j] = d[(i - 1) % 2][j] + d[i % 2][j - 1];
*/ 

/*
三维方式：
dp[i][j][k]表示从第k个人从第i个开始拿,上一轮对手拿走j个(所以这轮他拿j或者j+1个),
dp值表示两者之间的差值 
k只有 0 1两个值  0代表A取,1代表B取，注意是从后向前推 
A拿用加，B拿用减  因为dp表示的是两者之间的差值 
dp(i,j,0) = max (dp[i+j, j,1]+(sum[i+j-1]-sum[i-1]), dp[i+j+1,j+1,1]+(sum[i+j]-sum[i-1]));
dp(i,j,1) = min (dp[i+j, j,0]-(sum[i+j-1]-sum[i-1]), dp[i+j+1,j+1,0]-(sum[i+j]-sum[i-1])); 
sum 是前缀和 
显然直接写会暴内存
观察可知k最大取值是sqrt(2*n)=200 
1+2+3+4+5+6+.x=((1+x)x)/2<=n,x<=sqrt(2*n)
利用滚动数组 第一维也可以优化 (不过为什么用滚动数组可以确保 一定不会出错呢？)
滚动的大小比k最大值大即可，这里取256，%256可以用&255来优化。
因为第一步要不然拿1 要不然拿 2 所以 最后的结果是dp[1][1][0],表示A从位置1开始拿 这一轮可以拿一个或者两个  
结果可能会出现负值 这应该是正确的 
*/ 





 
