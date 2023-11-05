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
void unordered_map_print(unordered_map<int, string> integers)
{
   cout << "unordered_map elements are: ";
// #if __cplusplus >= 201103L
   for (auto it = integers.begin(); it != integers.end(); it++)
       cout << (*it).first << " : " << (*it).second << " ";
// #else
    // for ( unordered_map<int, string>::iterator it = integers.begin(); it != integers.end(); it++)
       // cout << (*it).first << " : " << (*it).second << " ";
// #endif
   cout << endl;
}

//二维 unordered_map 实例化
void two_dimensional_init_test(void)
{
    //定义二维
    unordered_map<int, string> subobj1 = { {1, "one"}, {2, "two"}, };
    unordered_map<int, string> subobj2 = { {3, "three"}, {4, "four"} };
    unordered_map<int, string> subobj3 = { {5, "five"}, {6, "six"} };
    unordered_map<int, unordered_map<int, string> > obj = { {1, subobj1}, {2, subobj2}, {3, subobj3}, };
 
    //输出二维 unordered_map
    for (unordered_map< int, unordered_map<int, string>>::iterator i = obj.begin(); i != obj.end(); i++) {
        cout << (*i).first << " : " << " ";
        for ( unordered_map<int, string>::iterator j = (*i).second.begin(); j != (*i).second.end(); j++)
            cout << (*j).first << " : " << (*j).second << " ";
        cout << endl;
    }
    cout << endl;
}


//分配新的内容替换原有的内容
void assign_test(void)
{
    unordered_map<int, string> unordered_maptable = { {3, "three"}, {1, "one"}, {5, "five"}, {2, "two"},  {4, "four"} };
    
    unordered_map_print(unordered_maptable); //unordered_map elements are: 5 : five 1 : one 2 : two 3 : three 4 : four 
    
    unordered_map<int, string> another2 = { {8, "eight"}, {7, "seven"} };
    
    //将 another2 的内容赋给 unordered_maptable
    unordered_maptable = another2;
    
    unordered_map_print(unordered_maptable); //unordered_map elements are:  8 : eight 7 : seven 
    
    unordered_map<int, string> another3 = { {9, "nine"}, {10, "ten"} };
    
    //将 another3 的内容赋给 unordered_maptable，another3内的值被清空
    unordered_maptable = move(another3);
    
    unordered_map_print(unordered_maptable); //unordered_map elements are: 10 : ten 9 : nine 
}

//交换元素
void swap_test(void)
{
    unordered_map<int, string> unordered_maptable = { {3, "three"}, {1, "one"}, {5, "five"}, {2, "two"},  {4, "four"} };
    unordered_map<int, string> another = { {8, "eight"}, {7, "seven"} };
    
    //交换
    unordered_maptable.swap(another);
    
    unordered_map_print(unordered_maptable); //unordered_map elements are: 8 : eight 7 : seven 
    unordered_map_print(another);  //unordered_map elements are: 5 : five 1 : one 2 : two 3 : three 4 : four
}

//判断是否为空
void empty_test(void)
{
    unordered_map<int, string> unordered_maptable;
    
    cout << "Empty:" << unordered_maptable.empty() << endl;   //Empty:1
    
    //放入元素
    unordered_maptable[0] = "zero";
    
    cout << "Empty:" << unordered_maptable.empty() << endl;   //Empty:0
    
    //删除元素
    unordered_maptable.erase(0);
    
    cout << "Empty:" << unordered_maptable.empty() << endl;   //Empty:1
}

//清空元素
void clear_test(void)
{
    unordered_map<int, string> unordered_maptable = { {3, "three"}, {1, "one"}, {5, "five"}, {2, "two"},  {4, "four"} };
    
    unordered_map_print(unordered_maptable); //unordered_map elements are: 5 : five 1 : one 2 : two 3 : three 4 : four 
    
    //清空所有元素
    unordered_maptable.clear();
    
    unordered_map_print(unordered_maptable); //unordered_map elements are:
}

