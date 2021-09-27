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
    //�`�I�ݭn����� ��struct��ӥ]�_��
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
		//��l��
		Node():key(0), color(1), left(NULL), right(NULL), parent(NULL){}
	};

    void left_rotation(Node* x){
        Node *y=x->right;                   // ��y���Vx��rightchild, �̫�y�|�ܦ�x��parent
        x->right=y->left;                   // ��y��leftchild���bx��rightchild
        if(y->left!=NULL){                  // �Ynode(j)��NIL�h����
            y->left->parent=x;              // �N���y��leftchild��parent�令x
            //cout <<"1"<<endl;
        }
        y->parent=x->parent;                // ��sy��parent
        if(x->parent==NULL) {
            root=y;                         // �Y���x�Oroot, �����y�ܦ��s��root
            //cout <<"2"<<endl;
        }
        else if(x==x->parent->left){        // �Y���x�O��parent��leftchild
            x->parent->left=y;              // ��s��y�]�O��parent��leftchild
            //cout <<"3"<<endl;
        }
        else {                              // �Y���x�O��parent��rightchild
            x->parent->right=y;             // ��s��y�]�O��parent��rightchild
            //cout << x->key<<"4"<<endl;
        }
            //cout << "5"<<endl;
        y->left=x;                          // �̫�~�ק�y�Px
        x->parent=y;

    }

	void right_rotation(Node* y){
        Node *x=y->left;                    // ��x�]��y��leftchild
        y->left=x->right;                   // ��x��rightchild���y��leftchild
        if(x->right!=NULL) {                // �Yx��rightchild����NIL, �N��parent���Vy
            x->right->parent=y;
        }
        x->parent=y->parent;                // �Nx��parent���V���y��parent
                                            // �H�U�@��if-else�N�ק���y��parent��child
        if(y->parent==NULL){                     // �Yy����Oroot, x�N�����s��root
            root=x;
        }
        else if(y==y->parent->right) {      // �Y���y�O��parent��leftchild,
            y->parent->right=x;             // x�N������s��parent��leftchild
        }
        else {                              // �Y���y�O��parent��rightchild,
            y->parent->left=x;              // x�N������s��parent��rightchild
        }
        x->right=y;                         // �Ny�]��x��rightchild
        y->parent=x;                        // �Nx�]��y��parent
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

//      ���򱡪p�ݭn��RBT ���ץ��H
//      ��s�Wnode���b���⪺node��child pointer�A�Φ�����P����۳s�ɡC
//
//      Case1�Guncle�O����A���׷s�W��node�Onode(X)��leftchild��rightchild�F
//      Case2�Guncle�O�¦�A�ӥB�s�W��node��node(X)��rightchild�F
//      Case3�Guncle�O�¦�A�ӥB�s�W��node��node(X)��leftchild�C

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

//    Case1�Gsibling������F
//    Case2�Gsibling���¦�A�ӥBsibling�����child���O�¦�F
//    Case3�Gsibling���¦�A�ӥBsibling��rightchild�O�¦�Aleftchild�O����F
//    Case4�Gsibling���¦�A�ӥBsibling��rightchild�O����C

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
