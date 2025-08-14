#include <iostream>

using namespace std;

struct Node
{
	int item = 0;	  
	Node* next = nullptr;

	friend ostream& operator<<(ostream& os, const Node& n)
	{
		cout << n.item << " " << flush;
		return os;
	}
};

void RecurPrint(Node* node)
{
	    //재귀
        if(node-> next != nullptr){
        node = node-> next;
        RecurPrint(node);
        }
        else{
           cout<<node->item <<endl;
        }
        
}

void IterPrint(Node* node)
{
	// TODO:
}

int main()
{
	// ListArray와 비교

	Node* first = nullptr;
	first = new Node;
	first->item = 1;
	first->next = nullptr;

	Node* second = nullptr;
	second = new Node;
	second->item = 2;
	second->next = nullptr;

	Node* third = nullptr;
	third = new Node;
	third->item = 3;
	third->next = nullptr;

	Node* fourth = nullptr;
	fourth = new Node;
	fourth->item = 4;
	fourth->next = nullptr;

	Node* fifth = nullptr;
	fifth = new Node;
	fifth->item = 5;
	fifth->next = nullptr;

	// 계속 추가 가능
/*
	cout << *first << endl;
	cout << *second << endl;
	cout << *third << endl;
	cout << *fourth << endl;
	cout << *fifth << endl;
	cout << endl;
*/
	//연결 관계 만들어 주기
	first->next = second;
    second->next = third;
    third->next = fourth;
    fourth->next = fifth;
    fifth->next = nullptr;
	
	// 마지막
	//cout << *(first) << endl;
	//cout << *(first->next) << endl;
	//cout << *(first->next->next) << endl;
	//cout << *(first->next->next->next) << endl;
	//cout << *(first->next->next->next->next) << endl;
	// cout << *(first->next->next->next->next->next) << endl; // 오류

	//cout << endl;
	{
		Node* current = first;//current 라는 노드 타입의 포인터는 first의 주소를 향한다.
		cout << *current << endl;//여기서는 first의 아이템 1을 출력.
       
        while(current->next != nullptr ){// 뭘 내가 잘못했을까. 흠......음....'\0' == char 타입이다. NULL
            current = current->next;
        }
		cout << current->item << endl;
	}

	// 재귀 호출 이용
	RecurPrint(first);
	cout << endl; 

	/* 반복문 이용
	IterPrint(first);
	cout << endl;

*/

/* 
    Node * temp = first;
	for(int i =0; i<5; i++){
        Node * totemp = temp;
        temp= temp->next;
        delete totemp;
    }
*/


Node * current = first;
while(current){
	Node* temp = current;

	current= current->next;
	delete[] temp;
}

	return 0;
}