#include <iostream>
#include <set>
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
void multiset_print(multiset<int> integers)
{
   cout << "multiset elements are: ";
// #if __cplusplus >= 201103L
   for (auto it = integers.begin(); it != integers.end(); it++)
       cout << *it << " ";
// #else
    // for (multiset<int>::iterator it = integers.begin(); it != integers.end(); it++)
       // cout << *it << " ";
// #endif
   cout << endl;
}
 
//三维 multiset 实例化
void three_dimensional_init_test(void)
{
    multiset<int> subobj1 = {10, 15, 18};
    multiset<int> subobj2 = {8, 26, 42};
    multiset<int> subobj3 = {37, 84, 86};
    multiset<multiset<int>> sobj1 = { subobj1, subobj2, subobj3 };
    multiset<multiset<int>> sobj2 = { subobj3, subobj2 };
    multiset<multiset<multiset<int>>> obj = { sobj1, sobj2 };

    //输出三维 multiset
    for (multiset<multiset<multiset<int>>>::iterator i = obj.begin(); i != obj.end(); i++) {
        for (multiset<multiset<int>>::iterator j = (*i).begin(); j != (*i).end(); j++) {
            for (multiset<int>::iterator k = (*j).begin(); k != (*j).end(); k++)
                cout << *k << " ";
            cout << endl;
        }
        cout << endl;
    }
    cout << endl;
}

//二维 multiset 实例化
void two_dimensional_init_test(void)
{
    //定义二维
    multiset<int> subobj1 = {10, 15, 18};
    multiset<int> subobj2 = {8, 26, 42};
    multiset<int> subobj3 = {37, 84, 86};
    multiset< multiset<int> > obj = { subobj1, subobj2, subobj3 };
 
    //输出二维 multiset
    for (multiset<multiset<int>>::iterator i = obj.begin(); i != obj.end(); i++) {
        for (multiset<int>::iterator j = (*i).begin(); j != (*i).end(); j++)
            cout << *j << " ";
        cout << endl;
    }
    cout << endl;
}

//二元排序谓词
template <typename T>
struct sort_descending
{
    bool operator() (const T& lhs, const T& rhs) const
    {
        return (lhs > rhs);
    }
};

//排序
void sort_test(void)
{
    multiset<int> integers = { 15, 84, 64, 38, 55 };
    
    //默认排序从小到大
    multiset_print(integers); //multiset elements are: 15 84 64 38 55
    
     //排序， 从大到小
    //方法一：
    multiset<int, sort_descending<int>> integers2 = { 15, 84, 64, 38, 55 };
    
    display_as_test_item(integers2);  //multiset elements are: 84 64 55 38 15
    
    //自定义结构排序
    multiset <test_item> item;
    item.insert(test_item("Jack", "178897"));
    item.insert(test_item("Bill", "978945"));
    item.insert(test_item("Angi", "348158"));
    
    // test_item 定义了运算符 < , test_item::operator<让 sort按姓名字母顺序排列元素
    display_as_test_item(item);
    // Angi: 348158
    // Bill: 978945
    // Jack: 178897
}

//分配新的内容替换原有的内容
void assign_test(void)
{
    multiset<int> integers = { 20, 21, 22, 23, 24 };
    
    multiset_print(integers); //multiset elements are: 20 21 22 23 24 
    
    multiset<int> another2 = {5, 86};
    
    //将 another2 的内容赋给 integers
    integers = another2;
    
    multiset_print(integers); //multiset elements are: 5 86 
    
    multiset<int> another3 = {8, 36};
    
    //将 another3 的内容赋给 integers，another3内的值被清空
    integers = move(another3);
    
    multiset_print(integers); //multiset elements are: 8 36 
}

//交换元素
void swap_test(void)
{
    multiset<int> integers = { 20, 21, 22, 23, 24 };
    multiset<int> another = { 30, 25 };
    
    //交换
    integers.swap(another);
    
    multiset_print(integers); //multiset elements are: 25 30
    multiset_print(another);  //multiset elements are: 20 21 22 23 24
}

//判断是否为空
void empty_test(void)
{
    multiset<int> integers;
    
    cout << "Empty:" << integers.empty() << endl;   //Empty:1
    
    //放入元素
    integers.insert(20);
    
    cout << "Empty:" << integers.empty() << endl;   //Empty:0
    
    //删除元素
    integers.erase(20);
    
    cout << "Empty:" << integers.empty() << endl;   //Empty:1
}

//清空元素
void clear_test(void)
{
    multiset<int> integers = { 20, 21, 22 };
    
    multiset_print(integers); //multiset elements are: 20 21 22 
    
    //清空所有元素
    integers.clear();
    
    multiset_print(integers); //multiset elements are:
}

