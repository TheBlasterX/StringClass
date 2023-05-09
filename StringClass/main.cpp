//
//  main.cpp
//  StringClass
//
//  Created by Ștefan Jipa on 04.05.2023.
//

#include <iostream>

using namespace std;

class String
{
    public:
        //default constuctor
        String() : _res(nullptr) , _len(0) /*if you have mebmers like const int a; or int &mem; or another object which does not have a default constructor, you can`t initialize in constructor, you can only do in the initializer list*/
        {
            
        }
    
        //constructor with parameters, you pass a const string
        String(const char* ch)
        {
            _len = (unsigned int)strlen(ch);
            _res = new char[_len + 1];
            strcpy(_res, ch);
        }
    
        /*copy constructor (is only called when the String is defined for the first time, only for initialization), const because we don`t want to accidentally change this resource
        & to pass by reference, otherwise it will try to copy everything from main call to here
         without & it will throw an error
         */
        String(const String& str)
        {
            _len = str._len;
            
            if (str._res)
            {
                _res = new char[_len + 1];
                strcpy(_res, str._res);
            } else
            {
                _res = nullptr;
            }
        }
    
        /** Copy assignment operator (called when the String is alreadt defined and tries to copy something else)
                Also, is called for something like this:
                    String str1; //def
                    String str3 = str1; //copy con
                    str3 = "Hellow"; //copy assignment operator
                              
         */
        String& operator=(const String& str)
        {
            if(this != &str)
            {
                delete[] _res; // it was allocated as an array new char[]
                _len = str._len;
                _res = new char[_len + 1];
                strcpy(_res, str._res);
            }
            return *this;
        }
        
        unsigned int length()
        {
            return _len;
        }
    
        // made friend function so we can access private member _res
        friend ostream& operator<<(ostream& out, const String& str);
        friend istream& operator>>(istream& in, String& str);
    
    private:
        char* _res;
        unsigned int _len;
};

/*define as global function, because we can not rewrite cout
 we return out because we can change the call, like this: cout << str2 << str3 << str4;
 */
ostream& operator<<(ostream& out, const String& str)
{
    if(nullptr == str._res)
    {
        out << "";
    } else{
        out << str._res;
    }
    
    return out;
}

/* If str is made const here will get the error 'All paths through this function will call itsel'
   The istream input stream object passed to the function is not const, so you can read input from it, but the String object passed as a parameter is const, which means you cannot modify it
 */
istream& operator>>(istream& in, String& str)
{
    const int buffersize = 1024;
    char buffer[buffersize];
    in.getline(buffer, buffersize);
    
    if (nullptr != str._res)
    {
        delete[] str._res;
    }
    
    str._res = new char[strlen(buffer) + 1];
    strcpy(str._res, buffer);
    
    return in;
}




int main(int argc, const char * argv[]) {
    
    String str1; //default constructor
    String str2 = "hello"; //parameterised constuctor
    String str3 = str1; //copy constructor
    
    cout << "Checking copy constructor on str3 for a nullstring : " << str3 << endl;
    
    str3 = str2; //copy assignment operator
    
    int len = str2.length();
    
    cout << "len of str2: " << len << endl;
    
    // cout will call << operator with str2 as parameter
    cout << str2 << endl; //overloading <<
    
    cin >> str1; //overload <<
    
    cout << "overloading operator << : " << str1 << endl;
 
    String str4(str1); //str3 = str1
    
    cout << "str3: " << str3 << " str4: " << str4 << endl;
    
    std::cout << "Hello, World!\n";
    return 0;
}
