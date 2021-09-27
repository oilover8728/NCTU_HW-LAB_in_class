#include<iostream>
#include<stdio.h>
#include<cstdlib>
#include<fstream>
#include<cstring>
#include<cctype>
#include<iomanip>

using namespace std;

FILE *pFile;
FILE *pOFile;

class red_black_tree{
private:
    //節點需要的資料 用struct整個包起來
	struct Node{
		int key;
		bool color; //black is false(0) , red is ture(1)
		Node *left, *right, *parent;
		Node* grandparent(){
			if(parent==NULL) {
                return NULL;
			}
			return parent->parent;
		}
		Node* uncle(){
			if(grandparent()==NULL) {
                return NULL;
			}
			if(parent==grandparent()->left) {
                return grandparent()->right;
			}
			return grandparent()->left;
		}
		Node* sibling(){
			if(parent==NULL) {
                return NULL;
			}
			if(this==parent->left) {
                return parent->right;
			}
			return parent->left;
		}
		//初始值
		Node():key(0), color(1), left(NULL), right(NULL), parent(NULL){}
	};

    void left_rotation(Node* x){
        Node *y=x->right;                   // 把y指向x的rightchild, 最後y會變成x的parent
        x->right=y->left;                   // 把y的leftchild托在x的rightchild
        if(y->left!=NULL){                  // 若node(j)為NIL則忽略
            y->left->parent=x;              // 將原先y的leftchild的parent改成x
            //cout <<"1"<<endl;
        }
        y->parent=x->parent;                // 更新y的parent
        if(x->parent==NULL) {
            root=y;                         // 若原先x是root, 旋轉後y變成新的root
            //cout <<"2"<<endl;
        }
        else if(x==x->parent->left){        // 若原先x是其parent的leftchild
            x->parent->left=y;              // 更新後y也是其parent的leftchild
            //cout <<"3"<<endl;
        }
        else {                              // 若原先x是其parent的rightchild
            x->parent->right=y;             // 更新後y也是其parent的rightchild
            //cout << x->key<<"4"<<endl;
        }
            //cout << "5"<<endl;
        y->left=x;                          // 最後才修改y與x
        x->parent=y;

    }

	void right_rotation(Node* y){
        Node *x=y->left;                    // 把x設成y的leftchild
        y->left=x->right;                   // 把x的rightchild放到y的leftchild
        if(x->right!=NULL) {                // 若x的rightchild不為NIL, 將其parent指向y
            x->right->parent=y;
        }
        x->parent=y->parent;                // 將x的parent指向原先y的parent
                                            // 以下一組if-else將修改原先y的parent之child
        if(y->parent==NULL){                     // 若y原先是root, x將成為新的root
            root=x;
        }
        else if(y==y->parent->right) {      // 若原先y是其parent之leftchild,
            y->parent->right=x;             // x就成為其新的parent之leftchild
        }
        else {                              // 若原先y是其parent之rightchild,
            y->parent->left=x;              // x就成為其新的parent之rightchild
        }
        x->right=y;                         // 將y設為x之rightchild
        y->parent=x;                        // 將x設為y之parent
    }

	void output_order(Node *x){
        if(x==NULL) {
            return;
        }
        if(x->left!=NULL && x->left!=NIL) {
            output_order(x->left);
        }
        fprintf(pOFile,"key: %d parent: ",x->key);
        if(x->parent==NULL) {
            fprintf(pOFile," ");
        }
        else {
            fprintf(pOFile,"%d",x->parent->key);
        }
        fprintf(pOFile," color: ");
        if(x->color==1){
            fprintf(pOFile,"red\n");
        }
        else{
            fprintf(pOFile,"black\n");
        }
        if(x->right!=NULL && x->right!=NIL) {
            output_order(x->right);
        }
    }

//      什麼情況需要對RBT 做修正？
//      當新增node接在紅色的node的child pointer，形成紅色與紅色相連時。
//
//      Case1：uncle是紅色，不論新增的node是node(X)的leftchild或rightchild；
//      Case2：uncle是黑色，而且新增的node為node(X)的rightchild；
//      Case3：uncle是黑色，而且新增的node為node(X)的leftchild。

