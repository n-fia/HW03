// HW03.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.

#include <iostream>
#include <algorithm>

template <typename T>
class SimpleVector {

public: //일단 멤버변수 data의 원소를 출력하기 위함
    T* data;        // T 타입의 배열을 가리키는 배열 포인터
    //T* dataFin;     // T 타입 배열의 마지막 원소를 가리키는 배열 포인터
    int currentCapacity;    //배열의 크기
    int currentSize;        //배열 원소의 개수

public:
    SimpleVector() { // 기본 생성자. T 타입 배열[크기 : 10]을 생성
        currentCapacity = 10;
        currentSize = 0;
        data = new T[currentCapacity];
        //dataFin = data + currentCapacity - 1;//마지막 원소(예정) 주소
    }

    SimpleVector(const int& capacity) : currentCapacity(capacity) { // capacity 크기의 배열 생성
        currentSize = 0;
        data = new T[currentCapacity];
        //dataFin = data + currentCapacity - 1;//마지막 원소(예정) 주소
    }

    SimpleVector(const SimpleVector& other) {//복사 생성자 구현

        currentCapacity = other.currentCapacity;
        currentSize = other.currentSize;
        T* temp_ptr = other.data;
        data = new T(temp_ptr->current);   //other과 동일한 객체를 만들기 위해 동일한 맴버변수로 만들어준다.
        //currentCapacity가 아니라 current를 가리키는데 왜 되지?
        //dataFin = data + currentCapacity - 1;
        //복사 생성자 : 깊은 복사를 하는 생성자. 메모리 공간이 다르다.
        //멤버변수를 가져오는데 똑같은 값으로 생성함.
        // main함수에서 객체를 만드는 거임b(a) 이렇게
    }

    //초기화 리스트 생성자 - 이삭튜터님이 보내주심
    SimpleVector(std::initializer_list<T> list) //이게 정해진 구조. <T>가 타입
    {
        currentCapacity = currentSize = list.size();//크기와 개수를 동일하게
        int i = 0;
        data = new T[currentCapacity];
        //dataFin = data + currentCapacity - 1;
        //범위 기반 포문. C++11 이상에서 동작
        //auto : 타입 추론. 컴파일 타임에 데이터 타입을 알아서 유추.
        for (const auto& e : list) // list의 요소 -> 아직 미정. 여기서는 T타입(string double float)
        {
            *(data+i) = e;
            i++;
        }
    }

    ~SimpleVector() {
        delete[] data;
        data = nullptr;
        //delete dataFin;   //댕글링포인터
        //dataFin = nullptr;
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
        //내가 배열의 크기를 추가하는 방법을 아나? > 새로운 배열을 만들어서 복사하고 delete? 그럼 그냥 배열은..
        //gpt가 new로 할당하고 delete로 삭제하래
    }

    void pop_back() {
        //arr의 size를 구해서 size=1번 인덱스 원소를 삭제하기
        //data[currentSize]=NULL; //nullptr을 가리키도록 설정할 수 없음. 포인터가 아니라 값이라서..
        if (currentSize > 0) { currentSize--; }
    }

    int size() {
        //배열의 원소 개수를 반환
        /*
        int i = 0;

        while (data + i != dataFin) {   //fin은 capacity의 마지막원소(없을 수도 있음) 주소를 가리키는데
            i++;    //마지막 인덱스(원소 개수 -1)까지 증가
        }

        //(currentCapacity < currentSize)
        if (i + 1< currentSize) {         //최대 원소 개수-1 (+1)< 현재 원소 개수
            std::cout << "size 오류 발생" << std::endl;
        }
        */

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
            for (int i = 0; i < currentSize; ++i) { //현재 배열을 미래 배열에 넣는다
                //tempArr_back(data+i);
                tempArr[i] = data[i];
            }
            //tempArr.push_back(data[i]);
            currentCapacity = newCapacity;
            delete[] data;
            data = nullptr;
            data = tempArr;
        }
    }

    void sortData() {
        //데이터 정렬. sort함수로 정렬하면 됨. 오름차순
        std::sort(data, data + currentSize);
        //
    }

    /*bool operator<(const MyData& other) const {
        return value < other.value;
    }*/
};

int main()
{
    std::cout << "Hello World!\n";
    std::string stringArr[] = { "apple", "banana", "Mango","grape","Cookie","blueberry","rice" };
    double doubleArr[] = { 1 , 6.0f , 3.3f , 5.56f , 34 , 7.85f , 2 , 5.5f , 64.3f };// double이어도 f 붙이기!

    //문자열 배열 선언
    SimpleVector<std::string> stringVector;
    //push_back()으로 원소 대입
    //for (size_t i = 0; i < stringArr.size(); ++i) {}
    for (size_t i = 0; i < 7; ++i) {
        stringVector.push_back(stringArr[i]);
    }

    //실수형 배열 선언
    SimpleVector<double> doubleVector;
    //push_back()으로 원소 대입
    //for (size_t i = 0; i < doubleArr.size(); ++i) {
    for (size_t i = 0; i < 9; ++i) {
        doubleVector.push_back(doubleArr[i]);
    }

    //초기화 리스트 생성자
    SimpleVector<float> floatVector = { 1 , 6.0f , 3.3f , 5.56f , 34 , 7.85f , 2 , 5.5f , 64.3f };

    //현재 상황 확인하기
    std::cout << "\n현재 문자열 배열 size : ";
    std::cout << stringVector.size() << "  ";
    std::cout << "\n현재 문자열 배열 capacity : ";
    std::cout << stringVector.capacity() << "  ";
    //for (int i = 0; i < stringVector.size(); ++i) {}
    std::cout << "\n현재 실수형 배열 size : ";
    std::cout << doubleVector.size() << "  ";
    //for (int i = 0; i < doubleVector.size(); ++i) {}
    std::cout << "\n현재 float형 배열 size : " << floatVector.size() << "  " << std::endl;
    for (int i = 0; i < floatVector.size(); ++i) {
        std::cout << *(floatVector.data + i) << " ";
    }

    //pop_back() 실행하기
    stringVector.pop_back();
    doubleVector.pop_back();
    floatVector.pop_back();
    //이것도 함수를 만들어서 객체지향적으로 하고 싶은데 힘들어서 그만할래 나 힘들어
    std::cout << "\npop_back 실행 후 stringVector size : " << stringVector.size() << "  " << std::endl;
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
    std::cout << "resize 실행 후 stringVector size : " << stringVector.size() << "  " << std::endl;
    std::cout << "resize 실행 후 doubleVector size : " << doubleVector.size() << "  " << std::endl;
    std::cout << "resize 실행 후 floatVector size : " << floatVector.size() << "  " << std::endl;

    //sort() 실행하기
    floatVector.sortData();
    std::cout << "sort 실행 후 floatVector : " << std::endl;
    for (int i = 0; i < floatVector.size(); ++i) {
        std::cout << *(floatVector.data + i) << std::endl;
    }
    //sort() 실행하기
    stringVector.sortData();
    std::cout << "sort 실행 후 stringVector : " << std::endl;
    for (int i = 0; i < stringVector.size(); ++i) {
        std::cout << *(stringVector.data + i) << std::endl;
    }

}