#include <iostream>
#include <queue>
#include <list>
#include <algorithm> //sort

using namespace std;
/************************************************************************/
/*                                                                      */
/************************************************************************/
//自定义测试用
struct test_item
{
    string name;
    string phone;
    string display;
    
    test_item(const string& tname, const string& tphone)
    {
        name = tname;
        phone = tphone;
        display = (name + ": " + phone);
    }
    
    bool operator == (const test_item& item_to_compare) const
    {
        return (item_to_compare.name == this->name);
    }
    
    bool operator < (const test_item& item_to_compare) const
    {
        return (this->name < item_to_compare.name);
    }
    
    operator const char*() const
    {
        return display.c_str();
    }
};

//二元谓词函数
bool sort_phone_number(const test_item& item1, const test_item& item2)
{
    return item1.phone < item2.phone;
}
/************************************************************************/
/*                                                                      */
/************************************************************************/
//分配新的内容替换原有的内容
void assign_test(void)
{
    queue<int> integers;
    
    //放入5个元素
    integers.push(20);
    integers.push(21);
    integers.push(22);
    integers.push(23);
    integers.push(24);
    
    queue<int> another2;
    
    another2.push(86);
    another2.push(86);
    
    //将 another2 的内容赋给 integers
    integers = another2;
    
    cout << "queue contains " << integers.size() << " elements" << endl;
    cout << "Element at front: " << integers.front() << endl;
    cout << "Element at back: " << integers.back() << endl;
    while(integers.size() != 0) {
        cout << "Deleting elements: " << integers.front() << endl;
        integers.pop(); //removes element at front
    }
    
    queue<int> another3;
        
    another3.push(36);
    another3.push(36);
    //将 another3 的内容赋给 integers，another3内的值被清空
    integers = move(another3);
    
    cout << "queue contains " << integers.size() << " elements" << endl;
    cout << "Element at front: " << integers.front() << endl;
    cout << "Element at back: " << integers.back() << endl;
    while(integers.size() != 0) {
        cout << "Deleting elements: " << integers.front() << endl;
        integers.pop(); //removes element at front
    }
}

//交换元素
void swap_test(void)
{
    queue<int> integers;
    
    //放入5个元素
    integers.push(20);
    integers.push(21);
    integers.push(22);
    integers.push(23);
    integers.push(24);
    
    queue<int> another;
    another.push(0);
    another.push(1);
    another.push(2);
    
    //交换
    integers.swap(another);
    
    cout << "queue contains " << integers.size() << " elements" << endl;
    cout << "Element at front: " << integers.front() << endl;
    cout << "Element at back: " << integers.back() << endl;
    while(integers.size() != 0) {
        cout << "Deleting elements: " << integers.front() << endl;
        integers.pop(); //removes element at front
    }
    
    cout << "queue contains " << another.size() << " elements" << endl;
    cout << "Element at front: " << another.front() << endl;
    cout << "Element at back: " << another.back() << endl;
    while(another.size() != 0) {
        cout << "Deleting elements: " << another.front() << endl;
        another.pop(); //removes element at front
    }
}

//访问元素
void front_back_test(void)
{
    queue<int> integers;
    
    //放入5个元素
    integers.push(20);
    integers.push(21);
    integers.push(22);
    integers.push(23);
    integers.push(24);
    
    //输出首元素
    cout << "Front:" << integers.front() << endl;   //Front:20
    
    //输出尾元素
    cout << "Back:" << integers.back() << endl;     //Back:24
}

//判断是否为空
void empty_test(void)
{
    queue<int> integers;
    
    cout << "Empty:" << integers.empty() << endl;   //Empty:1
    
    //放入元素
    integers.push(20);
    
    cout << "Empty:" << integers.empty() << endl;   //Empty:0
    
    //删除元素
    integers.pop();
    
    cout << "Empty:" << integers.empty() << endl;   //Empty:1
}

//大小
void size_test(void)
{
    queue<int> integers;
    
    //大小
    cout << "Size:" << integers.size() << endl; //Size:0
    
    integers.push(10);
    
    cout << "Size:" << integers.size() << endl; //Size:1
    
    integers.push(11);
    
    cout << "Size:" << integers.size() << endl; //Size:2
    
    integers.push(12);
    
    cout << "Size:" << integers.size() << endl; //Size:3
    
    integers.pop();
    
    cout << "Size:" << integers.size() << endl; //Size:2
}

//开头删除元素
void pop_test(void)
{
    queue<int> integers;
    
    integers.push(10);
    integers.push(12);
    integers.push(66);
    
    cout << "queue contains " << integers.size() << " elements" << endl;
    cout << "Element at front: " << integers.front() << endl;
    cout << "Element at back: " << integers.back() << endl;
    while(integers.size() != 0) {
        cout << "Deleting elements: " << integers.front() << endl;
        integers.pop(); //removes element at front
    }
    
    if(integers.empty())
        cout << "The queue is now empty!" << endl;
}

//末尾插入元素
void push_test(void)
{
    queue<int> integers;
    
    integers.push(10);
    integers.push(12);
    integers.push(66);
    
    cout << "queue contains " << integers.size() << " elements" << endl;
    cout << "Element at front: " << integers.front() << endl;
    cout << "Element at back: " << integers.back() << endl;
    while(integers.size() != 0) {
        cout << "Deleting elements: " << integers.front() << endl;
        integers.pop(); //removes element at front
    }
    
    if(integers.empty())
        cout << "The queue is now empty!" << endl;
}

//实例化
void init_test(void)
{
    //整型 queue 类
    queue<int> integers;
    
    //使用一个queue初始化另一个queue，即复制queue对象
    queue<int> copyVector(integers);
    
    //使用一个queue初始化另一个queue，即复制queue对象
    queue<int> copyVector2 = integers;

    //底层容器默认为 deque, 可指定 vector 或 list 来存储数据
    queue<int, deque<int>> intQueueedInDeq;
    //底层容器修改为 vector
    queue<int, vector<int>> intQueueedInVec;
    //底层容器修改为 vector
    queue<int, list<int>> intQueueedInList;
}
/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    cout << __cplusplus << endl;
    
    init_test();        //实例化
    push_test();        //末尾插入元素
    pop_test();         //开头删除元素
    size_test();        //大小
    empty_test();       //判断是否为空
    front_back_test();          //访问元素
    swap_test();        //交换元素
    assign_test();      //分配新的内容替换原有的内容
    
    return 0;
}