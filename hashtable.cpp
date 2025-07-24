#include <iostream>
#include <string> // std::string

using namespace std;

template<typename K, typename V>
class HashTable
{
public:
	struct Item
	{
		K key = K();
		V value = V();
	};

	HashTable(const int& cap = 8)
	{
		capacity_ = cap;
		table_ = new Item[capacity_];
	}

	~HashTable()
	{
		delete[] table_;
	}

	void Insert(const Item& item)
	{
		size_t index = HashFunc(item.key); // 키를 용량으로 나눈 나머지를 인덱스로 하겠다.
        for(int i = index % capacity_; i< capacity_; i++){
			if(table_[index].key != K()){
				continue;
			}
			else{
				table_[index % capacity_] = item;
				return;
			}
		}
	}

	V Get(const K& key)
	{
		size_t index = HashFunc(key); // 1211을 넣었다, 그럼 3이 나오잖아
        
        for(int i = 0; i< capacity_; i++){
            index = (index + i) % capacity_;
            size_t temp = index;

            if(table_[temp].key == key){
                return table_[temp].value;
            }
        }//이런 생각을 하다니 이건 어떤 생각이냐면 index를 키값을 사용해서 구했는데 
        //그 인덱스 값의 키와 집어넣은 키가 맞는지 한번 확인 하고 만약에 아니라면 다른 곳에 있구나 
        //생각하고 집어넣는 거라고 생각하면 된다.
       return -1;
    }
	// 정수 -> 해시값
	//size_t HashFunc(const int& key)
	//{
	//	return key % capacity_;
	//}

	//문자열을 정수 인덱스(해시값)로 변환
	// Horner's method
	size_t HashFunc(const string& s)
	{
        size_t index = 0;
        int g = 3;
        for(int i= 0 ;i< s.length(); i++){
            index += g * index + s.at(i); //g를 곱해주는 이유가 뭐냐면 각 자릿수마다
        }                       // g가 많이 붙어있으면 높은 자리 숫자라는 거겠지??
	  return index % capacity_;
	}

	void Print()
	{
		for (int i = 0; i < capacity_; i++)
			cout << i << " : " << table_[i].key << " " << table_[i].value << endl;
		cout << endl;
	}

private:
	Item* table_ = nullptr;
	int capacity_ = 0;
};

int main()
{
    /*
	// 충돌 
	// - 개방 주소법: 선형 조사법
	// - 체이닝: 멤버 변수 Item* table_ 대신에 LinkedList<Item>* table_사용

	// 키: int, 값: int 인 경우
	// 키의 범위가 아주 크고 아이템의 개수는 적을 경우
	{
		using Item = HashTable<int, int>::Item;

		HashTable<int, int> h(8);

		h.Insert(Item{ 123, 456 });

		h.Print();

		cout << "Get 123 " << h.Get(123) << endl;

		h.Insert(Item{ 1000021, 9898 });

		h.Print();

		cout << "Get 1000021 " << h.Get(1000021) << endl;

		h.Insert(Item{ 1211, 999 }); // 충돌!

		h.Print();

		cout << "Get 123 " << h.Get(123) << endl;
		cout << "Get 1211 " << h.Get(1211) << endl;
	}
*/
	// 키: std::string, 값: int
	{
		using Item = HashTable<string, int>::Item;

		HashTable<string, int> h(8);

		h.Insert(Item{ "apple", 1 });
		h.Insert(Item{ "orange", 2 });
		h.Insert(Item{ "mandarin", 4 });

		h.Print();

		cout << "apple " << h.Get("apple") << endl;
		cout << "orange " << h.Get("orange") << endl;
	cout << endl;

		h.Print();

		h.Insert(Item{ "tomato", 4 });

		h.Print(); 

		cout << "apple " << h.Get("apple") << endl;
		cout << "orange " << h.Get("orange") << endl;
		cout << "pineapple " << h.Get("pineapple") << endl;
		cout << endl;
	}

	return 0;
}// 마무리 작업 필요로함 7/24일 확