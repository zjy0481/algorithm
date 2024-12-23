#include <iostream>
#include <functional>
#include <vector>
#include <algorithm>
#include <string>
#include <sstream>

using namespace std;

#define Eternal 1000000000

void ChangeString(vector<int>&vec,int a,int k,int b) {
    //一共画两个括号，如果括号中只有一个数就不用画，ret1、ret2分别对应两个括号是否需要画,若不用画则设置为已画完
    bool ret1_1=(k==a),ret1_2=(k==a),ret2_1=(b-k==1),ret2_2=(b-k==1);   //表示是否画完
    for(int i=0;i<vec.size();i++){      //-1代表左半括号，-2代表右半括号
        if(vec[i]==a&&!ret1_1){
            vec.insert(vec.begin()+i,-1);
            ret1_1=1;
        }
        if(vec[i]==k&&!ret1_2){
            vec.insert(vec.begin()+i+1,-2);
            ret1_2=1;
        }
        if(vec[i]==k&&!ret2_1){
            vec.insert(vec.begin()+i+2,-1);
            ret2_1=1;
        }
        if(vec[i]==b&&!ret2_2){
            vec.insert(vec.begin()+i+1,-2);
            ret2_2=1;
        }
        if(ret1_1&&ret1_2&&ret2_1&&ret2_2){break;}
    }
}


void FindBestResult(int left,int right,function<int(int,int)> func,vector<pair<int,int>>& vector_,vector<int>& result,int& total){
    if(left==right) return;
    if(left+1==right){
        total+=vector_[left].first*vector_[left].second*vector_[right].second;
        return;
    }

    int k=func(left,right);
    ChangeString(result,left,k,right);
    total+=vector_[left].first*vector_[k].second*vector_[right].second;

    FindBestResult(left,k,func,vector_,result,total);
    FindBestResult(k+1,right,func,vector_,result,total);
}

int main(){
    int n;
    cin>>n;
    int* nums_=new int[n+1];
    for(int i=0;i<n+1;i++){
        cin>>nums_[i];
    }
    vector<pair<int,int>> vector_;

    for(int i=0;i<n;i++){
        vector_.push_back(make_pair(nums_[i],nums_[i+1]));
    }

    function<int(int,int)> FindPartBest= [=](int left,int right) -> int  {
        int sum=Eternal,ans=left;
        for(int i=left;i<right;i++){
            // temp=vector_[left].first*vector_[i].second*vector_[right].second;
            // 直接比较vector_[i].second即可
            if(vector_[i].second<sum) {
                sum=vector_[i].second;
                ans=i;
            }
        }
        return ans;
    };

    vector<int> result;
    for(int i=0;i<n;i++){
        result.push_back(i);
    }

    int total_mul_=0;

    FindBestResult(0,n-1,FindPartBest,vector_,result,total_mul_);

    // for(int i=0;i<result.size();i++){
    //     cout<<result[i]<<endl;
    // }

    cout<<total_mul_<<"  ";

    for(auto iterator:result){
        if(iterator==-1){cout<<"(";}
        else if(iterator==-2){cout<<")";}
        else{
            cout<<"A"<<iterator+1;
        }
    }
    cout<<endl;


}