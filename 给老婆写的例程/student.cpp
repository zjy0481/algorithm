#include "student.h"

using namespace std;

void Student::set_name(string name){
    this->name = name;
}

void Student::set_num(int num){
    this->num = num;
}

void Student::set_score(int cs, int ms, int es){
    this->score.chinese_score = cs;
    this->score.math_score = ms;
    this->score.english_score = es;
}

void Student::print(){
    cout<<"姓名："<<name<<" 学号："<<num<<" 语文成绩："<<score.chinese_score<<" 数学成绩："<<score.math_score<<" 英语成绩："<<score.english_score<<endl;
}

void StudentList::AddStudent(string name,int num,int cs,int ms,int es){
    if(head==nullptr){  //如果链表为空，则直接创建头节点，否则在视图head->next会报错，因为head根本不存在，这个如果想不明白我画个图和老婆详细讲
        head = new Student(name,num,cs,ms,es);
        this->nums++;
        cout<<"添加成功！"<<endl;
        return;
    }
    else{
        Student *temp=head;
        for(;temp->next!=nullptr;temp=temp->next);  //使temp指向链表中最后一个节点
        temp->next = new Student(name,num,cs,ms,es);
        this->nums++;
        cout<<"添加成功！"<<endl;
        return;
    }
}

void StudentList::DeleteStudent(string name){
    Student *p = this->SearchStudent(name);
    if(p){      //如果查找结果不为空，则删除指定对象，并维护链表关系；如果不理解这里p为什么能作为if的条件，可以来问老猪咪
        Student *temp=head;
        for(;temp->next!=p;temp=temp->next);    //使temp指向p（要删除的节点）的前一个节点
        temp->next = p->next;
        delete p;
        p=nullptr;
        cout<<"删除成功！"<<endl;
        this->nums--;
        return;
    }
    else{       //查找结果为空
        cout<<"删除失败！所要删除的学生不存在！"<<endl;
        return;
    }
}

void StudentList::DeleteStudent(int num){   //逻辑和上一个函数一模一样
    Student *p = this->SearchStudent(num);
    if(p){
        Student *temp=head;
        for(;temp->next!=p;temp=temp->next);
        temp->next = p->next;
        delete p;
        p=nullptr;
        cout<<"删除成功！"<<endl;
        this->nums--;
        return;
    }
    else{
        cout<<"删除失败！所要删除的学生不存在！"<<endl;
        return;
    }
}

Student* StudentList::SearchStudent(string name){
    if(head==nullptr){
        cout<<"查找失败！该学生不存在！"<<endl;
        return nullptr;
    }
    for(Student *temp=head;temp!=nullptr;temp=temp->next){  //遍历整个链表，查找是否对应名字的对象，有则直接返回，没有则cout错误信息并返回nullptr
        if(temp->name==name){
            cout<<"查找成功！"<<endl;
            return temp;
        }
    }
    cout<<"查找失败！该学生不存在！"<<endl;
    return nullptr;
}

Student* StudentList::SearchStudent(int num){       //逻辑和上一个函数一模一样
    if(head==nullptr){
        cout<<"查找失败！该学生不存在！"<<endl;
        return nullptr;
    }
    for(Student *temp=head;temp!=nullptr;temp=temp->next){
        if(temp->num==num){
            cout<<"查找成功！"<<endl;
            return temp;
        }
    }
    cout<<"查找失败！该学生不存在！"<<endl;
    return nullptr;
}

void StudentList::ModifyStudent(){      //
    if(this->nums==0){      //增加这个判断只是为了下面输出的提示信息不会出现“请输入序号（1~0）”的情况
        cout<<"当前学生列表为空！没有可供修改的信息！"<<endl;
        return;
    }
    this->Show();
    cout<<"您想要修改第几行？请输入序号（1~"<<nums<<")： ";
    int i;
    cin>>i;
    if(i>=1&&i<=nums){
        Student* temp=head;
        for(int j=1;j<i;j++){       //使temp指向要修改的节点
            temp=temp->next;
        }
        cout<<"请输入新的学生姓名："<<endl;
        string name;
        cin>>name;
        temp->set_name(name);
        cout<<"请输入新的学生学号："<<endl;
        int num;
        cin>>num;
        temp->set_num(num);
        cout<<"请输入该学生的语数英成绩："<<endl;
        int cs,ms,es;
        cin>>cs>>ms>>es;
        temp->set_score(cs,ms,es);
        cout<<"修改成功！"<<endl;
        return;
    }
    else{
        cout<<"请输入正确的序号！"<<endl;
        return;
    }
}

int StudentList::GetNum(){
    return this->nums;
}

void StudentList::Show(){       //显示所有学生信息
    if(head==nullptr){
        cout<<"当前学生列表为空！"<<endl;
        return;
    }
    int i=1;
    for(Student *temp=head;temp!=nullptr;temp=temp->next){
        cout<<i<<"| ";
        temp->print();
        i++;
    }
}

void StudentList::Free(){
    while(head!=nullptr){
        Student* temp = head;
        head = head->next;
        delete temp;
    }
    cout<<"学生信息链表已被释放"<<endl;
}