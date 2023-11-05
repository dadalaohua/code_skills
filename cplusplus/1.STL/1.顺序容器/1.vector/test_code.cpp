#include <iostream>
#include <vector>

#include <algorithm> //sort
#include <tuple>    // std::tuple

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
void vector_print(vector<int> integers)
{
   cout << "vector elements are: ";
// #if __cplusplus >= 201103L
   for (auto it = integers.begin(); it != integers.end(); it++)
       cout << *it << " ";
// #else
    // for (vector<int>::iterator it = integers.begin(); it != integers.end(); it++)
       // cout << *it << " ";
// #endif
   cout << endl;
}

void vector_pairprint(vector< pair<int, int> > pairintegers)
{
    cout << "vector elements are: ";
    for (auto it = pairintegers.begin(); it != pairintegers.end(); it++)
       cout << it->first << " : " << it->second << ", ";
    cout << endl;
}

void vector_tupleprint(vector< tuple<int, int> > tupleintegers)
{
    cout << "vector elements are: ";
    for (auto it = tupleintegers.begin(); it != tupleintegers.end(); it++) {
        cout << get<0>(*it) << " : " << get<1>(*it) << ", ";
    }
    cout << endl;
}


//三维 vector 实例化
void three_dimensional_init_test(void)
{
    vector<vector<vector<int>>> obj(3, vector<vector<int>>(4));
    vector<vector<vector<int>>> obj2(3, vector<vector<int>>(4, vector<int>(5)));
    vector<vector<vector<int>>> obj3(3, vector<vector<int>>(4, vector<int>(5, 6)));
    
    //输出三维 vector
    for(size_t i = 0; i < obj3.size(); i++) {
        for(size_t j = 0; j < obj3[i].size(); j++) {
            for(size_t k = 0; k < obj3[i][j].size(); k++) {
                cout << obj3[i][j][k] << " ";
            }
            cout << endl;
        }
        cout << endl;
    }
    cout << endl;
}

