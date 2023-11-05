#include <iostream>
#include <unordered_map>
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
       cout << element->first << " : " << element->second << " ";
       
   cout << endl;
}

//printing all elements
void unordered_multimap_print(unordered_multimap<int, string> integers)
{
   cout << "unordered_multimap elements are: ";
// #if __cplusplus >= 201103L
   for (auto it = integers.begin(); it != integers.end(); it++)
       cout << (*it).first << " : " << (*it).second << " ";
// #else
    // for ( unordered_multimap<int, string>::iterator it = integers.begin(); it != integers.end(); it++)
       // cout << (*it).first << " : " << (*it).second << " ";
// #endif
   cout << endl;
}

//二维 unordered_multimap 实例化
void two_dimensional_init_test(void)
{
    //定义二维
    unordered_multimap<int, string> subobj1 = { {1, "one"}, {2, "two"}, };
    unordered_multimap<int, string> subobj2 = { {3, "three"}, {4, "four"} };
    unordered_multimap<int, string> subobj3 = { {5, "five"}, {6, "six"} };
    unordered_multimap<int, unordered_multimap<int, string> > obj = { {1, subobj1}, {2, subobj2}, {3, subobj3}, };
 
    //输出二维 unordered_multimap
    for (unordered_multimap< int, unordered_multimap<int, string>>::iterator i = obj.begin(); i != obj.end(); i++) {
        cout << (*i).first << " : " << " ";
        for ( unordered_multimap<int, string>::iterator j = (*i).second.begin(); j != (*i).second.end(); j++)
            cout << (*j).first << " : " << (*j).second << " ";
        cout << endl;
    }
    cout << endl;
}


//分配新的内容替换原有的内容
void assign_test(void)
{
    unordered_multimap<int, string> unordered_multimaptable = { {3, "three"}, {1, "one"}, {5, "five"}, {2, "two"},  {4, "four"} };
    
    unordered_multimap_print(unordered_multimaptable); //unordered_multimap elements are: 5 : five 1 : one 2 : two 3 : three 4 : four 
    
    unordered_multimap<int, string> another2 = { {8, "eight"}, {7, "seven"} };
    
    //将 another2 的内容赋给 unordered_multimaptable
    unordered_multimaptable = another2;
    
    unordered_multimap_print(unordered_multimaptable); //unordered_multimap elements are:  8 : eight 7 : seven 
    
    unordered_multimap<int, string> another3 = { {9, "nine"}, {10, "ten"} };
    
    //将 another3 的内容赋给 unordered_multimaptable，another3内的值被清空
    unordered_multimaptable = move(another3);
    
    unordered_multimap_print(unordered_multimaptable); //unordered_multimap elements are: 10 : ten 9 : nine 
}

//交换元素
void swap_test(void)
{
    unordered_multimap<int, string> unordered_multimaptable = { {3, "three"}, {1, "one"}, {5, "five"}, {2, "two"},  {4, "four"} };
    unordered_multimap<int, string> another = { {8, "eight"}, {7, "seven"} };
    
    //交换
    unordered_multimaptable.swap(another);
    
    unordered_multimap_print(unordered_multimaptable); //unordered_multimap elements are: 8 : eight 7 : seven 
    unordered_multimap_print(another);  //unordered_multimap elements are: 5 : five 1 : one 2 : two 3 : three 4 : four
}

//判断是否为空
void empty_test(void)
{
    unordered_multimap<int, string> unordered_multimaptable;
    
    cout << "Empty:" << unordered_multimaptable.empty() << endl;   //Empty:1
    
    //放入元素
    unordered_multimaptable.insert(make_pair(0, "zero"));
    
    cout << "Empty:" << unordered_multimaptable.empty() << endl;   //Empty:0
    
    //删除元素
    unordered_multimaptable.erase(0);
    
    cout << "Empty:" << unordered_multimaptable.empty() << endl;   //Empty:1
}

//清空元素
void clear_test(void)
{
    unordered_multimap<int, string> unordered_multimaptable = { {3, "three"}, {1, "one"}, {5, "five"}, {2, "two"},  {4, "four"} };
    
    unordered_multimap_print(unordered_multimaptable); //unordered_multimap elements are: 5 : five 1 : one 2 : two 3 : three 4 : four 
    
    //清空所有元素
    unordered_multimaptable.clear();
    
    unordered_multimap_print(unordered_multimaptable); //unordered_multimap elements are:
}

