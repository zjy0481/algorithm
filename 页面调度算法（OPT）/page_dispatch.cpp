#include <iostream>
#include <vector>

using namespace std;

#define internal_storage int    //内存物理块号，-1表示不在内存中，0、1、2分别对应三个块

class table_entry {
public:
    table_entry(): page_number(0), position(-1), next_visit(-1), time(-1), last_visit(-1), now_visit(false) {}
    table_entry(int n, internal_storage p){
        page_number = n;
        position = p;
    }

    int page_number;    //页号
    internal_storage position;  //对应的物理块号
    ///以下用于方便算法设计
    int next_visit; //距离下次访问该页的时间，opt
    int time;  //进入内存的时间，fifo
    int last_visit; //距离上次访问该页的时间，lru
    bool now_visit; //当前该页是否在被访问，clock
    friend class page_table;
    friend class TLB;
};

class page_table {     //页表，长度固定为3
public:
    vector<table_entry> pages;
    int now_cnt;
    void initialize(){
        now_cnt = 0;
        for (int i = 0; i < 3; i++) {
            pages.push_back(table_entry(-1, -1));
        }
    }
};

int main() {
    system("chcp 65001");
    vector<int> progress({4, 3, 2, 1, 4 ,3, 5, 4, 3, 2});
    page_table page_table_;
    page_table_.initialize();

    auto OPT=[&](){
        int page_table_hit_cnt=0;
        int total_cnt=0;
        while(!progress.empty()){
            //OPT函数所需的前处理
            int next_times[6]={-1,-1,-1,-1,-1,-1};
            for(int i=1;i<6;i++){
                for(int j=0;j<progress.size();j++){
                    if(i==progress[j]){
                        next_times[i]=j;
                        break;
                    }
                }
                if(next_times[i]==-1){next_times[i]=INT_MAX;}
            }
            int page_number_=progress[0];

            //分三种情况：页面不存在、页表命中、需要调入或替换
            cout << "请求访问页"<<page_number_<<endl;
            total_cnt++;
            if(page_number_>5){
                cout<<"页面请求越界！"<<endl;
                progress.erase(progress.begin());
                continue;
            }

            if(page_table_.pages[0].page_number==page_number_||page_table_.pages[1].page_number==page_number_||page_table_.pages[2].page_number==page_number_){
                page_table_hit_cnt++;
                cout << "页表命中" << endl;
                progress.erase(progress.begin());
            }
            else{
                cout<<"未命中，需要调入或替换页面"<<endl;
                if(page_table_.now_cnt<3){ //直接调入
                    int internal_position;
                    //修改页表
                    for(int i=0;i<3;i++){
                        if(page_table_.pages[i].page_number==-1){
                            page_table_.pages[i].page_number=page_number_;
                            page_table_.pages[i].position=i;
                            internal_position=i;
                            break;
                        }
                    }
                    cout<<"页面调入完成"<<endl;
                    // page_table_hit_cnt++;
                    // hit_cnt++;
                    // total_cnt++;
                    page_table_.now_cnt++;
                }
                else{       //需要替换，这里使用OPT算法
                    //找到最大的
                    int max_time=-1,flag;
                    for(int i=1;i<=5;i++){
                        if(next_times[i]>max_time && i!=page_number_){
                            max_time=progress[i];
                            flag=i;
                        }
                    }
                    
                    //更新页表
                    for(int i=0;i<3;i++){
                        if(page_table_.pages[i].page_number==flag){
                            page_table_.pages[i].page_number=page_number_;
                            break;
                        }
                    }
                    cout<<"页面替换完成"<<endl;
                    cout<<"使用页面"<<page_number_<<"替换了"<<flag<<endl;
                    // page_table_hit_cnt++;
                    // hit_cnt++;
                    // total_cnt++;
                }
                progress.erase(progress.begin());
            }
        }
        cout<<page_table_hit_cnt<<"\t"<<total_cnt<<endl;
        cout<<"命中率为："<<static_cast<double>(page_table_hit_cnt)/static_cast<double>(total_cnt)<<endl;
    };

    OPT();

    system("pause");
    return 0;

}