#include <iostream>
#include <vector>
#include <forward_list>

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
template <typename T>
void display_as_test_item(const T& container)
{
    for (auto element = container.cbegin(); 
        element != container.cend();
        ++element)
       cout << *element << endl;
       
   cout << endl;
}

//printing all elements
void forward_list_print(forward_list<int> integers)
{
   cout << "forward_list elements are: ";
// #if __cplusplus >= 201103L
    for (auto it = integers.begin(); it != integers.end(); it++)
        cout << *it << " ";
// #else
    // for (forward_list<int>::iterator it = integers.begin(); it != integers.end(); it++)
       // cout << *it << " ";
// #endif
   cout << endl;
}

//三维 vector 实例化
void three_dimensional_init_test(void)
{
    forward_list<forward_list<forward_list<int>>> obj(3, forward_list<forward_list<int>>(4));
    forward_list<forward_list<forward_list<int>>> obj2(3, forward_list<forward_list<int>>(4, forward_list<int>(5)));
    forward_list<forward_list<forward_list<int>>> obj3(3, forward_list<forward_list<int>>(4, forward_list<int>(5, 6)));
    
    //输出三维 forward_list
    for (auto i = obj3.begin(); i != obj3.end(); i++) {
        for (auto j = (*i).begin(); j != (*i).end(); j++) {
            for (auto k = (*j).begin(); k != (*j).end(); k++) {
                cout << *k << " ";
            }
            cout << endl;
        }
        cout << endl;
    }
    cout << endl;
}

//二维 forward_list 实例化
void two_dimensional_init_test(void)
{
    int row = 5, col = 6; 
    
    //定义二维 forward_list 5行6列 
    forward_list< forward_list<int> > obj(row, forward_list<int>(col)); 
 
    //输出二维 forward_list
    for (forward_list<forward_list<int>>::iterator i = obj.begin(); i != obj.end(); i++) {
        for (forward_list<int>::iterator j = (*i).begin(); j != (*i).end(); j++)
            cout << *j << " ";
        cout << endl;
    }
    cout << endl;
    
    
    //定义二维 forward_list 5行6列 初始化所有的值为 7
    forward_list< forward_list<int> > obj2(row, forward_list<int>(col, 7)); 
 
    //输出二维 forward_list
    for (auto i = obj2.begin(); i != obj2.end(); i++) {
        for (auto j = (*i).begin(); j != (*i).end(); j++)
            cout << *j << " ";
        cout << endl;
    }
    cout << endl;
    
    //定义二维 forward_list 5行
    forward_list< forward_list<int> > obj3(row);
    
    //动态二维 forward_list 为每一行为 6 列，值全为9 
    for (auto i = obj3.begin(); i != obj3.end(); i++) {
        (*i).resize(col, 9); 
    }
    
    //输出二维 forward_list
    for (auto i = obj3.begin(); i != obj3.end(); i++) {
        for (auto j = (*i).begin(); j != (*i).end(); j++)
            cout << *j << " ";
        cout << endl;
    }
    cout << endl;
    
#if __cplusplus >= 201703L
    //定义二维 forward_list 5行6列 初始化所有的值为 7
    forward_list obj4(row, forward_list<int> (col, 7));
    
    //输出二维 forward_list
    for (auto i = obj4.begin(); i != obj4.end(); i++) {
        for (auto j = (*i).begin(); j != (*i).end(); j++)
            cout << *j << " ";
        cout << endl;
    }
    cout << endl;
#endif
}

//反转
void reverse_test(void)
{
    forward_list<int> integers = {15, 84, 64, 38, 55};
    
    forward_list_print(integers); //forward_list elements are: 15 84 64 38 55
    
    integers.reverse();
    
    forward_list_print(integers); //forward_list elements are: 55 38 64 84 15
}

//二元谓词函数
bool sort_predicate_descending(int x, int y)
{
    return x > y;
}
//其他写法
// bool sort_predicate_descending(const int& x, const int& y)
// {
    // return x > y;
// }

