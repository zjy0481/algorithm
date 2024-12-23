#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
    string s1, s2;
    cin >> s1 >> s2;
    int m = s1.length();
    int n = s2.length();
    
    auto editDistance = [&](string string1, string string2) -> int {
        vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));   //方便后续操作，空出第0行和第0列

        for(int i=0;i<m;i++){       //如果一个字串长度为0，一个为i，显然编辑距离为i
            dp[i][0] = i;
        }

        for(int j=0;j<n;j++){       //同理
            dp[0][j] = j;
        }

        for(int i=1;i<=m;i++){       //dp
            for(int j=1;j<=n;j++){
                if(string1[i-1]==string2[j-1]){
                    dp[i][j] = dp[i-1][j-1];
                }else{
                    dp[i][j] = min(dp[i-1][j-1], min(dp[i][j-1], dp[i-1][j])) + 1;
                }
            }
        }

        return dp[m][n];
    };

    cout << editDistance(s1, s2) << endl;
    return 0;
}