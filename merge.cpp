#include <iostream>
#include <iomanip>

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

void Print(int* arr, int left, int right)
{
	for (int i = left; i <= right; i++)
		cout << setw(3) << arr[i] << " ";
	cout << endl;
}

void Merge(int init[], int merged[], int left, int mid, int right)
{
	int i, j, k, l;
	i = left;
	j = mid + 1;
	k = left;

	cout << "  Left : ";
	Print(init, left, mid);
	cout << " Right : ";
	Print(init, mid + 1, right);

	// 인덱스를 2개 이용해서 정렬하면서 merge
	while(i <= mid && j <= right ){ // left <= 1; mid +1 <= 3;
		if(init[i] > init[j]){ //left = 0. mid = 1 ;         mid+ 1 = 2 right =3;
			merged[k++] = init[j++]; //  3  , k =1 , i =0; j= 3;
		}//오른쪽이 출력 된 상황 
		else{//왼쪽 출력된 상황
			merged[k++] = init[i++]; // 3 27 38   , k =3, i =2; j =3;  
		}
	}
	if(i <= mid){  
		for(int u = i; u <= mid; u++){
			merged[k++] = init[u]; 
		}
	}
	if(j <= right){ // j =3 <=right
		for(int u = j; u <= right; u++){  // u =3 u>right
			merged[k++] = init[u];
		}
	// merged -> init 복사

	}
	for (l = left; l <= right; l++)
		init[l] = merged[l];

	cout << "Merged : ";
	Print(init, left, right);
	cout << endl;
}

void MergeSort(int arr[], int merged[], int left, int right)
{
	int mid;
	if (left < right)
	{
		mid = (left + right) / 2;

		MergeSort(arr, merged, left, mid); //arr을 merged로 복사,재귀를 사용해서 반으로 쪼갤수 있을 때까지 쪼개기. 왼쪽 파트 
		MergeSort(arr, merged, mid + 1, right);// 오른쪽 파트 

		Merge(arr, merged, left, mid, right);
	}
}

int main()
{
	//int arr[] = { 3, 4, 2, 1, 7, 5, 8, 9, 0, 6 }; // 위키피디아 예시
	int arr[] = { 38, 27, 43, 3, 9, 82, 10 }; // https://en.wikipedia.org/wiki/Merge_sort
	int n = sizeof(arr) / sizeof(arr[0]);

	int* merged = new int[n]; // 추가 메모리 필요 //merged에는 7개의 공간 메모리가 있다.

	Print(arr, 0, n - 1);
	cout << endl;

	MergeSort(arr, merged, 0, n - 1);

	Print(merged, 0, n - 1);
	cout << endl;

	delete[] merged;

	// 시간 복잡도: 최악, 최선, 평균 모두 O(nlogn)
	// 공간 복잡도: O(n) 추가 공간 필요
}