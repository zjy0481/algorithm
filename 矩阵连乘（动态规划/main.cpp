#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <functional>
#include <iomanip>

using namespace std;

#define Eternal 10000000

int main() {
    int times=0;
    vector<int> n_;
    vector<vector<int>> nums_;
    while(!cin.eof()){
        int temp;
        cin>>temp;
        n_.push_back(temp);
        nums_.push_back(vector<int>());
        for(int i=0;i<n_[times]+1;i++){
            cin>>temp;
            nums_[times].push_back(temp);
        }
        times++;
    }
    
    times--;        //最后一次读入是EOF，所以要减去

    for(int times_=1;times_<=times;times_++){
    int n=n_[times_-1];
    int* nums=new int[n+1],** sum=new int*[n],** sep=new int*[n];
    //sum[i][j]代表Ai乘到Aj的最小次数，sep[i][j]代表最优分割
    for(int i=0;i<n;i++){
        sum[i]=new int[n];
        sep[i]=new int[n];
    }
    for(int i=0;i<n+1;i++){
        nums[i]=nums_[times_-1][i];
    }
    //动态规划初始化
    for(int i=0;i<n;i++){sum[i][i]=0;}
    for(int i=0;i<n-1;i++){
        sum[i][i+1]=nums[i]*nums[i+1]*nums[i+2];
        sep[i][i+1]=i;
    }

    function<void(int,int)> func=[&](int left,int right)->void {
        for(int k=left;k<right;k++){
            int temp=sum[left][k]+sum[k+1][right]+nums[left]*nums[k+1]*nums[right+1];
            if(temp<sum[left][right]){
                sum[left][right]=temp;
                sep[left][right]=k;
            }
        }
    };

    for(int i=n-2;i>0;i--){             //最外层：初始化两层后，还需要迭代n-2次得到最终结果，本次迭代为n-i+1个矩阵相乘
        for(int j=0;j<i;j++){           //中间层：每次迭代需要计算i次，得到i个sum，j代表起始位置
            sum[j][j+n-i]=Eternal;      //初始化为无限大
            func(j,j+n-i);              //内层：每个sum有n-i种分割方式，k代表分割位置
        }
    }

    int total_cnt=sum[0][n-1];

    bool ret_left=0, ret_right=0;   //是否已经禁用最外层括号
    function<void(int,int)> print=[&](int left,int right)->void {
        if(left==right) cout<<"A"<<left+1;
        else{
            if(!left && !ret_left){ret_left=1;}
            else{cout<<"(";}

            print(left,sep[left][right]);
            print(sep[left][right]+1,right);

            if((right==n-1) && !ret_right){ret_right=1;}
            else{cout<<")";}
        }
    };
    cout<<"Case "<<times_<<endl;
    cout<<total_cnt<<" ";
    print(0,n-1);
    cout<<endl;

    }
    return 0;
}