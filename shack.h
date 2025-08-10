#pragma once

#include <cassert>
#include <iostream>

template<typename T> // 템플릿 사용
class Stack
{
public:

	Stack(int capacity = 1)
	{
		Resize(capacity);
	}

	~Stack()
	{
		if (stack_) delete[] stack_;
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
        if(Size() == 0) true;

		return false;
	}

	int Size() const
	{
       return top_ + 1;
	}

	void Print()
	{
		using namespace std;

		for (int i = 0; i < Size(); i++) // Size() 사용
			cout << stack_[i] << " ";
		cout << endl;
	}

	// Returns TOP element of stack.
	
    T& Top() const
	{
		return stack_[top_];
	}

	// Insert item into the TOP of the stack
	void Push(const T& item)
	{
		if(capacity_ == Size()){
            Resize(capacity_ * 2);
        }
        stack_[++top_] = item;
	}

	// Delete the TOP element of the stack
	void Pop()
	{
		top_--;
	}

protected: // 뒤에서 상속해서 사용
	T* stack_ = nullptr;
	int top_ = -1; // 0 아님
	int capacity_ = 0;
};