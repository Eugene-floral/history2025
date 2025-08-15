#pragma once

#include <cassert>
#include <stdint.h>
#include <iostream>

using namespace std;
template<typename T>
class SinglyLinkedList
{
public:
	struct Node
	{
		T item = T();
		Node* next = nullptr; //클래스 내 구조체.
	};

	SinglyLinkedList()//이니셜라이저 리스트. 
	{
	}

	SinglyLinkedList(const SinglyLinkedList& list)//복사 생성자.
	{
		
		if(list.first_ == nullptr){return;}

			first_ = new Node; 
			first_->item = list.first_->item; // 첫번째 값 복사함.

			Node * src = list.first_->next;
			Node * dest = first_;// 왜 이렇게 쓰는지 이해해야 함 first는 머리를 향하는 것인데 first에 겹치게 쓸수는 없음.
			//왜 src는 ->next인데 dest는 ->next가 아닌가?라 한다면 first_는 새로 만드는 곳인데,
			//다음 노드는 만들어줘야함 아직 없음.
			// 그래서 반복문 안에 집어넣어서 만드는것!

			while(src){ //src가 널을 가르키지 않을 동안
				dest-> next = new Node;
				dest = dest-> next;//다음 포인터로 dest설정.
				dest-> item = src-> item;//이미 다음값을 가르키는 src의 아이템 복사 dest에
				src = src-> next;//그 다음으로 보냄.
			}
		}

	~SinglyLinkedList()
	{
		Clear();
	}

	void Clear() // 모두 지워야(delete) 합니다.
	{
		Node* cur = first_;

		while(cur){
			Node* temp = cur;// 첫번째 노드 포인터 저장
			cur = cur ->next; //다음 포인터를 가르킴
			delete temp;//지워 반복.
		}
	}

	bool IsEmpty()
	{
		return first_ == nullptr;
	}

	int Size()
	{
		int size = 0;
			Node *cur = first_;
			while(cur){

			cur = cur ->next;
			size++;
			}

			return size  ;//맨 처음 값은 세지 않음.
	}

	T Front()
	{
		assert(first_);//first !=nullptr
		
		return first_->item;
	}

	T Back()
	{
		assert(first_);

		Node *cur = first_;
		// 1 2 n 
		while(cur->next != nullptr){
		cur = cur->next;
		}

		return cur->item;
	}

	Node* Find(T item)
	{
		Node *cur = first_;
		while(cur){
			if(cur->item == item){
				return cur;
			}
			else{ 
				cur= cur->next;
			}
		}
		return nullptr;
	}

	void InsertBack(Node* node, T item)//뒤에 갖다 붙이기.
	{
		//포인터를 준 이유는 포인터 
		if(node->next != nullptr ){
		Node* al = node->next;//원래 그 노드 뒤의 노드를 저장.

		node->next = new Node;// 공간 할당.//노드 뒤에 새로운 노드 공간을 만들고.
		Node* t = node->next;//만약에 node 값이

		t->item = item;
		t->next = al;
		}
	}

	void Remove(Node* n) //temp를 집어넣잖아 근데 1 2 3 50 1000 이거잖어.
	{
		assert(first_);

		Node *cur = first_;
		Node *real = n->next;

		while(cur-> next != n){ //만약에 cur의 다음이 n이면 멈춰, 그러면 n바로 전 노드의 값이 cur애 둘어가지 않겠어요?
			cur = cur -> next;
			}
			delete  n;// cur은 n바로 전 노드이고. 그 노드와 real 과 연결하면 되잖아.
			cur-> next = real;
		}
		
	void PushFront(T item)//기존의 first_를 얘가 먹는겨. 그러면 어떻게?
	{
		
		if(first_){
			Node* newfirst = new Node;
			newfirst->item = item;
			newfirst->next = first_;
			first_ = newfirst;
		}
		else{// null이야.
			first_ = new Node;
			first_-> item = item;
		}
		
	}

	void PushBack(T item)
	{
		if (first_)
		{
			Node *cur = first_;
			while(cur->next != nullptr ){ //cur이 널이 아닐 경우까지 반복 결국 cur=null
				cur = cur-> next;
			}
			cur-> next = new Node;

			Node* newtail = cur ->next;
			
			newtail-> item = item;
			newtail-> next =nullptr;
			
		}
		else
		{
			first_ = new Node;
			first_-> item = item;
			first_->next =nullptr;

		}
	}

	void PopFront()
	{
		if (IsEmpty())
		{
			
			cout << "Nothing to Pop in PopFront()" << endl;
			return;
		}

		if(first_){
		Node* temp = first_ ->next;
		delete first_;
		first_ = temp;
		}
	}

	void PopBack()
	{
		if (IsEmpty())
		{
			cout << "Nothing to Pop in PopBack()" << endl;
			return;
		}//그러니까 cur을 지워도 그전 포인터는 cur을 계속해서 가르키고 있다는 점.

		//따라서 그 전 노드가 가르킬 공간을 만들어 줘야 한다는 건가?
		Node* prev = first_;//prev는 cur임.
		Node* cur = first_->next;//cur은 first-의 다음 노드를 가리킴.
		
		while(cur->next != nullptr){//만약 first의 다음 노드의 다음이 null이 아니라면 
			prev =cur;//first는 그다음 노드가 되고 .
			cur = cur->next;//또 하나 건너
		}
		delete cur;
		prev->next = nullptr;
 
		
	}

	void Reverse()
	{
		if(first_ == nullptr) return ;

		Node *prev = nullptr;
		Node *cur = first_;
		
		while(cur != nullptr){
			Node * nxt = cur-> next; //cur의 다음 노드 기억.
			cur-> next = prev;

			prev = cur;
			cur = nxt;
		}

		first_ = prev ;

		//처음은 cur이라고 설정하는 거지./cur의 다음 노드는 nullptr임.
	}

	void SetPrintDebug(bool flag)
	{
		print_debug_ = flag;
	}

	void Print()
	{
		Node* current = first_;

		if (IsEmpty())
			cout << "Empty" << endl;
		else
		{
			cout << "Size = " << Size() << " ";

			while (current)
			{
				if (print_debug_)
				{
					//cout << "[" << current << ", " << current->item << ", " << current->next << "]";

					// 주소를 짧은 정수로 출력 (앞 부분은 대부분 동일하기때문에 뒷부분만 출력)
					cout << "[" << reinterpret_cast<uintptr_t>(current) % 100000 << ", "
						<< current->item << ", "
						<< reinterpret_cast<uintptr_t>(current->next) % 100000 << "]";
				}
				else
				{
					cout << current->item;
				}

				if (current->next)
					cout << " -> ";
				else
					cout << " -> NULL";

				current = current->next;
			}
			cout << endl;
		}
	}

protected:
	Node* first_ = nullptr;

	bool print_debug_ = false;
};