#pragma once

#include <cassert>
#include <iostream>
#include <iomanip>

template<typename T>
class MinHeap
{
public:
	MinHeap(int cap = 10)
	{
		assert(cap > 0);

		capacity_ = cap;
		size_ = 0;
		heap_ = new T[capacity_ + 1]; // heap[0]은 비워둡니다.
	}
/**/ 
	void Resize(int new_capacity)
	{
		T* new_heap = new T[new_capacity];
		memcpy(new_heap, heap_, sizeof(T) * (size_ + 1)); // +1 주의
		if (heap_) delete[] heap_;
		heap_ = new_heap;
		capacity_ = new_capacity;
	}

	T Top()
	{
		return heap_[1]; // 1번 인덱스 자리
	}

	bool IsEmpty()
	{
		return size_ == 0;
	}

	void Print()
	{
		using namespace std;
		cout << "Index: ";
		for (int i = 1; i <= size_; i++)
			cout << setw(3) << i;
		cout << endl;

		cout << "Value: ";
		for (int i = 1; i <= size_; i++)
			cout << setw(3) << heap_[i];
		cout << endl << endl;
	}

	void Push(const T& item)
	{
	    using namespace std;
		cout << "Push " << item << endl;

		if (size_ == capacity_)//만약에 사이즈가 꽉찼어?/ 용량 늘려.
			Resize(capacity_ * 2);// 만약에 사이즈가 카파시티와 같으면 ?? ==>  카파는 수용 가능한 용량 , 사이즈는 들어있는 수;
        
		// 삽입: 일단 맨 마지막에 삽입한 후에 부모 노드로 올린다.

		size_ += 1; // 푸쉬했으면 숫자 하나 들어왔으니까 사이즈 하나 커지고, 
		int current = size_; // 마지막에 추가가될 위치 (인덱스) // 숫자의 개수이자 인덱스가 되는 거지 current가.

		while (current != 1 && ( heap_[current/ 2] > item )) // 부모 위치의 값이 추가하려는 값보다 작다면
		{
			// 부모 위치의 값을 자식 위치로 복사해서 내린다.
			heap_[current] = heap_[current / 2];//값 복사,
            
			cout << "Current = " << current << endl;
			Print();// 복사된 상태에서 출력을 하고, 그리고 current 값을 바꿔야지.

			current = current / 2;
		}

		heap_[current] = item; // 최종적으로 결정된 위치에 복사
	}

	void Pop()
	{
		assert(!IsEmpty());

		using namespace std;
		cout << "Pop()" << endl;

		heap_[1].~T(); // 소멸자 호출 

		// 삭제: 가장 마지막 값을 루트로 옮긴 후에 내려 보낸다.

		T last_item = heap_[size_]; // 마지막 아이템 복사
		size_--;					// 크기 줄이기
//크기를 왜 줄여?? 마지막 값 뺏으니깐~

		int current = 1;			// 루트 노드에서 시작
		int child = 2;				// current * 2 (루트의 왼쪽 자식 인덱스)
		while (child <= size_)// 자식 왼쪽 인덱스가 사이즈 값 이하일때만 .무 슨 뜻이야? -> 전체 크기보다 커지면 그만둔다.
		{
			// left, right 중에서 더 큰 자식의 인덱스를 찾는다. 이때 자식이 하나라면 찾을 필요 없음
            if(child + 1 > size_) break;
			if(heap_[child] < heap_[child + 1]) child = child + 1;
            
			// 마지막 값이 더 큰 자식의 값 이상이면 더이상 적절한 위치를 찾을 필요가 없기 때문에 루프 중단
			
            if(last_item >= heap_[child]) break;
			// 자식 값을 부모 위치로 복사, 
			else{
                heap_[current] = heap_[child];
            }

			cout << "Current = " << current << ", child = " << child << endl;
		    Print();

			// 그 자식 위치로 current 인덱스 변경, child 인덱스도 그 다음 자식 위치로 변경
			current = child; child = current * 2;
		}

		heap_[current] = last_item;
	}

private:
	T* heap_ = nullptr;
	int size_ = 0;
	int capacity_ = 0;
};