#include <iostream>
#include <unordered_set>
#include <vector>
#include <list>

using namespace std;
/************************************************************************/
/*                                                                      */
/************************************************************************/
//自定义测试数据结构
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
    
    // size_t operator()(const test_item& rc) const    //重载hash
    // {
        // return hash<string>()(rc.name) ^ hash<string>()(rc.phone);
    // }
};

class test_item_hash
{
public:
    size_t operator()(const test_item& item) const    //重载hash
    {
        return hash<string>()(item.name); //使用 name 做哈希
        // return hash<string>()(item.name) ^ hash<string>()(item.phone); //如果使用 name 和 phone 同时做哈希，那么传入的值必须包含 name 和 phone
    }
};
/************************************************************************/
/*                                                                      */
/************************************************************************/
//自定义测试数据结构 2
struct test_item_2
{
    int x;
};

size_t test_item_2_hash(const test_item_2& val)
{
    return hash<int>()(val.x);
}

bool test_item_2_equal(const test_item_2& val1, const test_item_2& val2)
{
    return val1.x == val2.x;
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
void unordered_set_print(unordered_set<int> integers)
{
   cout << "unordered_set elements are: ";
// #if __cplusplus >= 201103L
   for (auto it = integers.begin(); it != integers.end(); it++)
       cout << *it << " ";
// #else
    // for (unordered_set<int>::iterator it = integers.begin(); it != integers.end(); it++)
       // cout << *it << " ";
// #endif
   cout << endl;
   
   cout << "Number of elements, size() = " << integers.size() << endl;
   cout << "Bucket count = " << integers.bucket_count() << endl;
   cout << "Max load factor = " << integers.max_load_factor() << endl;
   cout << "Load factor = " << integers.load_factor() << endl << endl;
}

//分配新的内容替换原有的内容
void assign_test(void)
{
    unordered_set<int> integers = { 20, 21, 22, 23, 24 };
    
    unordered_set_print(integers); //unordered_set elements are: 20 21 22 23 24 
    
    unordered_set<int> another2 = {5, 86};
    
    //将 another2 的内容赋给 integers
    integers = another2;
    
    unordered_set_print(integers); //unordered_set elements are: 86 5 
    
    unordered_set<int> another3 = {8, 36};
    
    //将 another3 的内容赋给 integers，another3内的值被清空
    integers = move(another3);
    
    unordered_set_print(integers); //unordered_set elements are: 36 8  
}

//交换元素
void swap_test(void)
{
    unordered_set<int> integers = { 20, 21, 22, 23, 24 };
    unordered_set<int> another = { 30, 25 };
    
    //交换
    integers.swap(another);
    
    unordered_set_print(integers); //unordered_set elements are: 30 25 
    unordered_set_print(another);  //unordered_set elements are: 20 21 22 23 24 
}

//判断是否为空
void empty_test(void)
{
    unordered_set<int> integers;
    
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
    unordered_set<int> integers = { 20, 21, 22 };
    
    unordered_set_print(integers); //unordered_set elements are: 21 22 20  
    
    //清空所有元素
    integers.clear();
    
    unordered_set_print(integers); //unordered_set elements are:
}

//删除元素
void erase_test(void)
{
    unordered_set<int> integers = { 20, 21, 22, 23, 24, 25, 26, 27 };
    
    unordered_set_print(integers); //unordered_set elements are: 22 23 24 25 26 27 20 21 
    
    //根据key删除特定元素
    integers.erase(23);
    
    unordered_set_print(integers); //unordered_set elements are: 22 24 25 26 27 20 21 
    
    //根据迭代器删除特定元素
    for(unordered_set<int>::iterator it = integers.begin(); it != integers.end();) {
        if(*it == 22) {
            it = integers.erase(it);
        } else {
            ++it;
        }
    }
    
    unordered_set_print(integers); //unordered_set elements are: 24 25 26 27 20 21 
    
    //根据迭代器删除指定范围元素，该方式对于 unordered_set 没有意义。 删除 27 之后的元素，含27
    auto elementFound = integers.find(27);
    
    if(elementFound != integers.end()) {
        integers.erase(elementFound, integers.end());
    }
    
    unordered_set_print(integers); //unordered_set elements are: 24 25 26 
    
    //根据迭代器删除指定范围元素，该方式对于 unordered_set 没有意义。  删除 25 之前的元素，不含25
    auto anotherFind = integers.find(25);
    
    if(anotherFind != integers.end()) {
        integers.erase(integers.begin(), anotherFind);
    }
    
    unordered_set_print(integers); //unordered_set elements are: 25 26 
    
    //清空所有元素
    integers.erase(integers.begin(), integers.end());
    
    unordered_set_print(integers); //unordered_set elements are: 
    
    
    
    //自定义结构
    unordered_set <test_item, test_item_hash> item;
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
        cout << "Element not found in unordered_set!" << endl;
    }
    
    
    
    //自定义结构 2
    unordered_set<test_item_2, decltype(&test_item_2_hash), decltype(&test_item_2_equal)> item_2(3, test_item_2_hash, test_item_2_equal);
    item_2.insert(test_item_2{5});
    item_2.insert(test_item_2{15});
    item_2.insert(test_item_2{25});
    
    //打印
    for (auto element = item_2.cbegin(); 
        element != item_2.cend();
        ++element)
       cout << (*element).x << endl; 
    cout << endl;
    
    //查找元素 15
    auto itemFind2 = item_2.find(test_item_2{15});
    
    if(itemFind2 != item_2.end()) {
        cout << "Element " << itemFind2->x << " found!" << endl;
        cout << "Displaying contents after erasing " << itemFind2->x << endl;
        item_2.erase(itemFind2);
    } else {
        cout << "Element not found in unordered_set!" << endl;
    }
    
    //打印
    for (auto element = item_2.cbegin(); 
        element != item_2.cend();
        ++element)
       cout << (*element).x << endl; 
    cout << endl;
}

