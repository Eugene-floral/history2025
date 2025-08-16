#pragma once

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
	class MyQueue : public Queue<Node*>
	{
	public:
		void Print()
		{
			using namespace std;

			for (int i = (this->front_ + 1) % this->capacity_; i != (this->rear_ + 1) % this->capacity_; i = (i + 1) % this->capacity_)
				cout << this->queue_[i]->item << " ";
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
	}

	int Sum()
	{
		return Sum(root_);
	}

	int Sum(Node* node)
	{
        if(!node) return 0;
        // 자 일단 재귀는 확정적임 왜냐하면 변수를 쓰면 계속해서 초기화가 되어버려
        return node-> item + Sum(node-> left) + Sum(node-> right);
	}

	int Height()
	{
		return Height(root_);
	}

	int Height(Node* node)
	{
        if(!node) return 0;

        int left = Height(node->left);
        int right = Height(node-> right);

		return 1 + fmax(left,right);
	}

	~BinaryTree()
	{
		DeleteTree(root_);
	}

	void DeleteTree(Node* node)
	{
		if (node)
		{
			if(node-> left) DeleteTree(node-> left);
			if(node-> right) DeleteTree(node-> right);
			delete node;
		}
	}

	void Preorder() { Preorder(root_); }
	void Preorder(Node* node)
	{
        using namespace std;

        Visit(node);
		if(node-> left)  Preorder(node-> left);
		if(node-> right) Preorder(node-> right);
	
	};

	void Inorder() { Inorder(root_); }
	void Inorder(Node* node)
	{
        
		if(node-> left)  Inorder(node-> left);
        Visit(node);
		if(node-> right) Inorder(node-> right);
	}

	void Postorder() { Postorder(root_); }
	void Postorder(Node* node)
	{
        
		if(node-> left)  Postorder(node-> left);
		if(node-> right) Postorder(node-> right);
        Visit(node);
        
	}

	void LevelOrder() //레벨 오더란?? level에 맞게끔 출력.
	{

		MyQueue q;
		Node* current = root_;

		while (current)
		{
			Visit(current);
            if(current-> left) q.Enqueue(current-> left); // 2
            if(current-> right)q.Enqueue(current-> right);// 2 5
            
            if(!q.IsEmpty()) current = q.Front();
            else current = nullptr;
            q.Dequeue();
		}
	}

	void IterPreorder()
	{
		if (!root_) return;
        Node* current = root_;
		MyStack s; // 힌트: MyStack q;
		s.Push(root_);

		while (!s.IsEmpty())
		{
            s.Pop();//null 5

            Visit(current);// 6 
            if(current-> right) s.Push(current-> right);// 5 
            if(current-> left)  s.Push(current-> left);//  5 2

            if(!s.IsEmpty()) current = s.Top(); // 2
        }
	}

	void IterInorder()
	{
		if (!root_) return;

		MyStack s;

		Node* current = root_;
		while (current || !s.IsEmpty())
		{
            while(current){
                s.Push(current);//6 2 1
                current = current-> left; 
            }// null 
            current = s.Top(); // 1 3 
            Visit(current); // 1 3
            s.Pop();   // 6 2 
             
            current = current-> right; // 3
            
		}
	}

	void IterPostorder()
	{
		if (!root_) return;
        Node* current = root_;

		Stack<Node*> s1, s2;
		s1.Push(root_);

		while (!s1.IsEmpty())
		{
            s2.Push(current);//6 5 4 2 1 3
            s1.Pop();//null
            if(current -> left) s1.Push(current-> left);// 
            if(current -> right)s1.Push(current-> right);// 3
            current = s1.Top();// 3
            
		}

		while (!s2.IsEmpty())
		{
			current = s2.Top();
            Visit(current);
            s2.Pop();
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