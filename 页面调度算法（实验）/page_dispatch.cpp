//关于页面调度序列：
//50%的指令是顺序执行，25%均匀分布在地址的前半部分，25%均匀分布在地址的后半部分
//设定：页面调度序列长度为length，分为length/2、length/4、length/4三部分
//虚存容量为32K，页面大小1K，物理空间8K
//算法包括OPT和LRU

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

//虚存表项类
class virtual_table_entry {
public:
    virtual_table_entry():position(-1), next_visit(INT_MAX), last_visit(INT_MAX){}
    virtual_table_entry(int p){
        position = p;
    }
    ~virtual_table_entry(){}

    int position;       //对应的物理块号，-1表示不在内存中
    ///以下用于方便算法设计
    int next_visit;     //距离下次访问该页的时间，opt，INT_MAX表示该页后续不再调度
    int last_visit;     //距离上次访问该页的时间，lru，INT_MAX表示该页从未访问过
};

//内存表项类
class memory_table_entry {
public:
    memory_table_entry(): page_number(-1){}
    memory_table_entry(int n){
        page_number = n;
    }
    ~memory_table_entry(){}

    int page_number;    //页号
};

//随机生成页面调度序列的函数
vector<int> generate_page_sequence(int length) {
    vector<int> page_sequence;
    for(int i = 0; i < length/2; i++) {   //顺序执行部分
        page_sequence.push_back(i%32);
    }
    for(int i = 0; i < length/4; i++) {   //前半部分随机分布
        page_sequence.push_back(rand()%16);
    }
    for(int i = 0; i < length/4; i++) {   //后半部分随机分布
        page_sequence.push_back(rand()%16 + 16);
    }
    return page_sequence;
}

//OPT调度算法
void OPT_function(vector<int> page_sequence){
    vector<virtual_table_entry> page_table(32); //虚存页表，数组下标对应页号
    vector<memory_table_entry> memory_table(8); //反向页表，数组下标对应物理块号
    int p_size=page_sequence.size();            //调度序列长度
    int hit_cnt=0;                              //命中次数

    for(int i = 0; i < p_size; i++) {           //外层循环，处理整个页面调度序列
        int visit_page = page_sequence[i];      //当前访问的页号
        if(page_table[visit_page].position != -1) { //命中
            hit_cnt++;
        }
        //未命中，判断是否需要置换
        for(int j = 0; j < 8; j++) {
            if(memory_table[j].page_number == -1) { //有空闲物理块
                memory_table[j].page_number = visit_page;
                page_table[visit_page].position = j;
                break;
            }
        }
        //确认需要置换
        //每次置换前需要先维护next_visit
        for(int j = 0; j < 32; j++) {
            int next = INT_MAX;
            for(int k = i; k < p_size; k++) {
                if(j == page_sequence[k]) {
                    next = k;
                    break;
                }
            }
            page_table[j].next_visit = next;
        }
        int replaced_page=-1,max_next=-1,memory_position=-1;
        for(int j = 0; j < 8; j++){ //找出要被替换的页面
            if(page_table[memory_table[j].page_number].next_visit > max_next) {
                max_next = page_table[memory_table[j].page_number].next_visit;
                replaced_page = memory_table[j].page_number;
                memory_position = j;
            }
        }
        //进行页面替换
        page_table[replaced_page].position = -1;
        page_table[visit_page].position = memory_position;
        memory_table[memory_position].page_number = visit_page;
    }
    cout<<"OPT算法命中次数："<<hit_cnt<<endl;
    cout<<"OPT算法命中率："<<static_cast<double>(hit_cnt)/static_cast<double>(p_size)<<endl;
}

//LRU调度算法
void LRU_function(vector<int> page_sequence) {
    vector<virtual_table_entry> page_table(32); //虚存页表，数组下标对应页号
    vector<memory_table_entry> memory_table(8); //反向页表，数组下标对应物理块号
    int p_size=page_sequence.size();            //调度序列长度
    int hit_cnt=0;                              //命中次数

    for(int i = 0; i < p_size; i++) {           //外层循环，处理整个页面调度序列
        int visit_page = page_sequence[i];      //当前访问的页号
        if(page_table[visit_page].position != -1) { //命中
            hit_cnt++;
        }
        //未命中，判断是否需要置换
        for(int j = 0; j < 8; j++) {
            if(memory_table[j].page_number == -1) { //有空闲物理块
                memory_table[j].page_number = visit_page;
                page_table[visit_page].position = j;
                break;
            }
        }
        //确认需要置换
        //每次置换前需要先维护last_visit
        for(int j = 0; j < 32; j++) {
            int last = INT_MAX;
            for(int k = i; k >= 0; k--) {   //其实这里从k=i-1开始也可以，因为已经确定了page_sequence[i]不在内存中，他不可能是被替换的页面，不过无伤大雅
                if(j == page_sequence[k]) {
                    last = i - k;
                    break;
                }
            }
        }
        int replaced_page=-1,max_last=-1,memory_position=-1;
        for(int j = 0; j < 8; j++){ //找出要被替换的页面
            if(page_table[memory_table[j].page_number].last_visit > max_last) {
                max_last = page_table[memory_table[j].page_number].last_visit;
                replaced_page = memory_table[j].page_number;
                memory_position = j;
            }
        }
        //进行页面替换
        page_table[replaced_page].position = -1;
        page_table[visit_page].position = memory_position;
        memory_table[memory_position].page_number = visit_page;
    }
    cout<<"LRU算法命中次数："<<hit_cnt<<endl;
    cout<<"LRU算法命中率："<<static_cast<double>(hit_cnt)/static_cast<double>(p_size)<<endl;
}

int main() {
    system("chcp 65001");
    int length;
    cout<<"请输入页面调度序列长度(4的倍数）：";
    cin>>length;
    vector<int> page_sequece(length);
    page_sequece = generate_page_sequence(length);
    cout<<"调度页面序列为："<<endl;
    for(auto i : page_sequece) {
        cout << i << " ";
    }
    cout << endl;
    OPT_function(page_sequece);
    cout<<endl;
    LRU_function(page_sequece);
    system("pause");
    return 0;
}