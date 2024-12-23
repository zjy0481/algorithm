#include <iostream>
#include <vector>
#include <functional>

using namespace std;

int main() {
    int times=1;
    while(!cin.eof()){
        int n=-1;  //货物数量
        cin >> n;
        if(n==-1) {break;}  //eof会多读入一次空行，直接跳出循环     
        vector<int> weight(n),value(n); //将问题视作01背包问题，weight为重量；value为价值，在该情境下等于重量
        int total_weight=0;
        for(int i=0;i<n;i++){
            cin >> weight[i];
            value[i]=weight[i];
            total_weight+=weight[i];
        }
        int ship1,ship2;        //船1和船2的载重量
        cin >> ship1 >> ship2;
        cout<<"Case "<<times<<endl;
        if(ship1+ship2<total_weight){
            cout << "No" << endl;
        }

        vector<int> result1(n),result2(n),now_load(n);  //result存放ship的最优解，now_load存放当前解
        int max_value1=0,max_value2=0;          //ship最优解的总价值

        //dfs函数，i为当前深度（或称之为第几个货物），weight_为当前船的已经负载的货物量，value_为当前船的已经负载的货物量，rest_value为剩余货物的总重量，ship为船的标号(1为船1,0为船2)，now_load为当前解
        function<void(int,int,int,int,int,vector<int>)> dfs=[&](int i,int weight_,int value_,int rest_value,bool ship_num,vector<int> now_load){
            int ship=ship_num ? ship1 : ship2;
            vector<int>& result=ship_num ? result1 : result2;   //要留作记录所以是引用
            int& max_value=ship_num ? max_value1 : max_value2;  //要留作记录所以是引用
            if(i==n){       //抵达叶子结点
                if(weight_<=ship && value_>max_value){
                    max_value=value_;
                    for(int j=0;j<n;j++){
                        result[j]=now_load[j];
                    }
                }
            }
            else{       //未抵达叶子结点，继续深入
                if(weight_+weight[i]<=ship && value_+rest_value>max_value){    //左孩子，如果已经超重或不可能超过最优解则直接舍弃
                    now_load[i]=1;
                    dfs(i+1,weight_+weight[i],value_+value[i],rest_value-value[i],ship_num,now_load);
                }
                if(value_+rest_value-value[i]>max_value){     //右孩子，如果不可能超过最优解则直接舍弃
                    now_load[i]=0;
                    dfs(i+1,weight_,value_,rest_value-value[i],ship_num,now_load);
                }
            }
        };

        dfs(0,0,0,total_weight,1,now_load);     //推导船1的最优解

        //将对应货物全部删去，再推导船2的最优解
        vector<int> loaded;
        int total_weight_2=total_weight;
        for(int i=0;i<n;i++){
            if(result1[i]==1){
                loaded.push_back(i);
                total_weight_2-=weight[i];
            }
        }
        n-=loaded.size();
        for(int i=0;i<loaded.size();i++){
            weight.erase(weight.begin()+loaded[i]-i);
            value.erase(value.begin()+loaded[i]-i);
        }

        dfs(0,0,0,total_weight_2,0,now_load);     //推导船2的最优解

        //输出结果
        if(max_value1+max_value2==total_weight){
            cout <<max_value1<<" ";
            for(int i:result1){
                cout<<i;
            }
            cout << endl;
        }
        else{
            cout<<"NO"<<endl;
        }

        times++;
    }
}