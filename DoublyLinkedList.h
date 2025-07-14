#pragma once

#include <cassert>
#include <stdint.h>
#include <algorithm>
#include <iostream>

using namespace std;

template<typename T>
class DoublyLinkedList
{
public:
	struct Node
	{
		T item = T();

		Node* left = nullptr;//next 대신.
		Node* right = nullptr;//next 대신.
	};

	DoublyLinkedList()
	{
	}
    //이니셜라이즈 리스트

	~DoublyLinkedList()
	{
		Clear();
	}//소멸자

	void Clear() // 모두 지워야(delete) 합니다.
	{
		Node* current = first_;

        while(current -> left != nullptr){
            current = current -> left;
        }

        while(current != nullptr){
            Node* temp = current;
            current = current -> right;
            delete temp;
        }
	}

	bool IsEmpty()
	{
        if(first_) return false;
        return true;
	}

	int Size()
    {
		int size = 0;

        Node* cur = first_;  //맨 왼쪽

        while(cur -> right != nullptr){
            cur = cur -> right; 
            size++;   //오른쪽으로 가면서 전체 개수 세기
        }

		return size + 1;
	}

	void Print()
	{
		using namespace std;

		Node* current = first_; //3 

		if (IsEmpty())
			cout << "Empty" << endl;
        
        else
		{
			cout << "Size = " << Size() << endl;
			cout << " Forward: ";              // forward로 출력이 되려면 12345

            while(current -> right != nullptr){

            cout << current -> item<<' '; // 3                       
            current = current -> right;                     

            }
            cout << current -> item<<' ';// 4
			cout << endl;//current 는 오른쪽 끝에 도달함.

			cout << "Backward: "; // backward로 출력이 되려면 54321 이렇게 나와야 한다.

            while(current->left != nullptr){
                cout << current -> item<<' ';// 4 3
                current = current -> left; //
            }
			cout << current -> item<<' ';
            cout << endl;
		}
	}

	Node* Find(T item)
	{
        Node* current = first_;

        while(current && current->item != item){
            current = current->right;
        }
        
        return current;

	}

	void InsertBack(Node* node, T item)
	{
		if (IsEmpty())
		{
			PushBack(item);
		}
		else
		{
			Node* current = first_-> right;
            Node* prev = first_;
            
            while(prev-> item != node-> item){

            prev = current;
            current = current -> right;
                
            }                                          //node = prev, node-> right =current

            prev-> right = new Node;  
            Node * temp = prev -> right;               // 노드 다음 새로운 공간 창출;

            temp -> item = item;
                        
            temp -> right = current;                     //오른쪽 잇고
            current ->left = temp;
            temp -> left = prev;                         //왼쪽 잇고.
		}
	}

	void PushFront(T item)
	{
        Node* current = first_;

        if(IsEmpty()){

        first_ = new Node;

        first_ -> item = item;
        first_ ->right = nullptr;
        first_ -> left = nullptr;
        
        return; 
        }

		else
        {
        current -> left = new Node;
        
        Node* temp = current -> left;

        temp -> item = item;

        temp -> left = nullptr;

        temp-> right = current;

        first_ = temp;

        }
    }

	void PushBack(T item)
	{
        if(IsEmpty()){

        first_ = new Node;

        first_ -> item = item;
        first_ ->right = nullptr;
        first_ -> left = nullptr;
        
        return; 
        }

		Node* current = first_;// 3이 first_

        while(current -> right != nullptr){//만약에 오른쪽이 비지 않았다면 

        current = current-> right;//맨 오른쪽 까지 가.
        }//맨 오른쪽 노드 을 찾은거 아냐.

        current -> right = new Node;
        Node * temp = current-> right;

        temp-> item = item;
        temp-> right = nullptr;

        temp -> left = current;
    
	}

	void PopFront()
	{
		if (IsEmpty())
		{
			using namespace std;
			cout << "Nothing to Pop in PopFront()" << endl;
			return;
		}
		assert(first_);

        Node* current = first_;//nullptr;
        Node* prev = first_ -> right;

        delete current;
        prev-> left = nullptr;
        
        prev = first_;
	}

	void PopBack()
	{
		if (IsEmpty())
		{
			using namespace std;
			cout << "Nothing to Pop in PopBack()" << endl;
			return;
		}

		Node* current = first_ -> right;
        Node* prev = first_;

        while(current -> right != nullptr){
            prev = current;
            current = current -> right;
        }

        delete current;
        prev -> right = nullptr;
		
	}

	void Reverse()
	{ //forward 1 2 3 4 가  4 3 2 1 이 됨 그러니까 1->right가 2여야 하는데 1->left가 2가 되는 거지.

		Node* current = first_; // 1임. 1->left는 2임. 근데 이걸 first-> left = prev이런 식인 거지.
        Node* temp = nullptr; // prev는 2임.

        while(current){

            temp = current -> left;//
            current -> left = current ->right;
            current-> right = temp;
            current = current -> left;
        }
        if (temp) {
        first_ = temp->left;
        first_->left = nullptr;
        }

    }

	T Front()
	{
		assert(first_);
        cout << first_->item; 
	}

	T Back()
	{
		assert(first_);

		Node* current = first_;

        while(current-> right != nullptr){
            current = current-> right;
        }
        return current->item;
	}

protected:
	Node* first_ = nullptr;
};