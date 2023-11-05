#include <iostream>
#include <queue>
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
    priority_queue<int> integers;
    
    //放入5个元素
    integers.push(20);
    integers.push(21);
    integers.push(22);
    integers.push(23);
    integers.push(24);
    
    priority_queue<int> another2;
    
    another2.push(86);
    another2.push(86);
    
    //将 another2 的内容赋给 integers
    integers = another2;
    
    cout << "priority_queue contains " << integers.size() << " elements" << endl;
    while(integers.size() != 0) {
        cout << "Deleting elements: " << integers.top() << endl;
        integers.pop(); //removes element at top
    }
    
    if(integers.empty())
        cout << "The priority_queue is now empty!" << endl;
    
    priority_queue<int> another3;
        
    another3.push(36);
    another3.push(36);
    //将 another3 的内容赋给 integers，another3内的值被清空
    integers = move(another3);
    
    cout << "priority_queue contains " << integers.size() << " elements" << endl;
    while(integers.size() != 0) {
        cout << "Deleting elements: " << integers.top() << endl;
        integers.pop(); //removes element at top
    }
    
    if(integers.empty())
        cout << "The priority_queue is now empty!" << endl;
}

//交换元素
void swap_test(void)
{
    priority_queue<int> integers;
    
    //放入5个元素
    integers.push(20);
    integers.push(21);
    integers.push(22);
    integers.push(23);
    integers.push(24);
    
    priority_queue<int> another;
    another.push(0);
    another.push(1);
    another.push(2);
    
    //交换
    integers.swap(another);
    
    cout << "priority_queue contains " << integers.size() << " elements" << endl;
    while(integers.size() != 0) {
        cout << "Deleting elements: " << integers.top() << endl;
        integers.pop(); //removes element at top
    }
    
    if(integers.empty())
        cout << "The priority_queue is now empty!" << endl;
    
    cout << "priority_queue contains " << another.size() << " elements" << endl;
    while(another.size() != 0) {
        cout << "Deleting elements: " << another.top() << endl;
        another.pop(); //removes element at top
    }
    
    if(another.empty())
        cout << "The priority_queue is now empty!" << endl;
}

//访问元素
void top_test(void)
{
    priority_queue<int> integers;
    
    //放入5个元素
    integers.push(20);
    integers.push(21);
    integers.push(22);
    integers.push(23);
    integers.push(24);
    
    //查看顶部元素
    cout << "top:" << integers.top() << endl;     //top:24
    
    
    //最大堆
    priority_queue<int, vector<int>, greater<int>> integers2;
    
    //放入5个元素
    integers2.push(20);
    integers2.push(21);
    integers2.push(22);
    integers2.push(23);
    integers2.push(24);
    
    //查看顶部元素
    cout << "top:" << integers2.top() << endl;     //top:20
}

