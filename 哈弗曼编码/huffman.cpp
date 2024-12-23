#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>

class Node{
public:
    Node():key(false),value(0),left_child(nullptr),right_child(nullptr){};
    ~Node(){}
    bool key;
    int value;
    Node* left_child;
    Node* right_child;
};

Node* BuildHuffman(std::vector<Node*> vec_Nodes){  //生成哈夫曼树
    while(vec_Nodes.size()>1){
        std::sort(vec_Nodes.begin(), vec_Nodes.end(),[&](Node* a, Node* b){return a->value < b->value;});
        Node* first=vec_Nodes[0];
        Node* second=vec_Nodes[1];
        Node* merge=new Node;
        merge->key=false;
        merge->value=first->value+second->value;
        if(first->value<second->value){
            merge->left_child=second;
            merge->right_child=first;
        }
        else{
            merge->left_child=first;
            merge->right_child=second;
        }
        vec_Nodes.erase(vec_Nodes.begin(),vec_Nodes.begin()+2);
        vec_Nodes.push_back(merge);
    }
    return vec_Nodes[0];    //返回根节点
}

void PrintResult(Node* root,std::vector<int> stack){  //打印结果
    if(root==nullptr){
        return;
    }
    if(root->key){
        std::cout<<root->value<<' ';
        for(int i:stack){
            std::cout<<i;
        }
        std::cout<<std::endl;
    }
    std::vector<int> stack_left,stack_right;
    for(int i=0;i<stack.size();i++){    //深拷贝
        stack_left.push_back(stack[i]);
        stack_right.push_back(stack[i]);
    }
    if(root->left_child!=nullptr){
        stack_left.push_back(0);
        PrintResult(root->left_child, stack_left);
    }
    if(root->right_child!=nullptr){
        stack_right.push_back(1);
        PrintResult(root->right_child, stack_right);
    }
    return;
}

int main(){
    int times;
    std::cin>>times;
    for(int k=1;k<=times;k++){
        int n;
        std::cin>>n;
        std::vector<Node*> vec_Nodes;
        for(int i=0;i<n;i++){
            Node* node=new Node;
            node->key=true;
            std::cin>>node->value;
            vec_Nodes.push_back(node);
        }
        Node* root=BuildHuffman(vec_Nodes);
        std::vector<int> stack;
        std::cout<<"Case "<<k<<std::endl;
        PrintResult(root, stack);
        std::cout<<std::endl;
    }
}