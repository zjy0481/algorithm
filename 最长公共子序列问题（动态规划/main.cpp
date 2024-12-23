#include <iostream>
#include <vector>
#include <functional>

using namespace std;

enum class Source{
    U,
    L,
    UL,
};

int main() {
    int times;
    cin >> times;
    for(int k=0;k<times;k++){

        //输入控制
        int nums1,nums2;
        cin >> nums1 >> nums2;
        vector<char> vec_1,vec_2;
        for(int i=0;i<nums1;i++){
            char temp;
            cin >> temp;
            vec_1.push_back(temp);
        }
        for(int i=0;i<nums2;i++){
            char temp;
            cin >> temp;
            vec_2.push_back(temp);
        }

        //动态规划
        int** LCS=new int* [nums1+1];          //LCS用于动态规划统计子序列长度
        for(int i=0;i<nums1+1;i++){
            LCS[i]=new int[nums2+1];
            for(int j=0;j<nums2+1;j++){
                LCS[i][j]=0;
            }
        }
        
        Source** source=new Source*[nums1];    //source用于记录子序列来源
        for(int i=0;i<nums1;i++){
            source[i]=new Source[nums2];
        }

        for(int i=1;i<nums1+1;i++){
            for(int j=1;j<nums2+1;j++){
                if(vec_1[i-1]==vec_2[j-1]){
                    LCS[i][j]=LCS[i-1][j-1]+1;
                    source[i-1][j-1]=Source::UL;
                }
                else if(LCS[i-1][j]>=LCS[i][j-1]){
                    LCS[i][j]=LCS[i-1][j];
                    source[i-1][j-1]=Source::U;
                }
                else{
                    LCS[i][j]=LCS[i][j-1];
                    source[i-1][j-1]=Source::L;
                }
            }
        }

        // for(int i=0;i<nums1;i++){
        //     for(int j=0;j<nums2;j++){
        //         cout<<LCS[i][j]<<" ";
        //     }
        //     cout<<endl;
        // }

        //输出控制
        cout<<"Case "<<k+1<<endl;
        cout<<LCS[nums1][nums2]<<" LCS(X,Y):";
        function<void(int i,int j)> print=[&](int i,int j){
            if(i==0||j==0){
                return;
            }
            if(source[i-1][j-1]==Source::UL){
                print(i-1,j-1);
                cout<<vec_1[i-1]<<" ";
            }
            if(source[i-1][j-1]==Source::U){
                print(i-1,j);
            }
            if(source[i-1][j-1]==Source::L){
                print(i,j-1);
            }
        };
        print(nums1,nums2);
        cout<<endl;
        
        //释放内存
        for(int i=0;i<nums1;i++){
            delete[] source[i];
        }
        delete[] source;
        for(int i=0;i<nums1+1;i++){
            delete[] LCS[i];
        }
        delete[] LCS;
    }
}