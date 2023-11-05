#include <iostream>
#include <array>

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
template <typename T>
void array_print(const T& integers)
{
    cout << "array elements are: ";
    for (auto it = integers.begin(); it != integers.end(); it++)
       cout << *it << " ";
    cout << endl;
}

//三维 array 实例化
void three_dimensional_init_test(void)
{
    array< array< array<int, 6>, 5 >, 4> obj;
    
    //输出三维 array
    for(size_t i = 0; i < obj.size(); i++) {
        for(size_t j = 0; j < obj[i].size(); j++) {
            obj[i][j].fill(0);
            for(size_t k = 0; k < obj[i][j].size(); k++) {
                cout << obj[i][j][k] << " ";
            }
            cout << endl;
        }
        cout << endl;
    }
    cout << endl;
}

//二维 array 实例化
void two_dimensional_init_test(void)
{
    //定义二维 array 5行6列 
    array< array<int, 5>, 6 > obj; 
    
    //输出二维 array
    for(size_t i = 0; i < obj.size(); i++) {
        obj[i].fill(0);
        for(size_t j = 0; j < obj[i].size(); j++) {
            cout << obj[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
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
    array<int, 5> integers{ {15, 84, 64, 38, 55} };
    
    array_print(integers); //array elements are: 15 84 64 38 55
    
    //排序， 从小到大
    sort(integers.begin(), integers.end());
    
    array_print(integers); //array elements are: 15 38 55 64 84 
    
    //排序， 从大到小
    //方法一：
    sort(integers.begin(), integers.end(), sort_predicate_descending);
    
    array_print(integers);  //array elements are: 84 64 55 38 15
    
    //方法二：
    sort(integers.begin(), integers.end(), [&](int x, int y) {
        return x > y;
    });
    
    array_print(integers); //array elements are: 84 64 55 38 15
    
    
    //自定义结构排序
    array <test_item, 3> item{ {test_item("Jack", "178897"), test_item("Bill", "978945"), test_item("Angi", "348158")} };
    
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

array<int, 5> return_test_function_1(void)
{
    array<int, 5> integers{ { 20, 21, 22, 23, 24 } };
    
    return integers;
}

array<int, 5> return_test_function_2(void)
{
    return array<int, 5> { {30, 31, 32, 33, 34} };
}

//返回值
void return_test(void)
{
    array<int, 5> ret1 = return_test_function_1();
    array_print(ret1); //array elements are: 20 21 22 23 24 
    
    array<int, 5> ret2 = return_test_function_2();
    array_print(ret2); //array elements are: 30 31 32 33 34
}

template<class T>
void tuple_sise_test(T t)
{
    //int a[tuple_size<T>::value]; 
    cout << tuple_size<T>::value << endl;   // 获取元素数量, 能用于编译时
}

//获取类型与大小
void tuple_type_sise_test(void)
{
    // 定义 array 并获取位于位置 0 的元素类型
    array<int, 10> data { {0, 1, 2, 3, 4, 5, 6, 7, 8, 9} };
    // using T = std::tuple_element<0, decltype(data)>::type; // int

    //获取元素数量
    tuple_sise_test(data);
}

//分配新的内容替换原有的内容
void assign_test(void)
{
    array<int, 5> integers = { {1, 2, 3, 4, 5} };
    
    array_print(integers); //array elements are: 1 2 3 4 5 
    
    array<int, 5> another2;
    another2.fill(86);
    
    //将 another2 的内容赋给 integers
    integers = another2;
    
    array_print(integers); //array elements are: 86 86 86 86 86 
    
    array<int, 5> another3;
    another3.fill(36);
    
    //将 another3 的内容赋给 integers，another3内的值被清空
    integers = move(another3);
    
    array_print(integers); //array elements are: 36 36 36 36 36 36 36 36 
}

//比较
void compare_test(void)
{
    array<int, 3> integers_1{ {1, 2, 3} };
    array<int, 3> integers_2{ {7, 8, 9} };
    array<int, 3> integers_3{ {1, 2, 3} };
    
    // bool型变量按照false、true的格式输出
    cout << boolalpha;

    // 比较不相等的容器
    cout << "integers_1 == integers_2 returns " << (integers_1 == integers_2) << endl; //false
    cout << "integers_1 != integers_2 returns " << (integers_1 != integers_2) << endl; //true
    cout << "integers_1 <  integers_2 returns " << (integers_1 <  integers_2) << endl; //true
    cout << "integers_1 <= integers_2 returns " << (integers_1 <= integers_2) << endl; //true
    cout << "integers_1 >  integers_2 returns " << (integers_1 >  integers_2) << endl; //false
    cout << "integers_1 >= integers_2 returns " << (integers_1 >= integers_2) << endl; //false

    cout << endl;

    // 比较相等的容器
    cout << "integers_1 == integers_3 returns " << (integers_1 == integers_3) << endl; //true
    cout << "integers_1 != integers_3 returns " << (integers_1 != integers_3) << endl; //false
    cout << "integers_1 <  integers_3 returns " << (integers_1 <  integers_3) << endl; //false
    cout << "integers_1 <= integers_3 returns " << (integers_1 <= integers_3) << endl; //true
    cout << "integers_1 >  integers_3 returns " << (integers_1 >  integers_3) << endl; //false
    cout << "integers_1 >= integers_3 returns " << (integers_1 >= integers_3) << endl; //true
    
    cout << endl;
}

//交换元素
void swap_test(void)
{
    array<int, 5> integers = { {1, 2, 3, 4, 5} };
    array<int, 5> another;
    another.fill(30);
    
    //交换
    integers.swap(another);
    
    array_print(integers); //array elements are: 30 30 30 30 30 
    array_print(another);  //array elements are: 1 2 3 4 5 
    
    //swap
    swap(integers, another);
    
    array_print(integers); //array elements are: 1 2 3 4 5 
    array_print(another);  //array elements are: 30 30 30 30 30  
}

//访问元素
void at_test(void)
{
    array<int, 5> integers = { {1, 2, 3, 4, 5} };
    
    for (size_t i = 0; i < integers.size(); i++)
       cout << integers[i] << " ";
    cout << endl;
    
    //遍历输出
    for (size_t i = 0; i < integers.size(); i++)
       cout << integers.at(i) << " ";
    cout << endl;
    
    //输出首元素
    cout << "Front:" << integers.front() << endl;   //Front:1
    
    //输出尾元素
    cout << "Back:" << integers.back() << endl;     //Back:5
    
    //data 访问
    int* ppintegers = integers.data();
    cout << *ppintegers << endl;
    cout << *(ppintegers + 1) << endl;
    cout << *(ppintegers + 2) << endl;
    
    cout << endl;
    
    //get 访问
    cout << get<0>(integers) << endl;
    cout << get<1>(integers) << endl;
    cout << get<2>(integers) << endl;
    cout << get<3>(integers) << endl;
    cout << get<4>(integers) << endl;
    
    cout << endl;
    
    //修改元素
    integers.at(3) = 6;
    cout << integers.at(3) << endl;
    
    integers.at(2) = 12;
    cout << integers.at(2) << endl;
    
    // 越界访问，会进行越界检查
    // integers.at(12) = 12;
    // //越界，抛出std::out_of_range异常
    // terminate called after throwing an instance of 'std::out_of_range'
    // what():  array::at
    
    get<1>(integers) = 66;
    cout << get<1>(integers) << endl;
}

//判断是否为空
void empty_test(void)
{
    array<int, 0> integers;
    
    cout << "Empty:" << integers.empty() << endl;   //Empty:1
    
    array<int, 1> integers2;
    
    cout << "Empty:" << integers2.empty() << endl;  //Empty:0
}

//大小与容量
void size_test(void)
{
    array<int, 5> integers;
    
    //大小和容量
    cout << "Size:" << integers.size() << endl;
    
    // 最大可允许的array元素数量值
    cout << "Max_size:" << integers.max_size() << endl;
}

//反向遍历元素
void r_iterate_test(void)
{
    array<int, 5> integers = { {1, 2, 3, 4, 5} };
    
    for (int i = integers.size() - 1; i >= 0; i--)
       cout << integers[i] << " ";
    cout << endl;
    
     array<int, 5>::reverse_iterator element = integers.rbegin();
    while(element != integers.rend()) {
        cout << *element << " ";
        
        ++element;
    }
    cout << endl;
    
    array<int, 5>::const_reverse_iterator celement = integers.crbegin();
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
    
    for (array<int, 5>::reverse_iterator it = integers.rbegin(); it != integers.rend(); it++)
       cout << *it << " ";
    cout << endl;
    
    for (auto it = integers.rbegin(); it != integers.rend(); it++)
        cout << *it << " ";
    cout << endl;
}

//正向遍历元素
void iterate_test(void)
{
    array<int, 5> integers = { {1, 2, 3, 4, 5} };
    
    for (size_t i = 0; i < integers.size(); i++)
       cout << integers[i] << " ";
    cout << endl;
    
    for (int v : integers)
       cout << v << " ";
    cout << endl;
    
    //使用迭代器
    array<int, 5>::iterator element = integers.begin();
    while(element != integers.end()) {
        cout << *element << " ";
        
        ++element;
    }
    cout << endl;
    
    array<int, 5>::const_iterator celement = integers.cbegin();
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
    
    for (array<int, 5>::iterator it = integers.begin(); it != integers.end(); it++)
       cout << *it << " ";
    cout << endl;
    
    for (auto it = integers.begin(); it != integers.end(); it++)
        cout << *it << " ";
    cout << endl;
    
    //data 访问
    int* ppintegers = integers.data();
    for (size_t i = 0; i < integers.size(); i++)
       cout << *(ppintegers + i) << " ";
    cout << endl;
    
    for (auto it = integers.data(); it < integers.data() + integers.size(); it++)
       cout << *it << " ";
    cout << endl;
}

//实例化
void init_test(void)
{
    //整型 array 类
    array<int, 1> integers;
    
    array_print(integers); //未初始化的数值
    
    //列表初始化
    array<int, 5> initarray = { {1, 2, 3, 4, 5} }; //或者是 array<int, 5> initarray = { 1, 2, 3, 4, 5 };
    
    array_print(initarray); //array elements are: 1 2 3 4 5 
    
    array<int, 5> initarray2{ {1, 2, 3, 4, 5} }; //或者是 array<int, 5> initarray2{ 1, 2, 3, 4, 5 };
    
    array_print(initarray2); //array elements are: 1 2 3 4 5 

    //设置初始大小为10
    array<int, 10> tenElements;
    
    array_print(tenElements); //未初始化的数值
    
    //使用一个array初始化另一个array，即复制array对象
    array<int, 5> copyarray(initarray);
    
    array_print(copyarray); //array elements are: 1 2 3 4 5 
    
    //使用一个array初始化另一个array，即复制array对象
    array<int, 5> copyarray2 = initarray;
    
    array_print(copyarray2); //array elements are: 1 2 3 4 5 
    
    //使用 fill 填充 5
    array<int, 3> fillintegers;
    fillintegers.fill(5);
    array_print(fillintegers); //array elements are: 5 5 5
    
    //使用 to_array
    //auto integerstoarray = std::to_array({1, 2, 3, 4, 5});
    
    //array_print(integerstoarray);
}
/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    cout << __cplusplus << endl;
    
    init_test();        //实例化
    // iterate_test();     //正向遍历元素
    // r_iterate_test();   //反向遍历元素
    // size_test();        //大小与容量
    // empty_test();       //判断是否为空
    // at_test();          //访问元素
    // swap_test();        //交换元素
    // compare_test();    //比较
    // assign_test();      //分配新的内容替换原有的内容
    // tuple_type_sise_test();
    // return_test();      //返回值
    // sort_test();        //排序
    
    // two_dimensional_init_test();    //二维 array 实例化
    // three_dimensional_init_test();    //三维 array 实例化
    return 0;
}