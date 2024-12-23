#include<iostream>  
#include<cstring>  
  
using namespace std;  
  
const int M = 300;  
const int N = 700;  
int A[N+1]; 
int B[M+1][N+1];
int L[M+1], R[M+1];

int MaxMSubSum(int m, int n);//动态规划：二维数组
void SearchSubQue(int m, int n, int B[M+1][N+1]);//利用二维数组B[][]查找第i段连续子序列的左右边界   
void PrintSubQue(int m); //输出m个子段  
  
int main()  
{  
	int m, n;
	cin >> m >> n;
	for (int i=1; i<=n; i++)
    	cin >> A[i];
    
    int maxSum;
    memset(L, 0, sizeof(L));
    memset(R, 0, sizeof(R));
    maxSum = MaxMSubSum(m, n);  
    cout << maxSum << endl; 
    SearchSubQue(m, n, B); //查找第i段连续子序列的左右边界 
    PrintSubQue(m);  //输出m个子段 
    
    return 0;  
}
int MaxMSubSum(int m, int n)//动态规划：二维数组    
{    
	int maxSum;
	
    for (int i=1; i<=m; i++)  
    {  
		B[i][i] = B[i-1][i-1] + A[i];
        for (int j=i+1; j<=n; j++)  
        {  
			maxSum = B[i][j-1]; //默认A[j]和A[j-1]同属于第i个子段 
            for (int k=i-1; k<j; k++)  //看看是不是A[j]独占第i个子段更好 
            {  
                if (maxSum < B[i-1][k])  
					maxSum = B[i-1][k];  
            }
            B[i][j] = maxSum + A[j]; 
        }  
    }  
    //遍历B[m][j]，找到最大值 
    maxSum = B[m][n];
    for (int j=m; j<n; j++)
    {
		if (maxSum < B[m][j])  
			maxSum = B[m][j];
	}
       
    return maxSum;    
}
void SearchSubQue(int m, int n, int B_[M+1][N+1])//利用二维数组B[][]查找第i段连续子序列的左右边界   
{  
    int maxSum;  
    int left, right;  
      
    for (int i=m,j=n; i>0; i--,j=left)  
    {  
        maxSum = B_[i][j];   
        right = j;  
        for (int k=j; k>=i; k--) //查找第i段连续子序列和的最大值和对应右边界  
        {  
            if (B_[i][k] > maxSum)  
            {  
                maxSum = B_[i][k];  
                right = k;  
            }  
        }   
        left = right; //查找第i段连续子序列的左边界  
        while (left>=i && B_[i][left]>0 && B_[i][left]>B_[i-1][left])  
        {  
            left--;  
        }   
          
        L[i] = left+1;  
        R[i] = right;   
    }  
}
 
void PrintSubQue(int m) //输出m个子段  
{
	for (int i=1; i<=m; i++) //输出m段子序列   
    {  
        cout << i << " : " << "("; 
		int s = A[R[i]]; 
        for (int j=L[i]; j<R[i]; j++)  
        {  
            cout << A[j] << ", "; 
			s += A[j]; 
        }  
        cout << A[R[i]] << ") = " << s << endl;   
    }  
}