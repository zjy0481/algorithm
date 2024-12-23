#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

int cur_pid=0;

//生成随机数的函数
int rand_num(int min,int max){
    return rand()%(max-min+1)+min;
}

enum stat_{ //进程状态
    R,      //RUN
    W,      //WAIT
    F       //FINISH
};

struct PCB{ //进程控制块
    PCB():pid(cur_pid++),plink(nullptr),ppri(rand_num(11,25 )),cur_cost(0),pcost(rand_num(4,10)),pstat(W){}
    int pid;
    PCB* plink;
    int ppri;
    int cur_cost;
    int pcost;
    stat_ pstat;
};

void Show(vector<PCB> &PCBs,bool show_title){
    if(show_title){
        cout<<"当前进程状态："<<endl;
        cout<<setw(20)<<"进程号"<<setw(20)<<"优先级"<<setw(20)<<"当前运行时间"<<setw(20)<<"所需时间片数"<<setw(15)<<"状态"<<endl;
    }
    for(auto &p:PCBs){
    cout<<setw(15)<<p.pid<<setw(15)<<p.ppri<<setw(15)<<p.cur_cost<<setw(15)<<p.pcost;
    switch(p.pstat){
        case R:
            cout<<setw(15)<<"RUN"<<endl;
            break;
        case W:
            cout<<setw(15)<<"WAIT"<<endl;
            break;
        case F:
            cout<<setw(15)<<"FINISH"<<endl;
            break;
        }
    }
    
    
}

int pri_schedule(vector<PCB> &PCBs){   //优先数调度算法
    auto sort_= [&](){
        //按优先级降序排序
        sort(PCBs.begin(),PCBs.end(),[](PCB &a,PCB &b){return a.ppri>b.ppri;});
        //维护链表
        for(int i=0;i<PCBs.size()-1;i++){
            PCBs[i].plink=&PCBs[i+1];
        }
    };

    sort_();
    int sum=0,time_slice=0;
    while(PCBs[0].pstat!=F){   //循环直至所有进程结束
        //执行就绪链表中第一个进程
        PCBs[0].pcost--;
        PCBs[0].cur_cost++;
        PCBs[0].pstat=R;
        time_slice++;
        system("cls");
        Show(PCBs,1);
        system("pause");

        if(PCBs[0].pcost==0){
            PCBs[0].pstat=F;
            PCBs[0].ppri=-1;
            PCBs[0].cur_cost=0;
            sum+=time_slice;
        }
        else{
            PCBs[0].ppri--;
            PCBs[0].pstat=W;
        }

        //重新排序
        sort_();
    }
    return static_cast<double>(sum)/static_cast<double>(PCBs.size());
}

int TT_schedule(vector<PCB> &PCBs){   //时间片轮转调度算法
    auto turn_= [&](){
        //将就绪链表中的第一个进程放到链表末尾
        PCBs.push_back(PCBs[0]);
        PCBs.erase(PCBs.begin());
        //维护链表
        for(int i=0;i<PCBs.size()-1;i++){
            PCBs[i].plink=&PCBs[i+1];
        }
    };

    vector<PCB> PCB_F;
    //维护链表
    for(int i=0;i<PCBs.size()-1;i++){
        PCBs[i].plink=&PCBs[i+1];
    }
    int sum=0, time_slice=0;
    while(PCBs[0].pstat!=F){   //循环直至所有进程结束
        //执行就绪链表中第一个进程
        PCBs[0].pcost--;
        PCBs[0].cur_cost++;
        PCBs[0].pstat=R;
        time_slice++;
        system("cls");
        Show(PCBs,1);
        Show(PCB_F,0);
        system("pause");

        if(PCBs[0].pcost==0){
            PCBs[0].pstat=F;
            PCBs[0].ppri=-1;
            sum+=time_slice;
            PCB_F.push_back(PCBs[0]);
            PCBs.erase(PCBs.begin());
        }
        else{
            PCBs[0].pstat=W;
            turn_();
        }
    }
    return static_cast<double>(sum)/static_cast<double>(PCB_F.size());
}

int shortest_job_first_schedule(vector<PCB> &PCBs){   //短作业优先调度算法
    auto sort_= [&](){
        //按所需时间片数升序排序
        sort(PCBs.begin(),PCBs.end(),[](PCB &a,PCB &b){return a.pcost<b.pcost;});
        //维护链表
        for(int i=0;i<PCBs.size()-1;i++){
            PCBs[i].plink=&PCBs[i+1];
        }
    };

    sort_();
    int i=0,sum=0,time_slice=0;
    while(PCBs[PCBs.size()-1].pstat!=F){   //循环直至所有进程结束
        PCBs[i].pcost--;
        PCBs[i].cur_cost++;
        PCBs[i].pstat=R;
        time_slice++;
        system("cls");
        Show(PCBs,1);
        system("pause");

        if(PCBs[i].pcost==0){
            PCBs[i].pstat=F;
            PCBs[i].ppri=-1;
            PCBs[i].cur_cost=0;
            i++;
            sum+=time_slice;
        }
        else{
            PCBs[i].ppri--;
            PCBs[i].pstat=W;
        }

        //重新排序
        sort_();
    }
    return static_cast<double>(sum)/static_cast<double>(PCBs.size());
}


int main(){
    system("chcp 65001");
    double pri_t, tt_t, sjf_t;
    while(1){
        system("cls");
        // int num=rand_num(5,10);
        int num=10;
        cout<<"当前进程数："<<num<<endl;
        vector<PCB> PCBs(num);
        cout<<"初始状态："<<endl;
        Show(PCBs,1);

        cout<<endl<<"调度算法："<<endl;
        cout<<"1.优先数"<<endl;
        cout<<"2.简单轮转"<<endl;
        cout<<"3.短作业优先"<<endl;
        cout<<"4.退出"<<endl;
        cout<<"请选择调度算法："<<endl;
        int choice;
        cin>>choice;
        switch(choice){
            case 1:
                system("cls");
                system("pause");
                pri_t=pri_schedule(PCBs);
                system("pause");
                break;

            case 2:
                system("cls");
                system("pause");
                tt_t=TT_schedule(PCBs);
                system("pause");
                break;

            case 3:
                system("cls");
                system("pause");
                sjf_t=shortest_job_first_schedule(PCBs);
                system("pause");
                break;

            case 4:
                cout<<"优先数算法的平均周转时间"<<pri_t<<endl;
                cout<<"简单轮转算法的平均周转时间"<<tt_t<<endl;
                cout<<"短作业优先算法的平均周转时间"<<sjf_t<<endl;
                system("pause");
                return 0;

            default:
                cout<<"输入错误"<<endl;
                break;
        }
    }

}