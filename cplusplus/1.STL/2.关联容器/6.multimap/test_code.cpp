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
void multimap_print(multimap<int, string> integers)
{
   cout << "multimap elements are: ";
// #if __cplusplus >= 201103L
   for (auto it = integers.begin(); it != integers.end(); it++)
       cout << (*it).first << " : " << (*it).second << " ";
// #else
    // for ( multimap<int, string>::iterator it = integers.begin(); it != integers.end(); it++)
       // cout << (*it).first << " : " << (*it).second << " ";
// #endif
   cout << endl;
}

//二维 multimap 实例化
void two_dimensional_init_test(void)
{
    //定义二维
    multimap<int, string> subobj1 = { {1, "one"}, {2, "two"}, };
    multimap<int, string> subobj2 = { {3, "three"}, {4, "four"} };
    multimap<int, string> subobj3 = { {5, "five"}, {6, "six"} };
    multimap<int, multimap<int, string> > obj = { {1, subobj1}, {2, subobj2}, {3, subobj3}, };
 
    //输出二维 multimap
    for (multimap< int, multimap<int, string>>::iterator i = obj.begin(); i != obj.end(); i++) {
        cout << (*i).first << " : " << " ";
        for ( multimap<int, string>::iterator j = (*i).second.begin(); j != (*i).second.end(); j++)
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
    multimap<int, string> multimaptable = { {3, "three"}, {1, "one"}, {5, "five"}, {2, "two"},  {4, "four"} };
    
    //默认排序按key从小到大
    multimap_print(multimaptable); //multimap elements are: 1 : one 2 : two 3 : three 4 : four 5 : five 
    
    //排序， 按key从大到小
    //方法一：
    multimap<int, string, greater<int>> multimaptable2 = { {3, "three"}, {1, "one"}, {5, "five"}, {2, "two"},  {4, "four"} };
    
    cout << "multimap elements are: ";
    for (auto it = multimaptable2.begin(); it != multimaptable2.end(); it++)
        cout << (*it).first << " : " << (*it).second << " ";
    cout << endl; //multimap elements are: 5 : five 4 : four 3 : three 2 : two 1 : one 
   
   
    //方法二：
    multimap<int, string, sort_descending<int>> multimaptable3 = { {3, "three"}, {1, "one"}, {5, "five"}, {2, "two"},  {4, "four"} };
    
    cout << "multimap elements are: ";
    for (auto it = multimaptable3.begin(); it != multimaptable3.end(); it++)
        cout << (*it).first << " : " << (*it).second << " ";
    cout << endl; //multimap elements are: 5 : five 4 : four 3 : three 2 : two 1 : one
    
    
    //方法三：
    multimap<int, string, sort_descending2> multimaptable4 = { {3, "three"}, {1, "one"}, {5, "five"}, {2, "two"},  {4, "four"} };
    
    cout << "multimap elements are: ";
    for (auto it = multimaptable4.begin(); it != multimaptable4.end(); it++)
        cout << (*it).first << " : " << (*it).second << " ";
    cout << endl; //multimap elements are: 5 : five 4 : four 3 : three 2 : two 1 : one
    
    
    
    //排序， 按val排序，把multimap中的元素放到序列容器（如vector）中，再用sort进行排序
    multimap<int, string> multimaptable5 = { {3, "three"}, {1, "one"}, {5, "five"}, {2, "two"},  {4, "four"} };
    
    //将multimap中的内容转存到vector中
    vector<pair<int, string>> vec(multimaptable5.begin(), multimaptable5.end());
    //对线性的vector进行排序
    sort(vec.begin(), vec.end(), cmp);
    
    cout << "multimap elements are: ";
    for (auto it = vec.begin(); it != vec.end(); it++)
        cout << (*it).first << " : " << (*it).second << " ";
    cout << endl; //multimap elements are: 5 : five 4 : four 1 : one 3 : three 2 : two
    
    
    //自定义结构排序
    multimap <test_item, string> item;
    item.insert(make_pair(test_item("Jack", "178897"), "one"));
    item.insert(pair<test_item, string>(test_item("Bill", "978945"), "two"));
    item.insert(make_pair(test_item("Angi", "348158"), "three"));
    
    // test_item 定义了运算符 < , test_item::operator<让 sort按姓名字母顺序排列元素
    display_as_test_item(item);
    // Angi: 348158 : three Bill: 978945 : two Jack: 178897 : one
}

//分配新的内容替换原有的内容
void assign_test(void)
{
    multimap<int, string> multimaptable = { {3, "three"}, {1, "one"}, {5, "five"}, {2, "two"},  {4, "four"} };
    
    multimap_print(multimaptable); //multimap elements are: 1 : one 2 : two 3 : three 4 : four 5 : five 
    
    multimap<int, string> another2 = { {8, "eight"}, {7, "seven"} };
    
    //将 another2 的内容赋给 multimaptable
    multimaptable = another2;
    
    multimap_print(multimaptable); //multimap elements are: 7 : seven 8 : eight 
    
    multimap<int, string> another3 = { {9, "nine"}, {10, "ten"} };
    
    //将 another3 的内容赋给 multimaptable，another3内的值被清空
    multimaptable = move(another3);
    
    multimap_print(multimaptable); //multimap elements are: 9 : nine 10 : ten 
}

//交换元素
void swap_test(void)
{
    multimap<int, string> multimaptable = { {3, "three"}, {1, "one"}, {5, "five"}, {2, "two"},  {4, "four"} };
    multimap<int, string> another = { {8, "eight"}, {7, "seven"} };
    
    //交换
    multimaptable.swap(another);
    
    multimap_print(multimaptable); //multimap elements are: 7 : seven 8 : eight
    multimap_print(another);  //multimap elements are: 1 : one 2 : two 3 : three 4 : four 5 : five
}

//判断是否为空
void empty_test(void)
{
    multimap<int, string> multimaptable;
    
    cout << "Empty:" << multimaptable.empty() << endl;   //Empty:1
    
    //放入元素
    multimaptable.insert(make_pair(0, "zero"));
    
    cout << "Empty:" << multimaptable.empty() << endl;   //Empty:0
    
    //删除元素
    multimaptable.erase(0);
    
    cout << "Empty:" << multimaptable.empty() << endl;   //Empty:1
}

//清空元素
void clear_test(void)
{
    multimap<int, string> multimaptable = { {3, "three"}, {1, "one"}, {5, "five"}, {2, "two"},  {4, "four"} };
    
    multimap_print(multimaptable); //multimap elements are: 1 : one 2 : two 3 : three 4 : four 5 : five 
    
    //清空所有元素
    multimaptable.clear();
    
    multimap_print(multimaptable); //multimap elements are:
}

//删除元素
void erase_test(void)
{
    multimap<int, string> multimaptable = { {3, "three"}, {8, "eight"}, {1, "one"}, {5, "five"}, {2, "two"},  {7, "seven"}, {4, "four"}, {6, "six"} };
    
    multimap_print(multimaptable); //multimap elements are: 1 : one 2 : two 3 : three 4 : four 5 : five 6 : six 7 : seven 8 : eight 
    
    //根据key删除特定元素
    multimaptable.erase(3);
    
    multimap_print(multimaptable); //multimap elements are: 1 : one 2 : two 4 : four 5 : five 6 : six 7 : seven 8 : eight 
    
     //根据迭代器删除特定元素
    for( multimap<int, string>::iterator it = multimaptable.begin(); it != multimaptable.end();) {
        if((*it).first == 5) {
            it = multimaptable.erase(it);
        } else {
            ++it;
        }
    }
    
    multimap_print(multimaptable); //multimap elements are: 1 : one 2 : two 4 : four 6 : six 7 : seven 8 : eight
    
    //根据迭代器删除指定范围元素 删除 7 之后的元素，含7
    auto elementFound = multimaptable.find(7);
    
    if(elementFound != multimaptable.end()) {
        multimaptable.erase(elementFound, multimaptable.end());
    }
    
    multimap_print(multimaptable); //multimap elements are: 1 : one 2 : two 4 : four 6 : six
    
    //根据迭代器删除指定范围元素 删除 2 之前的元素，不含2
    auto anotherFind = multimaptable.find(2);
    
    if(anotherFind != multimaptable.end()) {
        multimaptable.erase(multimaptable.begin(), anotherFind);
    }
    
    multimap_print(multimaptable); //multimap elements are: 2 : two 4 : four 6 : six 
    
    //清空所有元素
    multimaptable.erase(multimaptable.begin(), multimaptable.end());
    
    multimap_print(multimaptable); //multimap elements are: 
    
    
    
    //自定义结构
    multimap <test_item, string> item;
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
        cout << "Element not found in multimap!" << endl;
    }
}

