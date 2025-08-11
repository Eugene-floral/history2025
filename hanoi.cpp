#include <iostream>
#include "Stack.h"

using namespace std;

Stack<char> tower[3];

void PrintTowers()
{
	cout << "Towers" << endl;
	cout << "0: ";
	tower[0].Print();
	cout << "1: ";
	tower[1].Print();
	cout << "2: ";
	tower[2].Print();
}

// 실제로 디스크를 움직여서 스택들을 업데이트
void MoveDisk(int from, int to) 
{
	if (tower[from].IsEmpty())
	{
		cout << "Tower " << from << " is empty." << endl;
		exit(0); // 오류 강제 종료
	}

	auto disk = tower[from].Top(); //disk에 타워[from]의 top에 있는 걸 복사해서 집어넣음.

	// 받을 타워가 비어 있으면 뭐든지 받을 수 있음
	// 알파벳 순서여야 받을 수 있음 (역순 X)
	if (!tower[to].IsEmpty() && tower[to].Top() > disk)//만약 tower[to]에 있는 함수가 비어있지 않고 디스크에 있는 수보다 그 값이 크다면 
	{
		cout << "Cannot place " << disk << " on " << tower[to].Top() << endl;
		exit(0); // 오류 강제 종료
	}
//안되고 종료
	tower[from].Pop(); //디스크로 저장된 Top 숫자는 원래있던 곳에서 사라지고
	tower[to].Push(disk); //to타워에 삽입됨

	cout << "Move disk" << disk << " from " << from << " to " << to << endl;
	PrintTowers();

}

void RecurMoveDisks(int n, int from , int temp , int to){
	//재귀라고 했으니까 일단 똑같은 거 하나 넣어줘.

	if( n == 1 ){
		MoveDisk(from, to);
	}
	
	RecurMoveDisks(n -1 ,from ,to ,temp);
	
	MoveDisk(from,to); // 뭐든지 가고자 하는 방향이 정해져 있다는 점.

	RecurMoveDisks(n - 1 ,temp, from ,to);
}

int main()
{
	int num_disks = 4;

	for (int i = 0; i < num_disks; i++)
		tower[0].Push('A' + i);// abc걸랑.

	PrintTowers();

	//MoveDisk(0, 2); // <- 디스크 하나만 움직이는 함수 tower 0 -> tower 2

	RecurMoveDisks(num_disks, 0, 1, 2);//n개의 문자가 이 타워 안에 들어있어. 그리고 0타워에서 2타워로 모두 옮길거야.
    // 그런데 1이라는 타워에 n-1개의 문자를 알파벳 순서대로 집어넣을 거란다.이 함수는 n-1개의 문자가 1타워에 들어가있고 나서 사용할수 있다.
//그런데 만약 4개
	return 0;
}