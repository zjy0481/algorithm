#include <iostream>
#include <cmath>
#include <functional>
#include <iomanip>
#include <string>
#include <sstream>

using namespace std;

int main(){
    string str; //用于输出格式控制
    vector<tuple<int,int,int>> v; //用于存储输入数据
    while(getline(cin,str)){
        istringstream ss(str);
        int k,x_,y_;
        ss >> k >> x_ >> y_;
        v.push_back(make_tuple(k,x_,y_));
    }

    int times=1; //times对应第几个case
    for(auto [k,x_,y_]:v) {
    int size,cnt=1; //2^k=size表示棋盘边长，x_和y_表示特殊标记位坐标，cnt为L型牌子计数器
    x_--;
    y_--;                   //坐标从0开始
    size=static_cast<int> (pow(2,k));
    int **chess_board = new int*[size];
    for(int i=0;i<size;i++){chess_board[i]=new int[size];}

    //初始化棋盘
    for(int i=0;i<size;i++){
        for(int j=0;j<size;j++){
            chess_board[i][j]=0;
        }
    }
    chess_board[x_][y_]=-1; //特殊标记位

    function<void(int,int,int,int,int)> func= [&](int size,int x_,int y_,int start_x,int start_y)->void{
        if(size==2){    //递归终止条件
            for(int i=start_x;i<start_x+size;i++){
                for(int j=start_y;j<start_y+size;j++){
                    if(chess_board[i][j]==0){chess_board[i][j]=cnt;}
                }
            }
            cnt++;
            return;
        }
        bool ret_x=(x_ < start_x+size/2), ret_y=(y_ < start_y+size/2);
        //ret_x是否在左半部分，ret_y是否在上半部分，11左上，10左下，01右上，00右下

        if(ret_x && ret_y){    //特定点在左上
            chess_board[start_x+size/2][start_y+size/2-1]=cnt;  //中偏右上
            chess_board[start_x+size/2-1][start_y+size/2]=cnt;  //中偏左下
            chess_board[start_x+size/2][start_y+size/2]=cnt;    //中偏右下
            cnt++;
            func(size/2,x_,y_,start_x,start_y);                                         //递归左上
            func(size/2,start_x+size/2,start_y+size/2-1,start_x+size/2,start_y);        //递归右上
            func(size/2,start_x+size/2-1,start_y+size/2,start_x,start_y+size/2);        //递归左下
            func(size/2,start_x+size/2,start_y+size/2,start_x+size/2,start_y+size/2);   //递归右下
        }

        if(ret_x && !ret_y){   //特定点在左下
            chess_board[start_x+size/2-1][start_y+size/2-1]=cnt;    //中偏左上
            chess_board[start_x+size/2][start_y+size/2-1]=cnt;      //中偏右上
            chess_board[start_x+size/2][start_y+size/2]=cnt;        //中偏右下
            cnt++;
            func(size/2,start_x+size/2-1,start_y+size/2-1,start_x,start_y);             //递归左上
            func(size/2,start_x+size/2,start_y+size/2-1,start_x+size/2,start_y);        //递归右上
            func(size/2,x_,y_,start_x,start_y+size/2);                                  //递归左下
            func(size/2,start_x+size/2,start_y+size/2,start_x+size/2,start_y+size/2);   //递归右下  
        }

        if(!ret_x && ret_y){   //特定点在右上
            chess_board[start_x+size/2-1][start_y+size/2-1]=cnt;    //中偏左上
            chess_board[start_x+size/2-1][start_y+size/2]=cnt;      //中偏左下
            chess_board[start_x+size/2][start_y+size/2]=cnt;        //中偏右下
            cnt++;
            func(size/2,start_x+size/2-1,start_y+size/2-1,start_x,start_y);             //递归左上
            func(size/2,x_,y_,start_x+size/2,start_y);                                  //递归右上
            func(size/2,start_x+size/2-1,start_y+size/2,start_x,start_y+size/2);        //递归左下
            func(size/2,start_x+size/2,start_y+size/2,start_x+size/2,start_y+size/2);   //递归右下
        }

        if(!ret_x && !ret_y){  //特定点在右下
            chess_board[start_x+size/2-1][start_y+size/2-1]=cnt;    //中偏左上
            chess_board[start_x+size/2][start_y+size/2-1]=cnt;      //中偏右上
            chess_board[start_x+size/2-1][start_y+size/2]=cnt;      //中偏左下
            cnt++;
            func(size/2,start_x+size/2-1,start_y+size/2-1,start_x,start_y);             //递归左上
            func(size/2,start_x+size/2,start_y+size/2-1,start_x+size/2,start_y);        //递归右上
            func(size/2,start_x+size/2-1,start_y+size/2,start_x,start_y+size/2);        //递归左下
            func(size/2,x_,y_,start_x+size/2,start_y+size/2);                           //递归右下
        }
    };

    func(size,x_,y_,0,0);

    //输出结果
    cout<<"Case "<<times<<": n="<<size<<endl;
    for(int i=0;i<size;i++){
        for(int j=0;j<size;j++) {
            if(chess_board[i][j]==-1) {cout<<"#"<<setw(3);}
            else if(j==size-1) {cout<<chess_board[i][j];}
            else {cout<<chess_board[i][j]<<setw(3);}
        }
        cout<<endl;
    }

    times++;
    }

    return 0;
}