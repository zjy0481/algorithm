#include <iostream>
#include <vector>
#include <algorithm>
#include <tuple>

using namespace std;

int main() {
    int times=1;
    while(!cin.eof()){
        int cnt=-1;
        cin >> cnt;
        if(cnt==-1){
            break;
        }

        int total_weight=0;
        vector<int> weights(cnt,0);
        for (int i = 0; i < cnt; i++) {
            cin >> weights[i];
            total_weight+=weights[i];
        }
        sort(weights.begin(), weights.end());   //从小到大排序，便于后续dp

        int ship1,ship2;
        cin >> ship1 >> ship2;
        if(ship1<ship2){        //优先装大船
            swap(ship1,ship2);
        }

        cout<<"Case "<<times<<endl;
        if(total_weight>ship1+ship2){
            cout<<"NO"<<endl;
        }

        auto dp_shipload=[&](int ship)->tuple<int,vector<int>>{
            vector<vector<tuple<int,vector<int>>>> dp(cnt+1,vector<tuple<int,vector<int>>>(ship+1,tuple<int,vector<int>>(0,vector<int>())));
            //dp矩阵，i表示货物数量，j表示船容量，tuple中int对应最大承载量，vector<int>对应货物下标
            for(int i=0;i<ship+1;i++){
                get<0>(dp[0][i])=0;     //货物数量为0时，最大承载量为0
            }
            for(int i=1;i<cnt+1;i++){
                get<0>(dp[i][0])=0;     //船容量为0时，最大承载量为0
            }

            for(int i=1;i<=cnt;i++){
                for(int j=1;j<=ship;j++){
                    if(weights[i-1]>j){
                        dp[i][j]=dp[i-1][j];
                    }
                    else{
                        int temp1=weights[i-1],temp2=get<0>(dp[i-1][j-weights[i-1]])+weights[i-1];
                        if(max(temp1,temp2)==get<0>(dp[i-1][j])){
                            dp[i][j]=dp[i-1][j];
                            continue;
                        }
                        if(temp1>=temp2){
                            dp[i][j]=make_tuple(temp1,vector<int>({i}));
                        }
                        else{
                            dp[i][j]=make_tuple(temp2,get<1>(dp[i-1][j-weights[i-1]]));
                            get<1>(dp[i][j]).push_back(i);
                        }
                    }
                }
            }

            return dp[cnt][ship];
        };

        auto dp1=dp_shipload(ship1);

        vector<int> temp(get<1>(dp1).size(),0);
        for(int i=0;i<get<1>(dp1).size();i++){
            temp[i]=get<1>(dp1)[i];
        }
        while(1){       //视作货物已被装入ship1，删去weights中对应货物
            if(temp.empty()){
                break;
            }
            else{
                weights.erase(weights.begin()+temp[0]-1);
                temp.erase(temp.begin());
            }
        }
        auto dp2=dp_shipload(ship2);
        if(get<0>(dp1)+get<0>(dp2)==total_weight){
            cout<<get<0>(dp1)<<" ";
            vector<int> temp(cnt,0);
            for(int i:get<1>(dp1)){
                temp[i-1]=1;
            }
            for(int i:temp){
                cout<<i;
            }
            cout<<endl;
        }
        else{
            cout<<"NO"<<endl;
        }

        times++;
    }
}