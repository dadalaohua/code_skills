#include <iostream>
#include <vector>
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
void list_print(list<int> integers)
{
   cout << "list elements are: ";
// #if __cplusplus >= 201103L
    for (auto it = integers.begin(); it != integers.end(); it++)
        cout << *it << " ";
// #else
    // for (list<int>::iterator it = integers.begin(); it != integers.end(); it++)
       // cout << *it << " ";
// #endif
   cout << endl;
}

//三维 vector 实例化
void three_dimensional_init_test(void)
{
    list<list<list<int>>> obj(3, list<list<int>>(4));
    list<list<list<int>>> obj2(3, list<list<int>>(4, list<int>(5)));
    list<list<list<int>>> obj3(3, list<list<int>>(4, list<int>(5, 6)));
    
    //输出三维 list
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

//二维 list 实例化
void two_dimensional_init_test(void)
{
    int row = 5, col = 6; 
    
    //定义二维 list 5行6列 
    list< list<int> > obj(row, list<int>(col)); 
 
    //输出二维 list
    for (list<list<int>>::iterator i = obj.begin(); i != obj.end(); i++) {
        for (list<int>::iterator j = (*i).begin(); j != (*i).end(); j++)
            cout << *j << " ";
        cout << endl;
    }
    cout << endl;
    
    
    //定义二维 list 5行6列 初始化所有的值为 7
    list< list<int> > obj2(row, list<int>(col, 7)); 
 
    //输出二维 list
    for (auto i = obj2.begin(); i != obj2.end(); i++) {
        for (auto j = (*i).begin(); j != (*i).end(); j++)
            cout << *j << " ";
        cout << endl;
    }
    cout << endl;
    
    //定义二维 list 5行
    list< list<int> > obj3(row);
    
    //动态二维 list 为每一行为 6 列，值全为9 
    for (auto i = obj3.begin(); i != obj3.end(); i++) {
        (*i).resize(col, 9); 
    }
    
    //输出二维 list
    for (auto i = obj3.begin(); i != obj3.end(); i++) {
        for (auto j = (*i).begin(); j != (*i).end(); j++)
            cout << *j << " ";
        cout << endl;
    }
    cout << endl;
    
#if __cplusplus >= 201703L
    //定义二维 list 5行6列 初始化所有的值为 7
    list obj4(row, list<int> (col, 7));
    
    //输出二维 list
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
    list<int> integers = {15, 84, 64, 38, 55};
    
    list_print(integers); //list elements are: 15 84 64 38 55
    
    integers.reverse();
    
    list_print(integers); //list elements are: 55 38 64 84 15
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
    list<int> integers;
    
    //放入5个元素
    integers.push_back(15);
    integers.push_back(84);
    integers.push_back(64);
    integers.push_back(38);
    integers.push_back(55);
    
    list_print(integers); //list elements are: 15 84 64 38 55
    
    //排序， 从小到大
    integers.sort();
    
    list_print(integers); //list elements are: 15 38 55 64 84 
    
    //排序， 从大到小
    //方法一：
    integers.sort(sort_predicate_descending);
    
    list_print(integers); //list elements are: 84 64 55 38 15
    
    //方法二：
    integers.sort([&](int x, int y) {
        return x > y;
    });
    
    list_print(integers); //list elements are: 84 64 55 38 15
    
    //自定义结构排序
    list <test_item> item;
    item.push_back(test_item("Jack", "178897"));
    item.push_back(test_item("Bill", "978945"));
    item.push_back(test_item("Angi", "348158"));
    
    display_as_test_item(item);
    // Jack: 178897
    // Bill: 978945
    // Angi: 348158
    
    // test_item 定义了运算符 < , test_item::operator<让 list::sort按姓名字母顺序排列元素
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
    list<int> integers;
    
    //放入5个元素
    integers.push_back(20);
    integers.push_back(21);
    integers.push_back(22);
    integers.push_back(23);
    integers.push_back(24);
    
    list_print(integers); //list elements are: 20 21 22 23 24 
    
    //替换成3个35
    integers.assign(3, 35);
    
    list_print(integers); //list elements are: 35 35 35
    
    list<int> another(6, 55);
    
    //替换成 another 的内容
    integers.assign(another.begin(), another.end());
    
    list_print(integers); //list elements are: 55 55 55 55 55 55
    
    list<int> another2(5, 86);
    
    //将 another2 的内容赋给 integers
    integers = another2;
    
    list_print(integers); //list elements are: 86 86 86 86 86 
    
    list<int> another3(8, 36);
    
    //将 another3 的内容赋给 integers，another3内的值被清空
    integers = move(another3);
    
    list_print(integers); //list elements are: 36 36 36 36 36 36 36 36 
}

//交换元素
void swap_test(void)
{
    list<int> integers;
    
    //放入5个元素
    integers.push_back(20);
    integers.push_back(21);
    integers.push_back(22);
    integers.push_back(23);
    integers.push_back(24);
    
    list<int> another(3, 30);
    
    //交换
    integers.swap(another);
    
    list_print(integers); //list elements are: 30 30 30 
    list_print(another);  //list elements are: 20 21 22 23 24
}

//访问元素
void at_test(void)
{
    list<int> integers;
    
    //放入5个元素
    integers.push_back(20);
    integers.push_back(21);
    integers.push_back(22);
    integers.push_back(23);
    integers.push_back(24);
    
    //输出首元素
    cout << "Front:" << integers.front() << endl;   //Front:20
    
    //输出尾元素
    cout << "Back:" << integers.back() << endl;     //Back:24
}

//判断是否为空
void empty_test(void)
{
    list<int> integers;
    
    cout << "Empty:" << integers.empty() << endl;   //Empty:1
    
    //放入元素
    integers.push_back(20);
    
    cout << "Empty:" << integers.empty() << endl;   //Empty:0
    
    //删除元素
    integers.pop_back();
    
    cout << "Empty:" << integers.empty() << endl;   //Empty:1
}

//清空元素
void clear_test(void)
{
    list<int> integers;
    
    //先放入3个元素
    integers.push_back(20);
    integers.push_back(21);
    integers.push_back(22);
    
    list_print(integers); //list elements are: 20 21 22 
    
    //清空所有元素
    integers.clear();
    
    list_print(integers); //list elements are:
}

//删除元素
void erase_test(void)
{
    list<int> integers;
    
    integers.push_back(20);
    integers.push_back(21);
    integers.push_back(22);
    integers.push_back(23);
    integers.push_back(24);
    
    list_print(integers); //list elements are: 20 21 22 23 24 
    
    //删除特定元素
    for(list<int>::iterator it = integers.begin(); it != integers.end();) {
        if(*it == 22) {
            it = integers.erase(it);
        } else {
            ++it;
        }
    }
    
    list_print(integers); //list elements are: 20 21 23 24 
    
    //清空所有元素
    integers.erase(integers.begin(), integers.end());
    
    list_print(integers); //list elements are:
    
    
    //自定义结构
    list <test_item> item;
    item.push_back(test_item("Jack", "178897"));
    item.push_back(test_item("Bill", "978945"));
    item.push_back(test_item("Angi", "348158"));
    
    display_as_test_item(item);
    // Jack: 178897
    // Bill: 978945
    // Angi: 348158
    
    // test_item 定义了运算符 == , test_item::operator==让 list::remove 与 list 中的姓名进行对比，姓名相同时返回true
    item.remove(test_item("Bill", ""));
    display_as_test_item(item);
    //Jack: 178897
    //Angi: 348158
}

//大小
void size_test(void)
{
    //设置初始大小为 2
    list<int> integers(2);
    
    //大小
    cout << "Size:" << integers.size() << endl; //Size:2
    
    integers.push_back(10);
    
    cout << "Size:" << integers.size() << endl; //Size:3
    
    integers.push_back(11);
    
    cout << "Size:" << integers.size() << endl; //Size:4
    
    integers.push_back(12);
    
    cout << "Size:" << integers.size() << endl; //Size:5
    
    // 最大可允许的list元素数量值
    cout << "Max_size:" << integers.max_size() << endl;
    
    //默认
    list<int> another;
    
    cout << "Size:" << another.size() << endl; //Size:0
    
    another.push_back(123);
    
    cout << "Size:" << another.size() << endl; //Size:1
    
    cout << "Max_size:" << integers.max_size() << endl;
    
    //修改大小
    another.resize(8);
    cout << "Size:" << another.size() << endl; //Size:8
}

//反向遍历元素
void r_iterate_test(void)
{
    list<int> integers;
    
    integers.push_back(10);
    integers.push_back(12);
    integers.push_back(66);
    
    list<int>::reverse_iterator element = integers.rbegin();
    while(element != integers.rend()) {
        cout << *element << " ";
        
        ++element;
    }
    cout << endl;
    
    list<int>::const_reverse_iterator celement = integers.crbegin();
    while(celement != integers.crend()) {
        cout << *celement << " ";
        
        ++celement;
    }
    cout << endl;
    
    auto acelement = integers.crbegin();
    while(acelement != integers.crend()) {
        cout << *acelement << " ";
        
        ++acelement;
    }
    cout << endl;
    
    for (list<int>::reverse_iterator it = integers.rbegin(); it != integers.rend(); it++)
       cout << *it << " ";
    cout << endl;
    
    for (auto it = integers.rbegin(); it != integers.rend(); it++)
        cout << *it << " ";
    cout << endl;
}

//正向遍历元素
void iterate_test(void)
{
    list<int> integers;
    
    integers.push_back(10);
    integers.push_back(12);
    integers.push_back(66);
    
    for (int v : integers)
       cout << v << " ";
    cout << endl;

    //使用迭代器
    list<int>::iterator element = integers.begin();
    while(element != integers.end()) {
        cout << *element << " ";
        
        ++element;
    }
    cout << endl;
    
    list<int>::const_iterator celement = integers.cbegin();
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
    
    for (list<int>::iterator it = integers.begin(); it != integers.end(); it++)
       cout << *it << " ";
    cout << endl;
    
    for (auto it = integers.begin(); it != integers.end(); it++)
        cout << *it << " ";
    cout << endl;
}

//在指定位置插入元素
void insert_test(void)
{
    //设置初始大小为4, 值为90
    list<int> integers(4, 90);
    
    list_print(integers); //list elements are: 90 90 90 90
    
    //在起始位置插入值 25
    integers.insert(integers.begin(), 25);
    
    list_print(integers); //list elements are: 25 90 90 90 90
    
    //在末尾位置插入 2 个值 35
    integers.insert(integers.end(), 2, 35);
    
    list_print(integers); //list elements are: 25 90 90 90 90 35 35
    
    //另一个 list，有两个值为30的元素
    list<int> another(2, 30);
    
    //将 another 的元素插入 integers 从起始位置开始的位置
    integers.insert(integers.begin(), another.begin(), another.end());
    
    list_print(integers); //list elements are: 30 30 25 90 90 90 90 35 35
    
    //将 another 的元素插入 integers 从末尾位置开始的位置
    integers.insert(integers.end(), another.begin(), another.end());
    
    list_print(integers); //list elements are: 30 30 25 90 90 90 90 35 35 30 30 
}

//开头删除元素
void pop_front_test(void)
{
    list<int> integers;
    
    //先放入3个元素
    integers.push_front(10);
    integers.push_front(12);
    integers.push_front(66);
    
    list_print(integers); //list elements are: 66 12 10
    
    //删除开头第一个元素
    integers.pop_front();
    
    list_print(integers); //list elements are: 12 10 
    
    //删除开头第一个元素
    integers.pop_front();
    
    list_print(integers); //list elements are: 10 
}

//末尾删除元素
void pop_back_test(void)
{
    list<int> integers;
    
    //先放入3个元素
    integers.push_back(10);
    integers.push_back(12);
    integers.push_back(66);
    
    list_print(integers); //list elements are: 10 12 66 
    
    //删除最后一个元素
    integers.pop_back();
    
    list_print(integers); //list elements are: 10 12 
    
    //删除最后一个元素
    integers.pop_back();
    
    list_print(integers); //list elements are: 10 
}

//开头插入元素
void push_front_test(void)
{
    list<int> integers;
    
    integers.push_front(10);
    integers.push_front(12);
    integers.push_front(66);
    
    list_print(integers);  //list elements are: 66 12 10 
}

//末尾插入元素
void push_back_test(void)
{
    list<int> integers;
    
    integers.push_back(10);
    integers.push_back(12);
    integers.push_back(66);
    
    list_print(integers);  //list elements are: 10 12 66 
}

//实例化
void init_test(void)
{
    //整型 list 类
    list<int> integers;
    
    list_print(integers); //list elements are: 
    
    //C++11引入的列表初始化
    list<int> initList = { 1, 2, 3, 4, 5 };
    
    list_print(initList); //list elements are: 1 2 3 4 5 

    //设置初始大小为10
    list<int> tenElements(10);
    
    list_print(tenElements); //list elements are: 0 0 0 0 0 0 0 0 0 0 
    
    //设置初始大小为10, 值为90
    list<int> tenElemInit(10, 90);
    
    list_print(tenElemInit); //list elements are: 90 90 90 90 90 90 90 90 90 90
    
    //使用一个list初始化另一个list，即复制list对象
    list<int> copyList(tenElemInit);
    
    list_print(copyList); //list elements are: 90 90 90 90 90 90 90 90 90 90
    
    //使用一个list初始化另一个list，即复制list对象
    list<int> copyList2 = tenElemInit;
    
    list_print(copyList2); //list elements are: 90 90 90 90 90 90 90 90 90 90
    
    //使用一个vector的值来初始化list
    vector<int> initVector(8, 64);
    
    list<int> copyVector(initVector.begin(), initVector.end());
    
    list_print(copyVector); //list elements are: 64 64 64 64 64 64 64 64
    
    //使用一个vector的前五个元素值来初始化list
    list<int> partialCopy(initVector.begin(), initVector.begin() + 5);
    
    list_print(partialCopy); //list elements are: 64 64 64 64 64 
    
    //使用一个vector的前五个元素值来初始化list，其中cbegin和cend由于C++11引入
    list<int> partialCopy2(initVector.cbegin(), initVector.cbegin() + 5);
    
    list_print(partialCopy2); //list elements are: 64 64 64 64 64 
    
}
/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    cout << __cplusplus << endl;
    
    // init_test();        //实例化
    // push_back_test();   //末尾插入元素
    // push_front_test();  //开头插入元素
    // pop_front_test();   //开头删除元素
    // pop_back_test();    //末尾删除元素
    // insert_test();      //在指定位置插入元素
    // iterate_test();     //正向遍历元素
    // r_iterate_test();   //反向遍历元素
    // size_test();        //大小
    // erase_test();       //删除元素
    // clear_test();       //清空元素
    // empty_test();       //判断是否为空
    // at_test();          //访问元素
    // swap_test();        //交换元素
    // assign_test();      //分配新的内容替换原有的内容
    // sort_test();        //排序
    reverse_test();     //反转
    
    // two_dimensional_init_test();    //二维 list 实例化
    // three_dimensional_init_test();    //三维 list 实例化
    return 0;
}