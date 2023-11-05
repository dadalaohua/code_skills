#include <iostream>
#include <deque>

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
void deque_print(deque<int> integers)
{
   cout << "deque elements are: ";
// #if __cplusplus >= 201103L
   for (auto it = integers.begin(); it != integers.end(); it++)
       cout << *it << " ";
// #else
    // for (deque<int>::iterator it = integers.begin(); it != integers.end(); it++)
       // cout << *it << " ";
// #endif
   cout << endl;
}

//三维 vector 实例化
void three_dimensional_init_test(void)
{
    deque<deque<deque<int>>> obj(3, deque<deque<int>>(4));
    deque<deque<deque<int>>> obj2(3, deque<deque<int>>(4, deque<int>(5)));
    deque<deque<deque<int>>> obj3(3, deque<deque<int>>(4, deque<int>(5, 6)));
    
    //输出三维 deque
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

//二维 deque 实例化
void two_dimensional_init_test(void)
{
    int row = 5, col = 6; 
    
    //定义二维 deque 5行6列 
    deque< deque<int> > obj(row, deque<int>(col)); 
 
    //输出二维 deque
    for(size_t i = 0; i < obj.size(); i++) {
        for(size_t j = 0; j < obj[i].size(); j++) {
            cout << obj[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
    
    //定义二维 deque 5行6列 初始化所有的值为 7
    deque< deque<int> > obj2(row, deque<int>(col, 7)); 
 
    //输出二维 deque
    for(size_t i = 0; i < obj2.size(); i++) {
        for(size_t j = 0; j < obj2[i].size(); j++) {
            cout << obj2[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
    
    //定义二维 deque 5行
    deque< deque<int> > obj3(row);
    
    //动态二维 deque 为每一行为 6 列，值全为0 
    for(size_t i = 0; i < obj3.size(); i++) { 
        //改变当前的大小
        obj3[i].resize(col); 
    }
    
    //输出二维 deque
    for(size_t i = 0; i < obj3.size(); i++) {
        for(size_t j = 0; j < obj3[i].size(); j++) {
            cout << obj3[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
    
#if __cplusplus >= 201703L
    //定义二维 deque 5行6列 初始化所有的值为 7
    deque obj4(row, deque<int> (col, 7));
    
    //输出二维 deque
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
    deque<int> integers;
    
    //放入5个元素
    integers.push_back(15);
    integers.push_back(84);
    integers.push_back(64);
    integers.push_back(38);
    integers.push_back(55);
    
    deque_print(integers); //deque elements are: 15 84 64 38 55
    
    //排序， 从小到大
    sort(integers.begin(), integers.end());
    
    deque_print(integers); //deque elements are: 15 38 55 64 84 
    
    //排序， 从大到小
    //方法一：
    sort(integers.begin(), integers.end(), sort_predicate_descending);
    
    deque_print(integers);  //deque elements are: 84 64 55 38 15
    
    //方法二：
    sort(integers.begin(), integers.end(), [&](int x, int y) {
        return x > y;
    });
    
    deque_print(integers);  //deque elements are: 84 64 55 38 15
    
    
    //自定义结构排序
    deque <test_item> item;
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

//分配新的内容替换原有的内容
void assign_test(void)
{
    deque<int> integers;
    
    //放入5个元素
    integers.push_back(20);
    integers.push_back(21);
    integers.push_back(22);
    integers.push_back(23);
    integers.push_back(24);
    
    deque_print(integers); //deque elements are: 20 21 22 23 24 
    
    //替换成3个35
    integers.assign(3, 35);
    
    deque_print(integers); //deque elements are: 35 35 35
    
    deque<int> another(6, 55);
    
    //替换成 another 的内容
    integers.assign(another.begin(), another.end());
    
    deque_print(integers); //deque elements are: 55 55 55 55 55 55
    
    deque<int> another2(5, 86);
    
    //将 another2 的内容赋给 integers
    integers = another2;
    
    deque_print(integers); //deque elements are: 86 86 86 86 86 
    
    deque<int> another3(8, 36);
    
    //将 another3 的内容赋给 integers，another3内的值被清空
    integers = move(another3);
    
    deque_print(integers); //deque elements are: 36 36 36 36 36 36 36 36
}

//交换元素
void swap_test(void)
{
    deque<int> integers;
    
    //放入5个元素
    integers.push_back(20);
    integers.push_back(21);
    integers.push_back(22);
    integers.push_back(23);
    integers.push_back(24);
    
    deque<int> another(3, 30);
    
    //交换
    integers.swap(another);
    
    deque_print(integers); //deque elements are: 30 30 30 
    deque_print(another);  //deque elements are: 20 21 22 23 24
}

//访问元素
void at_test(void)
{
    deque<int> integers;
    
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
}

//判断是否为空
void empty_test(void)
{
    deque<int> integers;
    
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
    deque<int> integers;
    
    //先放入3个元素
    integers.push_back(20);
    integers.push_back(21);
    integers.push_back(22);
    
    deque_print(integers); //deque elements are: 20 21 22 
    
    //清空所有元素
    integers.clear();
    
    deque_print(integers); //deque elements are:
}

//删除元素
void erase_test(void)
{
    deque<int> integers;
    
    integers.push_back(20);
    integers.push_back(21);
    integers.push_back(22);
    integers.push_back(23);
    integers.push_back(24);
    
    deque_print(integers); //deque elements are: 20 21 22 23 24 
    
    //删除特定元素
    for(deque<int>::iterator it = integers.begin(); it != integers.end();) {
        if(*it == 22) {
            it = integers.erase(it);
        } else {
            ++it;
        }
    }
    
    deque_print(integers); //deque elements are: 20 21 23 24 
    
    //删除特定范围的元素
    integers.erase(integers.begin() + 2, integers.end());
    
    deque_print(integers); //deque elements are: 20 21
    
    //清空所有元素
    integers.erase(integers.begin(), integers.end());
    
    deque_print(integers); //deque elements are:
}

//大小
void size_test(void)
{
    //设置初始大小为 2
    deque<int> integers(2);
    
    //大小
    cout << "Size:" << integers.size() << endl; //Size:2
    
    integers.push_back(10);
    
    cout << "Size:" << integers.size() << endl; //Size:3
    
    integers.push_back(11);
    
    cout << "Size:" << integers.size() << endl; //Size:4
    
    integers.push_back(12);
    
    cout << "Size:" << integers.size() << endl; //Size:5
    
    // 最大可允许的deque元素数量值
    cout << "Max_size:" << integers.max_size() << endl;
    
    //默认
    deque<int> another;
    
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
    deque<int> integers;
    
    integers.push_back(10);
    integers.push_back(12);
    integers.push_back(66);
    
    for (int i = integers.size() - 1; i >= 0; i--)
       cout << integers[i] << " ";
    cout << endl;
    
    deque<int>::reverse_iterator element = integers.rbegin();
    while(element != integers.rend()) {
        cout << *element << " ";
        
        ++element;
    }
    cout << endl;
    
    deque<int>::const_reverse_iterator celement = integers.crbegin();
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
    
    for (deque<int>::reverse_iterator it = integers.rbegin(); it != integers.rend(); it++)
       cout << *it << " ";
    cout << endl;
    
    for (auto it = integers.rbegin(); it != integers.rend(); it++)
        cout << *it << " ";
    cout << endl;
}

//正向遍历元素
void iterate_test(void)
{
    deque<int> integers;
    
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
    deque<int>::iterator element = integers.begin();
    while(element != integers.end()) {
        cout << *element << " ";
        
        ++element;
    }
    cout << endl;
    
    deque<int>::const_iterator celement = integers.cbegin();
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
    
    for (deque<int>::iterator it = integers.begin(); it != integers.end(); it++)
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
    deque<int> integers(4, 90);
    
    deque_print(integers); //deque elements are: 90 90 90 90
    
    //在起始位置插入值 25
    integers.insert(integers.begin(), 25);
    
    deque_print(integers); //deque elements are: 25 90 90 90 90
    
    //在末尾位置插入 2 个值 35
    integers.insert(integers.end(), 2, 35);
    
    deque_print(integers); //deque elements are: 25 90 90 90 90 35 35
    
    //在从起始位置开始+2的位置插入值 45
    integers.insert(integers.begin() + 2, 45);
    
    deque_print(integers); //deque elements are: 25 90 45 90 90 90 35 35
    
    //在末尾位置之前的2个位置处插入值 55
    integers.insert(integers.end() - 2, 55);
    
    deque_print(integers); //deque elements are: 25 90 45 90 90 90 55 35 35
    
    //另一个 deque，有两个值为30的元素
    deque<int> another(2, 30);
    
    //将 another 的元素插入 integers 从起始位置开始+1的位置
    integers.insert(integers.begin() + 1, another.begin(), another.end());
    
    deque_print(integers); //deque elements are: 25 30 30 90 45 90 90 90 55 35 35
}

//开头删除元素
void pop_front_test(void)
{
    deque<int> integers;
    
    //先放入3个元素
    integers.push_front(10);
    integers.push_front(12);
    integers.push_front(66);
    
    deque_print(integers); //deque elements are: 66 12 10
    
    //删除开头第一个元素
    integers.pop_front();
    
    deque_print(integers); //deque elements are: 12 10 
    
    //删除开头第一个元素
    integers.pop_front();
    
    deque_print(integers); //deque elements are: 10 
}

//末尾删除元素
void pop_back_test(void)
{
    deque<int> integers;
    
    //先放入3个元素
    integers.push_back(10);
    integers.push_back(12);
    integers.push_back(66);
    
    deque_print(integers); //deque elements are: 10 12 66 
    
    //删除最后一个元素
    integers.pop_back();
    
    deque_print(integers); //deque elements are: 10 12 
    
    //删除最后一个元素
    integers.pop_back();
    
    deque_print(integers); //deque elements are: 10 
}

//开头插入元素
void push_front_test(void)
{
    deque<int> integers;
    
    integers.push_front(10);
    integers.push_front(12);
    integers.push_front(66);
    
    deque_print(integers);  //deque elements are: 66 12 10 
}

//末尾插入元素
void push_back_test(void)
{
    deque<int> integers;
    
    integers.push_back(10);
    integers.push_back(12);
    integers.push_back(66);
    
    deque_print(integers);  //deque elements are: 10 12 66 
}

//实例化
void init_test(void)
{
    //整型 deque 类
    deque<int> integers;
    
    deque_print(integers); //deque elements are: 
    
    //C++11引入的列表初始化
    deque<int> initVector = { 1, 2, 3, 4, 5 };
    
    deque_print(initVector); //deque elements are: 1 2 3 4 5 

    //设置初始大小为10
    deque<int> tenElements(10);
    
    deque_print(tenElements); //deque elements are: 0 0 0 0 0 0 0 0 0 0 
    
    //设置初始大小为10, 值为90
    deque<int> tenElemInit(10, 90);
    
    deque_print(tenElemInit); //deque elements are: 90 90 90 90 90 90 90 90 90 90
    
    //使用一个deque初始化另一个deque，即复制deque对象
    deque<int> copyVector(tenElemInit);
    
    deque_print(copyVector); //deque elements are: 90 90 90 90 90 90 90 90 90 90
    
    //使用一个deque初始化另一个deque，即复制deque对象
    deque<int> copyVector2 = tenElemInit;
    
    deque_print(copyVector2); //deque elements are: 90 90 90 90 90 90 90 90 90 90
    
    //使用另一个deque的前五个元素初始化
    deque<int> partialCopy(tenElemInit.begin(), tenElemInit.begin() + 5);
    
    deque_print(partialCopy); //deque elements are: 90 90 90 90 90
    
    //使用另一个deque的前五个元素初始化，其中cbegin和cend由于C++11引入
    deque<int> partialCopy2(tenElemInit.cbegin(), tenElemInit.cbegin() + 5);
    
    deque_print(partialCopy2); //deque elements are: 90 90 90 90 90
    
}
/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    cout << __cplusplus << endl;
    
    init_test();        //实例化
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
    
    // two_dimensional_init_test();    //二维 deque 实例化
    // three_dimensional_init_test();    //三维 deque 实例化
    return 0;
}