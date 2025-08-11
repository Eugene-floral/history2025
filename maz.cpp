#include <iostream>

#include "Stack.h"

using namespace std;

constexpr int kNumRows = 10;    // 10행
constexpr int kNumCols = 9;     // 9열.

char maze[kNumRows][kNumCols] =
{
	{'1', '1', '1', '1', '1', '1', '1', '1', '1'},
	{'1', 'S', '0', '0', '0', '0', '0', '0', '1'},
	{'1', '1', '1', '1', '0', '1', '0', '1', '1'},
	{'1', '0', '0', '0', '0', '0', '0', '0', '1'},
	{'1', '0', '1', '1', '1', '1', '1', '1', '1'},
	{'1', '0', '0', '0', '0', '0', '0', '0', '1'},x
	{'1', '1', '1', '1', '1', '0', '1', '1', '1'},
	{'1', '1', '1', '0', '0', '0', '1', '0', '1'},
	{'1', '0', '0', '0', '0', '0', '0', 'G', '1'}, // <- 'G'를 만나면 종료
	{'1', '1', '1', '1', '1', '1', '1', '1', '1'},
};

void PrintMaze()
{
	for (int j = 0; j < kNumRows; j++)
	{
		for (int i = 0; i < kNumCols; i++)
			cout << maze[j][i] << " ";
		cout << endl;
	}
}

struct Pos // 구조체명인 pos로 한다.
{
	int row;
	int col;

	// 디버깅을 위한 편의 기능
	friend ostream& operator<<(ostream& os, const Pos& pos)
	{
		cout << "(" << pos.row << ", " << pos.col << ")" << flush;
		return os;
	}
};

void RecurMaze(Pos p)  // 재귀를 이용해서 Recur 한다.  p.row, p.col; //row는 행,  col은 열.
{
	const char mark = maze[p.row][p.col]; // mark 라는 문자형 변수는 maze[][]의 값을 저장한다.

	if (mark == 'G')
	{
		cout << "Found!" << endl; //만약 G값에 도달한다면, found 를 출력하겠다.
		return;
	}

    if(mark != 'x' && mark != '1'){

        maze[p.row][p.col] = 'x';

        RecurMaze({p.row +1 , p.col });// 하
        RecurMaze({p.row  , p.col + 1 });// 우
        RecurMaze({p.row , p.col - 1 });//좌
        RecurMaze({p.row  -1 , p.col });//상

    }
}

//조기 종료가 가능한 버전
int ORecurMaze(Pos p)
{
	const char mark = maze[p.row][p.col]; // mark 라는 문자형 변수는 maze[][]의 값을 저장한다.

	if (mark == 'G')
	{
		cout << "Found!" << endl; //만약 G값에 도달한다면, found 를 출력하겠다.
		return 1;
	}

    if(mark != 'x' && mark != '1'){

        maze[p.row][p.col] = 'x';

        if(ORecurMaze({p.row +1, p.col }))   return 1;    // 하
        if(ORecurMaze({p.row  , p.col + 1 }))     return 1;    // 우
        if(ORecurMaze({p.row   , p.col - 1 }))     return 1;    // 좌
        if(ORecurMaze({p.row -1 , p.col }))     return 1;    // 상
    }
    return 0;
}

void StackMaze()
{
	Stack<Pos> s;

	Pos start = { 1, 1 }; // i = 1, j = 1  시작 지점
	//Pos start;
	//start.row = 1;
	//start.col = 1;

	s.Push(start); // s.Push({1, 1});

	// s.Print(); // 디버깅에 사용 가능

	while (!s.IsEmpty())
	{
		Pos p = s.Top();
		s.Pop();

		cout << p << " "; // 디버깅 출력

		const char mark = maze[p.row][p.col];

		if (mark == 'G')
		{
			cout << "Found!" << endl;
			break;
		}

        if(mark != 'x' && mark != '1'){

            maze[p.row][p.col] = 'x';

		    s.Push({p.row +1 , p.col});
            s.Push({p.row  , p.col + 1 });
            s.Push({p.row   , p.col - 1 });
            s.Push({p.row -1 , p.col });
        }
	}
}

int main()
{
	PrintMaze();

    cout << endl;
    cout<< endl;
	//RecurMaze({ 1, 1 });
    //ORecurMaze({ 1, 1 });
	StackMaze();

	PrintMaze();

	return 0;
}