//删除元素
void erase_test(void)
{
    multiset<int> integers = { 20, 21, 22, 23, 24, 25, 26, 27 };
    
    multiset_print(integers); //multiset elements are: 20 21 22 23 24 25 26 27
    
    //根据key删除特定元素
    integers.erase(23);
    
    multiset_print(integers); //multiset elements are: 20 21 22 24 25 26 27 
    
    //根据迭代器删除特定元素
    for(multiset<int>::iterator it = integers.begin(); it != integers.end();) {
        if(*it == 22) {
            it = integers.erase(it);
        } else {
            ++it;
        }
    }
    
    multiset_print(integers); //multiset elements are: 20 21 24 25 26 27
    
    //根据迭代器删除指定范围元素 删除 26 之后的元素，含26
    auto elementFound = integers.find(26);
    
    if(elementFound != integers.end()) {
        integers.erase(elementFound, integers.end());
    }
    
    multiset_print(integers); //multiset elements are: 20 21 24 25 
    
    //根据迭代器删除指定范围元素 删除 21 之前的元素，不含21
    auto anotherFind = integers.find(21);
    
    if(anotherFind != integers.end()) {
        integers.erase(integers.begin(), anotherFind);
    }
    
    multiset_print(integers); //multiset elements are: 21 24 25 
    
    //清空所有元素
    integers.erase(integers.begin(), integers.end());
    
    multiset_print(integers); //multiset elements are: 
    
    
    
    //自定义结构
    multiset <test_item> item;
    item.insert(test_item("Jack", "178897"));
    item.insert(test_item("Bill", "978945"));
    item.insert(test_item("Angi", "348158"));
    
    display_as_test_item(item);
    
    //查找元素 姓名为Bill
    auto itemFind = item.find(test_item("Bill", ""));
    
    if(itemFind != item.end()) {
        cout << "Element " << *itemFind << " found!" << endl;
        cout << "Displaying contents after erasing " << *itemFind << endl;
        item.erase(itemFind);
        display_as_test_item(item);
    } else {
        cout << "Element not found in multiset!" << endl;
    }
}

//大小
void size_test(void)
{
    //设置初始值
    multiset<int> integers = { 22, 8, 66 };
    
    //大小和容量
    cout << "Size:" << integers.size() << endl;
    
    integers.insert(10);
    
    cout << "Size:" << integers.size() << endl;
    
    integers.insert(11);
    
    cout << "Size:" << integers.size() << endl;
    
    integers.insert(12);
    
    cout << "Size:" << integers.size() << endl;
    
    // 最大可允许的multiset元素数量值
    cout << "Max_size:" << integers.max_size() << endl;
}

//反向遍历元素
void r_iterate_test(void)
{
    multiset<int> integers = { 22, 12, 66 };
    
    multiset<int>::reverse_iterator element = integers.rbegin();
    while(element != integers.rend()) {
        cout << *element << " ";
        
        ++element;
    }
    cout << endl;
    
    multiset<int>::const_reverse_iterator celement = integers.crbegin();
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
    
    for (multiset<int>::reverse_iterator it = integers.rbegin(); it != integers.rend(); it++)
       cout << *it << " ";
    cout << endl;
    
    for (multiset<int>::const_reverse_iterator it = integers.crbegin(); it != integers.crend(); it++)
       cout << *it << " ";
    cout << endl;
    
    for (auto it = integers.rbegin(); it != integers.rend(); it++)
        cout << *it << " ";
    cout << endl;
}

//正向遍历元素
void iterate_test(void)
{
    multiset<int> integers = { 22, 12, 66 };
    
    for (int v : integers)
       cout << v << " ";
    cout << endl;

    //使用迭代器
    multiset<int>::iterator element = integers.begin();
    while(element != integers.end()) {
        cout << *element << " ";
        
        ++element;
    }
    cout << endl;
    
    multiset<int>::const_iterator celement = integers.cbegin();
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
    
    for (multiset<int>::iterator it = integers.begin(); it != integers.end(); it++)
       cout << *it << " ";
    cout << endl;
    
    for (multiset<int>::const_iterator it = integers.cbegin(); it != integers.cend(); it++)
       cout << *it << " ";
    cout << endl;
    
    for (auto it = integers.begin(); it != integers.end(); it++)
        cout << *it << " ";
    cout << endl;
}