//大小
void size_test(void)
{
    //设置初始值
    unordered_set<int> integers = { 22, 8, 66 };
    
    //大小和容量
    cout << "Size:" << integers.size() << endl;
    
    integers.insert(10);
    
    cout << "Size:" << integers.size() << endl;
    
    integers.insert(11);
    
    cout << "Size:" << integers.size() << endl;
    
    integers.insert(12);
    
    cout << "Size:" << integers.size() << endl;
    
    // 最大可允许的unordered_set元素数量值
    cout << "Max_size:" << integers.max_size() << endl;
}


//正向遍历元素
void iterate_test(void)
{
    unordered_set<int> integers = { 22, 12, 66 };
    
    for (int v : integers)
       cout << v << " ";
    cout << endl;

    //使用迭代器
    unordered_set<int>::iterator element = integers.begin();
    while(element != integers.end()) {
        cout << *element << " ";
        
        ++element;
    }
    cout << endl;
    
    unordered_set<int>::const_iterator celement = integers.cbegin();
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
    
    for (unordered_set<int>::iterator it = integers.begin(); it != integers.end(); it++)
       cout << *it << " ";
    cout << endl;
    
    for (unordered_set<int>::const_iterator it = integers.cbegin(); it != integers.cend(); it++)
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
    unordered_set<int> integers = { 30, 10, 20, 50, 40 };
    
    unordered_set_print(integers); //unordered_set elements are: 40 50 20 10 30 
    
    //插入值 56
    integers.insert(56);
    
    unordered_set_print(integers); //unordered_set elements are: 56 50 40 30 20 10 
    
    //插入值 16
    integers.insert(16);
    
    unordered_set_print(integers); //unordered_set elements are: 56 16 50 40 30 20 10 
    
    //插入值 25，这个integers.begin()没啥用
    integers.insert(integers.begin(), 25);
    
    unordered_set_print(integers); //unordered_set elements are: 56 25 16 50 40 30 20 10 
    
    //插入值 35，这个integers.end()没啥用
    integers.insert(integers.end(), 35);
    
    unordered_set_print(integers); //unordered_set elements are: 56 35 25 16 50 40 30 20 10 
   
    //另一个 unordered_set，有两个元素
    unordered_set<int> another = {88, 36};
    
    //将 another 的元素插入 integers
    integers.insert(another.begin(), another.end());
    
    unordered_set_print(integers); //unordered_set elements are: 88 56 35 36 25 16 50 40 30 20 10 
}

