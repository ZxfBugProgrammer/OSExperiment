#include<stdio.h>
#include<algorithm>
#include<string.h>
#include<math.h>
using namespace std;
typedef long long ll;
ll sum[20010]; 
ll dp[300][300][2];
//������������ 
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
			sum[i]=sum[i]+sum[i-1];//ǰ׺�� 
		}
		memset(dp,0,sizeof(dp));
		for(int i=n;i>0;i--)
		{
			for(int j=200;j>0;j--)
			{
				if(i+j-1<=n)//���ֻ����i+j-1<=n ��ô ��һ�־Ͳ���ȡj+1���� ֻ��ȡj��
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
���ڹ������飺
��ά�������
int i, j, d[100][100];
for(i = 1; i < 100; i++)
    for(j = 0; j < 100; j++)
        d[i][j] = d[i - 1][j] + d[i][j - 1];
�����d[i][j]ֻ������d[i - 1][j], d[i][j - 1]; 
���ù�������
int i, j, d[2][100];
for(i = 1; i < 100; i++)
    for(j = 0; j < 100; j++)
        d[i % 2][j] = d[(i - 1) % 2][j] + d[i % 2][j - 1];
*/ 

/*
��ά��ʽ��
dp[i][j][k]��ʾ�ӵ�k���˴ӵ�i����ʼ��,��һ�ֶ�������j��(������������j����j+1��),
dpֵ��ʾ����֮��Ĳ�ֵ 
kֻ�� 0 1����ֵ  0����Aȡ,1����Bȡ��ע���ǴӺ���ǰ�� 
A���üӣ�B���ü�  ��Ϊdp��ʾ��������֮��Ĳ�ֵ 
dp(i,j,0) = max (dp[i+j, j,1]+(sum[i+j-1]-sum[i-1]), dp[i+j+1,j+1,1]+(sum[i+j]-sum[i-1]));
dp(i,j,1) = min (dp[i+j, j,0]-(sum[i+j-1]-sum[i-1]), dp[i+j+1,j+1,0]-(sum[i+j]-sum[i-1])); 
sum ��ǰ׺�� 
��Ȼֱ��д�ᱩ�ڴ�
�۲��֪k���ȡֵ��sqrt(2*n)=200 
1+2+3+4+5+6+.x=((1+x)x)/2<=n,x<=sqrt(2*n)
���ù������� ��һάҲ�����Ż� (����Ϊʲô�ù����������ȷ�� һ����������أ�)
�����Ĵ�С��k���ֵ�󼴿ɣ�����ȡ256��%256������&255���Ż���
��Ϊ��һ��Ҫ��Ȼ��1 Ҫ��Ȼ�� 2 ���� ���Ľ����dp[1][1][0],��ʾA��λ��1��ʼ�� ��һ�ֿ�����һ����������  
������ܻ���ָ�ֵ ��Ӧ������ȷ�� 
*/ 





 