//删除元素
void erase_test(void)
{
    unordered_multimap<int, string> unordered_multimaptable = { {3, "three"}, {8, "eight"}, {1, "one"}, {5, "five"}, {2, "two"},  {7, "seven"}, {4, "four"}, {6, "six"} };
    
    unordered_multimap_print(unordered_multimaptable); //unordered_multimap elements are: 1 : one 2 : two 3 : three 4 : four 5 : five 6 : six 7 : seven 8 : eight 
    
    //根据key删除特定元素
    unordered_multimaptable.erase(3);
    
    unordered_multimap_print(unordered_multimaptable); //unordered_multimap elements are: 1 : one 2 : two 4 : four 5 : five 6 : six 7 : seven 8 : eight 
    
     //根据迭代器删除特定元素
    for( unordered_multimap<int, string>::iterator it = unordered_multimaptable.begin(); it != unordered_multimaptable.end();) {
        if((*it).first == 5) {
            it = unordered_multimaptable.erase(it);
        } else {
            ++it;
        }
    }
    
    unordered_multimap_print(unordered_multimaptable); //unordered_multimap elements are: 1 : one 2 : two 4 : four 6 : six 7 : seven 8 : eight
    
    //根据迭代器删除指定范围元素 删除 7 之后的元素，含7
    auto elementFound = unordered_multimaptable.find(7);
    
    if(elementFound != unordered_multimaptable.end()) {
        unordered_multimaptable.erase(elementFound, unordered_multimaptable.end());
    }
    
    unordered_multimap_print(unordered_multimaptable); //unordered_multimap elements are: 1 : one 2 : two 4 : four 6 : six
    
    //根据迭代器删除指定范围元素 删除 2 之前的元素，不含2
    auto anotherFind = unordered_multimaptable.find(2);
    
    if(anotherFind != unordered_multimaptable.end()) {
        unordered_multimaptable.erase(unordered_multimaptable.begin(), anotherFind);
    }
    
    unordered_multimap_print(unordered_multimaptable); //unordered_multimap elements are: 2 : two 4 : four 6 : six 
    
    //清空所有元素
    unordered_multimaptable.erase(unordered_multimaptable.begin(), unordered_multimaptable.end());
    
    unordered_multimap_print(unordered_multimaptable); //unordered_multimap elements are: 
    
    
    
    //自定义结构
    unordered_multimap <test_item, string, test_item_hash> item;
    item.insert(make_pair(test_item("Jack", "178897"), "one"));
    item.insert(pair<test_item, string>(test_item("Bill", "978945"), "two"));
    item.insert(make_pair(test_item("Angi", "348158"), "three"));
    
    display_as_test_item(item);
    
    //查找元素 姓名为Bill
    auto itemFind = item.find(test_item("Bill", ""));
    
    if(itemFind != item.end()) {
        cout << "Element " << itemFind->first << " " << itemFind->second << " found!" << endl;
        cout << "Displaying contents after erasing " << itemFind->first << endl;
        item.erase(itemFind);
        display_as_test_item(item);
    } else {
        cout << "Element not found in unordered_multimap!" << endl;
    }
    
    //自定义结构 2
    unordered_multimap<test_item_2, string, decltype(&test_item_2_hash), decltype(&test_item_2_equal)> item_2(3, test_item_2_hash, test_item_2_equal);
    item_2.insert(make_pair(test_item_2{1}, "one"));
    item_2.insert(pair<test_item_2, string>(test_item_2{2}, "two"));
    item_2.insert(make_pair(test_item_2{3}, "three"));
    
    //打印
    for (auto element = item_2.cbegin(); 
        element != item_2.cend();
        ++element)
       cout << "Element " << (*element).first.x << " " << (*element).second << endl; 
    cout << endl;
    
    //查找元素 2
    auto itemFind2 = item_2.find(test_item_2{2});
    
    if(itemFind2 != item_2.end()) {
        cout << "Element " << itemFind2->first.x << " " << itemFind2->second << " found!" << endl;
        cout << "Displaying contents after erasing " << itemFind2->first.x << endl;
        item_2.erase(itemFind2);
    } else {
        cout << "Element not found in unordered_multimap!" << endl;
    }
    
    //打印
    for (auto element = item_2.cbegin(); 
        element != item_2.cend();
        ++element)
       cout << "Element " << (*element).first.x << " " << (*element).second << endl; 
    cout << endl;
}

