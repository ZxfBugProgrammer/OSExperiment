#include<stdio.h>
#include<algorithm>
#include<string.h>
#include<math.h>
using namespace std;
typedef long long ll;
#define INF 0x3f3f3f3f
int sum[20010]; 
int dp[20002][202];
//�����ں��� 
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
			sum[i]=sum[i]+sum[i-1];//ǰ׺�� 
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
				if(i<=1&&j<=2) //����Ҫ��������ʱ�Ƚ� 
				{
					if(dp[i][j]>ret) ret=dp[i][j];
				} 
			}
		} 
		printf("%d\n",ret);
	}
}
// ��ά��dp[20000][200]�ܹ�������longlong���ܹ� ������int 
/*
һ����Ҫ��ֵ����ֵ�����ܴ�һ����Ҫ�����ܵ�С���ȼ������˶�������Լ�����һ���˲�ֵ��
��ΪA-B>0 B-A<0 �������������󣬸�����0��£Ҳ������ 
dp[i][j]��ʾ��ǰ��λ��iȡ��,ȡj��,����������ֵ��
ת�Ʒ���Ϊdp[i][j]=sum[i+j-1]-sum[i-1]-max(dp[i+j][j],dp[i+j][j+1])��
��Ϊ���ܵ�ǰi��ôѡ���������һ���ᾡ���������ֵ���������Ǿ��ں�����ܵ���������һ�����ļ���
Ȼ�������������Ŀǰ�Ĳ�ֵ 
�������˵�� "���Ǻ��ߵ��������Ȼ��ȡmax����������"����Ҳ����ָ�ĺ����Ǹ��� 
���ȡdp[1][1]��dp[1][2]�����ֵ���ɣ� 
����ΪʲôҪ��ʱ��Ҫ�ȽϽ��ֵ����Ϊ: ����1 -1�������Ӧ�����-1����ʱdp[1][2]��û�ж���� 
max(dp[1][1],dp[1][2])�Ľ����0������������Խ�dp��ʼ��Ϊ-INF ʵ��ɹ�  

*/ 
