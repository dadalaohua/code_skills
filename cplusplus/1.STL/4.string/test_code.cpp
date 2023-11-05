#include <iostream>
#include <string>
#include <string.h> //strlen

#include <algorithm> //find,reverse,transform

using namespace std;
/************************************************************************/
/*                                                                      */
/************************************************************************/

/************************************************************************/
/*                                                                      */
/************************************************************************/
//print
void string_print(string str)
{
   cout << "string is: " << str << endl;
}

//返回函数1
string return_test_function_1(void)
{
    string str("Hello String!");
    return str;
}

//返回函数2
string return_test_function_2(void)
{
    string str("Hello String!");
    return string(str.begin(), str.end());
}

//返回函数3
string return_test_function_3(void)
{
    return string("Hello String!");
}

//返回函数4
string return_test_function_4(void)
{
    return string(2, 'A');
}

//返回值
void return_test(void)
{
    string ret1 = return_test_function_1();
    string_print(ret1); //string is: Hello String!
    
    string ret2 = return_test_function_2();
    string_print(ret2); //string is: Hello String!
    
    string ret3 = return_test_function_3();
    string_print(ret3); //string is: Hello String!
    
    string ret4 = return_test_function_4();
    string_print(ret4); //string is: AA
}

//字符串长度
void size_test(void)
{
    string str("Hello String!");
    
    //size
    cout << str.size() << endl;
    
    //length
    cout << str.length() << endl;
    
    //strlen
    cout << strlen(str.c_str()) << endl;
}

//对比字符串
void compare_test(void)
{
    string str("Hello String!");
    cout << str << endl << endl;
    
    string str2("Hello String!");
    if(str.compare(str2) == 0) {
        cout << "str == str2" << endl;  //字符串相同
    } else {
        cout << "str != str2" << endl;  //字符串不相同
    }
    
    if(str.compare("Hello String!") == 0) {
        cout << "str == str2" << endl;  //字符串相同
    } else {
        cout << "str != str2" << endl;  //字符串不相同
    }
    
    string str3("String!");
    //对比 str 起始偏移 6，长度为 7 的字符串与 str3 进行对比
    if(str.compare(6, 7, str3) == 0) {
        cout << "str == str3" << endl;  //字符串相同
    } else {
        cout << "str != str3" << endl;  //字符串不相同
    }
    
    string str4("Hi, String!!!");
    //对比 str 起始偏移 6，长度为 7 的字符串与 str4 起始偏移 4，长度为 7  进行对比
    if(str.compare(6, 7, str4, 4, 7) == 0) {
        cout << "str == str4" << endl;  //字符串相同
    } else {
        cout << "str != str4" << endl;  //字符串不相同
    }
    
    //C风格字符串
    const char* constCStyleString = "Hello String!";
    if(str.compare(constCStyleString) == 0) {
        cout << "str == constCStyleString" << endl;  //字符串相同
    } else {
        cout << "str != constCStyleString" << endl;  //字符串不相同
    }
    
    const char* constCStyleString2 = "String!";
    //对比 str 起始偏移 6，长度为 7 的字符串与 constCStyleString2 进行对比
    if(str.compare(6, 7, constCStyleString2) == 0) {
        cout << "str == constCStyleString2" << endl;  //字符串相同
    } else {
        cout << "str != constCStyleString2" << endl;  //字符串不相同
    }
    
    const char* constCStyleString3 = "String!!!";
    //对比 str 起始偏移 6，长度为 7 的字符串与 constCStyleString3 进行对比
    if(str.compare(6, 7, constCStyleString3, 7) == 0) {
        cout << "str == constCStyleString3" << endl;  //字符串相同
    } else {
        cout << "str != constCStyleString3" << endl;  //字符串不相同
    }
}

