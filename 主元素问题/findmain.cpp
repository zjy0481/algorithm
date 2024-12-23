#include <iostream>
using namespace std;
 
#define MAXNUM 100
 
//基于分治法的线性期望时间求主元素算法
void Swap(int *a, int *b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}
 
//随机划分
int PartitionRandom(int a[], int first, int last)
{
    int priot = first + rand() % (last - first + 1);
    Swap(&a[first], &a[priot]);
    int key = a[first];
 
    while(first < last)
    {
        while(first < last && a[last] >= key)
        {
            last--;
        }
        Swap(&a[first], &a[last]);
 
        while(first < last && a[first] <= key)
        {
            first++;
        }
        Swap(&a[first], &a[last]);
    }
    return first;
}
 
int Select(int a[], int first, int last , int i)
{
    if(first == last)
    {
        return a[first];
    }
    int priot = PartitionRandom(a, first, last);
    int k = priot - first + 1;
    if(k == i)
    {
        return a[k];
    }
    if(k > i)
    {
        return Select(a, first, priot - 1, i);
    }
    else//k < i
    {
        return Select(a, priot + 1, last, i - k);
    }
}
 
void FindMaster(int a[], int length)
{
    int mid = length/2;
    int key = Select(a, 0, length - 1, mid);
    cout << "中位数为:" << key << endl;
    int count = 0;
    for(int i = 0; i < length; i++)
    {
        if(a[i] == key)
        {
            count++;
        }
    }
    if(count > mid)
    {
        cout << "主元素为:" << key << endl;
    }
    else
    {
        cout << "该数组中没有主元素" << endl;
    }
 
}
 
int main(int argc, char* argv[])
{
    int a[MAXNUM];
    int length;
    cout << "请输入数组元素个数:";
    cin >> length;
    for(int i = 0; i < length; i++)
    {
        cin >> a[i];
    }
    cout << "输入的元素如下所示：" << endl;
    for(int i = 0; i < length; i++)
    {
        cout << a[i] << " ";
    }
    cout << endl;
 
    FindMaster(a, length);
    
    return 0;
}