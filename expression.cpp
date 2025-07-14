#include <iostream>

#include "Stack.h"
#include "Queue.h"
#include "BinaryTree.h"

using namespace std;

// Function to return precedence of operators
int Prec(char c);
void InfixToPostfix(Queue<char>& q, Queue<char>& output);
int EvalPostfix(Queue<char>& q);

class ExpressionTree : public BinaryTree<char>
{
public:
	typedef BinaryTree<char> Base;

	ExpressionTree(Node* root) : Base(root) {}// 생성자이다.

	bool IsDigit(char c) //함수
	{//     if (!IsDigit(node->item)) cout << "(";
		if (c >= '0' && c <= '9') return true;
		else return false; // 0 부터 9까지의 숫자면 진실.
	}

	int Evaluate() // 함수
	{
		return Evaluate(Base::root_); // 계산, 헤더 파일의 포인터인 root_를 사용한다.
	}

	int Evaluate(Node* node)// 루트 부터 시작함.//ㅎㅁ수
	{
        // ( 5 + ( ( 3 - 2 ) * 4 ) ) 

    if (node->item >= '0' && node->item <= '9')
        return node->item - '0';
    else if (node->item == '*')
        return Evaluate(node->left) * Evaluate(node->right);
    else if (node->item == '+')
        return Evaluate(node->left) + Evaluate(node->right);
    else if (node->item == '-')
        return Evaluate(node->left) - Evaluate(node->right);
    else // '/'
        return Evaluate(node->left) / Evaluate(node->right);
        
}
	void Infix() { Infix(root_); cout << endl; }
	void Infix(Node* node) {
        if(node) return;
        if(!IsDigit(node-> item)) cout<<'('; 
        Infix(node-> left);

        cout<< node-> item;
        
        Infix(node-> right);
        if(!IsDigit(node-> item)) cout<<')'; 
    }

	void Postfix() { Postfix(root_);  cout << endl; }
	void Postfix(Node* node) {
		if(node) return;
        Postfix(node-> left);
        Postfix(node-> right);
        cout<<node-> item;
	}

	// Infix -> postfix -> expression tree
	ExpressionTree(const char* infix)  // 이건 infix로 중위표기식으로 표현된 문자열을 받아서 트리를 만드는 함수이다.
	{
		// Infix -> Postfix (예제 재사용)

		Queue<char> q; //infix로 표현한 수식을 postfix로 바꿔야 겠지??
		
        for (int i = 0; infix[i] != '\0'; i++) 
			q.Enqueue(infix[i]); //q에 수식을 전부 집어넣어라.
		
        cout << "  Infix: ";
		q.Print();                  // infix는 (5 +((3-2)* 4))로 들어갔을 것.
		
        Queue<char> postfix;        // postfix 라는 큐를 새로 만듦.
		InfixToPostfix(q, postfix);// 532-4*+ 이렇게 만들었다는 소리임.
		
        cout << "Postfix: ";

        postfix.Print();//Postfix로 만들면 532-4*+ 이렇게 됩니다.fifo;

		// Postfix -> Expression tree 이제 이 postfix로 트리를 만들어볼거에용~~~ 이 소리임.

		Stack<Node*> s;// 스택을 하나 만듭니다.

		while (!postfix.IsEmpty())//postfix 안의 큐가 전부 사라질때까지 반복한다.
		{
			char c = postfix.Front();  //   532-4*+ 
			postfix.Dequeue();// 그리고 큐에서는 삭제.

			if (c >= '0' && c <= '9' ) // 만약 5가 여기 안의 수야 그렇다면??  532-4*+
			{
				Node* leaf = new Node{c , nullptr, nullptr};
				
				s.Push(leaf);
			}       // 5 3 2 순으로 집어 넣어져 있음. stack에 그리고 -를 만났음. 그렇다면? 
			else
			{
				Node* right = s.Top(); s.Pop();// 그렇지 사실은 이렇게 되어야 연산자들도 자식 노드가 될수가 있어.
				Node* left = s.Top(); s.Pop();
				Node* parent = new Node{c ,left ,right}; //아예 공간 할당을 새로 해야 하네.. 싸발.이 생각을 아예 못함
				s.Push(parent);
			}
		}

		root_ = s.Top();// 이걸로 미루어보았을 때, root는 +가 되어야 겠지?? 
	}
};// 결괏값을 예측 해보자 s라는 스택의   5+

