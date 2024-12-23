#include <iostream>
#include <vector>
#include <algorithm>
#include <tuple>

using namespace std;

enum Choice {
    HEADS,
    TAILS,
    NONE
};

int main() {
    int n;
    cin >> n;
    vector<int> coins(n, 0);
    for (int i=0;i<n;i++){
        cin >> coins[i];
    }

    vector<vector<tuple<int,Choice>>> dp(n,vector<tuple<int,Choice>>(n,make_tuple(0,NONE)));

    auto func_dp=[&](vector<int>& coins_)      //dp函数，返回取头部还是尾部，传入当前硬币序列
    ->Choice{
        int n_=coins_.size();
        for(int len=0;len<n_;len++){
            for(int i=0;i<n_-len;i++){
                int j=i+len;
                if(len==0){         //只有一个硬币，头尾无所谓
                    dp[i][j]=make_tuple(coins_[i],HEADS);
                }
                else if(len==1){    //有两个硬币，选大的
                    if(coins_[i]>coins_[j]){
                        dp[i][j]=make_tuple(coins_[i]+coins_[j],HEADS);
                    }
                    else{
                        dp[i][j]=make_tuple(coins_[i]+coins_[j],TAILS);
                    }
                }

                else{
                    int temp_head=max(coins_[i]+get<0>(dp[i+1][j-1]),coins_[i]+get<0>(dp[i+2][j]));
                    int temp_tail=max(coins_[j]+get<0>(dp[i+1][j-1]),coins_[j]+get<0>(dp[i][j-2]));
                    if(temp_head>temp_tail){
                        dp[i][j]=make_tuple(temp_head,HEADS);
                    }
                    else{
                        dp[i][j]=make_tuple(temp_tail,TAILS);
                    }
                }
            }
        }
        return get<1>(dp[0][n_-1]);
    };

    //开始模拟双方游戏，每次通过dp计算最优解
    Choice player1_choice, player2_choice;
    int player1_score=0, player2_score=0;
    while(coins.size()>1){      //每轮取走两个硬币，硬币数量至少大于1
        player1_choice=func_dp(coins);
        if(player1_choice==HEADS){
            player1_score+=coins[0];
            coins.erase(coins.begin());
        }
        else{
            player1_score+=coins[coins.size()-1];
            coins.erase(coins.end()-1);
        }
        player2_choice=func_dp(coins);
        if(player2_choice==HEADS){
            player2_score+=coins[0];
            coins.erase(coins.begin());
        }
        else{
            player2_score+=coins[coins.size()-1];
            coins.erase(coins.end()-1);
        }
    }
    if(coins.size()==1){
        player1_score+=coins[0];
    }

    //判定胜负
    if(player1_score>player2_score){
        cout<<"先手胜  得分"<<player1_score<<endl;
    }
    else if(player1_score<player2_score){
        cout<<"后手胜  得分"<<player2_score<<endl;
    }
    else{
        cout<<"平局"<<endl;
    }
}