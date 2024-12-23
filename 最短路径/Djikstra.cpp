#include <iostream>
#include <vector>
#include <tuple>
#include <stack>

using namespace std;
#define MAX 9999999

int main() {
    int times=1;
    while (!cin.eof()){
        int n=-1;
        cin >> n;
        if(n==-1){break;}   //避免eof读取多余空行
        int** arcs = new int*[n];
        for(int i = 0; i < n; i++) {
            arcs[i] = new int[n];
        }
        for(int i = 0; i < n; i++) {        //输入邻接矩阵
            for(int j = 0; j < n; j++) {
                cin >> arcs[i][j];
            }
        }
        int start, end;
        cin >> start >> end;
        start--;
        end--;


        vector<tuple<int, bool,int>> dist;  //记录距离和是否已确定最短路径(权重，是否确定，前驱)
        for(int i = 0; i < n; i++) {
            dist.push_back(make_tuple(MAX, false, -1));
        }
        dist[start] = make_tuple(0, false, start);  //设为false方便循环

        vector<tuple<int,int,int>> edge;    //记录边(起点，终点，权重)
        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){
                if(arcs[i][j] != -1){
                    edge.push_back(make_tuple(i,j,arcs[i][j]));
                }
            }
        }
        int edge_num = edge.size();
        
        //Dijkstra算法
        int min_dis = MAX;
        int min_point;
        
        while(1){
            //判断是否跳出
            if(get<1>(dist[end]) == true) {break;}

            min_dis = MAX;
            for(int i = 0; i < n; i++) {    //寻找当前距离最小的点
                if(get<1>(dist[i]) == false && get<0>(dist[i]) < min_dis) {
                    min_dis = get<0>(dist[i]);
                    min_point = i;
                }
            }

            for(int i = 0; i < edge_num; i++){  //更新dist
                int temp=get<0>(dist[min_point])+get<2>(edge[i]);
                if(get<0>(edge[i])==min_point && temp < get<0>(dist[get<1>(edge[i])])){
                    dist[get<1>(edge[i])]=make_tuple(temp, false, min_point);
                }
            }
            int temp=get<2>(dist[min_point]);
            dist[min_point] = make_tuple(min_dis, true, temp);  //更新“是否确定”
        }

        cout<<"Case "<<times<<endl;
        int dis = get<0>(dist[end]);
        cout << "The least distance from "<<start+1<<"->"<<end+1<<" is "<<dis<<endl;

        stack<int> route;
        int temp = end;
        while(temp!=start){
            route.push(temp);
            temp = get<2>(dist[temp]);
        }
        
        route.push(start);
        cout <<"the path is "<<route.top()+1;
        route.pop();
        while(!route.empty()){
            cout <<"->"<< route.top()+1;
            route.pop();
        }
        cout << endl;
        times++;
    }

    return 0;
    
}