//插入元素
void insert_test(void)
{
    //初始化
    multiset<int> integers = { 30, 10, 20, 50, 40 };
    
    multiset_print(integers); //multiset elements are: 10 20 30 40 50
    
    //插入值 56
    integers.insert(56);
    
    multiset_print(integers); //multiset elements are: 10 20 30 40 50 56 
    
    //插入值 16
    integers.insert(16);
    
    multiset_print(integers); //multiset elements are: 10 16 20 30 40 50 56 
    
    //插入值 25，这个integers.begin()没啥用
    integers.insert(integers.begin(), 25);
    
    multiset_print(integers); //multiset elements are: 10 16 20 25 30 40 50 56
    
    //插入值 35，这个integers.end()没啥用
    integers.insert(integers.end(), 35);
    
    multiset_print(integers); //multiset elements are: 10 16 20 25 30 35 40 50 56 
   
    //另一个 multiset，有两个元素
    multiset<int> another = {88, 36};
    
    //将 another 的元素插入 integers
    integers.insert(another.begin(), another.end());
    
    multiset_print(integers); //multiset elements are: 10 16 20 25 30 35 36 40 50 56 88 
}

//查找元素
void find_test(void)
{
    //初始化
    multiset<int> integers = { 30, 10, 20, 50, 40 };
    
    multiset_print(integers); //multiset elements are: 10 20 30 40 50
    
    //查找元素 30
    auto elementFound = integers.find(30);
    
    if(elementFound != integers.end()) {
        cout << "Element " << *elementFound << " found!" << endl;
    } else {
        cout << "Element not found in multiset!" << endl;
    }
    
    //查找元素 66
    auto anotherFind = integers.find(66);
    
    if(anotherFind != integers.end()) {
        cout << "Element " << *anotherFind << " found!" << endl;
    } else {
        cout << "Element not found in multiset!" << endl;
    }
    
    //自定义结构
    multiset <test_item> item;
    item.insert(test_item("Jack", "178897"));
    item.insert(test_item("Bill", "978945"));
    item.insert(test_item("Angi", "348158"));
    
    display_as_test_item(item);
    
    //查找元素 姓名为Bill
    auto itemFind = item.find(test_item("Bill", ""));
    
    if(itemFind != item.end()) {
        cout << "Element " << *itemFind << " found!" << endl;
    } else {
        cout << "Element not found in multiset!" << endl;
    }
    
    itemFind = item.find(test_item("John", ""));
    
    if(itemFind != item.end()) {
        cout << "Element " << *itemFind << " found!" << endl;
    } else {
        cout << "Element not found in multiset!" << endl;
    }
}

//实例化
void init_test(void)
{
    //整型 multiset 类
    multiset<int> integers;
    
    multiset_print(integers); //multiset elements are: 
    
    //C++11引入的列表初始化
    multiset<int> initSet = { 1, 2, 3, 4, 5 };
    
    multiset_print(initSet); //multiset elements are: 1 2 3 4 5 
    
    //初始化重复元素
    multiset<int> initSet2 = { 3, 3, 3 };
    
    multiset_print(initSet2); //multiset elements are: 3, 3, 3
    
     //使用一个multiset初始化另一个multiset，即复制multiset对象
    multiset<int> copySet(initSet);
    
    multiset_print(copySet); //multiset elements are: 1 2 3 4 5 
    
    //使用一个multiset初始化另一个multiset，即复制multiset对象
    multiset<int> copySet2 = initSet;
    
    multiset_print(copySet2); //multiset elements are: 1 2 3 4 5 
    
    //使用另一个multiset的所有元素初始化
    multiset<int> partialCopy(initSet.begin(), initSet.end());
    
    multiset_print(partialCopy); //multiset elements are: 1 2 3 4 5 
    
    //使用另一个multiset的所有元素初始化，其中cbegin和cend由于C++11引入 //不可用，为空
    // multiset<int> partialCopy2(initSet.cbegin(), initSet.cbegin());
    
    // multiset_print(partialCopy2); //multiset elements are:
    
    
    //使用 vector 的值来初始化 multiset
    vector<int> initVector = { 1, 2, 3, 4, 5 };
    
    multiset<int> copyVector(initVector.begin(), initVector.end());
    
    multiset_print(copyVector); //multiset elements are: 1 2 3 4 5
    
    //使用 list 的值来初始化 multiset
    list<int> initList = { 1, 2, 3, 4, 5 };
    
    multiset<int> copyList(initList.begin(), initList.end());
    
    multiset_print(copyList); //multiset elements are: 1 2 3 4 5
}
/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    cout << __cplusplus << endl;
    
    init_test();        //实例化
    // find_test();        //查找元素
    // insert_test();      //插入元素
    // iterate_test();     //正向遍历元素
    // r_iterate_test();   //反向遍历元素
    // size_test();        //大小
    // erase_test();       //删除元素
    // clear_test();       //清空元素
    // empty_test();       //判断是否为空
    // swap_test();        //交换元素
    // assign_test();      //分配新的内容替换原有的内容
    // sort_test();        //排序
    
    // two_dimensional_init_test();    //二维 multiset 实例化
    // three_dimensional_init_test();    //三维 multiset 实例化
    return 0;
}