    void insert_Fixed(Node* current){
		if(current->parent==NULL){
			root=current;
			current->color=0;
			return;
		}
		if(current->parent->color==0) {
            return;
		}
		if(current->uncle()!=NULL && current->uncle()->color==1){
			current->parent->color=0;
			current->uncle()->color=0;
			current->grandparent()->color=1;
			insert_Fixed(current->grandparent());
			return;
		}
		if(current->parent->right==current && current->parent==current->grandparent()->left){
			left_rotation(current->parent);
			current=current->left;
		}
		else if(current==current->parent->left && current->parent==current->grandparent()->right){
			right_rotation(current->parent);
			current=current->right;
		}
		current->parent->color=0;
		current->grandparent()->color=1;
		if(current==current->parent->left && current->parent==current->grandparent()->left) {
                right_rotation(current->grandparent());
		}
		else {
            left_rotation(current->grandparent());
		}
	}

    Node* Find_Smallest(Node *x){
        while(x->left!=NULL){
            x=x->left;
        }
        return x;
    }

//    Case1：sibling為紅色；
//    Case2：sibling為黑色，而且sibling的兩個child都是黑色；
//    Case3：sibling為黑色，而且sibling的rightchild是黑色，leftchild是紅色；
//    Case4：sibling為黑色，而且sibling的rightchild是紅色。

    void delete_Fixed(Node *current){
        if(current->parent == NULL){
            current->color = 0;
            root=current;
            return;
        }
        Node* brother=current->sibling();
        if(brother->color == 1) {//case 1
            current->parent->color = 1;
            current->color = 0;
            if(current == current->parent->left) {
                left_rotation(current->parent);
            }
            else {
                right_rotation(current->parent);
            }
        }
        if(current->parent->color==0 && brother->color==0 && brother->left->color==0 && brother->right->color==0){
            brother->color = 1;
            delete_Fixed(current->parent);
        }
		else if(current->parent->color==1 && brother->color==0 && brother->left->color==0 && brother->right->color==0){
            brother->color = 1;
            current->parent->color = 0;
        }
		else{
            if(brother->color == 0) {
                if(current==current->parent->left && brother->left->color==1 && brother->right->color==0){
                    brother->color = 1;
                    brother->left->color = 0;
                    right_rotation(brother);
                }
				else if(current==current->parent->right && brother->left->color==0 && brother->right->color==1){
                    brother->color = 1;
                    brother->right->color = 0;
                    left_rotation(brother);
                }
            }
            brother->color = current->parent->color;
            current->parent->color = 0;
            if(current == current->parent->left){
                brother->right->color = 0;
                left_rotation(current->parent);
            }
			else {
                brother->left->color = 0;
                right_rotation(current->parent);
            }
        }
    }

    void delete_node(Node *x){
        Node *child;
        if(x->right!=NULL){
            child = x->left;
        }
        else{
            child = x->right;
        }
        //Node *child =(x->right!=NULL)? x->left : x->right;
        if(child==NULL) {
            child=NIL;
        }
        if(x->parent == NULL && x->left== NULL && x->right== NULL){
            x = NULL;
            root = x;
            return;
        }
        if(x->parent == NULL){
            delete x;
            child->parent = NULL;
            root = child;
            root->color = 0;
            return;
        }
        if(x->parent->left== x){
            x->parent->left= child;
        }
		else{
            x->parent->right= child;
        }
        child->parent = x->parent;
        if(x->color == 0){
            if(child->color == 1) {
                child->color = 0;
            }
			else {
                delete_Fixed(child);
			}
        }
        delete x;
    }