//排序
void sort_test(void)
{
    forward_list<int> integers = {15, 84, 64, 38, 55};
    
    forward_list_print(integers); //forward_list elements are: 15 84 64 38 55
    
    //排序， 从小到大
    integers.sort();
    
    forward_list_print(integers); //forward_list elements are: 15 38 55 64 84 
    
    //排序， 从大到小
    //方法一：
    integers.sort(sort_predicate_descending);
    
    forward_list_print(integers); //forward_list elements are: 84 64 55 38 15
    
    //方法二：
    integers.sort([&](int x, int y) {
        return x > y;
    });
    
    forward_list_print(integers); //forward_list elements are: 84 64 55 38 15
    
    //自定义结构排序
    forward_list <test_item> item;
    item.push_front(test_item("Angi", "348158"));
    item.push_front(test_item("Bill", "978945"));
    item.push_front(test_item("Jack", "178897"));
    
    display_as_test_item(item);
    // Jack: 178897
    // Bill: 978945
    // Angi: 348158
    
    // test_item 定义了运算符 < , test_item::operator<让 forward_list::sort按姓名字母顺序排列元素
    item.sort();
    display_as_test_item(item);
    // Angi: 348158
    // Bill: 978945
    // Jack: 178897
    
    // 使用二元谓词函数按电话号码进行排序
    item.sort(sort_phone_number);
    display_as_test_item(item);
    // Jack: 178897
    // Angi: 348158
    // Bill: 978945
}

//分配新的内容替换原有的内容
void assign_test(void)
{
    forward_list<int> integers = {20, 21, 22, 23, 24};
    
    forward_list_print(integers); //forward_list elements are: 20 21 22 23 24 
    
    //替换成3个35
    integers.assign(3, 35);
    
    forward_list_print(integers); //forward_list elements are: 35 35 35
    
    forward_list<int> another(6, 55);
    
    //替换成 another 的内容
    integers.assign(another.begin(), another.end());
    
    forward_list_print(integers); //forward_list elements are: 55 55 55 55 55 55
    
    forward_list<int> another2(5, 86);
    
    //将 another2 的内容赋给 integers
    integers = another2;
    
    forward_list_print(integers); //forward_list elements are: 86 86 86 86 86 
    
    forward_list<int> another3(8, 36);
    
    //将 another3 的内容赋给 integers，another3内的值被清空
    integers = move(another3);
    
    forward_list_print(integers); //forward_list elements are: 36 36 36 36 36 36 36 36 
}

//交换元素
void swap_test(void)
{
    forward_list<int> integers = {20, 21, 22, 23, 24};
    
    forward_list<int> another(3, 30);
    
    //交换
    integers.swap(another);
    
    forward_list_print(integers); //forward_list elements are: 30 30 30 
    forward_list_print(another);  //forward_list elements are: 20 21 22 23 24
}

//访问元素
void at_test(void)
{
    forward_list<int> integers = {20, 21, 22, 23, 24};
    
    //输出首元素
    cout << "Front:" << integers.front() << endl;   //Front:20
}

//判断是否为空
void empty_test(void)
{
    forward_list<int> integers;
    
    cout << "Empty:" << integers.empty() << endl;   //Empty:1
    
    //放入元素
    integers.push_front(20);
    
    cout << "Empty:" << integers.empty() << endl;   //Empty:0
    
    //删除元素
    integers.pop_front();
    
    cout << "Empty:" << integers.empty() << endl;   //Empty:1
}

//清空元素
void clear_test(void)
{
    forward_list<int> integers = {20, 21, 22};
    
    forward_list_print(integers); //forward_list elements are: 20 21 22 
    
    //清空所有元素
    integers.clear();
    
    forward_list_print(integers); //forward_list elements are:
}

//大小
void size_test(void)
{
    //设置初始大小为 2
    forward_list<int> integers(2);
    
    // 最大可允许的forward_list元素数量值
    cout << "Max_size:" << integers.max_size() << endl;
}

