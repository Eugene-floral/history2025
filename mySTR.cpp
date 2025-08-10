#include "Mystring.h"

using namespace std;

// 비어 있는 MyString() 생성
MyString::MyString()
{
	str_ = nullptr;
	size_ = 0;
}

// 맨 뒤에 널 캐릭터'\0'가 들어 있는 문자열로부터 초기화
MyString::MyString(const char* init) //문제 => char 
{
	size_ = strlen(init); // init이 포인터라 strlen을 써야 하는데 몰랐음.

	str_ = new char[size_+ 1]; //str = 이라고 할 생각 못함.

	memcpy(str_,init, size_ + 1); //+1 안했을거임.
}

// MyString의 다른 instance로부터 초기화
MyString::MyString(const MyString& str) //총체적 난국.
{
    // str은 mystring 타입임.
    size_ = str.size_; //쓰벌. mystring 의 클래스 개념이 부족한가 싸발.
    str_ = new char[size_ + 1]; //이것도 str = 이렇게 할 생각 못함.
    memcpy(str_ , str.str_ ,size_); //그 사이즈 만큼 복사도 해줬고,

}

MyString::~MyString()
{
	delete str_;
}

bool MyString::IsEmpty()
{
	return Length() == 0;
}

bool MyString::IsEqual(const MyString& str) // 편의상 참조& 사용
{
    for(int i =0; i < str.size_; i++){
        if(str_[i] != str.str_[i]) return false;
    }
	return true;
}

int MyString::Length()
{
	return size_;
}

void MyString::Resize(int new_size) // 이게 빡세던데,
{//resize 도 문제가 심함,.

    char * newstr = new char[new_size];

    memcpy(newstr, str_, size_);
    
    delete str_; //ㄱ존에 것을 지워줘야 하는거 ㄴ당연 왜냐하면 두개가 되어버리잖아.
    str_ = newstr;
    size_ = new_size;
    
}

// 인덱스 start위치의 글자부터 num개의 글자로 새로운 문자열 만들기
MyString MyString::Substr(int start, int num)
{
	// 복사할 인덱스: start, start + 1, ... , start + num - 1
	// assert(start + num - 1 < this-> size_); // 문제를 단순하게 만들기 위해 가정
	MyString temp;

    temp.Resize(num); //할당 해줘야 하는데 안함 왜 안했냐 

    int j =0;

    for(int i = start; i < start + num; i++){ // 인덱스 3부터 4개 
        temp.str_[j++] = str_[i];
    }

	return temp;
}

MyString MyString::Concat(MyString app_str) //app_str 은 뒤에 추가할 문자열. //할당 해줘야 하나?? 근데 temp는 할당이 안돼.

{
	MyString temp;

    temp.Resize(size_ + app_str.size_);

    memcpy(temp.str_ , str_ , size_);
    memcpy(&temp.str_[size_], app_str.str_ , app_str.size_);// 아하 주소값을 써줘야 하는구나 이거 모름 내가 써볼라고 했는데 저번에 공부했는데 못함.

	return temp;
}

MyString MyString::Insert(MyString t, int start)
{

	assert(start >= 0);
	assert(start <= this->size_);

	MyString temp;
    temp.Resize(size_ + t.size_);

    int j = 0;
    for(int i = 0; i < start; i++){
        temp.str_[i] = str_[i];
    }
    for(int i = start; i < start + t.size_; i++){ // i=0 1 2
        temp.str_[i] = t.str_[j++];
    }

    for(int i = start + t.size_; i < t.size_ + size_; i++){ 
        temp.str_[i] = str_[i - t.size_];
    }

	return temp;
}

int MyString::Find(MyString pat) //pat.str_ = "EF" 라고 해보면.
{ //6 -2
	for(int i = 0; i <= size_ - pat.size_; i++){ //만약에 i 값을 찾음. 그게 같았다면?? 
        for(int j = 0; j < pat.size_; j++){

            if(str_[i + j] != pat.str_[j]) // i =4;  j =2;
            break;
            
            if(j == pat.size_ -1)
            return i;
        }
    }
    
    return -1;
}

void MyString::Print()
{
	for (int i = 0; i < size_; i++)
		cout << str_[i];
	cout << endl;
}