	void delete_child(Node *x, int data){
        if(x->key > data){
            if(x->left==NULL) {
                return;
            }
            return delete_child(x->left, data);
        }
		else if(x->key < data){
            if(x->right==NULL){
                return;
            }
            return delete_child(x->right, data);
        }
		else{
            if(x->right==NULL){
                delete_node(x);
                return;
            }
            Node *smallest = Find_Smallest(x->right);
            int temp;
            temp=x->key;
            x->key=smallest->key;
            smallest->key=temp;
            delete_node(smallest);
        }
    }

Node *root;
Node *NIL;

public:
    //construct
	red_black_tree(){
		NIL=new Node;
		root=NULL;
		NIL->color=0;
	}

	//destruct
	~red_black_tree(){
	}

	void output_order(){
		if(root==NULL) {
            return;
		}
		output_order(root);
	}

	void insert(int data) {
        if(root==NULL){
            root=new Node();
            root->color=0;
            root->left=NULL;
			root->right=NULL;
			root->parent=NULL;
            root->key=data;
        }
		else{ //insert(root, data);
            Node *x = root;
            Node *y = NULL;
            while(x!=NULL){
                y=x;
                if(data < x->key){
                    x=x->left;
                }
                else{
                    x=x->right;
                }
            }
            Node *insert_node=new Node();
            insert_node->key=data;
            insert_node->left=NULL;
            insert_node->right=NULL;
            insert_node->parent=y;
            insert_node->color=1;
            if(data<y->key){
                y->left=insert_node;
            }
            else{
                y->right=insert_node;
            }
            insert_Fixed(insert_node);
		}
	}

	void delete_value(int data){
        return delete_child(root, data);
    }

};

int main(){
    //construct the RBT
	red_black_tree tree;

	// I/O File
    char buffer[1024]={0};  //buffer the txt.line
    pFile = fopen("input.txt", "r" );
    pOFile = fopen ("output.txt","w");

	int n=0;                //number of tests
    int num=0;              //count what's number of tests
    int mode;               //for insert or delete
    int array[1000];        //for input data array

    //clean the buffer
    memset(buffer,0,sizeof(buffer));
    //get the first line
    fgets(buffer, sizeof(buffer),pFile);
    //get how many tests in n
    n=buffer[0]-48;

    while(!feof(pFile)&&num!=n){
        //get insert or delete
        memset(buffer,0,sizeof(buffer));
        fgets(buffer, sizeof(buffer),pFile);
        mode = buffer[0]-48;

        //insert
        if(mode == 1){
            //cout << "Insert: ";
            fprintf(pOFile,"Insert: ");
            //read the test integers and store in array
            memset(buffer,0,sizeof(buffer));
            fgets(buffer, sizeof(buffer),pFile);
            //split with blank
            int size=0;
            char *pch;
            pch = strtok(buffer," ");
            while(pch!=NULL){
                array[size]=atoi(pch);
                //cout << size << " "<<array[size] << endl;
                size++;
                pch = strtok(NULL," ");
            }
            //cout << array[0];
            fprintf(pOFile,"%d",array[0]);
            for(int i=1;i<size;i++){
                //cout << ", "<<array[i];
                fprintf(pOFile,", %d",array[i]);
            }
            //cout << endl;
            fprintf(pOFile,"\n");
            for(int i=0;i<size;i++){
                tree.insert(array[i]);
            }
            tree.output_order();
        }

        //delete
        else if(mode == 2){
            //cout << "Delete: ";
            fprintf(pOFile,"Delete: ");
            //read the test integers and store in array
            memset(buffer,0,sizeof(buffer));
            fgets(buffer, sizeof(buffer),pFile);
            //split with blank
            int size=0;
            char *pch;
            pch = strtok(buffer," ");
            while(pch!=NULL){
                array[size]=atoi(pch);
                size++;
                pch = strtok(NULL," ");
            }
            //cout << array[0];
            fprintf(pOFile,"%d",array[0]);
            for(int i=1;i<size;i++){
                //cout << ", "<<array[i];
                fprintf(pOFile,", %d",array[i]);
            }
            //cout << endl;
            fprintf(pOFile,"\n");
            for(int i=0;i<size;i++){
                tree.delete_value(array[i]);
            }
            tree.output_order();
        }

    }
	return 0;
}