//大小
void size_test(void)
{
    //设置初始值
    unordered_multimap<int, string> unordered_multimaptable = { {3, "three"}, {1, "one"}, {5, "five"}, {2, "two"},  {4, "four"} };
    
    //大小和容量
    cout << "Size:" << unordered_multimaptable.size() << endl;
    
    //插入值 6
    unordered_multimaptable.insert(make_pair(6, "six"));
    
    cout << "Size:" << unordered_multimaptable.size() << endl;
    
    //插入值 7
    unordered_multimaptable.insert(make_pair(7, "seven"));
    
    cout << "Size:" << unordered_multimaptable.size() << endl;
    
    //插入值 8
    unordered_multimaptable.insert(pair<int, string> (8, "eight"));
    
    cout << "Size:" << unordered_multimaptable.size() << endl;
    
    // 最大可允许的unordered_multimap元素数量值
    cout << "Max_size:" << unordered_multimaptable.max_size() << endl;
    
    cout << "Number of elements, size() = " << unordered_multimaptable.size() << endl;
    cout << "Bucket count = " << unordered_multimaptable.bucket_count() << endl;
    cout << "Max load factor = " << unordered_multimaptable.max_load_factor() << endl;
    cout << "Load factor = " << unordered_multimaptable.load_factor() << endl << endl;
}

//正向遍历元素
void iterate_test(void)
{
    unordered_multimap<int, string> unordered_multimaptable = { {3, "three"}, {1, "one"}, {5, "five"}, {2, "two"},  {4, "four"} };
    
    for (auto v : unordered_multimaptable)
       cout << v.first << " : " << v.second << " ";
    cout << endl;

    //使用迭代器
    unordered_multimap<int, string>::iterator element = unordered_multimaptable.begin();
    while(element != unordered_multimaptable.end()) {
        cout << (*element).first << " : " << (*element).second << " ";
        
        ++element;
    }
    cout << endl;
    
    unordered_multimap<int, string>::const_iterator celement = unordered_multimaptable.cbegin();
    while(celement != unordered_multimaptable.cend()) {
        cout << (*celement).first << " : " << (*celement).second << " ";
        
        ++celement;
    }
    cout << endl;
    
    auto acelement = unordered_multimaptable.cbegin();
    while(acelement != unordered_multimaptable.cend()) {
        cout << (*acelement).first << " : " << (*acelement).second << " ";
        
        ++acelement;
    }
    cout << endl;
    
    for ( unordered_multimap<int, string>::iterator it = unordered_multimaptable.begin(); it != unordered_multimaptable.end(); it++)
       cout << (*it).first << " : " << (*it).second << " ";
    cout << endl;
    
    for ( unordered_multimap<int, string>::const_iterator it = unordered_multimaptable.cbegin(); it != unordered_multimaptable.cend(); it++)
       cout << (*it).first << " : " << (*it).second << " ";
    cout << endl;
    
    for (auto it = unordered_multimaptable.begin(); it != unordered_multimaptable.end(); it++)
        cout << (*it).first << " : " << (*it).second << " ";
    cout << endl;
    
    for (auto it = unordered_multimaptable.begin(); it != unordered_multimaptable.end(); it++)
        cout << get<0>(*it) << " : " << get<1>(*it) << " ";
    cout << endl;
}

//插入元素
void insert_test(void)
{
    //初始化
    unordered_multimap<int, string> unordered_multimaptable = { {3, "three"}, {1, "one"}, {5, "five"}, {2, "two"},  {4, "four"} };
    
    unordered_multimap_print(unordered_multimaptable); //unordered_multimap elements are: 5 : five 1 : one 2 : two 3 : three 4 : four
    
    //插入值 6
    unordered_multimaptable.insert(make_pair(6, "six"));
    
    unordered_multimap_print(unordered_multimaptable); //unordered_multimap elements are: 1 : one 2 : two 3 : three 4 : four 5 : five 6 : six
    
    //插入值 7
    unordered_multimaptable.insert(make_pair(7, "seven"));
    
    unordered_multimap_print(unordered_multimaptable); //unordered_multimap elements are: 1 : one 2 : two 3 : three 4 : four 5 : five 6 : six 7 : seven 
    
    //插入值 8
    unordered_multimaptable.insert(pair<int, string> (8, "eight"));
    
    unordered_multimap_print(unordered_multimaptable); //unordered_multimap elements are: 1 : one 2 : two 3 : three 4 : four 5 : five 6 : six 7 : seven 8 : eight 
    
    //插入值 11
    unordered_multimaptable.insert(unordered_multimap<int, string>::value_type (11, "eleven"));
    
    unordered_multimap_print(unordered_multimaptable); //multimap elements are: 11 : eleven 1 : one 2 : two 3 : three 4 : four 5 : five 6 : six 7 : seven 8 : eight 
    
    
    //另一个 unordered_multimap，有两个元素
    unordered_multimap<int, string> another = { {9, "nine"}, {10, "ten"} };
    
    //将 another 的元素插入 unordered_multimaptable
    unordered_multimaptable.insert(another.begin(), another.end());
    
    unordered_multimap_print(unordered_multimaptable); //unordered_multimap elements are: 11 : eleven 1 : one 2 : two 3 : three 4 : four 5 : five 6 : six 7 : seven 8 : eight 9 : nine 10 : ten 
}

