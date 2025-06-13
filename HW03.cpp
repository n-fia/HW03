// HW03.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.

#include <iostream>
#include <algorithm>

template <typename T>
class SimpleVector {

public: //일단 멤버변수 data의 원소를 출력하기 위함
    T* data;        // T 타입의 배열을 가리키는 배열 포인터
    int currentCapacity;    //배열의 크기
    int currentSize;        //배열 원소의 개수

public:
    SimpleVector() { // 기본 생성자. T 타입 배열[크기 : 10]을 생성
        currentCapacity = 10;
        currentSize = 0;
        data = new T[currentCapacity];
    }

    SimpleVector(const int& capacity) : currentCapacity(capacity) { // capacity 크기의 배열 생성
        currentSize = 0;
        data = new T[currentCapacity];
    }

    //복사 생성자
    SimpleVector(const SimpleVector& other) {

        currentCapacity = other.currentCapacity;    //other과 동일한 객체를 만들기 위해 동일한 맴버변수로 만들어준다.
        currentSize = other.currentSize;
        T* temp_ptr = other.data;   //그냥 data가 other데이터 가리키면 얕은 복사니까 temp > 복사생성자의 data로 복사
        data = new T[currentCapacity];   //T타입 배열을 가리킬 수 있는 배열 포인터 data(멤버변수)가 other과 같은 크기의 배열을 생성하여 가리키도록
        for (int i = 0; i < currentSize; ++i) {
            *(data + i) = *(temp_ptr + i);
            //data[i] = other.data[i];
        }
        //delete temp_ptr;//댕글링 포인터
        temp_ptr=nullptr;
        //복사 생성자 : 깊은 복사를 하는 생성자. 메모리 공간이 다르다.
        //멤버변수를 가져오는데 똑같은 값으로 생성함.
        // main함수에서 b(a) 이렇게 객체를 만든다.
    }

    //초기화 리스트 생성자
    SimpleVector(std::initializer_list<T> list) //이게 정해진 구조. <T>가 타입
    {
        currentCapacity = currentSize = list.size();//크기와 개수를 동일하게
        int i = 0;
        data = new T[currentCapacity];
        //범위 기반 포문. C++11 이상에서 동작
        //auto : 타입 추론. 컴파일 타임에 데이터 타입을 알아서 유추.
        for (const auto& e : list) // list의 요소 여기서는 T타입(string double float ... )
        {
            *(data+i) = e;
            ++i;
            //data[i++]=e;와 같은 말
        }
    }

    ~SimpleVector() {
        delete[] data;
        data = nullptr;
    }

    void push_back(const T& value) {    //원소 value를 data의 맨 뒤(size()기준)에 추가함
        if (currentCapacity > currentSize) {
            *(data + currentSize) = value;  //주소(맨 뒤 빈 곳)의 값을 value로 지정
            currentSize++;
        }
        else {
            //크기를 추가한다
            resize(currentSize + 5);    //원래 원소 개수 + 5 크기 할당
            *(data + currentSize) = value;
            currentSize++;
        }
    }

    void pop_back() {
        if (currentSize > 0) { currentSize--; }
    }

    int size() {
        //배열의 원소 개수를 반환
        return currentSize;
    }

    int capacity() {

        return currentCapacity;
    }

    void resize(int newCapacity) {
        //원하는 크기(newCapacity)가 > 배열의 크기(CurrentCapacity)보다 크면
        //정수만큼 배열의 크기를 재할당한다.(기존 원소는 그대로)
        //배열 크기 재할당
        //새로운 배열을 만들어서 원소를 for문으로 넣기
        if (newCapacity > currentCapacity) {
            T* tempArr = new T[newCapacity];
            for (int i = 0; i < currentSize; ++i) { //현재 배열을 temp 배열에 넣는다
                tempArr[i] = data[i];
            }

            currentCapacity = newCapacity;
            delete[] data;
            data = nullptr;
            data = tempArr;     //temp배열을 가리킨다

            tempArr = nullptr; //이거만 하면 됨. delete X
        }
    }

    void sortData() {
        //데이터 정렬. sort함수로 정렬. 오름차순
        std::sort(data, data + currentSize);
    }

};

