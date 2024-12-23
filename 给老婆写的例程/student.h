#include <iostream>
#include <string>
#include <map>

using namespace std;

class Score{        //分数类，按老婆的思路写的，但这样子写会有一个问题，就是这个类的可扩展性比较差，如果加一门课，就得加一个成员变量
    public:
    //默认构造
    Score():chinese_score(0),math_score(0),english_score(0){};
    //含参构造
    Score(int cs,int ms,int es):chinese_score(cs),math_score(ms),english_score(es){};
    //拷贝构造
    Score(const Score& s):chinese_score(s.chinese_score),math_score(s.math_score),english_score(s.english_score){};
    //析构
    ~Score(){};
    friend class Student;

    private:
    int chinese_score;
    int math_score;
    int english_score;
};
//如果想要优化，可以使用数组来存储所有分数，也可以使用map容器或其他容器来存储（这个可能老婆还没学到）

class Student{
    public:
    //默认构造
    Student():name(""),num(0),score(),next(nullptr){};
    //含参构造
    Student(string na,int nu,int cs,int ms,int es):name(na),num(nu),score(cs,ms,es),next(nullptr){};
    //析构
    ~Student(){};
    friend class StudentList;

    //功能函数部分
    void set_name(string name);             //设置姓名
    void set_num(int num);                  //设置学号
    void set_score(int cs,int ms,int es);   //设置分数
    void print();                           //打印学生信息

    private:
    string name;    //姓名
    int num;        //学号
    Score score;    //分数
    Student* next;  //指向下一个学生信息，用于链表
};

//实际上学生信息也可以通过容器来优化可扩展性，例如使用tuple容器来存储所有信息
//到此为止，我们只完成了信息单元的编写，并没有决定通过哪种方式来存储信息，也就是，我们只编写了存储单个学生信息的类，但并没有决定要通过什么数据类型来存储学生信息，例如我们可以建立一个以student为节点的链表来管理所有学生的信息
//正好老婆搞不太懂指针，我就用链表来写例程了（其实有很多更优、现成的数据结构），只要能看懂的话，老婆应该大概也能理解指针了

class StudentList{  //编写学生链表类来管理所有学生信息
    public:
    //默认构造
    StudentList():head(nullptr),nums(0){};
    //析构
    ~StudentList(){
        this->Free();
    };

    //功能函数部分
    //一个管理系统所需要的最基础的功能便是增删查改、显示与内存释放
    void AddStudent(string name,int num,int cs,int ms,int es);      //添加学生信息
    void DeleteStudent(string name);                                //删除学生信息
    void DeleteStudent(int num);                                    //删除学生信息（这里是重载）
    Student* SearchStudent(string name);                            //查找学生信息，返回查找到的学生对象的指针，如果未找到就返回nullptr（这里暂未考虑重名或重学号的情况，如果想做也可以，但最好使用一些容器，这里暂时不做）
    Student* SearchStudent(int num);                                //查找学生信息（这里是重载）
    void ModifyStudent();   //修改学生信息

    int GetNum();                                                   //获取当前系统中的学生数量
    void Show();                                                    //显示所有学生信息
    void Free();                                                    //释放链表
    //这里只写了最基本的功能，还可以添加其他功能，例如排序、统计、存储到文件以及从文件初始化等（排序就比如像高考一样，能根据分数对每位学生进行排序；统计就比如计算平均分，中位分等等）

    private:
    Student* head;  //指向链表头部的指针
    int nums;        //学生数量
};