//判断是否为空
void empty_test(void)
{
    priority_queue<int> integers;
    
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
    priority_queue<int> integers;
    
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

//删除元素
void pop_test(void)
{
    priority_queue<int> integers;
    
    integers.push(10);
    integers.push(12);
    integers.push(66);
    
    cout << "priority_queue contains " << integers.size() << " elements" << endl;
    while(integers.size() != 0) {
        cout << "Deleting elements: " << integers.top() << endl;
        integers.pop(); //removes element at top
    }
    
    if(integers.empty())
        cout << "The priority_queue is now empty!" << endl;
}

//插入元素
void push_test(void)
{
    priority_queue<int> integers;
    
    integers.push(10);
    integers.push(12);
    integers.push(66);
    
    cout << "priority_queue contains " << integers.size() << " elements" << endl;
    while(integers.size() != 0) {
        cout << "Deleting elements: " << integers.top() << endl;
        integers.pop(); //removes element at top
    }
    
    if(integers.empty())
        cout << "The priority_queue is now empty!" << endl;
    
    
    //最大堆
    priority_queue<int, vector<int>, greater<int>> integers2;
    
    integers2.push(10);
    integers2.push(12);
    integers2.push(66);
    
    cout << "priority_queue contains " << integers2.size() << " elements" << endl;
    while(integers2.size() != 0) {
        cout << "Deleting elements: " << integers2.top() << endl;
        integers2.pop(); //removes element at top
    }
    
    if(integers2.empty())
        cout << "The priority_queue is now empty!" << endl;
}

//插入元素
void emplace_test(void)
{
    priority_queue<int> integers;
    
    integers.emplace(10);
    integers.emplace(12);
    integers.emplace(66);
    
    cout << "priority_queue contains " << integers.size() << " elements" << endl;
    while(integers.size() != 0) {
        cout << "Deleting elements: " << integers.top() << endl;
        integers.pop(); //removes element at top
    }
    
    if(integers.empty())
        cout << "The priority_queue is now empty!" << endl;
    
    
    //最大堆
    priority_queue<int, vector<int>, greater<int>> integers2;
    
    integers2.emplace(10);
    integers2.emplace(12);
    integers2.emplace(66);
    
    cout << "priority_queue contains " << integers2.size() << " elements" << endl;
    while(integers2.size() != 0) {
        cout << "Deleting elements: " << integers2.top() << endl;
        integers2.pop(); //removes element at top
    }
    
    if(integers2.empty())
        cout << "The priority_queue is now empty!" << endl;
}

struct custom_cmp //重写仿函数
{
    bool operator() (pair<int, int> a, pair<int, int> b) 
    {
        if(a.first == b.first) {
            return a.second < b.second; //大顶堆
        }
        return a.first > b.first; //小顶堆
    }
};

//实例化
void init_test(void)
{
    //整型 priority_queue 类
    priority_queue<int> integers;
    
    //使用一个priority_queue初始化另一个priority_queue，即复制priority_queue对象
    priority_queue<int> copyVector(integers);
    
    //使用一个priority_queue初始化另一个priority_queue，即复制priority_queue对象
    priority_queue<int> copyVector2 = integers;

    //底层容器默认为 vector, 可指定 deque 来存储数据
    priority_queue<int, vector<int>> intpriority_queueedInVec;
    //底层容器修改为 deque
    priority_queue<int, deque<int>> intpriority_queueedInDeq;
    
    //底层容器默认使用 less 比较，默认最大堆
    priority_queue<int, vector<int>, less<int>> intpriority_queueedInVecless;
    //使用 greater 比较，最小堆
    priority_queue<int, vector<int>, greater<int>> intpriority_queueedInVecgreater;
    
    //pair最大堆
    priority_queue<pair<int, int>, vector< pair<int, int> >, less< pair<int, int> > > pqMax;
    //pair最小堆
    priority_queue<pair<int, int>, vector< pair<int, int> >, greater< pair<int, int> > > pqMin;
    
    //自定义
    priority_queue<pair<int, int>, vector<pair<int, int> >, custom_cmp> pqcustom;
    
    //C++ 20支持
    // auto cmp = [] (const auto& a, const auto& b) {
        // return a.first > b.first || (a.first == b.first && a.second < b.second); //第一个元素小顶堆，如果相等则第二个元素大顶堆
    // };
    // auto cmp = [] (const auto& a, const auto& b) {
        // const auto& [a1, a2] = a;
        // const auto& [b1, b2] = b;
        // return a1 > b1 || a1 == b1 && a2 < b2; //第一个元素小顶堆，如果相等则第二个元素大顶堆
    // };
    // priority_queue<pair<int, int>, vector<pair<int, int> >, decltype(cmp)> pqcustom2;
    
    // priority_queue<pair<int, int>, vector<pair<int, int> >, decltype([] (const auto& a, const auto& b) {
        // return a.first > b.first || (a.first == b.first && a.second < b.second); //第一个元素小顶堆，如果相等则第二个元素大顶堆
    // })> pqcustom3;
}
/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    cout << __cplusplus << endl;
    
    // init_test();        //实例化
    emplace_test();     //末尾插入元素
    // push_test();        //末尾插入元素
    // pop_test();         //开头删除元素
    // size_test();        //大小
    // empty_test();       //判断是否为空
    // top_test();         //访问元素
    // swap_test();        //交换元素
    // assign_test();      //分配新的内容替换原有的内容
    
    return 0;
}