//大小
void size_test(void)
{
    //设置初始值
    multimap<int, string> multimaptable = { {3, "three"}, {1, "one"}, {5, "five"}, {2, "two"},  {4, "four"} };
    
    //大小和容量
    cout << "Size:" << multimaptable.size() << endl;
    
    //插入值 6
    multimaptable.insert(make_pair(6, "six"));
    
    cout << "Size:" << multimaptable.size() << endl;
    
    //插入值 7
    multimaptable.insert(make_pair(7, "seven"));
    
    cout << "Size:" << multimaptable.size() << endl;
    
    //插入值 8
    multimaptable.insert(pair<int, string> (8, "eight"));
    
    cout << "Size:" << multimaptable.size() << endl;
    
    // 最大可允许的multimap元素数量值
    cout << "Max_size:" << multimaptable.max_size() << endl;
}

//反向遍历元素
void r_iterate_test(void)
{
    multimap<int, string> multimaptable = { {3, "three"}, {1, "one"}, {5, "five"}, {2, "two"},  {4, "four"} };
    
    multimap<int, string>::reverse_iterator element = multimaptable.rbegin();
    while(element != multimaptable.rend()) {
        cout << (*element).first << " : " << (*element).second << " ";
        
        ++element;
    }
    cout << endl;
    
    multimap<int, string>::const_reverse_iterator celement = multimaptable.crbegin();
    while(celement != multimaptable.crend()) {
        cout << (*celement).first << " : " << (*celement).second << " ";
        
        ++celement;
    }
    cout << endl;
    
    auto acelement = multimaptable.crbegin();
    while(acelement != multimaptable.crend()) {
        cout << (*acelement).first << " : " << (*acelement).second << " ";
        
        ++acelement;
    }
    cout << endl;
    
    for ( multimap<int, string>::reverse_iterator it = multimaptable.rbegin(); it != multimaptable.rend(); it++)
       cout << (*it).first << " : " << (*it).second << " ";
    cout << endl;
    
    for ( multimap<int, string>::const_reverse_iterator it = multimaptable.crbegin(); it != multimaptable.crend(); it++)
       cout << (*it).first << " : " << (*it).second << " ";
    cout << endl;
    
    for (auto it = multimaptable.rbegin(); it != multimaptable.rend(); it++)
        cout << (*it).first << " : " << (*it).second << " ";
    cout << endl;
    
    for (auto it = multimaptable.rbegin(); it != multimaptable.rend(); it++)
        cout << get<0>(*it) << " : " << get<1>(*it) << " ";
    cout << endl;
}