//正向遍历元素
void iterate_test(void)
{
    forward_list<int> integers = {10, 12, 66};
    
    for (int v : integers)
       cout << v << " ";
    cout << endl;

    //使用迭代器
    forward_list<int>::iterator element = integers.begin();
    while(element != integers.end()) {
        cout << *element << " ";
        
        ++element;
    }
    cout << endl;
    
    forward_list<int>::const_iterator celement = integers.cbegin();
    while(celement != integers.cend()) {
        cout << *celement << " ";
        
        ++celement;
    }
    cout << endl;
    
    auto acelement = integers.cbegin();
    while(acelement != integers.cend()) {
        cout << *acelement << " ";
        
        ++acelement;
    }
    cout << endl;
    
    for (forward_list<int>::iterator it = integers.begin(); it != integers.end(); it++)
       cout << *it << " ";
    cout << endl;
    
    for (auto it = integers.begin(); it != integers.end(); it++)
        cout << *it << " ";
    cout << endl;
}

//开头删除元素
void pop_front_test(void)
{
    forward_list<int> integers;
    
    //先放入3个元素
    integers.push_front(10);
    integers.push_front(12);
    integers.push_front(66);
    
    forward_list_print(integers); //forward_list elements are: 66 12 10
    
    //删除开头第一个元素
    integers.pop_front();
    
    forward_list_print(integers); //forward_list elements are: 12 10 
    
    //删除开头第一个元素
    integers.pop_front();
    
    forward_list_print(integers); //forward_list elements are: 10 
}

//开头插入元素
void push_front_test(void)
{
    forward_list<int> integers;
    
    integers.push_front(10);
    integers.push_front(12);
    integers.push_front(66);
    
    forward_list_print(integers);  //forward_list elements are: 66 12 10 
}

//实例化
void init_test(void)
{
    //整型 forward_list 类
    forward_list<int> integers;
    
    forward_list_print(integers); //forward_list elements are: 
    
    //C++11引入的列表初始化
    forward_list<int> initList = { 1, 2, 3, 4, 5 };
    
    forward_list_print(initList); //forward_list elements are: 1 2 3 4 5 

    //设置初始大小为10
    forward_list<int> tenElements(10);
    
    forward_list_print(tenElements); //forward_list elements are: 0 0 0 0 0 0 0 0 0 0 //未初始化，数值随机，为栈的值
    
    //设置初始大小为10, 值为90
    forward_list<int> tenElemInit(10, 90);
    
    forward_list_print(tenElemInit); //forward_list elements are: 90 90 90 90 90 90 90 90 90 90
    
    //使用一个forward_list初始化另一个forward_list，即复制forward_list对象
    forward_list<int> copyList(tenElemInit);
    
    forward_list_print(copyList); //forward_list elements are: 90 90 90 90 90 90 90 90 90 90
    
    //使用一个forward_list初始化另一个forward_list，即复制forward_list对象
    forward_list<int> copyList2 = tenElemInit;
    
    forward_list_print(copyList2); //forward_list elements are: 90 90 90 90 90 90 90 90 90 90
    
    //使用一个vector的值来初始化forward_list
    vector<int> initVector(8, 64);
    
    forward_list<int> copyVector(initVector.begin(), initVector.end());
    
    forward_list_print(copyVector); //forward_list elements are: 64 64 64 64 64 64 64 64
    
    //使用一个vector的前五个元素值来初始化forward_list
    forward_list<int> partialCopy(initVector.begin(), initVector.begin() + 5);
    
    forward_list_print(partialCopy); //forward_list elements are: 64 64 64 64 64 
    
    //使用一个vector的前五个元素值来初始化forward_list，其中cbegin和cend由于C++11引入
    forward_list<int> partialCopy2(initVector.cbegin(), initVector.cbegin() + 5);
    
    forward_list_print(partialCopy2); //forward_list elements are: 64 64 64 64 64 
    
}
/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    cout << __cplusplus << endl;
    
    init_test();        //实例化
    // push_front_test();  //开头插入元素
    // pop_front_test();   //开头删除元素
    // iterate_test();     //正向遍历元素
    // size_test();        //大小
    // clear_test();       //清空元素
    // empty_test();       //判断是否为空
    // at_test();          //访问元素
    // swap_test();        //交换元素
    // assign_test();      //分配新的内容替换原有的内容
    // sort_test();        //排序
    // reverse_test();     //反转
    
    // two_dimensional_init_test();    //二维 forward_list 实例化
    // three_dimensional_init_test();    //三维 forward_list 实例化
    return 0;
}