//查找元素
void find_test(void)
{
    //初始化
    unordered_set<int> integers = { 30, 10, 20, 50, 40 };
    
    unordered_set_print(integers); //unordered_set elements are: 40 50 20 10 30 
     
    //查找元素 30
    auto elementFound = integers.find(30);
    
    if(elementFound != integers.end()) {
        cout << "Element " << *elementFound << " found!" << endl;
    } else {
        cout << "Element not found in unordered_set!" << endl;
    }
    
    //查找元素 66
    auto anotherFind = integers.find(66);
    
    if(anotherFind != integers.end()) {
        cout << "Element " << *anotherFind << " found!" << endl;
    } else {
        cout << "Element not found in unordered_set!" << endl;
    }
    
    //自定义结构
    unordered_set <test_item, test_item_hash> item;
    item.insert(test_item("Jack", "178897"));
    item.insert(test_item("Bill", "978945"));
    item.insert(test_item("Angi", "348158"));
    
    display_as_test_item(item);
    
    //查找元素 姓名为Bill
    auto itemFind = item.find(test_item("Bill", ""));
    
    if(itemFind != item.end()) {
        cout << "Element " << *itemFind << " found!" << endl;
    } else {
        cout << "Element not found in unordered_set!" << endl;
    }
    
    itemFind = item.find(test_item("John", ""));
    
    if(itemFind != item.end()) {
        cout << "Element " << *itemFind << " found!" << endl;
    } else {
        cout << "Element not found in unordered_set!" << endl;
    }
    
    
    //自定义结构 2
    unordered_set<test_item_2, decltype(&test_item_2_hash), decltype(&test_item_2_equal)> item_2(3, test_item_2_hash, test_item_2_equal);
    item_2.insert(test_item_2{5});
    item_2.insert(test_item_2{15});
    item_2.insert(test_item_2{25});
    
    //打印
    for (auto element = item_2.cbegin(); 
        element != item_2.cend();
        ++element)
       cout << (*element).x << endl; 
    cout << endl;
    
    //查找元素 15
    auto itemFind2 = item_2.find(test_item_2{15});
    
    if(itemFind2 != item_2.end()) {
        cout << "Element " << itemFind2->x << " found!" << endl;
    } else {
        cout << "Element not found in unordered_set!" << endl;
    }
    
    itemFind2 = item_2.find(test_item_2{20});
    
    if(itemFind2 != item_2.end()) {
        cout << "Element " << (*itemFind2).x << " found!" << endl;
    } else {
        cout << "Element not found in unordered_set!" << endl;
    }
}

//实例化
void init_test(void)
{
    //整型 unordered_set 类
    unordered_set<int> integers;
    
    unordered_set_print(integers); //unordered_set elements are: 
    
    //C++11引入的列表初始化
    unordered_set<int> initSet = { 1, 2, 3, 4, 5 };
    
    unordered_set_print(initSet); //unordered_set elements are: 5 1 2 3 4 
    
    //初始化重复元素
    unordered_set<int> initSet2 = { 3, 3, 3 };
    
    unordered_set_print(initSet2); //unordered_set elements are: 3
    
     //使用一个unordered_set初始化另一个unordered_set，即复制unordered_set对象
    unordered_set<int> copySet(initSet);
    
    unordered_set_print(copySet); //unordered_set elements are: 5 1 2 3 4 
    
    //使用一个unordered_set初始化另一个unordered_set，即复制unordered_set对象
    unordered_set<int> copySet2 = initSet;
    
    unordered_set_print(copySet2); //unordered_set elements are: 5 1 2 3 4 
    
    //使用另一个unordered_set的所有元素初始化
    unordered_set<int> partialCopy(initSet.begin(), initSet.end());
    
    unordered_set_print(partialCopy); //unordered_set elements are: 5 1 2 3 4 
    
    //使用另一个unordered_set的所有元素初始化，其中cbegin和cend由于C++11引入 //不可用，为空
    // unordered_set<int> partialCopy2(initSet.cbegin(), initSet.cbegin());
    
    // unordered_set_print(partialCopy2); //unordered_set elements are:
    
    
    //使用 vector 的值来初始化 unordered_set
    vector<int> initVector = { 1, 2, 3, 4, 5 };
    
    unordered_set<int> copyVector(initVector.begin(), initVector.end());
    
    unordered_set_print(copyVector); //unordered_set elements are: 5 1 2 3 4 
    
    //使用 list 的值来初始化 unordered_set
    list<int> initList = { 1, 2, 3, 4, 5 };
    
    unordered_set<int> copyList(initList.begin(), initList.end());
    
    unordered_set_print(copyList); //unordered_set elements are: 5 1 2 3 4 
}
/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    cout << __cplusplus << endl;
    
    // init_test();        //实例化
    // find_test();        //查找元素
    // insert_test();      //插入元素
    // iterate_test();     //正向遍历元素
    // size_test();        //大小
    erase_test();       //删除元素
    // clear_test();       //清空元素
    // empty_test();       //判断是否为空
    // swap_test();        //交换元素
    // assign_test();      //分配新的内容替换原有的内容
    
    return 0;
}