//正向遍历元素
void iterate_test(void)
{
    multimap<int, string> multimaptable = { {3, "three"}, {1, "one"}, {5, "five"}, {2, "two"},  {4, "four"} };
    
    for (auto v : multimaptable)
       cout << v.first << " : " << v.second << " ";
    cout << endl;

    //使用迭代器
    multimap<int, string>::iterator element = multimaptable.begin();
    while(element != multimaptable.end()) {
        cout << (*element).first << " : " << (*element).second << " ";
        
        ++element;
    }
    cout << endl;
    
    multimap<int, string>::const_iterator celement = multimaptable.cbegin();
    while(celement != multimaptable.cend()) {
        cout << (*celement).first << " : " << (*celement).second << " ";
        
        ++celement;
    }
    cout << endl;
    
    auto acelement = multimaptable.cbegin();
    while(acelement != multimaptable.cend()) {
        cout << (*acelement).first << " : " << (*acelement).second << " ";
        
        ++acelement;
    }
    cout << endl;
    
    for ( multimap<int, string>::iterator it = multimaptable.begin(); it != multimaptable.end(); it++)
       cout << (*it).first << " : " << (*it).second << " ";
    cout << endl;
    
    for ( multimap<int, string>::const_iterator it = multimaptable.cbegin(); it != multimaptable.cend(); it++)
       cout << (*it).first << " : " << (*it).second << " ";
    cout << endl;
    
    for (auto it = multimaptable.begin(); it != multimaptable.end(); it++)
        cout << (*it).first << " : " << (*it).second << " ";
    cout << endl;
    
    for (auto it = multimaptable.begin(); it != multimaptable.end(); it++)
        cout << get<0>(*it) << " : " << get<1>(*it) << " ";
    cout << endl;
}