//删除元素
void erase_test(void)
{
    unordered_map<int, string> unordered_maptable = { {3, "three"}, {8, "eight"}, {1, "one"}, {5, "five"}, {2, "two"},  {7, "seven"}, {4, "four"}, {6, "six"} };
    
    unordered_map_print(unordered_maptable); //unordered_map elements are: 1 : one 2 : two 3 : three 4 : four 5 : five 6 : six 7 : seven 8 : eight 
    
    //根据key删除特定元素
    unordered_maptable.erase(3);
    
    unordered_map_print(unordered_maptable); //unordered_map elements are: 1 : one 2 : two 4 : four 5 : five 6 : six 7 : seven 8 : eight 
    
     //根据迭代器删除特定元素
    for( unordered_map<int, string>::iterator it = unordered_maptable.begin(); it != unordered_maptable.end();) {
        if((*it).first == 5) {
            it = unordered_maptable.erase(it);
        } else {
            ++it;
        }
    }
    
    unordered_map_print(unordered_maptable); //unordered_map elements are: 1 : one 2 : two 4 : four 6 : six 7 : seven 8 : eight
    
    //根据迭代器删除指定范围元素 删除 7 之后的元素，含7
    auto elementFound = unordered_maptable.find(7);
    
    if(elementFound != unordered_maptable.end()) {
        unordered_maptable.erase(elementFound, unordered_maptable.end());
    }
    
    unordered_map_print(unordered_maptable); //unordered_map elements are: 1 : one 2 : two 4 : four 6 : six
    
    //根据迭代器删除指定范围元素 删除 2 之前的元素，不含2
    auto anotherFind = unordered_maptable.find(2);
    
    if(anotherFind != unordered_maptable.end()) {
        unordered_maptable.erase(unordered_maptable.begin(), anotherFind);
    }
    
    unordered_map_print(unordered_maptable); //unordered_map elements are: 2 : two 4 : four 6 : six 
    
    //清空所有元素
    unordered_maptable.erase(unordered_maptable.begin(), unordered_maptable.end());
    
    unordered_map_print(unordered_maptable); //unordered_map elements are: 
    
    
    
    //自定义结构
    unordered_map <test_item, string, test_item_hash> item;
    item.insert(make_pair(test_item("Jack", "178897"), "one"));
    item.insert(pair<test_item, string>(test_item("Bill", "978945"), "two"));
    item[test_item("Angi", "348158")] = "three";
    
    display_as_test_item(item);
    
    //查找元素 姓名为Bill
    auto itemFind = item.find(test_item("Bill", ""));
    
    if(itemFind != item.end()) {
        cout << "Element " << itemFind->first << " " << itemFind->second << " found!" << endl;
        cout << "Displaying contents after erasing " << itemFind->first << endl;
        item.erase(itemFind);
        display_as_test_item(item);
    } else {
        cout << "Element not found in unordered_map!" << endl;
    }
    
    //自定义结构 2
    unordered_map<test_item_2, string, decltype(&test_item_2_hash), decltype(&test_item_2_equal)> item_2(3, test_item_2_hash, test_item_2_equal);
    item_2.insert(make_pair(test_item_2{1}, "one"));
    item_2.insert(pair<test_item_2, string>(test_item_2{2}, "two"));
    item_2[test_item_2{3}] = "three";
    
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
        cout << "Element not found in unordered_map!" << endl;
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
    unordered_map<int, string> unordered_maptable = { {3, "three"}, {1, "one"}, {5, "five"}, {2, "two"},  {4, "four"} };
    
    //大小和容量
    cout << "Size:" << unordered_maptable.size() << endl;
    
    //插入值 6
    unordered_maptable[6] = "six";
    
    cout << "Size:" << unordered_maptable.size() << endl;
    
    //插入值 7
    unordered_maptable.insert(make_pair(7, "seven"));
    
    cout << "Size:" << unordered_maptable.size() << endl;
    
    //插入值 8
    unordered_maptable.insert(pair<int, string> (8, "eight"));
    
    cout << "Size:" << unordered_maptable.size() << endl;
    
    // 最大可允许的unordered_map元素数量值
    cout << "Max_size:" << unordered_maptable.max_size() << endl;
    
    cout << "Number of elements, size() = " << unordered_maptable.size() << endl;
    cout << "Bucket count = " << unordered_maptable.bucket_count() << endl;
    cout << "Max load factor = " << unordered_maptable.max_load_factor() << endl;
    cout << "Load factor = " << unordered_maptable.load_factor() << endl << endl;
}

