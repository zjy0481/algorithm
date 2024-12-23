#include <iostream>
#include <vector>
#include <tuple>
#include <queue>

using namespace std;

int main() {
    vector<string> start,end;
    int times=0;
    while(!cin.eof()){
        string s1,s2;
        cin>>s1>>s2;
        start.push_back(s1);
        end.push_back(s2);
        times++;
    }
    times--;    //因为多读了一个空行
    
    //初始化起点和终点
    vector<int> start_y(times,0),start_x(times,0),end_y(times,0),end_x(times,0);
    for(int i=0;i<times;i++){
        start_y[i] = start[i][0]-'a'+1;   //列
        start_x[i] = start[i][1]-'0';     //行
        end_y[i] = end[i][0]-'a'+1;
        end_x[i] = end[i][1]-'0';
    }

    //从起点到终点进行BFS
    //因为是计算最短步数，所以显然BFS效率更高

    for(int i=0;i<times;i++){
        queue<tuple<int,int,int>> pos;  //x，y，步数
        pos.push({start_x[i],start_y[i],0});

        auto jump = [&](tuple<int,int,int> point)->bool{    //传入一个点，向8个方向jump，如果jump后不是终点则加入队列，是则返回true
            int x=get<0>(point),y=get<1>(point),step=get<2>(point)+1;
            if(end_x[i]!=x+2||end_y[i]!=y-1){
                pos.push({x+2,y-1,step});
            }
            else{return true;}

            if(end_x[i]!=x+2||end_y[i]!=y+1){
                pos.push({x+2,y+1,step});
            }
            else{return true;}

            if(end_x[i]!=x+1||end_y[i]!=y-2){
                pos.push({x+1,y-2,step});
            }
            else{return true;}

            if(end_x[i]!=x+1||end_y[i]!=y+2){
                pos.push({x+1,y+2,step});
            }
            else{return true;}

            if(end_x[i]!=x-1||end_y[i]!=y-2){
                pos.push({x-1,y-2,step});
            }
            else{return true;}

            if(end_x[i]!=x-1||end_y[i]!=y+2){
                pos.push({x-1,y+2,step});
            }
            else{return true;}

            if(end_x[i]!=x-2||end_y[i]!=y-1){
                pos.push({x-2,y-1,step});
            }
            else{return true;}

            if(end_x[i]!=x-2||end_y[i]!=y+1){
                pos.push({x-2,y+1,step});
            }
            else{return true;}

            return false;
        };

        while(1){
            if(jump(pos.front())){break;}
            pos.pop();
        }
        int step_min=get<2>(pos.front())+1;
        cout<<start[i]<<"==>"<<end[i]<<": "<<step_min<<" moves"<<endl;
    }
}