//插入元素
void insert_test(void)
{
    //初始化
    multimap<int, string> multimaptable = { {3, "three"}, {1, "one"}, {5, "five"}, {2, "two"},  {4, "four"} };
    
    multimap_print(multimaptable); //multimap elements are: 1 : one 2 : two 3 : three 4 : four 5 : five
    
    //插入值 6
    // multimaptable[6] = "six"; //不支持该写法
    multimaptable.insert(make_pair(6, "six"));
    
    multimap_print(multimaptable); //multimap elements are: 1 : one 2 : two 3 : three 4 : four 5 : five 6 : six
    
    //插入值 7
    multimaptable.insert(make_pair(7, "seven"));
    
    multimap_print(multimaptable); //multimap elements are: 1 : one 2 : two 3 : three 4 : four 5 : five 6 : six 7 : seven 
    
    //插入值 8
    multimaptable.insert(pair<int, string> (8, "eight"));
    
    multimap_print(multimaptable); //multimap elements are: 1 : one 2 : two 3 : three 4 : four 5 : five 6 : six 7 : seven 8 : eight 
    
    //插入值 11
    multimaptable.insert(multimap<int, string>::value_type (11, "eleven"));
    
    multimap_print(multimaptable); //multimap elements are: 1 : one 2 : two 3 : three 4 : four 5 : five 6 : six 7 : seven 8 : eight 11 : eleven 
    
    
    //另一个 map，有两个元素
    map<int, string> another = { {9, "nine"}, {10, "ten"} };
    
    //将 another 的元素插入 multimaptable
    multimaptable.insert(another.begin(), another.end());
    
    multimap_print(multimaptable); //multimap elements are: 1 : one 2 : two 3 : three 4 : four 5 : five 6 : six 7 : seven 8 : eight 9 : nine 10 : ten 11 : eleven
}

//查找元素
void find_test(void)
{
    //初始化
    multimap<int, string> multimaptable = { {3, "three"}, {3, "three2"}, {1, "one"}, {5, "five"}, {2, "two"},  {4, "four"} };
    
    multimap_print(multimaptable); //multimap elements are: 1 : one 2 : two 3 : three 4 : four 5 : five
    
    //查找元素 3
    auto elementFound = multimaptable.find(3);
    
    if(elementFound != multimaptable.end()) {
        //获取 key 为 3 的数量
        size_t numPairsInMap = multimaptable.count(3);
        
        cout << "Element " << elementFound->first << " found!" << endl;
        //遍历所有 key 为 3 的值
        for(size_t counter = 0; counter < numPairsInMap; ++counter) {
            cout << "Key = " << elementFound->first << ", val [" << counter << "] = " << "]" << elementFound->second << endl;
            ++elementFound;
        }
    } else {
        cout << "Element not found in multimap!" << endl;
    }
    
    //查找元素 6
    auto anotherFind = multimaptable.find(6);
    
    if(anotherFind != multimaptable.end()) {
        cout << "Element " << anotherFind->first << " : "<< anotherFind->second << " found!" << endl;
    } else {
        cout << "Element not found in multimap!" << endl;
    }
    
    //判断 3 在 map 中的数量
    size_t num = multimaptable.count(3);
    cout << "Element " << 3 << " count " << num << endl;
    
    //判断 6 在 map 中的数量
    num = multimaptable.count(6);
    cout << "Element " << 6 << " count " << num << endl;
    
    
    
    //插入值 8
    multimaptable.insert(pair<int, string> (8, "eight"));
    
    multimap_print(multimaptable); //map elements are: 1 : one 2 : two 3 : three 4 : four 5 : five 8 : eight
    
    
    //查找第一个大于或等于key的数值
    auto iter = multimaptable.lower_bound(2); 
    if(iter != multimaptable.end()) {
        cout << "Element " << iter->first << " " << iter->second << " found!" << endl; // Element 2 two found!
    } else {
        cout << "Element not found in map!" << endl;
    }
    
    //查找第一个大于key的数值
    iter = multimaptable.upper_bound(2); 
    if(iter != multimaptable.end()) {
        cout << "Element " << iter->first << " " << iter->second << " found!" << endl; //Element 3 three found!
    } else {
        cout << "Element not found in map!" << endl;
    }
    
    //查找第一个大于或等于key的数值
    iter = multimaptable.lower_bound(6); 
    if(iter != multimaptable.end()) {
        cout << "Element " << iter->first << " " << iter->second << " found!" << endl; //Element 8 eight found!
    } else {
        cout << "Element not found in map!" << endl;
    }
    
    //查找第一个大于key的数值
    iter = multimaptable.upper_bound(6); 
    if(iter != multimaptable.end()) {
        cout << "Element " << iter->first << " " << iter->second << " found!" << endl; //Element 8 eight found!
    } else {
        cout << "Element not found in map!" << endl;
    }
    
    
    
    //自定义结构
    multimap <test_item, string> item;
    item.insert(make_pair(test_item("Jack", "178897"), "one"));
    item.insert(pair<test_item, string>(test_item("Bill", "978945"), "two"));
    item.insert(make_pair(test_item("Angi", "348158"), "three"));
    
    display_as_test_item(item);
    
    //查找元素 姓名为Bill
    auto itemFind = item.find(test_item("Bill", ""));
    
    if(itemFind != item.end()) {
        cout << "Element " << itemFind->first << " " << itemFind->second << " found!" << endl;
    } else {
        cout << "Element not found in multimap!" << endl;
    }
    
    itemFind = item.find(test_item("John", ""));
    
    if(itemFind != item.end()) {
        cout << "Element " << itemFind->first << itemFind->second << " found!" << endl;
    } else {
        cout << "Element not found in multimap!" << endl;
    }
}