//正向遍历元素
void iterate_test(void)
{
    unordered_map<int, string> unordered_maptable = { {3, "three"}, {1, "one"}, {5, "five"}, {2, "two"},  {4, "four"} };
    
    for (auto v : unordered_maptable)
       cout << v.first << " : " << v.second << " ";
    cout << endl;

    //使用迭代器
    unordered_map<int, string>::iterator element = unordered_maptable.begin();
    while(element != unordered_maptable.end()) {
        cout << (*element).first << " : " << (*element).second << " ";
        
        ++element;
    }
    cout << endl;
    
    unordered_map<int, string>::const_iterator celement = unordered_maptable.cbegin();
    while(celement != unordered_maptable.cend()) {
        cout << (*celement).first << " : " << (*celement).second << " ";
        
        ++celement;
    }
    cout << endl;
    
    auto acelement = unordered_maptable.cbegin();
    while(acelement != unordered_maptable.cend()) {
        cout << (*acelement).first << " : " << (*acelement).second << " ";
        
        ++acelement;
    }
    cout << endl;
    
    for ( unordered_map<int, string>::iterator it = unordered_maptable.begin(); it != unordered_maptable.end(); it++)
       cout << (*it).first << " : " << (*it).second << " ";
    cout << endl;
    
    for ( unordered_map<int, string>::const_iterator it = unordered_maptable.cbegin(); it != unordered_maptable.cend(); it++)
       cout << (*it).first << " : " << (*it).second << " ";
    cout << endl;
    
    for (auto it = unordered_maptable.begin(); it != unordered_maptable.end(); it++)
        cout << (*it).first << " : " << (*it).second << " ";
    cout << endl;
    
    for (auto it = unordered_maptable.begin(); it != unordered_maptable.end(); it++)
        cout << get<0>(*it) << " : " << get<1>(*it) << " ";
    cout << endl;
}

//插入元素
void insert_test(void)
{
    //初始化
    unordered_map<int, string> unordered_maptable = { {3, "three"}, {1, "one"}, {5, "five"}, {2, "two"},  {4, "four"} };
    
    unordered_map_print(unordered_maptable); //unordered_map elements are: 5 : five 1 : one 2 : two 3 : three 4 : four
    
    //插入值 6
    unordered_maptable[6] = "six";
    
    unordered_map_print(unordered_maptable); //unordered_map elements are: 1 : one 2 : two 3 : three 4 : four 5 : five 6 : six
    
    //插入值 7
    unordered_maptable.insert(make_pair(7, "seven"));
    
    unordered_map_print(unordered_maptable); //unordered_map elements are: 1 : one 2 : two 3 : three 4 : four 5 : five 6 : six 7 : seven 
    
    //插入值 8
    unordered_maptable.insert(pair<int, string> (8, "eight"));
    
    unordered_map_print(unordered_maptable); //unordered_map elements are: 1 : one 2 : two 3 : three 4 : four 5 : five 6 : six 7 : seven 8 : eight 
    
    //插入值 11
    unordered_maptable.insert(unordered_map<int, string>::value_type (11, "eleven"));
    
    unordered_map_print(unordered_maptable); //unordered_map elements are: 11 : eleven 1 : one 2 : two 3 : three 4 : four 5 : five 6 : six 7 : seven 8 : eight 
    
    
    //另一个 unordered_multimap，有两个元素
    unordered_multimap<int, string> another = { {9, "nine"}, {10, "ten"} };
    
    //将 another 的元素插入 unordered_maptable
    unordered_maptable.insert(another.begin(), another.end());
    
    unordered_map_print(unordered_maptable); //unordered_map elements are: 11 : eleven 1 : one 2 : two 3 : three 4 : four 5 : five 6 : six 7 : seven 8 : eight 9 : nine 10 : ten 
    
    
    
    //插入重复元素, 使用 insert 插入重复元素会失败
    unordered_maptable.insert(make_pair(7, "seven_seven"));
    
    unordered_map_print(unordered_maptable); //unordered_map elements are: 1 : one 2 : two 3 : three 4 : four 5 : five 6 : six 7 : seven 8 : eight 11 : eleven 
    
    //插入重复元素, 使用数组方式会覆盖
    unordered_maptable[6] = "six_six";
    
    unordered_map_print(unordered_maptable); //unordered_map elements are: 1 : one 2 : two 3 : three 4 : four 5 : five 6 : six_six 7 : seven 8 : eight 9 : nine 10 : ten 11 : eleven  
    
    //判断插入是否成功
    pair<unordered_map<int, string>::iterator, bool> Insert_Pair;
    //插入重复元素,使用 insert 插入重复元素会失败
    Insert_Pair = unordered_maptable.insert(unordered_map<int, string>::value_type (3, "three_three"));
    
    if(Insert_Pair.second == true) {
        cout << "Insert Successfully" << endl;  
    } else {
        cout << "Insert Failure" << endl;   //Insert Failure
    }
}