//转换字符串
void transform_test(void)
{
    string str("Hello String! Wake up to a beautiful day!");
    cout << str << endl << endl;
    
    //转换为大写
    transform(str.begin(), str.end(), str.begin(), ::toupper);
    cout << str << endl << endl;    //HELLO STRING! WAKE UP TO A BEAUTIFUL DAY!
    
    //转换为小写
    transform(str.begin(), str.end(), str.begin(), ::tolower);
    cout << str << endl << endl;    //hello string! wake up to a beautiful day!
    
    //整型转字符串
    string str2;
    int val = 123;
    str2 = to_string(val);
    string_print(str2); //string is: 123
}

//反转字符串
void reverse_test(void)
{
    string str("Hello String! Wake up to a beautiful day!");
    cout << str << endl << endl;
    
    reverse(str.begin(), str.end());
    
    cout << str << endl << endl;
}

//删除字符串
void erase_test(void)
{
    string str("Hello String! Wake up to a beautiful day!");
    cout << str << endl << endl;
    
    //从偏移 13 的位置 删除 5 个字符
    str.erase(13, 5);
    cout << str << endl << endl; //Hello String! up to a beautiful day!
    
    //使用 find 算法查找整个字符串中的字符'S'，然后删除掉
    string::iterator iCharS = find(str.begin(), str.end(), 'S');
    if(iCharS != str.end()) {
        str.erase(iCharS);
    }
    cout << str << endl << endl; //Hello tring! up to a beautiful day!
    
    //删除所有字符
    str.erase(str.begin(), str.end());
    cout << str << endl << endl; //
    
    if(str.length() == 0) {
        cout << "The string is empty" << endl;
    }
    
    //删除所有字符
    string str2("Good day String! Today is beautiful!");
    cout << str2 << endl << endl;
    
    str2.clear();
    
    if(str2.length() == 0) {
        cout << "The string is empty" << endl;
    }
}

//截取字符串
void substr_test(void)
{
    string str("Good day String! Today is beautiful!");
    cout << str << endl << endl;
    
    //查找字符串，从偏移 0 开始
    size_t charPos = str.find("day", 0);
    if(charPos != string::npos) {
        //获取偏移后的字符串
        string str2 = str.substr(charPos);
        cout << str2 << endl << endl;   //day String! Today is beautiful!
        
        //获取偏移后的字符串，长度为 3
        string str3 = str.substr(charPos, 3);
        cout << str3 << endl << endl;   //day
    }
    
    //获取偏移 5 后的字符串
    string str2 = str.substr(5);
    cout << str2 << endl << endl;   //day String! Today is beautiful!
    
    //获取偏移 5 后的字符串，长度为 3
    string str3 = str.substr(5, 3);
    cout << str3 << endl << endl;   //day
}

//查找字符串
void find_test(void)
{
    string str("Good day String! Today is beautiful!");
    cout << str << endl << endl;
    
    //查找字符串，从偏移 0 开始
    size_t charPos = str.find("day", 0);
    if(charPos != string::npos) {
        cout << "First instance \"day\" at pos. " << charPos << endl;   //First instance "day" at pos. 5
    } else {
        cout << "Substring not found." << endl;
    }
    
    cout << "Locating all instances of substring \"day\"" << endl;
    size_t subStrPos = str.find("day", 0);
    while(subStrPos != string::npos) {
        cout << "\"day\" found at position " << subStrPos << endl;
        
        size_t searchOffset = subStrPos + 1;
        subStrPos = str.find("day", searchOffset);
    }
}

//拼接字符串
void append_test(void)
{
    string str("Hello");
    string str2(" String!");
    
    //运算符 +=
    str += str2;
    cout << str << endl << endl;
    
    //append string
    string str3("Cease");
    str.append(str3);
    cout << str << endl << endl;
    
    //append
    str.append(" to");
    cout << str << endl << endl;
    
    //C风格字符串
    const char* constCStyleString = " struggle";
    str.append(constCStyleString);
    cout << str << endl << endl;
    
    //运算符
    str = str + " and" + " you cease to live.";
    cout << str << endl << endl;
}

