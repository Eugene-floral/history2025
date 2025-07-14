#pragma once

#include <cassert>
#include <iostream>

template<typename T> // 템플릿 사용
class Stack
{
public:
	Stack(int capacity = 1)//stack(1)
	{
		assert(capacity > 0);
		Resize(capacity); //stack 기본적으로 카파가 1이다.
	}

	~Stack()
	{
		if(stack_) delete[] stack_;
	}

	void Resize(int new_capacity)
	{
		T* new_stack = new T[new_capacity];
		memcpy(new_stack, stack_, sizeof(T) * Size());
		if (stack_) delete[] stack_;
		stack_ = new_stack;
		capacity_ = new_capacity;
	}

	bool IsEmpty() const
	{
       if(top_ == -1) return true;

       return false;
    }

	int Size() const
	{
		return top_ + 1 ;
	}

	void Print()
	{
		using namespace std;

		for (int i = 0; i < Size(); i++) // Size() 사용
			cout << stack_[i] << " ";
		cout << endl;
	}

	// Returns TOP element of stack.
	T& Top() const//탬플릿 t를 사용해서 t의 형태가 이 top의 형태라고 설정.
	{
		assert(!IsEmpty());

		return stack_[top_];
	}

	// Insert item into the TOP of the stack
	void Push(const T& item)
	{
        if(top_ + 1 >= capacity_){//top_ = 0; capa = 1;    top_ =1 
        Resize(capacity_ * 2);//이런 생각을 할줄 알아야 해.
        }
        stack_[++top_] = item;

	}

	// Delete the TOP element of the stack
	void Pop()
	{
		assert(!IsEmpty());
        --top_;
	}

protected: // 뒤에서 상속해서 사용
	T* stack_ = nullptr;
	int top_ = -1; // 0 아님
	int capacity_ = 0;
};