//查找元素
void find_test(void)
{
    //初始化
    unordered_map<int, string> unordered_maptable = { {3, "three"}, {1, "one"}, {5, "five"}, {2, "two"},  {4, "four"} };
    
    unordered_map_print(unordered_maptable); //unordered_map elements are: 5 : five 1 : one 2 : two 3 : three 4 : four
    
    //查找元素 3
    auto elementFound = unordered_maptable.find(3);
    
    if(elementFound != unordered_maptable.end()) {
        //获取 key 为 3 的数量
        size_t numPairsInMap = unordered_maptable.count(3);
        
        cout << "Element " << elementFound->first << " found!" << endl;
        //遍历所有 key 为 3 的值
        for(size_t counter = 0; counter < numPairsInMap; ++counter) {
            cout << "Key = " << elementFound->first << ", val [" << counter << "] = " << "]" << elementFound->second << endl;
            ++elementFound;
        }
    } else {
        cout << "Element not found in unordered_map!" << endl;
    }
    
    //查找元素 6
    auto anotherFind = unordered_maptable.find(6);
    
    if(anotherFind != unordered_maptable.end()) {
        cout << "Element " << anotherFind->first << " : "<< anotherFind->second << " found!" << endl;
    } else {
        cout << "Element not found in unordered_map!" << endl;
    }
    
    //判断 3 在 unordered_map 中的数量
    size_t num = unordered_maptable.count(3);
    cout << "Element " << 3 << " count " << num << endl;
    
    //判断 6 在 unordered_map 中的数量
    num = unordered_maptable.count(6);
    cout << "Element " << 6 << " count " << num << endl;
    
    //自定义结构
    unordered_map <test_item, string, test_item_hash> item;
    item.insert(make_pair(test_item("Jack", "178897"), "one"));
    item.insert(pair<test_item, string>(test_item("Bill", "978945"), "two"));
    item[test_item("Angi", "348158")] = "three";
    
    display_as_test_item(item);
    
    //查找元素 姓名为Bill
    auto itemFind = item.find(test_item("Bill", ""));
    
    if(itemFind != item.end()) {
        cout << "Element " << itemFind->first << " " << itemFind->second << " found!" << endl;
    } else {
        cout << "Element not found in unordered_map!" << endl;
    }
    
    itemFind = item.find(test_item("John", ""));
    
    if(itemFind != item.end()) {
        cout << "Element " << itemFind->first << itemFind->second << " found!" << endl;
    } else {
        cout << "Element not found in unordered_map!" << endl;
    }
    
    
    //自定义结构 2
    unordered_map<test_item_2, string, decltype(&test_item_2_hash), decltype(&test_item_2_equal)> item_2(3, test_item_2_hash, test_item_2_equal);
    item_2.insert(make_pair(test_item_2{1}, "one"));
    item_2.insert(pair<test_item_2, string>(test_item_2{2}, "two"));
    item_2[test_item_2{3}] = "three";
    
    //查找元素 2
    auto itemFind2 = item_2.find(test_item_2{2});
    
    if(itemFind2 != item_2.end()) {
        cout << "Element " << itemFind2->first.x << " " << itemFind2->second << " found!" << endl;
    } else {
        cout << "Element not found in unordered_map!" << endl;
    }
    
    itemFind2 = item_2.find(test_item_2{5});
    
    if(itemFind2 != item_2.end()) {
        cout << "Element " << (*itemFind2).first.x << " " << (*itemFind2).second << " found!" << endl;
    } else {
        cout << "Element not found in unordered_map!" << endl;
    }
}