//查找元素
void find_test(void)
{
    //初始化
    unordered_multimap<int, string> unordered_multimaptable = { {3, "three"}, {3, "three2"}, {1, "one"}, {5, "five"}, {2, "two"},  {4, "four"} };
    
    unordered_multimap_print(unordered_multimaptable); //unordered_multimap elements are: 5 : five 1 : one 2 : two 3 : three 4 : four
    
    //查找元素 3
    auto elementFound = unordered_multimaptable.find(3);
    
    if(elementFound != unordered_multimaptable.end()) {
        //获取 key 为 3 的数量
        size_t numPairsInMap = unordered_multimaptable.count(3);
        
        cout << "Element " << elementFound->first << " found!" << endl;
        //遍历所有 key 为 3 的值
        for(size_t counter = 0; counter < numPairsInMap; ++counter) {
            cout << "Key = " << elementFound->first << ", val [" << counter << "] = " << "]" << elementFound->second << endl;
            ++elementFound;
        }
    } else {
        cout << "Element not found in unordered_multimap!" << endl;
    }
    
    //查找元素 6
    auto anotherFind = unordered_multimaptable.find(6);
    
    if(anotherFind != unordered_multimaptable.end()) {
        cout << "Element " << anotherFind->first << " : "<< anotherFind->second << " found!" << endl;
    } else {
        cout << "Element not found in unordered_multimap!" << endl;
    }
    
    //判断 3 在 unordered_multimap 中的数量
    size_t num = unordered_multimaptable.count(3);
    cout << "Element " << 3 << " count " << num << endl;
    
    //判断 6 在 unordered_multimap 中的数量
    num = unordered_multimaptable.count(6);
    cout << "Element " << 6 << " count " << num << endl;
    
    //自定义结构
    unordered_multimap <test_item, string, test_item_hash> item;
    item.insert(make_pair(test_item("Jack", "178897"), "one"));
    item.insert(pair<test_item, string>(test_item("Bill", "978945"), "two"));
    item.insert(make_pair(test_item("Angi", "348158"), "three"));
    
    display_as_test_item(item);
    
    //查找元素 姓名为Bill
    auto itemFind = item.find(test_item("Bill", ""));
    
    if(itemFind != item.end()) {
        cout << "Element " << itemFind->first << " " << itemFind->second << " found!" << endl;
    } else {
        cout << "Element not found in unordered_multimap!" << endl;
    }
    
    itemFind = item.find(test_item("John", ""));
    
    if(itemFind != item.end()) {
        cout << "Element " << itemFind->first << itemFind->second << " found!" << endl;
    } else {
        cout << "Element not found in unordered_multimap!" << endl;
    }
    
    
    //自定义结构 2
    unordered_multimap<test_item_2, string, decltype(&test_item_2_hash), decltype(&test_item_2_equal)> item_2(3, test_item_2_hash, test_item_2_equal);
    item_2.insert(make_pair(test_item_2{1}, "one"));
    item_2.insert(pair<test_item_2, string>(test_item_2{2}, "two"));
    item_2.insert(make_pair(test_item_2{3}, "three"));
    
    //查找元素 2
    auto itemFind2 = item_2.find(test_item_2{2});
    
    if(itemFind2 != item_2.end()) {
        cout << "Element " << itemFind2->first.x << " " << itemFind2->second << " found!" << endl;
    } else {
        cout << "Element not found in unordered_multimap!" << endl;
    }
    
    itemFind2 = item_2.find(test_item_2{5});
    
    if(itemFind2 != item_2.end()) {
        cout << "Element " << (*itemFind2).first.x << " " << (*itemFind2).second << " found!" << endl;
    } else {
        cout << "Element not found in unordered_multimap!" << endl;
    }
}

