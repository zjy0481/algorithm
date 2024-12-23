#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>

using namespace std;

// 定义最大需求矩阵、分配矩阵和可用资源向量
// 对于所有矩阵的[i][j]，i表示进程编号，j表示资源编号
vector<vector<int>> maxDemand;
vector<vector<int>> allocation;
vector<int> available;
vector<int> total_Resources;

// 定义进程数量和资源种类数量
int numProcesses;
int numResources;

vector<vector<int>> need(numProcesses, vector<int>(numResources));

bool isSafeState(vector<int> work, vector<vector<int>> need, vector<vector<int>> allocation) {
    vector<bool> finish(numProcesses, false);
    vector<int> safeSequence;

    for (int i = 0; i < numProcesses; i++) {
        bool found = false;
        for (int j = 0; j < numProcesses; j++) {
            if (!finish[j] && need[j] <= work) {
                for (int k = 0; k < numResources; k++) {
                    work[k] += allocation[j][k];
                }
                finish[j] = true;
                safeSequence.push_back(j);
                found = true;
                break;
            }
        }
        if (!found) {
            return false;
        }
    }

    cout<<"安全序列为: "<<endl;
    for (int i = 0; i < numProcesses; i++) {
        cout<<safeSequence[i]<<" ";
    }
    cout<<endl;
    return true;
}

// 银行家算法
bool bankerAlgorithm(int process, vector<int> request) {
    for (int i = 0; i < numResources; i++) {
        if (request[i] > need[process][i] || request[i] > available[i]) {
            return false;
        }
    }

    for (int i = 0; i < numResources; i++) {
        available[i] -= request[i];
        allocation[process][i] += request[i];
        need[process][i] -= request[i];
    }

    if (isSafeState(available, need, allocation)) {
        return true;
    } else {
        for (int i = 0; i < numResources; i++) {
            available[i] += request[i];
            allocation[process][i] -= request[i];
            need[process][i] += request[i];
        }
        return false;
    }
}

int main() {
    // 输入进程数量和资源种类数量
    cout << "请输入进程数量: ";
    cin >> numProcesses;
    cout << "请输入资源类型数量: ";
    cin >> numResources;

    // 输入系统拥有的资源总量
    cout << "请输入系统拥有的资源总量:" << endl;
    for (int i = 0; i < numResources; i++) {
        int input;
        cin >> input;
        total_Resources.push_back(input);
    }

    // 随机生成最大需求矩阵
    cout<<"随机生成的最大需求矩阵如下"<<endl;
    for(int i = 0; i < numProcesses; i++) {
        vector<int> row;
        for (int j = 0; j < numResources; j++) {
            int input = rand() % (total_Resources[j]+1);    //随机生成0到资源总量之间的整数，+1是因为资源需求量可以等于系统的资源总量
            row.push_back(input);
            cout <<setw(2)<< input << " ";
        }
        maxDemand.push_back(row);
        cout << endl;
    }

    // 随机生成分配矩阵
    available = total_Resources;    //初始化可用资源向量
    cout << "随机生成的分配矩阵如下:" << endl;
    for(int i = 0; i < numProcesses; i++) {
        vector<int> row;
        for(int j=0;j<numResources;j++) {
            double x = (static_cast<double>(rand())/RAND_MAX);    //生成0-1之间的随机小数
            if(x<0.25){x+=0.5;}             //这里+了0.5因为怕生成的小数太小
            int max_ = available[j]<maxDemand[i][j] ? available[j]:maxDemand[i][j];    //分配矩阵既不能超过maxDemand，也不能超过available
            int input =static_cast<int>((max_+1)*x) ? rand() % static_cast<int>((max_+1)*x) : 0;
            //随机生成0到可用量之间的整数，加了一个随机数x是因为害怕前面的进程占用掉太多资源，后面的进程分配不到，5不够还原实际应用场景
            row.push_back(input);
            available[j] -= input;
            cout<<setw(2) << input << " ";
        }
        allocation.push_back(row);
        cout << endl;
    }
    cout<<endl;

    // 输出资源可用量向量
    cout<<"当前资源可用量向量如下:"<<endl;
    for(int i=0;i<numResources;i++) {
        cout <<setw(2)<< available[i] << " ";
    }
    cout << endl;

    // 计算并输出需求矩阵
    for (int i = 0; i < numProcesses; i++) {
        vector<int> row;
        for (int j = 0; j < numResources; j++) {
            int temp = maxDemand[i][j] - allocation[i][j];
            row.push_back(temp);
        }
        need.push_back(row);
    }
    cout << "当前需求矩阵如下:" << endl;
    for (int i = 0; i < numProcesses; i++) {
        for (int j = 0; j < numResources; j++) {
            cout <<setw(2)<< need[i][j] << " ";
        }
        cout << endl;
    }

    // 输入进程号和请求资源向量
    int process;
    vector<int> request(numResources);
    cout << "输入请求资源的进程号（0~进程数-1）: ";
    cin >> process;
    cout << "输入该进程请求的资源量: ";
    for (int i = 0; i < numResources; i++) {
        cin >> request[i];
    }

    // 执行银行家算法
    if (bankerAlgorithm(process, request)) {
        cout << "请求通过，资源予以分配。" << endl;
    } else {
        cout << "不存在安全序列，驳回该请求，不予分配资源。" << endl;
    }

    return 0;
}
