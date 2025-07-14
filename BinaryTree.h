#pragma once
#include <algorithm>
#include <iostream>
#include <fstream>
#include <string> // BinaryTree 출력

#include "Queue.h"
#include "Stack.h"

template<typename T>
class BinaryTree
{
public:
	struct Node
	{
		T item = T();
		Node* left = nullptr; // Left child
		Node* right = nullptr; // Right child
	};

	// 디버깅 도구: 큐에서 주소 대신에 아이템 출력
	class MyQueue : public Queue<Node*> // Queue<node*>를 참조하여 사용함.
	{
	public:
		void Print()
		{
			using namespace std;//이건 큐잖아. front_는 null이니까 그 뒤에걸 출력 인데 capa로 나눠야 원형으로 돌아감. 쨋든 여기부터, i는 rear_ + 1;

			for (int i = (this -> front_ + 1) % this -> capacity_ ; i != (this-> rear_ + 1) % this  -> capacity_; i = (i + 1) % this -> capacity_)
				cout << this -> queue_[i] -> item << " ";
			cout << endl;
		}
	};

	// 디버깅 도구: 스택에서 주소 대신에 아이템 출력
	class MyStack : public Stack<Node*>
	{
	public:
		void Print()
		{
			using namespace std;

			for (int i = 0; i < this->Size(); i++)
				cout << this->stack_[i]->item << " ";
			cout << endl;
		}
	};

	BinaryTree() {}

	BinaryTree(Node* root)
	{
		root_ = root;
	}

	bool IsEmpty()
	{
		return root_ == nullptr;
	}

	void Visit(Node* node)
	{
		using namespace std;
		cout << node->item << " "; // 수행하고 싶은 작업 구현(여기서는 출력)
	}//visit 을 하면 접근한 노드의 값을 출력한다.

	int Sum()
	{
		return Sum(root_); 
	}

	int Sum(Node* node)//node 는 루트임.

	{
        if(node == nullptr) return 0;

        Node *cur = root_;
            
		return node->item + Sum(node-> left) + Sum(node-> right);
	}
    // 굳 아주 잘했으.

	int Height()
	{
		return Height(root_);
	}// 전체 높이 구하기.

	int Height(Node* node)  // 교수님께서 이걸 원하진 않았을 것 같다. 왜냐하면 헤더파일에 algorithm이 없어.
	{
        if( node == nullptr) return 0;

        int left = Height(node-> left);
        int right = Height(node-> right);

        return 1 + fmax(left,right);
//몰겠다.
	}

	~BinaryTree()
	{
		DeleteTree(root_);
	}

	void DeleteTree(Node* node)
	{
		using namespace std;

		if(node){

		if(node == nullptr) return;
		
		Postorder(node -> left);
		Postorder(node -> right);

		delete node;
		}
	}

	void Preorder() { Preorder(root_); }
	void Preorder(Node* node)//6 2 1 3 5 4 
	{
		using namespace std;

		if(node == nullptr) return;

		cout << node -> item << ' ';

		Preorder(node-> left);
		Preorder(node-> right);
	}

	void Inorder() { Inorder(root_); }
	void Inorder(Node* node)
	{
		using namespace std;

		if(node-> left != nullptr){
		Inorder(node -> left);
		}
		cout<< node -> item <<' ';
		if(node ->right!= nullptr){
		Inorder(node-> right);
		}
	}

	void Postorder() { Postorder(root_); }
	void Postorder(Node* node) // 3 1 2 4 5 6
	{
		using namespace std;

		if(node == nullptr) return;
		
		Postorder(node -> left);
		Postorder(node -> right);

		cout<< node-> item<<' ';
	}

	void LevelOrder()
	{
		using namespace std;
		//Queue<Node*> q
		MyQueue q;

		Node* current = root_;

		while(current)   // current가 null이 아닐 경우까지 반복한다.
		{
			Visit(current);
		
			if(current -> left) q.Enqueue(current-> left);
			if(current -> right) q.Enqueue(current-> right);
			if(q.IsEmpty()) return;

			cout << endl;
			cout << "Queue: ";
			q.Print();

			current = q.Front();
			q.Dequeue();
		}	
	}	
	void IterPreorder()
	{
		using namespace std;

		if (!root_) return;

		MyStack s;
		Node* current = root_;

		s.Push(root_);

		while (!s.IsEmpty())
		{
			current = s.Top();
			Visit(current);// 6 , 2 , 1 , 3 ,5, 4
			cout<<endl;
			cout<< "Stack :";
			s.Print();//6,  5 2, 5 3, 5
			s.Pop();///null, 2, 1, 3, 5
			if(current -> right) s.Push(current-> right); // 5, 3 ,4
			if(current -> left) s.Push(current-> left);//2, 1
		}
	}

	void IterInorder()
	{
		using namespace std;
		if (!root_) return;

		MyStack s;

		Node* current = root_;
		
		while (current || !s.IsEmpty())
		{
			while(current){
				s.Push(current);
				current = current -> left;
			}
			current = s.Top();
			Visit(current);
			cout<< endl;
			cout<< " Stack: ";
			s.Print();

			s.Pop();//current 를 널로 만드는건가?
				
			current = current -> right;
		}
	}

	void IterPostorder()
	{
		using namespace std;
		if (!root_) return;

		MyStack s1, s2;
		s1.Push(root_);
		Node* current = root_;
//일단 왼쪽 노드 루트 빼고 나머지를 
		while (!s1.IsEmpty())
		{
			current = s1.Top(); // 6 5 4 2 1 3
			
			s2.Push(current);//  6 5 
			s1.Pop(); //  null, null, 
			if(current -> left ) s1.Push(current->left);   // 1 
			if(current -> right ) s1.Push(current-> right); // 
		}

		while (!s2.IsEmpty())
		{ // 6 5 4 2 1 3
			Visit(current);
			cout<< endl;
			cout<< "Stack: ";
			s2.Print();

			s2.Pop(); // 3
			current = s2.Top(); // 1
		}
	}

	void Print2D();
	void PrintLevel(int n);
	void DisplayLevel(Node* p, int lv, int d);

protected:
	Node* root_ = nullptr;
};

// 디버깅 편의 도구
// https://stackoverflow.com/questions/36802354/print-binary-tree-in-a-pretty-way-using-c
template<typename T>
void BinaryTree<T>::Print2D()
{
	using namespace std;
	int i = 0;
	while (i < Height()) {
		PrintLevel(i);
		i++;
		cout << endl;
	}
}

template<typename T>
void BinaryTree<T>::PrintLevel(int n) {
	using namespace std;
	Node* temp = root_;
	int val = (int)pow(2.0, Height() - n + 1.0);
	cout << setw(val) << "";
	DisplayLevel(temp, n, val);
}

template<typename T>
void BinaryTree<T>::DisplayLevel(Node* p, int lv, int d) {
	using namespace std;
	int disp = 2 * d;
	if (lv == 0) {
		if (p == NULL) {
			cout << "   ";
			cout << setw(disp - 3) << "";
			return;
		}
		else {
			int result = ((p->item <= 1) ? 1 : (int)log10(p->item) + 1);
			cout << " " << p->item << " ";
			cout << setw(static_cast<streamsize>(disp) - result - 2) << "";
		}
	}
	else
	{
		if (p == NULL && lv >= 1) {
			DisplayLevel(NULL, lv - 1, d);
			DisplayLevel(NULL, lv - 1, d);
		}
		else {
			DisplayLevel(p->left, lv - 1, d);
			DisplayLevel(p->right, lv - 1, d);
		}
	}
}