//实例化
void init_test(void)
{
    //整型 multimap 类
    multimap<int, string> integers;
    
    multimap_print(integers); //multimap elements are: 
    
     //C++11引入的列表初始化
    multimap<int, string> initmultimap = { {1, "one"}, {2, "two"}, {3, "three"}, {4, "four"}, {5, "five"} };
    
    multimap_print(initmultimap); //multimap elements are: 1 : one 2 : two 3 : three 4 : four 5 : five
    
    multimap<int, string> initmultimap1 = { make_pair(1, "one"), make_pair(2, "two"), make_pair(3, "three"), make_pair(4, "four"), make_pair(5, "five") };
    
    multimap_print(initmultimap1); //multimap elements are: 1 : one 2 : two 3 : three 4 : four 5 : five
    
    multimap<int, string> initmultimap2 = { pair<int, string>(1, "one"), pair<int, string>(2, "two"), pair<int, string>(3, "three"), pair<int, string>(4, "four"), pair<int, string>(5, "five") };
    
    multimap_print(initmultimap2); //multimap elements are: 1 : one 2 : two 3 : three 4 : four 5 : five
    
    //初始化重复元素
    multimap<int, string> initmultimap3 = { {3, "three"}, {3, "three"} };
    
    multimap_print(initmultimap3); //multimap elements are: 3 : three 3 : three 
    
     //使用一个multimap初始化另一个multimap，即复制multimap对象
    multimap<int, string> copymultimap(initmultimap);
    
    multimap_print(copymultimap); //multimap elements are: 1 : one 2 : two 3 : three 4 : four 5 : five
    
    //使用一个multimap初始化另一个multimap，即复制multimap对象
    multimap<int, string> copymultimap2 = initmultimap;
    
    multimap_print(copymultimap2); //multimap elements are: 1 : one 2 : two 3 : three 4 : four 5 : five
    
    //使用另一个multimap的所有元素初始化
    multimap<int, string> partialCopy(initmultimap.begin(), initmultimap.end());
    
    multimap_print(partialCopy); //multimap elements are: 1 : one 2 : two 3 : three 4 : four 5 : five
    
    //使用另一个multimap的所有元素初始化
    multimap<int, string> partialCopy2(initmultimap.cbegin(), initmultimap.cend());
    
    multimap_print(partialCopy2); //multimap elements are: 1 : one 2 : two 3 : three 4 : four 5 : five
    
    //使用一个map初始化另一个multimap，即复制map对象
    map<int, string> initmap = { {1, "one"}, {2, "two"}, {3, "three"}, {4, "four"}, {5, "five"} };
    multimap<int, string> copymap(initmap.begin(), initmap.end());
    
    multimap_print(copymap); //multimap elements are: 1 : one 2 : two 3 : three 4 : four 5 : five
    
    //使用 vector 的值来初始化 multimap
    vector<pair<int, string>> initVector = { {1, "one"}, {2, "two"}, {3, "three"}, {4, "four"}, {5, "five"} };
    
    multimap<int, string> copyVector(initVector.begin(), initVector.end());
    
    multimap_print(copyVector); //multimap elements are: 1 : one 2 : two 3 : three 4 : four 5 : five
    
    //使用 list 的值来初始化 multimap
   list<pair<int, string>> initList = { {1, "one"}, {2, "two"}, {3, "three"}, {4, "four"}, {5, "five"} };
    
    multimap<int, string> copyList(initList.begin(), initList.end());
    
    multimap_print(copyList); //multimap elements are: 1 : one 2 : two 3 : three 4 : four 5 : five
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
    
    two_dimensional_init_test();    //二维 multimap 实例化
    
    return 0;
}