//访问字符串
void access_test(void)
{
    string str("Hello String!");
    
    //数组形式
    for(size_t charCounter = 0; charCounter < str.length(); ++charCounter) {
        cout << str[charCounter];
    }
    cout << endl;
    
    //迭代器
    for(auto charLocator = str.begin(); charLocator != str.end(); ++charLocator) {
        cout << *charLocator;
    }
    cout << endl;
    
    for(string::iterator charLocator = str.begin(); charLocator != str.end(); ++charLocator) {
        cout << *charLocator;
    }
    cout << endl;
    
    //迭代器
    for(auto charLocator = str.cbegin(); charLocator != str.cend(); ++charLocator) {
        cout << *charLocator;
    }
    cout << endl;
    
    for(string::const_iterator charLocator = str.cbegin(); charLocator != str.cend(); ++charLocator) {
        cout << *charLocator;
    }
    cout << endl;
    
    //const char*
    cout << str.c_str() << endl;
    
    //const char*
    const char* cstr = str.c_str();
    cout << cstr << endl;
    
    for(size_t charCounter = 0; charCounter < strlen(cstr); ++charCounter) {
        cout << cstr[charCounter];
    }
    cout << endl;
    
    //string
    cout << str << endl;
    
    //auto
    for(auto word : str) {
        cout << word;
    }
    cout << endl;
    
    //char
    for(char word : str) {
        cout << word;
    }
    cout << endl;
}

//实例化
void init_test(void)
{
    //string 类
    string str;
    string_print(str); //string is:
    
    //初始化字符串
    string str2("Hello String!");
    string_print(str2); //string is: Hello String!
    
    //初始化字符串
    string str3 = "Hello String!";
    string_print(str3); //string is: Hello String!
    
    //C风格字符串
    const char* constCStyleString = "Hello String!";
    //复制 constCStyleString
    string strFromConst(constCStyleString);
    string_print(strFromConst); //string is: Hello String!
    
    //复制 constCStyleString
    string strFromConst2 = constCStyleString;
    string_print(strFromConst2); //string is: Hello String!
    
    //复制 str2
    string str2Copy(str2);
    string_print(str2Copy); //string is: Hello String!
    
    //复制 str2
    string str2Copy2 = str2;
    string_print(str2Copy2); //string is: Hello String!
    
    //复制前5个字符
    string strPartialCopy(constCStyleString, 5);
    string_print(strPartialCopy); //string is: Hello
    
    //复制str2，从第6个Byte开始
    string str2PartialCopy(str2, 6);
    string_print(str2PartialCopy); //string is: String!
    
    //复制 str2
    string str2PartialCopy2(str2.begin(), str2.end());
    string_print(str2PartialCopy2); //string is: Hello String!
    
    //复制 str2，从第6个字符开始
    string str2PartialCopy3(str2.begin() + 6, str2.end());
    string_print(str2PartialCopy3); //string is: String!
    
    
    //复制 str2，从头开始直到结束前的 8 个字符
    string str2PartialCopy4(str2.begin(), str2.end() - 8);
    string_print(str2PartialCopy4); //string is: Hello
    
    
    //复制 str2
    string str2PartialCopy5(str2.cbegin(), str2.cend());
    string_print(str2PartialCopy5); //string is: Hello String!
    
    
    //初始化 10 个 a
    string strRepeatChars(10, 'a');
    string_print(strRepeatChars); //string is: aaaaaaaaaa
    
    
    //C++14 新增 operator ""s，可以包含并操作含有空字符的字符缓冲区
    // string str14s("C++ 14 \0 initialization"s);
    // string_print(str14s); //string is: C++ 14  initialization
}
/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    cout << __cplusplus << endl;
    
    init_test();        //实例化
    // access_test();      //访问字符串
    // append_test();      //拼接字符串
    // find_test();        //查找字符串
    // substr_test();      //截取字符串
    // erase_test();       //删除字符串
    // reverse_test();     //反转字符串
    // transform_test();   //转换字符串
    // compare_test();     //对比字符串
    // size_test();        //字符串长度
    // return_test();      //返回值

    return 0;
}