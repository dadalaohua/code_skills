#include <iostream>
#include <map>
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
       cout << element->first << " : " << element->second << " ";
       
   cout << endl;
}

//printing all elements
void map_print(map<int, string> integers)
{
   cout << "map elements are: ";
// #if __cplusplus >= 201103L
   for (auto it = integers.begin(); it != integers.end(); it++)
       cout << (*it).first << " : " << (*it).second << " ";
// #else
    // for ( map<int, string>::iterator it = integers.begin(); it != integers.end(); it++)
       // cout << (*it).first << " : " << (*it).second << " ";
// #endif
   cout << endl;
}

//二维 map 实例化
void two_dimensional_init_test(void)
{
    //定义二维
    map<int, string> subobj1 = { {1, "one"}, {2, "two"}, };
    map<int, string> subobj2 = { {3, "three"}, {4, "four"} };
    map<int, string> subobj3 = { {5, "five"}, {6, "six"} };
    map<int, map<int, string> > obj = { {1, subobj1}, {2, subobj2}, {3, subobj3}, };
 
    //输出二维 map
    for (map< int, map<int, string>>::iterator i = obj.begin(); i != obj.end(); i++) {
        cout << (*i).first << " : " << " ";
        for ( map<int, string>::iterator j = (*i).second.begin(); j != (*i).second.end(); j++)
            cout << (*j).first << " : " << (*j).second << " ";
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

struct sort_descending2 {
    bool operator()(const int& lhs, const int& rhs)const {
        return (lhs > rhs);
    }
};

bool cmp(const pair<int, string>& lhs, const pair<int, string>& rhs) {
    return lhs.second < rhs.second;
}

//排序
void sort_test(void)
{
    map<int, string> maptable = { {3, "three"}, {1, "one"}, {5, "five"}, {2, "two"},  {4, "four"} };
    
    //默认排序按key从小到大
    map_print(maptable); //map elements are: 1 : one 2 : two 3 : three 4 : four 5 : five 
    
    //排序， 按key从大到小
    //方法一：
    map<int, string, greater<int>> maptable2 = { {3, "three"}, {1, "one"}, {5, "five"}, {2, "two"},  {4, "four"} };
    
    cout << "map elements are: ";
    for (auto it = maptable2.begin(); it != maptable2.end(); it++)
        cout << (*it).first << " : " << (*it).second << " ";
    cout << endl; //map elements are: 5 : five 4 : four 3 : three 2 : two 1 : one 
   
   
    //方法二：
    map<int, string, sort_descending<int>> maptable3 = { {3, "three"}, {1, "one"}, {5, "five"}, {2, "two"},  {4, "four"} };
    
    cout << "map elements are: ";
    for (auto it = maptable3.begin(); it != maptable3.end(); it++)
        cout << (*it).first << " : " << (*it).second << " ";
    cout << endl; //map elements are: 5 : five 4 : four 3 : three 2 : two 1 : one
    
    
    //方法三：
    map<int, string, sort_descending2> maptable4 = { {3, "three"}, {1, "one"}, {5, "five"}, {2, "two"},  {4, "four"} };
    
    cout << "map elements are: ";
    for (auto it = maptable4.begin(); it != maptable4.end(); it++)
        cout << (*it).first << " : " << (*it).second << " ";
    cout << endl; //map elements are: 5 : five 4 : four 3 : three 2 : two 1 : one
    
    
    
    //排序， 按val排序，把map中的元素放到序列容器（如vector）中，再用sort进行排序
    map<int, string> maptable5 = { {3, "three"}, {1, "one"}, {5, "five"}, {2, "two"},  {4, "four"} };
    
    //将map中的内容转存到vector中
    vector<pair<int, string>> vec(maptable5.begin(), maptable5.end());
    //对线性的vector进行排序
    sort(vec.begin(), vec.end(), cmp);
    
    cout << "map elements are: ";
    for (auto it = vec.begin(); it != vec.end(); it++)
        cout << (*it).first << " : " << (*it).second << " ";
    cout << endl; //map elements are: 5 : five 4 : four 1 : one 3 : three 2 : two
    
    
    //自定义结构排序
    map <test_item, string> item;
    item.insert(make_pair(test_item("Jack", "178897"), "one"));
    item.insert(pair<test_item, string>(test_item("Bill", "978945"), "two"));
    item[test_item("Angi", "348158")] = "three";
    
    // test_item 定义了运算符 < , test_item::operator<让 sort按姓名字母顺序排列元素
    display_as_test_item(item);
    // Angi: 348158 : three Bill: 978945 : two Jack: 178897 : one
}

//分配新的内容替换原有的内容
void assign_test(void)
{
    map<int, string> maptable = { {3, "three"}, {1, "one"}, {5, "five"}, {2, "two"},  {4, "four"} };
    
    map_print(maptable); //map elements are: 1 : one 2 : two 3 : three 4 : four 5 : five 
    
    map<int, string> another2 = { {8, "eight"}, {7, "seven"} };
    
    //将 another2 的内容赋给 maptable
    maptable = another2;
    
    map_print(maptable); //map elements are: 7 : seven 8 : eight 
    
    map<int, string> another3 = { {9, "nine"}, {10, "ten"} };
    
    //将 another3 的内容赋给 maptable，another3内的值被清空
    maptable = move(another3);
    
    map_print(maptable); //map elements are: 9 : nine 10 : ten 
}

//交换元素
void swap_test(void)
{
    map<int, string> maptable = { {3, "three"}, {1, "one"}, {5, "five"}, {2, "two"},  {4, "four"} };
    map<int, string> another = { {8, "eight"}, {7, "seven"} };
    
    //交换
    maptable.swap(another);
    
    map_print(maptable); //map elements are: 7 : seven 8 : eight
    map_print(another);  //map elements are: 1 : one 2 : two 3 : three 4 : four 5 : five
}

//判断是否为空
void empty_test(void)
{
    map<int, string> maptable;
    
    cout << "Empty:" << maptable.empty() << endl;   //Empty:1
    
    //放入元素
    maptable[0] = "zero";
    
    cout << "Empty:" << maptable.empty() << endl;   //Empty:0
    
    //删除元素
    maptable.erase(0);
    
    cout << "Empty:" << maptable.empty() << endl;   //Empty:1
}

//清空元素
void clear_test(void)
{
    map<int, string> maptable = { {3, "three"}, {1, "one"}, {5, "five"}, {2, "two"},  {4, "four"} };
    
    map_print(maptable); //map elements are: 1 : one 2 : two 3 : three 4 : four 5 : five 
    
    //清空所有元素
    maptable.clear();
    
    map_print(maptable); //map elements are:
}

//删除元素
void erase_test(void)
{
    map<int, string> maptable = { {3, "three"}, {8, "eight"}, {1, "one"}, {5, "five"}, {2, "two"},  {7, "seven"}, {4, "four"}, {6, "six"} };
    
    map_print(maptable); //map elements are: 1 : one 2 : two 3 : three 4 : four 5 : five 6 : six 7 : seven 8 : eight 
    
    //根据key删除特定元素
    maptable.erase(3);
    
    map_print(maptable); //map elements are: 1 : one 2 : two 4 : four 5 : five 6 : six 7 : seven 8 : eight 
    
     //根据迭代器删除特定元素
    for( map<int, string>::iterator it = maptable.begin(); it != maptable.end();) {
        if((*it).first == 5) {
            it = maptable.erase(it);
        } else {
            ++it;
        }
    }
    
    map_print(maptable); //map elements are: 1 : one 2 : two 4 : four 6 : six 7 : seven 8 : eight
    
    //根据迭代器删除指定范围元素 删除 7 之后的元素，含7
    auto elementFound = maptable.find(7);
    
    if(elementFound != maptable.end()) {
        maptable.erase(elementFound, maptable.end());
    }
    
    map_print(maptable); //map elements are: 1 : one 2 : two 4 : four 6 : six
    
    //根据迭代器删除指定范围元素 删除 2 之前的元素，不含2
    auto anotherFind = maptable.find(2);
    
    if(anotherFind != maptable.end()) {
        maptable.erase(maptable.begin(), anotherFind);
    }
    
    map_print(maptable); //map elements are: 2 : two 4 : four 6 : six 
    
    //清空所有元素
    maptable.erase(maptable.begin(), maptable.end());
    
    map_print(maptable); //map elements are: 
    
    
    
    //自定义结构
    map <test_item, string> item;
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
        cout << "Element not found in map!" << endl;
    }
}

//大小
void size_test(void)
{
    //设置初始值
    map<int, string> maptable = { {3, "three"}, {1, "one"}, {5, "five"}, {2, "two"},  {4, "four"} };
    
    //大小和容量
    cout << "Size:" << maptable.size() << endl;
    
    //插入值 6
    maptable[6] = "six";
    
    cout << "Size:" << maptable.size() << endl;
    
    //插入值 7
    maptable.insert(make_pair(7, "seven"));
    
    cout << "Size:" << maptable.size() << endl;
    
    //插入值 8
    maptable.insert(pair<int, string> (8, "eight"));
    
    cout << "Size:" << maptable.size() << endl;
    
    // 最大可允许的map元素数量值
    cout << "Max_size:" << maptable.max_size() << endl;
}

//反向遍历元素
void r_iterate_test(void)
{
    map<int, string> maptable = { {3, "three"}, {1, "one"}, {5, "five"}, {2, "two"},  {4, "four"} };
    
    map<int, string>::reverse_iterator element = maptable.rbegin();
    while(element != maptable.rend()) {
        cout << (*element).first << " : " << (*element).second << " ";
        
        ++element;
    }
    cout << endl;
    
    map<int, string>::const_reverse_iterator celement = maptable.crbegin();
    while(celement != maptable.crend()) {
        cout << (*celement).first << " : " << (*celement).second << " ";
        
        ++celement;
    }
    cout << endl;
    
    auto acelement = maptable.crbegin();
    while(acelement != maptable.crend()) {
        cout << (*acelement).first << " : " << (*acelement).second << " ";
        
        ++acelement;
    }
    cout << endl;
    
    for ( map<int, string>::reverse_iterator it = maptable.rbegin(); it != maptable.rend(); it++)
       cout << (*it).first << " : " << (*it).second << " ";
    cout << endl;
    
    for ( map<int, string>::const_reverse_iterator it = maptable.crbegin(); it != maptable.crend(); it++)
       cout << (*it).first << " : " << (*it).second << " ";
    cout << endl;
    
    for (auto it = maptable.rbegin(); it != maptable.rend(); it++)
        cout << (*it).first << " : " << (*it).second << " ";
    cout << endl;
    
    for (auto it = maptable.rbegin(); it != maptable.rend(); it++)
        cout << get<0>(*it) << " : " << get<1>(*it) << " ";
    cout << endl;
}

//正向遍历元素
void iterate_test(void)
{
    map<int, string> maptable = { {3, "three"}, {1, "one"}, {5, "five"}, {2, "two"},  {4, "four"} };
    
    for (auto v : maptable)
       cout << v.first << " : " << v.second << " ";
    cout << endl;

    //使用迭代器
    map<int, string>::iterator element = maptable.begin();
    while(element != maptable.end()) {
        cout << (*element).first << " : " << (*element).second << " ";
        
        ++element;
    }
    cout << endl;
    
    map<int, string>::const_iterator celement = maptable.cbegin();
    while(celement != maptable.cend()) {
        cout << (*celement).first << " : " << (*celement).second << " ";
        
        ++celement;
    }
    cout << endl;
    
    auto acelement = maptable.cbegin();
    while(acelement != maptable.cend()) {
        cout << (*acelement).first << " : " << (*acelement).second << " ";
        
        ++acelement;
    }
    cout << endl;
    
    for ( map<int, string>::iterator it = maptable.begin(); it != maptable.end(); it++)
       cout << (*it).first << " : " << (*it).second << " ";
    cout << endl;
    
    for ( map<int, string>::const_iterator it = maptable.cbegin(); it != maptable.cend(); it++)
       cout << (*it).first << " : " << (*it).second << " ";
    cout << endl;
    
    for (auto it = maptable.begin(); it != maptable.end(); it++)
        cout << (*it).first << " : " << (*it).second << " ";
    cout << endl;
    
    for (auto it = maptable.begin(); it != maptable.end(); it++)
        cout << get<0>(*it) << " : " << get<1>(*it) << " ";
    cout << endl;
}

//插入元素
void insert_test(void)
{
    //初始化
    map<int, string> maptable = { {3, "three"}, {1, "one"}, {5, "five"}, {2, "two"},  {4, "four"} };
    
    map_print(maptable); //map elements are: 1 : one 2 : two 3 : three 4 : four 5 : five
    
    //插入值 6
    maptable[6] = "six";
    
    map_print(maptable); //map elements are: 1 : one 2 : two 3 : three 4 : four 5 : five 6 : six
    
    //插入值 7
    maptable.insert(make_pair(7, "seven"));
    
    map_print(maptable); //map elements are: 1 : one 2 : two 3 : three 4 : four 5 : five 6 : six 7 : seven 
    
    //插入值 8
    maptable.insert(pair<int, string> (8, "eight"));
    
    map_print(maptable); //map elements are: 1 : one 2 : two 3 : three 4 : four 5 : five 6 : six 7 : seven 8 : eight 
    
    //插入值 11
    maptable.insert(map<int, string>::value_type (11, "eleven"));
    
    map_print(maptable); //map elements are: 1 : one 2 : two 3 : three 4 : four 5 : five 6 : six 7 : seven 8 : eight 11 : eleven 
    
    
    //另一个 map，有两个元素
    map<int, string> another = { {9, "nine"}, {10, "ten"} };
    
    //将 another 的元素插入 maptable
    maptable.insert(another.begin(), another.end());
    
    map_print(maptable); //1 : one 2 : two 3 : three 4 : four 5 : five 6 : six 7 : seven 8 : eight 9 : nine 10 : ten 11 : eleven 

    
    //插入重复元素, 使用 insert 插入重复元素会失败
    maptable.insert(make_pair(7, "seven_seven"));
    
    map_print(maptable); //map elements are: 1 : one 2 : two 3 : three 4 : four 5 : five 6 : six 7 : seven 8 : eight 11 : eleven 
    
    //插入重复元素, 使用数组方式会覆盖
    maptable[6] = "six_six";
    
    map_print(maptable); //map elements are: 1 : one 2 : two 3 : three 4 : four 5 : five 6 : six_six 7 : seven 8 : eight 9 : nine 10 : ten 11 : eleven  
    
    //判断插入是否成功
    pair<map<int, string>::iterator, bool> Insert_Pair;
    //插入重复元素,使用 insert 插入重复元素会失败
    Insert_Pair = maptable.insert(map<int, string>::value_type (3, "three_three"));
    
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
    map<int, string> maptable = { {3, "three"}, {1, "one"}, {5, "five"}, {2, "two"},  {4, "four"} };
    
    map_print(maptable); //map elements are: 1 : one 2 : two 3 : three 4 : four 5 : five
    
    //查找元素 3
    auto elementFound = maptable.find(3);
    
    if(elementFound != maptable.end()) {
        cout << "Element " << elementFound->first << " : "<< elementFound->second << " found!" << endl;
    } else {
        cout << "Element not found in map!" << endl;
    }
    
    //查找元素 6
    auto anotherFind = maptable.find(6);
    
    if(anotherFind != maptable.end()) {
        cout << "Element " << anotherFind->first << " : "<< anotherFind->second << " found!" << endl;
    } else {
        cout << "Element not found in map!" << endl;
    }
    
    //判断 3 在 map 中的数量
    size_t num = maptable.count(3);
    cout << "Element " << 3 << " count " << num << endl;
    
    //判断 6 在 map 中的数量
    num = maptable.count(6);
    cout << "Element " << 6 << " count " << num << endl;
    
    
    
    //插入值 8
    maptable.insert(pair<int, string> (8, "eight"));
    
    map_print(maptable); //map elements are: 1 : one 2 : two 3 : three 4 : four 5 : five 8 : eight
    
    
    //查找第一个大于或等于key的数值
    auto iter = maptable.lower_bound(2); 
    if(iter != maptable.end()) {
        cout << "Element " << iter->first << " " << iter->second << " found!" << endl; // Element 2 two found!
    } else {
        cout << "Element not found in map!" << endl;
    }
    
    //查找第一个大于key的数值
    iter = maptable.upper_bound(2); 
    if(iter != maptable.end()) {
        cout << "Element " << iter->first << " " << iter->second << " found!" << endl; //Element 3 three found!
    } else {
        cout << "Element not found in map!" << endl;
    }
    
    //查找第一个大于或等于key的数值
    iter = maptable.lower_bound(6); 
    if(iter != maptable.end()) {
        cout << "Element " << iter->first << " " << iter->second << " found!" << endl; //Element 8 eight found!
    } else {
        cout << "Element not found in map!" << endl;
    }
    
    //查找第一个大于key的数值
    iter = maptable.upper_bound(6); 
    if(iter != maptable.end()) {
        cout << "Element " << iter->first << " " << iter->second << " found!" << endl; //Element 8 eight found!
    } else {
        cout << "Element not found in map!" << endl;
    }
    
    
    
    //自定义结构
    map <test_item, string> item;
    item.insert(make_pair(test_item("Jack", "178897"), "one"));
    item.insert(pair<test_item, string>(test_item("Bill", "978945"), "two"));
    item[test_item("Angi", "348158")] = "three";
    
    display_as_test_item(item);
    
    //查找元素 姓名为Bill
    auto itemFind = item.find(test_item("Bill", ""));
    
    if(itemFind != item.end()) {
        cout << "Element " << itemFind->first << " " << itemFind->second << " found!" << endl;
    } else {
        cout << "Element not found in map!" << endl;
    }
    
    itemFind = item.find(test_item("John", ""));
    
    if(itemFind != item.end()) {
        cout << "Element " << itemFind->first << itemFind->second << " found!" << endl;
    } else {
        cout << "Element not found in map!" << endl;
    }
}

//实例化
void init_test(void)
{
    //整型 map 类
    map<int, string> integers;
    
    map_print(integers); //map elements are: 
    
     //C++11引入的列表初始化
    map<int, string> initmap = { {1, "one"}, {2, "two"}, {3, "three"}, {4, "four"}, {5, "five"} };
    
    map_print(initmap); //map elements are: 1 : one 2 : two 3 : three 4 : four 5 : five
    
    map<int, string> initmap1 = { make_pair(1, "one"), make_pair(2, "two"), make_pair(3, "three"), make_pair(4, "four"), make_pair(5, "five") };
    
    map_print(initmap1); //map elements are: 1 : one 2 : two 3 : three 4 : four 5 : five
    
    map<int, string> initmap2 = { pair<int, string>(1, "one"), pair<int, string>(2, "two"), pair<int, string>(3, "three"), pair<int, string>(4, "four"), pair<int, string>(5, "five") };
    
    map_print(initmap2); //map elements are: 1 : one 2 : two 3 : three 4 : four 5 : five
    
    //初始化重复元素，只会剩 1 个
    map<int, string> initmap3 = { {3, "three"}, {3, "three"} };
    
    map_print(initmap3); //map elements are: 3 : three
    
     //使用一个map初始化另一个map，即复制map对象
    map<int, string> copymap(initmap);
    
    map_print(copymap); //map elements are: 1 : one 2 : two 3 : three 4 : four 5 : five
    
    //使用一个map初始化另一个map，即复制map对象
    map<int, string> copymap2 = initmap;
    
    map_print(copymap2); //map elements are: 1 : one 2 : two 3 : three 4 : four 5 : five
    
    //使用另一个map的所有元素初始化
    map<int, string> partialCopy(initmap.begin(), initmap.end());
    
    map_print(partialCopy); //map elements are: 1 : one 2 : two 3 : three 4 : four 5 : five
    
    //使用另一个map的所有元素初始化
    map<int, string> partialCopy2(initmap.cbegin(), initmap.cend());
    
    map_print(partialCopy2); //map elements are: 1 : one 2 : two 3 : three 4 : four 5 : five
    
    //使用 vector 的值来初始化 map
    vector<pair<int, string>> initVector = { {1, "one"}, {2, "two"}, {3, "three"}, {4, "four"}, {5, "five"} };
    
    map<int, string> copyVector(initVector.begin(), initVector.end());
    
    map_print(copyVector); //map elements are: 1 : one 2 : two 3 : three 4 : four 5 : five
    
    //使用 list 的值来初始化 map
    list<pair<int, string>> initList = { {1, "one"}, {2, "two"}, {3, "three"}, {4, "four"}, {5, "five"} };
    
    map<int, string> copyList(initList.begin(), initList.end());
    
    map_print(copyList); //map elements are: 1 : one 2 : two 3 : three 4 : four 5 : five
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
    r_iterate_test();   //反向遍历元素
    size_test();        //大小
    erase_test();       //删除元素
    clear_test();       //清空元素
    empty_test();       //判断是否为空
    swap_test();        //交换元素
    assign_test();      //分配新的内容替换原有的内容
    sort_test();        //排序
    
    two_dimensional_init_test();    //二维 map 实例化
    
    return 0;
}