int main()
{
    std::cout << "Hello World!\n";
    std::string stringArr[] = { "apple", "banana", "Mango","grape","Cookie","blueberry","rice" };
    size_t strSize = sizeof(stringArr) / sizeof(stringArr[0]);
    double doubleArr[] = { 1 , 6.0 , 3.3 , 5.56 , 34 , 7.85 , 2 , 5.5 , 64.3 };
    size_t doubleSize = sizeof(doubleArr) / sizeof(doubleArr[0]);
    char charArr[] = {'a','b','d','2','3'};
    size_t charSize = sizeof(charArr) / sizeof(charArr[0]);

    //문자열 배열 선언
    SimpleVector<std::string> stringVector;
    //push_back()으로 원소 대입
    for (size_t i = 0; i < strSize; ++i) {
        stringVector.push_back(stringArr[i]);
    }

    //실수형 배열 선언
    SimpleVector<double> doubleVector;
    //push_back()으로 원소 대입
    for (size_t i = 0; i < doubleSize; ++i) {
        doubleVector.push_back(doubleArr[i]);
    }

    //초기화 리스트 생성자로 객체 선언
    SimpleVector<float> floatVector = { 1 , 6.0f , 3.3f , 5.56f , 34 , 7.85f , 2 , 5.5f , 64.3f };
    
    //복사 생성자로 객체 선언
    SimpleVector<std::string> strVector2(stringVector); //stringVector와 같은 객체 생성 ! >> T타입 클래스이기 때문에 타입을 지정해줘야 함

    //현재 상황 확인하기
    std::cout << "\n현재 문자열 배열 size : ";
    std::cout << stringVector.size() << "  ";
    std::cout << "\n현재 문자열 배열 capacity : ";
    std::cout << stringVector.capacity() << "  ";
    std::cout << "\n복사한 문자열 배열 capacity : ";
    std::cout << strVector2.capacity() << "  ";
    std::cout << "\n현재 double형 배열 size : ";
    std::cout << doubleVector.size() << "  ";
    std::cout << "\n현재 float형 배열 size : ";
    std::cout << floatVector.size() << "  " << std::endl;
    for (int i = 0; i < floatVector.size(); ++i) {
        std::cout << *(floatVector.data + i) << " ";
    }

    //pop_back() 실행하기
    stringVector.pop_back();
    doubleVector.pop_back();
    floatVector.pop_back();

    std::cout << "\n\npop_back 실행 후 stringVector size : " << stringVector.size() << "  " << std::endl;
    std::cout << "pop_back 실행 후 doubleVector size : " << doubleVector.size() << "  " << std::endl;
    std::cout << "pop_back 실행 후 floatVector size : " << floatVector.size() << "  " << std::endl;

    std::cout << "\n현재 string형 배열" << std::endl;
    std::cout << "size : " << stringVector.size() << "  " << std::endl;
    for (int i = 0; i < stringVector.size(); ++i) {
        std::cout << *(stringVector.data + i) << std::endl;
    }

    std::cout << "\n현재 float형 배열" << std::endl;
    std::cout << "size : " << floatVector.size() << "  " << std::endl;
    for (int i = 0; i < floatVector.size(); ++i) {
        std::cout << *(floatVector.data + i) << std::endl;
    }

    //resize() 실행하기
    stringVector.resize(15);
    doubleVector.resize(3);
    floatVector.resize(13);
    std::cout << "\nresize 실행 후 stringVector size : " << stringVector.size() << "  " << std::endl;
    std::cout << "resize 실행 후 doubleVector size : " << doubleVector.size() << "  " << std::endl;
    std::cout << "resize 실행 후 floatVector size : " << floatVector.size() << "  " << std::endl;

    //sort() 실행하기
    floatVector.sortData();
    std::cout << "\nsort 실행 후 floatVector : " << std::endl;
    for (int i = 0; i < floatVector.size(); ++i) {
        std::cout << *(floatVector.data + i) << std::endl;
    }
    //sort() 실행하기
    stringVector.sortData();
    std::cout << "\nsort 실행 후 stringVector : " << std::endl;
    for (int i = 0; i < stringVector.size(); ++i) {
        std::cout << *(stringVector.data + i) << std::endl;
    }

}