//实例化
void init_test(void)
{
    //整型 unordered_multimap 类
    unordered_multimap<int, string> integers;
    
    unordered_multimap_print(integers); //unordered_multimap elements are: 
    
     //C++11引入的列表初始化
    unordered_multimap<int, string> initunordered_multimap = { {1, "one"}, {2, "two"}, {3, "three"}, {4, "four"}, {5, "five"} };
    
    unordered_multimap_print(initunordered_multimap); //unordered_multimap elements are: 5 : five 1 : one 2 : two 3 : three 4 : four
    
    unordered_multimap<int, string> initunordered_multimap1 = { make_pair(1, "one"), make_pair(2, "two"), make_pair(3, "three"), make_pair(4, "four"), make_pair(5, "five") };
    
    unordered_multimap_print(initunordered_multimap1); //unordered_multimap elements are: 5 : five 1 : one 2 : two 3 : three 4 : four
    
    unordered_multimap<int, string> initunordered_multimap2 = { pair<int, string>(1, "one"), pair<int, string>(2, "two"), pair<int, string>(3, "three"), pair<int, string>(4, "four"), pair<int, string>(5, "five") };
    
    unordered_multimap_print(initunordered_multimap2); //unordered_multimap elements are: 5 : five 1 : one 2 : two 3 : three 4 : four
    
    //初始化重复元素
    unordered_multimap<int, string> initunordered_multimap3 = { {3, "three"}, {3, "three"} };
    
    unordered_multimap_print(initunordered_multimap3); //unordered_multimap elements are: 3 : three
    
     //使用一个unordered_multimap初始化另一个unordered_multimap，即复制unordered_multimap对象
    unordered_multimap<int, string> copyunordered_multimap(initunordered_multimap);
    
    unordered_multimap_print(copyunordered_multimap); //unordered_multimap elements are: 5 : five 1 : one 2 : two 3 : three 4 : four
    
    //使用一个unordered_multimap初始化另一个unordered_multimap，即复制unordered_multimap对象
    unordered_multimap<int, string> copyunordered_multimap2 = initunordered_multimap;
    
    unordered_multimap_print(copyunordered_multimap2); //unordered_multimap elements are: 5 : five 1 : one 2 : two 3 : three 4 : four
    
    //使用另一个unordered_multimap的所有元素初始化
    unordered_multimap<int, string> partialCopy(initunordered_multimap.begin(), initunordered_multimap.end());
    
    unordered_multimap_print(partialCopy); //unordered_multimap elements are: 5 : five 1 : one 2 : two 3 : three 4 : four
    
    //使用另一个unordered_multimap的所有元素初始化
    unordered_multimap<int, string> partialCopy2(initunordered_multimap.cbegin(), initunordered_multimap.cend());
    
    unordered_multimap_print(partialCopy2); //unordered_multimap elements are: 5 : five 1 : one 2 : two 3 : three 4 : four
    
    //使用一个map初始化另一个multimap，即复制map对象
    unordered_map<int, string> initunordered_map = { {1, "one"}, {2, "two"}, {3, "three"}, {4, "four"}, {5, "five"} };
    unordered_multimap<int, string> copyunordered_map(initunordered_map.begin(), initunordered_map.end());
    
    unordered_multimap_print(copyunordered_map); //unordered_multimap elements are: 1 : one 2 : two 3 : three 4 : four 5 : five
    
    //使用 vector 的值来初始化 unordered_multimap
    vector<pair<int, string>> initVector = { {1, "one"}, {2, "two"}, {3, "three"}, {4, "four"}, {5, "five"} };
    
    unordered_multimap<int, string> copyVector(initVector.begin(), initVector.end());
    
    unordered_multimap_print(copyVector); //unordered_multimap elements are: 5 : five 1 : one 2 : two 3 : three 4 : four
    
    //使用 list 的值来初始化 unordered_multimap
    list<pair<int, string>> initList = { {1, "one"}, {2, "two"}, {3, "three"}, {4, "four"}, {5, "five"} };
    
    unordered_multimap<int, string> copyList(initList.begin(), initList.end());
    
    unordered_multimap_print(copyList); //unordered_multimap elements are: 5 : five 1 : one 2 : two 3 : three 4 : four
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
    iterate_test();     //正向遍历元素
    // size_test();        //大小
    // erase_test();       //删除元素
    // clear_test();       //清空元素
    // empty_test();       //判断是否为空
    // swap_test();        //交换元素
    // assign_test();      //分配新的内容替换原有的内容
    
    // two_dimensional_init_test();    //二维 unordered_multimap 实例化
    
    return 0;
}