//实例化
void init_test(void)
{
    //整型 unordered_map 类
    unordered_map<int, string> integers;
    
    unordered_map_print(integers); //unordered_map elements are: 
    
     //C++11引入的列表初始化
    unordered_map<int, string> initunordered_map = { {1, "one"}, {2, "two"}, {3, "three"}, {4, "four"}, {5, "five"} };
    
    unordered_map_print(initunordered_map); //unordered_map elements are: 5 : five 1 : one 2 : two 3 : three 4 : four
    
    unordered_map<int, string> initunordered_map1 = { make_pair(1, "one"), make_pair(2, "two"), make_pair(3, "three"), make_pair(4, "four"), make_pair(5, "five") };
    
    unordered_map_print(initunordered_map1); //unordered_map elements are: 5 : five 1 : one 2 : two 3 : three 4 : four
    
    unordered_map<int, string> initunordered_map2 = { pair<int, string>(1, "one"), pair<int, string>(2, "two"), pair<int, string>(3, "three"), pair<int, string>(4, "four"), pair<int, string>(5, "five") };
    
    unordered_map_print(initunordered_map2); //unordered_map elements are: 5 : five 1 : one 2 : two 3 : three 4 : four
    
    //初始化重复元素，只会剩 1 个
    unordered_map<int, string> initunordered_map3 = { {3, "three"}, {3, "three"} };
    
    unordered_map_print(initunordered_map3); //unordered_map elements are: 3 : three
    
     //使用一个unordered_map初始化另一个unordered_map，即复制unordered_map对象
    unordered_map<int, string> copyunordered_map(initunordered_map);
    
    unordered_map_print(copyunordered_map); //unordered_map elements are: 5 : five 1 : one 2 : two 3 : three 4 : four
    
    //使用一个unordered_map初始化另一个unordered_map，即复制unordered_map对象
    unordered_map<int, string> copyunordered_map2 = initunordered_map;
    
    unordered_map_print(copyunordered_map2); //unordered_map elements are: 5 : five 1 : one 2 : two 3 : three 4 : four
    
    //使用另一个unordered_map的所有元素初始化
    unordered_map<int, string> partialCopy(initunordered_map.begin(), initunordered_map.end());
    
    unordered_map_print(partialCopy); //unordered_map elements are: 5 : five 1 : one 2 : two 3 : three 4 : four
    
    //使用另一个unordered_map的所有元素初始化
    unordered_map<int, string> partialCopy2(initunordered_map.cbegin(), initunordered_map.cend());
    
    unordered_map_print(partialCopy2); //unordered_map elements are: 5 : five 1 : one 2 : two 3 : three 4 : four
    
    //使用 vector 的值来初始化 unordered_map
    vector<pair<int, string>> initVector = { {1, "one"}, {2, "two"}, {3, "three"}, {4, "four"}, {5, "five"} };
    
    unordered_map<int, string> copyVector(initVector.begin(), initVector.end());
    
    unordered_map_print(copyVector); //unordered_map elements are: 5 : five 1 : one 2 : two 3 : three 4 : four
    
    //使用 list 的值来初始化 unordered_map
    list<pair<int, string>> initList = { {1, "one"}, {2, "two"}, {3, "three"}, {4, "four"}, {5, "five"} };
    
    unordered_map<int, string> copyList(initList.begin(), initList.end());
    
    unordered_map_print(copyList); //unordered_map elements are: 5 : five 1 : one 2 : two 3 : three 4 : four
}
/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    cout << __cplusplus << endl;
    
    init_test();        //实例化
    find_test();        //查找元素
    insert_test();      //插入元素
    iterate_test();     //正向遍历元素
    size_test();        //大小
    erase_test();       //删除元素
    clear_test();       //清空元素
    empty_test();       //判断是否为空
    swap_test();        //交换元素
    assign_test();      //分配新的内容替换原有的内容
    
    two_dimensional_init_test();    //二维 unordered_map 实例化
    
    return 0;
}