int main()
{
	using Node = ExpressionTree::Node;

	// 5 + (3 - 2) * 4
	// 
	//    +
	//	/   \
	// 5     *
	//	    / \
	//	   -   4
	//	  / \
	//	 3   2

	Node* n1 = new Node{ '5', nullptr, nullptr };
	Node* n2 = new Node{ '+', nullptr, nullptr };
	Node* n3 = new Node{ '3', nullptr, nullptr };
	Node* n4 = new Node{ '-', nullptr, nullptr };
	Node* n5 = new Node{ '2', nullptr, nullptr };
	Node* n6 = new Node{ '*', nullptr, nullptr };
	Node* n7 = new Node{ '4', nullptr, nullptr };

	// +
	n2->left = n1; // 5
	n2->right = n6; // *

	// *
	n6->left = n4; // -
	n6->right = n7; // 4

	// -
	n4->left = n3; // 3
	n4->right = n5; // 2

	ExpressionTree tree(n2);

	tree.Print2D();

	// 수식 트리에 저장되어 있는 수식을 실제로 계산해서 그 결과를 출력합니다.
	cout << "Evaluated = " << tree.Evaluate() << endl; // Evaluated = 9

    // 수식 트리에 저장되어 있는 수식을 Infix 방식으로 출력합니다.
	cout << "  Infix: ";
	tree.Infix();   // (5+((3-2)*4)) <- 출력 예시

	// 수식 트리에 저장되어 있는 수식을 Postfix 방식으로 출력합니다.
	cout << "Postfix: ";
	tree.Postfix(); // 532-4*+ <- 출력 예시

	cout << endl;

	// Infix -> Postfix -> Expression Tree
	{
		// const char infix[] = "1+(1*2+3)*4";
		const char infix[] = "(5+((3-2)*4))";

		// 생성자에서 문자열로 입력받은 수식을 내부적으로 Infix -> Postfix 과정을 거쳐 트리로 저장합니다.
		ExpressionTree tree(infix);

		tree.Print2D();

		// 수식 트리에 저장되어 있는 수식을 실제로 계산해서 그 결과를 출력합니다.
		cout << "Evaluated = " << tree.Evaluate() << endl; // Evaluated = 9
	}

	return 0;
}

// Function to return precedence of operators
int Prec(char c)
{
	if (c == '/' || c == '*')
		return 2;
	else if (c == '+' || c == '-')
		return 1;
	else
		return -1;  // '('는 우선순위가 아주 낮은 것으로 처리
}

void InfixToPostfix(Queue<char>& q, Queue<char>& output)
{
	Stack<char> s; // 우선순위가 낮은 연산을 보류하기 위한 스택

	output.SetDebugFlag(false);

	while (!q.IsEmpty())
	{
		char c = q.Front();
		q.Dequeue();

		//cout << c << endl;

		if (c >= '0' && c <= '9') // 숫자(피연산자)라면 output에 추가
			output.Enqueue(c);
		else if (c == '(') // 여는 괄호라면 스택에 추가
			s.Push(c);
		else if (c == ')') // 닫는 괄호를 만나면
		{
			// 여는 괄호 전까지를 스택에서 꺼내서 출력에 넣기
			while (s.Top() != '(')
			{
				output.Enqueue(s.Top());
				s.Pop();
			}
			s.Pop(); // 여는 괄호 제거
		}
		else // 연산자를 만나면
		{
			// 스택에서 c보다 우선순위가 높거나 같은 것들을 꺼내서 추가
			while (!s.IsEmpty() && Prec(c) <= Prec(s.Top()))
			{
				output.Enqueue(s.Top());
				s.Pop();
			}

			// c는 스택에 추가
			s.Push(c);
		}

		//cout << "Stack: ";
		//s.Print();
		//cout << "Output:";
		//output.Print();
		//cout << endl;
	}

	// 스택에 남아있는 것들을 모두 추가
	while (!s.IsEmpty())
	{
		output.Enqueue(s.Top());
		s.Pop();
	}
}

int EvalPostfix(Queue<char>& q)
{
	Stack<int> s;

	while (!q.IsEmpty())
	{
		char c = q.Front();
		q.Dequeue();

		//cout << c << endl;

		if (c != '+' && c != '-' && c != '*' && c != '/')
		{
			s.Push(c - '0'); // 입력이 연산자가 아니면 일단 저장
		}
		else
		{
			//cout << "Operator: " << c << endl;

			// 입력이 연산자이면 스택에서 꺼내서 연산에 사용
			int op2 = s.Top(); // op1, op2 순서 주의
			s.Pop();
			int op1 = s.Top();
			s.Pop();

			if (c == '+') {
				s.Push(op1 + op2);
			}
			else if (c == '-') {
				s.Push(op1 - op2);
			}
			else if (c == '*') {
				s.Push(op1 * op2);
			}
			else if (c == '/')
			{
				s.Push(op1 / op2);
			}
			else
			{
				cout << "Wrong operator" << endl;
				exit(-1); // 강제 종료
			}
		}

		//cout << "Stack: ";
		//s.Print();
	}

	return s.Top();
}