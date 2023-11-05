#include <iostream>
#include <stack>
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
    stack<int> integers;
    
    //放入5个元素
    integers.push(20);
    integers.push(21);
    integers.push(22);
    integers.push(23);
    integers.push(24);
    
    stack<int> another2;
    
    another2.push(86);
    another2.push(86);
    
    //将 another2 的内容赋给 integers
    integers = another2;
    
    cout << "stack contains " << integers.size() << " elements" << endl;
    while(integers.size() != 0) {
        cout << "Popping topmost elements: " << integers.top() << endl;
        integers.pop();
    }
    
    stack<int> another3;
    
    another3.push(36);
    another3.push(36);
    
    //将 another3 的内容赋给 integers，another3内的值被清空
    integers = move(another3);
    
    cout << "stack contains " << integers.size() << " elements" << endl;
    while(integers.size() != 0) {
        cout << "Popping topmost elements: " << integers.top() << endl;
        integers.pop();
    } 
}

//交换元素
void swap_test(void)
{
    stack<int> integers;
    
    //放入5个元素
    integers.push(20);
    integers.push(21);
    integers.push(22);
    integers.push(23);
    integers.push(24);
    
    stack<int> another;
    another.push(0);
    another.push(1);
    another.push(2);
    
    //交换
    integers.swap(another);
    
    cout << "stack contains " << integers.size() << " elements" << endl;
    while(integers.size() != 0) {
        cout << "Popping topmost elements: " << integers.top() << endl;
        integers.pop();
    }
    
    cout << "stack contains " << another.size() << " elements" << endl;
    while(another.size() != 0) {
        cout << "Popping topmost elements: " << another.top() << endl;
        another.pop();
    }
}

//判断是否为空
void empty_test(void)
{
    stack<int> integers;
    
    cout << "Empty:" << integers.empty() << endl;   //Empty:1
    
    //放入元素
    integers.push(20);
    
    cout << "Empty:" << integers.empty() << endl;   //Empty:0
    
    //删除元素
    integers.pop();
    
    cout << "Empty:" << integers.empty() << endl;   //Empty:1
}

//大小与容量
void size_test(void)
{
    stack<int> integers;
    
    //大小
    cout << "Size:" << integers.size() << endl;
    
    integers.push(10);
    
    cout << "Size:" << integers.size() << endl;
    
    integers.push(11);
    
    cout << "Size:" << integers.size() << endl;
    
    integers.push(12);
    
    cout << "Size:" << integers.size() << endl;
    
    integers.pop();
    
    cout << "Size:" << integers.size() << endl;
    
    integers.pop();
    
    cout << "Size:" << integers.size() << endl;
    
    integers.pop();
    
    cout << "Size:" << integers.size() << endl;
}

//查看栈顶元素
void top_test(void)
{
    stack<int> integers;
    
    //先放入3个元素
    integers.push(10);
    integers.push(12);
    integers.push(66);
    
    //逐个弹出栈顶元素
    cout << "stack contains " << integers.size() << " elements" << endl;
    while(integers.size() != 0) {
        cout << "Popping topmost elements: " << integers.top() << endl;
        integers.pop();
    }
    
    if(integers.empty())
        cout << "Popping all elements empties stack!"  << endl;
}

//删除元素
void pop_test(void)
{
    stack<int> integers;
    
    //先放入3个元素
    integers.push(10);
    integers.push(12);
    integers.push(66);
    
    //逐个弹出栈顶元素
    cout << "stack contains " << integers.size() << " elements" << endl;
    while(integers.size() != 0) {
        cout << "Popping topmost elements: " << integers.top() << endl;
        integers.pop();
    }
    
    if(integers.empty())
        cout << "Popping all elements empties stack!"  << endl;
}

//插入元素
void push_test(void)
{
    stack<int> integers;
    
    integers.push(10);
    integers.push(12);
    integers.push(66);
    
    cout << "stack contains " << integers.size() << " elements" << endl;
    while(integers.size() != 0) {
        cout << "Popping topmost elements: " << integers.top() << endl;
        integers.pop();
    }
    
    if(integers.empty())
        cout << "Popping all elements empties stack!"  << endl;
}

//实例化
void init_test(void)
{
    //整型 stack 类
    stack<int> integers;
    
    //使用一个stack初始化另一个stack，即复制stack对象
    stack<int> copystack(integers);
    
    //使用一个stack初始化另一个stack，即复制stack对象
    stack<int> copystack2 = integers;
    
    //底层容器默认为 deque, 可指定 vector 或 list 来存储数据
    stack<int, deque<int>> intStackedInDeq;
    //底层容器修改为 vector
    stack<int, vector<int>> intStackedInVec;
    //底层容器修改为 vector
    stack<int, list<int>> intStackedInList;
}
/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    cout << __cplusplus << endl;
    
    init_test();        //实例化
    push_test();        //插入元素
    pop_test();         //删除元素
    top_test();         //查看栈顶元素
    size_test();        //大小
    empty_test();       //判断是否为空
    swap_test();        //交换元素
    assign_test();      //分配新的内容替换原有的内容

    return 0;
}