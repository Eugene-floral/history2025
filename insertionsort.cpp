#include <iostream>

using namespace std;

bool CheckSorted(int* arr, int size)
{
	for (int i = 0; i < size - 1; i++)
	{
		if (arr[i] > arr[i + 1])
			return false;
	}

	return true;
}

void Print(int* arr, int size)
{
	for (int i = 0; i < size; i++)
		cout << arr[i] << " ";
	cout << endl;
}

int main()
{
	int arr[] = { 8, 3, 2, 5, 1, 2 };
	//int arr[] = { 6, 5, 4, 3, 2, 1 }; // Worst
	//int arr[] = { 1, 2, 3, 4, 5, 6 }; // Best
	int n = sizeof(arr) / sizeof(arr[0]);

	// Insertion Sort
	{
        for(int i = 1; i < n; i++){
            int key = arr[i]; //arr[1] = 3
            int j = i - 1; // j = 0,
            for(; j >= 0 && key < arr[j]; j--){
                arr[j + 1] = arr[j]; //j = 0 arr[1] = arr[0];
            }
            arr[j+1] = key; 
        }
	}

    Print(arr,n);

	// Stability
}