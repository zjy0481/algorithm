#include "student.h"

using namespace std;

int main(){
    system("chcp 65001"); //设置控制台输出编码为UTF-8
    StudentList list;
    while(1){
        system("cls");
        cout<<"——————————欢迎使用学生成绩管理系统（主菜单）——————————"<<endl<<endl;
        cout<<"请选择操作："<<endl;
        cout<<"1.显示所有学生信息"<<endl;
        cout<<"2.添加学生信息"<<endl;
        cout<<"3.删除学生信息"<<endl;
        cout<<"4.查找学生信息"<<endl;
        cout<<"5.修改学生信息"<<endl;
        cout<<"6.退出"<<endl;
        cout<<"请输入操作编号（1~6）： ";
        int choice,choice_;
        cin>>choice;
        string name;
        int num,cs,ms,es;
        switch(choice){
            case 1:
                system("cls");
                cout<<"——————————欢迎使用学生成绩管理系统（显示所有学生信息）——————————"<<endl<<endl;
                cout<<"所有学生信息如下："<<endl<<endl;
                list.Show();
                system("pause");
                break;
            case 2:
                system("cls");
                cout<<"——————————欢迎使用学生成绩管理系统（添加学生信息）——————————"<<endl<<endl;
                cout<<"请输入新的学生姓名："<<endl;
                cin>>name;
                cout<<"请输入新的学生学号："<<endl;
                cin>>num;
                cout<<"请输入该学生的语数英成绩："<<endl;
                cin>>cs>>ms>>es;
                list.AddStudent(name,num,cs,ms,es);
                system("pause");
                break;
            case 3:
                while(1){
                    system("cls");
                    cout<<"——————————欢迎使用学生成绩管理系统（删除学生信息）——————————"<<endl<<endl;
                    cout<<"请选择操作："<<endl;
                    cout<<"1.按姓名删除"<<endl;
                    cout<<"2.按学号删除"<<endl;
                    cout<<"3.返回主菜单"<<endl;
                    cout<<"请输入操作编号（1~3）： ";
                    cin>>choice_;
                    if(choice_==3) break;
                    switch(choice_){
                        case 1:
                            cout<<"请输入要删除的学生姓名："<<endl;
                            cin>>name;
                            list.DeleteStudent(name);
                            system("pause");
                            break;
                        case 2:
                            cout<<"请输入要删除的学生学号："<<endl;
                            cin>>num;
                            list.DeleteStudent(num);
                            system("pause");
                            break;
                        default:
                            cout<<"输入有误，请重新输入！"<<endl;
                            system("pause");
                            break;
                    }
                }
                break;
            case 4:
                while(1){
                    system("cls");
                    cout<<"——————————欢迎使用学生成绩管理系统（查找学生信息）——————————"<<endl<<endl;
                    cout<<"请选择操作："<<endl;
                    cout<<"1.按姓名查找"<<endl;
                    cout<<"2.按学号查找"<<endl;
                    cout<<"3.返回主菜单"<<endl;
                    cout<<"请输入操作编号（1~3）： ";
                    cin>>choice_;
                    if(choice_==3) break;
                    switch(choice_){
                        case 1:
                            cout<<"请输入要查找的学生姓名："<<endl;
                            cin>>name;
                            Student* temp=list.SearchStudent(name);
                            cout<<"查找结果如下："<<endl;
                            temp->print();
                            system("pause");
                            break;
                        case 2:
                            cout<<"请输入要查找的学生学号："<<endl;
                            cin>>num;
                            Student* temp_=list.SearchStudent(num);
                            cout<<"查找结果如下："<<endl;
                            temp_->print();
                            system("pause");
                            break;
                        default:
                            cout<<"输入有误，请重新输入！"<<endl;
                            system("pause");
                            break;
                    }
                }
                break;
            case 5:
                while(1){
                    system("cls");
                    cout<<"——————————欢迎使用学生成绩管理系统（修改学生信息）——————————"<<endl<<endl;
                    list.ModifyStudent();
                    system("pause");
                }
                break;
            case 6:
                system("cls");
                cout<<"感谢您的使用！"<<endl;
                list.Free();
                system("pause");
                return 0;
            default:
                cout<<"输入有误，请重新输入！"<<endl;
                system("pause");
                system("cls");
                break;
        }
    }

    return 0;
}