//二维 vector 实例化
void two_dimensional_init_test(void)
{
    int row = 5, col = 6; 
    
    //定义二维 vector 5行6列 
    vector< vector<int> > obj(row, vector<int>(col)); 
 
    //输出二维 vector
    for(size_t i = 0; i < obj.size(); i++) {
        for(size_t j = 0; j < obj[i].size(); j++) {
            cout << obj[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
    
    //定义二维 vector 5行6列 初始化所有的值为 7
    vector< vector<int> > obj2(row, vector<int>(col, 7)); 
 
    //输出二维 vector
    for(size_t i = 0; i < obj2.size(); i++) {
        for(size_t j = 0; j < obj2[i].size(); j++) {
            cout << obj2[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
    
    //定义二维 vector 5行
    vector< vector<int> > obj3(row);
    
    //动态二维 vector 为每一行为 6 列，值全为0 
    for(size_t i = 0; i < obj3.size(); i++) { 
        //改变当前的大小
        obj3[i].resize(col); 
    }
    
    //输出二维 vector
    for(size_t i = 0; i < obj3.size(); i++) {
        for(size_t j = 0; j < obj3[i].size(); j++) {
            cout << obj3[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
    
#if __cplusplus >= 201703L
    //定义二维 vector 5行6列 初始化所有的值为 7
    vector obj4(row, vector<int> (col, 7));
    
    //输出二维 vector
    for(size_t i = 0; i < obj4.size(); i++) {
        for(size_t j = 0; j < obj4[i].size(); j++) {
            cout << obj4[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
#endif
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
    vector<int> integers;
    
    //放入5个元素
    integers.push_back(15);
    integers.push_back(84);
    integers.push_back(64);
    integers.push_back(38);
    integers.push_back(55);
    
    vector_print(integers); //vector elements are: 15 84 64 38 55
    
    //排序， 从小到大
    sort(integers.begin(), integers.end());
    
    vector_print(integers); //vector elements are: 15 38 55 64 84 
    
    //排序， 从大到小
    //方法一：
    sort(integers.begin(), integers.end(), sort_predicate_descending);
    
    vector_print(integers);  //vector elements are: 84 64 55 38 15
    
    //方法二：
    sort(integers.begin(), integers.end(), [&](int x, int y) {
        return x > y;
    });
    
    vector_print(integers); //vector elements are: 84 64 55 38 15
    
    
    //自定义结构排序
    vector <test_item> item;
    item.push_back(test_item("Jack", "178897"));
    item.push_back(test_item("Bill", "978945"));
    item.push_back(test_item("Angi", "348158"));
    
    display_as_test_item(item);
    // Jack: 178897
    // Bill: 978945
    // Angi: 348158
    
    // test_item 定义了运算符 < , test_item::operator<让 sort按姓名字母顺序排列元素
    sort(item.begin(), item.end());
    display_as_test_item(item);
    // Angi: 348158
    // Bill: 978945
    // Jack: 178897
    
    // 使用二元谓词函数按电话号码进行排序
    sort(item.begin(), item.end(), sort_phone_number);
    display_as_test_item(item);
    // Jack: 178897
    // Angi: 348158
    // Bill: 978945
}

vector<int> return_test_function_1(void)
{
    vector<int> integers;
    
    //放入5个元素
    integers.push_back(20);
    integers.push_back(21);
    integers.push_back(22);
    integers.push_back(23);
    integers.push_back(24);
    
    return integers;
}

vector<int> return_test_function_2(void)
{
    vector<int> integers;
    
    //放入5个元素
    integers.push_back(25);
    integers.push_back(26);
    integers.push_back(27);
    integers.push_back(28);
    integers.push_back(29);
    
    return vector<int> {integers.begin(), integers.end()};
}

vector<int> return_test_function_3(void)
{
    return vector<int> { 30, 31, 32, 33, 34 };
}

//返回值
void return_test(void)
{
    vector<int> ret1 = return_test_function_1();
    vector_print(ret1); //vector elements are: 20 21 22 23 24 
    
    vector<int> ret2 = return_test_function_2();
    vector_print(ret2); //vector elements are: 25 26 27 28 29
    
    vector<int> ret3 = return_test_function_3();
    vector_print(ret3); //vector elements are: 30 31 32 33 34
}

//分配新的内容替换原有的内容
void assign_test(void)
{
    vector<int> integers;
    
    //放入5个元素
    integers.push_back(20);
    integers.push_back(21);
    integers.push_back(22);
    integers.push_back(23);
    integers.push_back(24);
    
    vector_print(integers); //vector elements are: 20 21 22 23 24 
    
    //替换成3个35
    integers.assign(3, 35);
    
    vector_print(integers); //vector elements are: 35 35 35
    
    vector<int> another(6, 55);
    
    //替换成 another 的内容
    integers.assign(another.begin(), another.end());
    
    vector_print(integers); //vector elements are: 55 55 55 55 55 55
    
    vector<int> another2(5, 86);
    
    //将 another2 的内容赋给 integers
    integers = another2;
    
    vector_print(integers); //vector elements are: 86 86 86 86 86 
    
    vector<int> another3(8, 36);
    
    //将 another3 的内容赋给 integers，another3内的值被清空
    integers = move(another3);
    
    vector_print(integers); //vector elements are: 36 36 36 36 36 36 36 36 
}

//交换元素
void swap_test(void)
{
    vector<int> integers;
    
    //放入5个元素
    integers.push_back(20);
    integers.push_back(21);
    integers.push_back(22);
    integers.push_back(23);
    integers.push_back(24);
    
    vector<int> another(3, 30);
    
    //交换
    integers.swap(another);
    
    vector_print(integers); //vector elements are: 30 30 30 
    vector_print(another);  //vector elements are: 20 21 22 23 24
}

//访问元素
void at_test(void)
{
    vector<int> integers;
    
    //放入5个元素
    integers.push_back(20);
    integers.push_back(21);
    integers.push_back(22);
    integers.push_back(23);
    integers.push_back(24);
    
    for (size_t i = 0; i < integers.size(); i++)
       cout << integers[i] << " ";
    cout << endl;
    
    //遍历输出
    for (size_t i = 0; i < integers.size(); i++)
       cout << integers.at(i) << " ";
    cout << endl;
    
    //输出首元素
    cout << "Front:" << integers.front() << endl;   //Front:20
    
    //输出尾元素
    cout << "Back:" << integers.back() << endl;     //Back:24
    
    
    vector< pair<int, int> > pairintegers;
    
    pairintegers.push_back({1, 2});
    pairintegers.push_back(pair<int, int>(3, 4));
    pairintegers.push_back(make_pair(5, 6));
    
    for (size_t i = 0; i < pairintegers.size(); i++)
       cout << pairintegers[i].first << " : " << pairintegers[i].second << ", ";
    cout << endl;
    
    for (size_t i = 0; i < pairintegers.size(); i++)
       cout << get<0>(pairintegers[i]) << " : " << get<1>(pairintegers[i]) << ", ";
    cout << endl;
}

//判断是否为空
void empty_test(void)
{
    vector<int> integers;
    
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
    vector<int> integers;
    
    //先放入3个元素
    integers.push_back(20);
    integers.push_back(21);
    integers.push_back(22);
    
    vector_print(integers); //vector elements are: 20 21 22 
    
    //清空所有元素
    integers.clear();
    
    vector_print(integers); //vector elements are:
}

//删除元素
void erase_test(void)
{
    vector<int> integers;
    
    integers.push_back(20);
    integers.push_back(21);
    integers.push_back(22);
    integers.push_back(23);
    integers.push_back(24);
    
    vector_print(integers); //vector elements are: 20 21 22 23 24 
    
    //删除特定元素
    for(vector<int>::iterator it = integers.begin(); it != integers.end();) {
        if(*it == 22) {
            it = integers.erase(it);
        } else {
            ++it;
        }
    }
    
    vector_print(integers); //vector elements are: 20 21 23 24 
    
    //删除特定范围的元素
    integers.erase(integers.begin() + 2, integers.end());
    
    vector_print(integers); //vector elements are: 20 21
    
    //清空所有元素
    integers.erase(integers.begin(), integers.end());
    
    vector_print(integers); //vector elements are:
}

//大小与容量
void size_test(void)
{
    //设置初始大小为 2
    vector<int> integers(2);
    
    //大小和容量
    cout << "Size:" << integers.size();
    cout << ", Capacity:" << integers.capacity() << endl;
    
    integers.push_back(10);
    
    cout << "Size:" << integers.size();
    cout << ", Capacity:" << integers.capacity() << endl;
    
    integers.push_back(11);
    
    cout << "Size:" << integers.size();
    cout << ", Capacity:" << integers.capacity() << endl;
    
    integers.push_back(12);
    
    cout << "Size:" << integers.size();
    cout << ", Capacity:" << integers.capacity() << endl;
    
    // 最大可允许的vector元素数量值
    cout << "Max_size:" << integers.max_size() << endl;
    
    //默认
    vector<int> another;
    
    cout << "Size:" << another.size();
    cout << ", Capacity:" << another.capacity() << endl;
    
    another.push_back(123);
    
    cout << "Size:" << another.size();
    cout << ", Capacity:" << another.capacity() << endl;
    
    cout << "Max_size:" << integers.max_size() << endl;
    
    //修改大小
    another.resize(8);
    cout << "Size:" << another.size();
    cout << ", Capacity:" << another.capacity() << endl;
    
    //修改容量
    another.reserve(16);
    cout << "Size:" << another.size();
    cout << ", Capacity:" << another.capacity() << endl;
}

//反向遍历元素
void r_iterate_test(void)
{
    vector<int> integers;
    
    integers.push_back(10);
    integers.push_back(12);
    integers.push_back(66);
    
    for (int i = integers.size() - 1; i >= 0; i--)
       cout << integers[i] << " ";
    cout << endl;
    
    vector<int>::reverse_iterator element = integers.rbegin();
    while(element != integers.rend()) {
        cout << *element << " ";
        
        ++element;
    }
    cout << endl;
    
    vector<int>::const_reverse_iterator celement = integers.crbegin();
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
    
    for (vector<int>::reverse_iterator it = integers.rbegin(); it != integers.rend(); it++)
       cout << *it << " ";
    cout << endl;
    
    for (auto it = integers.rbegin(); it != integers.rend(); it++)
        cout << *it << " ";
    cout << endl;
}

//正向遍历元素
void iterate_test(void)
{
    vector<int> integers;
    
    integers.push_back(10);
    integers.push_back(12);
    integers.push_back(66);
    
    for (size_t i = 0; i < integers.size(); i++)
       cout << integers[i] << " ";
    cout << endl;
    
    for (int v : integers)
       cout << v << " ";
    cout << endl;

    //使用迭代器
    vector<int>::iterator element = integers.begin();
    while(element != integers.end()) {
        cout << *element << " ";
        
        ++element;
    }
    cout << endl;
    
    vector<int>::const_iterator celement = integers.cbegin();
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
    
    for (vector<int>::iterator it = integers.begin(); it != integers.end(); it++)
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
    vector<int> integers(4, 90);
    
    vector_print(integers); //vector elements are: 90 90 90 90
    
    //在起始位置插入值 25
    integers.insert(integers.begin(), 25);
    
    vector_print(integers); //vector elements are: 25 90 90 90 90
    
    //在末尾位置插入 2 个值 35
    integers.insert(integers.end(), 2, 35);
    
    vector_print(integers); //vector elements are: 25 90 90 90 90 35 35
    
    //在从起始位置开始+2的位置插入值 45
    integers.insert(integers.begin() + 2, 45);
    
    vector_print(integers); //vector elements are: 25 90 45 90 90 90 35 35
    
    //在末尾位置之前的2个位置处插入值 55
    integers.insert(integers.end() - 2, 55);
    
    vector_print(integers); //vector elements are: 25 90 45 90 90 90 55 35 35
    
    //另一个 vector，有两个值为30的元素
    vector<int> another(2, 30);
    
    //将 another 的元素插入 integers 从起始位置开始+1的位置
    integers.insert(integers.begin() + 1, another.begin(), another.end());
    
    vector_print(integers); //vector elements are: 25 30 30 90 45 90 90 90 55 35 35
}

//末尾删除元素
void pop_back_test(void)
{
    vector<int> integers;
    
    //先放入3个元素
    integers.push_back(10);
    integers.push_back(12);
    integers.push_back(66);
    
    vector_print(integers); //vector elements are: 10 12 66 
    
    //删除最后一个元素
    integers.pop_back();
    
    vector_print(integers); //vector elements are: 10 12 
    
    //删除最后一个元素
    integers.pop_back();
    
    vector_print(integers); //vector elements are: 10 
}

//末尾插入元素
void push_back_test(void)
{
    vector<int> integers;
    
    integers.push_back(10);
    integers.push_back(12);
    integers.push_back(66);
    
    vector_print(integers);
    

    vector< pair<int, int> > pairintegers; //vector elements are: 10 12 66 
    
    pairintegers.push_back({1, 2});
    pairintegers.push_back(pair<int, int>(3, 4));
    pairintegers.push_back(make_pair(5, 6));
    
    vector_pairprint(pairintegers); //vector elements are: 1 : 2, 3 : 4, 5 : 6, 
    
    
    vector< tuple<int, int> > tupleintegers;
    
    tupleintegers.push_back(tuple<int, int>(7, 8));
    tupleintegers.push_back(make_tuple(9, 10));
    
    vector_tupleprint(tupleintegers); //vector elements are: 7 : 8, 9 : 10, 
}

//末尾插入元素
void emplace_back_test(void)
{
    vector<int> integers;
    
    integers.emplace_back(10);
    integers.emplace_back(12);
    integers.emplace_back(66);
    
    vector_print(integers);
}

//实例化
void init_test(void)
{
    //整型 vector 类
    vector<int> integers;
    
    vector_print(integers); //vector elements are: 
    
    //C++11引入的列表初始化
    vector<int> initVector = { 1, 2, 3, 4, 5 };
    
    vector_print(initVector); //vector elements are: 1 2 3 4 5 

    //设置初始大小为10
    vector<int> tenElements(10);
    
    vector_print(tenElements); //vector elements are: 0 0 0 0 0 0 0 0 0 0 
    
    //设置初始大小为10, 值为90
    vector<int> tenElemInit(10, 90);
    
    vector_print(tenElemInit); //vector elements are: 90 90 90 90 90 90 90 90 90 90
    
    //使用一个vector初始化另一个vector，即复制vector对象
    vector<int> copyVector(tenElemInit);
    
    vector_print(copyVector); //vector elements are: 90 90 90 90 90 90 90 90 90 90
    
    //使用一个vector初始化另一个vector，即复制vector对象
    vector<int> copyVector2 = tenElemInit;
    
    vector_print(copyVector2); //vector elements are: 90 90 90 90 90 90 90 90 90 90
    
    //使用另一个vector的前五个元素初始化
    vector<int> partialCopy(tenElemInit.begin(), tenElemInit.begin() + 5);
    
    vector_print(partialCopy); //vector elements are: 90 90 90 90 90
    
    //使用另一个vector的前五个元素初始化，其中cbegin和cend由于C++11引入
    vector<int> partialCopy2(tenElemInit.cbegin(), tenElemInit.cbegin() + 5);
    
    vector_print(partialCopy2); //vector elements are: 90 90 90 90 90
    
    
    //初始化一对数值
    vector< pair<int, int> > pairintegers = {{1, 2}, {3, 4}};
    vector_pairprint(pairintegers); //vector elements are: 1 : 2, 3 : 4, 
    
    vector< pair<int, int> > pairintegers2(2, pair<int, int>(5, 6));
    vector_pairprint(pairintegers2); //vector elements are: 5 : 6, 5 : 6, 
    
    vector< pair<int, int> > pairintegers3(2, make_pair(7, 8));
    vector_pairprint(pairintegers3); //vector elements are: 7 : 8, 7 : 8,
    
    vector< tuple<int, int> > tupleintegers2(2, tuple<int, int>(5, 6));
    vector_tupleprint(tupleintegers2); //vector elements are: 5 : 6, 5 : 6, 
    
    vector< tuple<int, int> > tupleintegers3(2, make_tuple(7, 8));
    vector_tupleprint(tupleintegers3); //vector elements are: 7 : 8, 7 : 8,
    
    //初始化更对数值
    vector< tuple<int, int, int> > tupleintegers4(2, tuple<int, int, int>(0, 1, 2));
    cout << "vector elements are: ";
    for (auto it = tupleintegers4.begin(); it != tupleintegers4.end(); it++) {
        cout << get<0>(*it) << " " << get<1>(*it) << " " << get<2>(*it) << ", ";
    }
    cout << endl; // 0 : 1, 2, 0 : 1, 2, 
    
    vector< tuple<int, int, int> > tupleintegers5(2, make_tuple(3, 4, 5));
    cout << "vector elements are: ";
    for (auto it = tupleintegers5.begin(); it != tupleintegers5.end(); it++) {
        cout << get<0>(*it) << " " << get<1>(*it) << " " << get<2>(*it) << ", ";
        
        //方式二
        //auto [x, y, z] = (*it);
        //cout << x << " : " << y << ", " << z << ", ";
    }
    cout << endl;
    
    vector< tuple<int, int, int, int, int, int> > tupleintegers6(2, make_tuple(3, 4, 5, 6, 7, 8));
    cout << "vector elements are: ";
    for (auto it = tupleintegers6.begin(); it != tupleintegers6.end(); it++) {
        for(int i = 0; i < tuple_size<decltype(*it)>::value; i++) {
            cout << get<i>(*it) << " ";
        }
        cout << ", ";
        
        // cout << get<0>(*it) << " " << get<1>(*it) << " " << get<2>(*it) << " " \
        // << get<3>(*it) << " " << get<4>(*it) << " " << get<5>(*it) << ", ";
        
        //方式二
        //auto [x1, x2, x3, x4, x5, x6] = (*it);
        //cout << x1 << " " << x2 << " " << x3 << " " << x4 << " " << x5 << " " << x6 << ", ";
    }
    cout << endl;
}
/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    cout << __cplusplus << endl;
    
    init_test();        //实例化
    // emplace_back_test();   //末尾插入元素
    // push_back_test();   //末尾插入元素
    // pop_back_test();    //末尾删除元素
    // insert_test();      //在指定位置插入元素
    // iterate_test();     //正向遍历元素
    // r_iterate_test();   //反向遍历元素
    // size_test();        //大小与容量
    // erase_test();       //删除元素
    // clear_test();       //清空元素
    // empty_test();       //判断是否为空
    // at_test();          //访问元素
    // swap_test();        //交换元素
    // assign_test();      //分配新的内容替换原有的内容
    // return_test();      //返回值
    // sort_test();        //排序
    
    // two_dimensional_init_test();    //二维 vector 实例化
    // three_dimensional_init_test();    //三维 vector 实例化
    return 0;
}