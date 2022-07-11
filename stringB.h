#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <initializer_list>
#include <iterator>


class stringB : public std::string {
private:
    int idCount = 0;

    struct IB{
        int id;
        bool flag;
    };
    std::vector<IB> IBvect;
    IB protoIB;

    void addToIBvect(int amount);

    void insertToIBvect(int pos, int amount);

    void eraseInIBvect(int pos, int amount);

    void replaceInIBvect(int pos, int eraseAmount, int insertAmount);

    void pop_backIBvectTimes(int amount);

public:
    stringB();
    stringB(const std::string& sB);
    stringB(const char* s);
    stringB(const char* s, size_t n);
    stringB(size_t n, char c);
    stringB(std::string&& str) noexcept;

    template <class InputIterator>
    stringB(InputIterator first, InputIterator last) 
    : std::string(first, last)                             { addToIBvect(size()); }

    stringB(const std::string sB, size_t pos, size_t len = npos);

  //stringB(initializer_list<char> il) : std::string(il)   { addToIBvect(size()); }

    template <class t>
    stringB& operator=(t str) { 
        IBvect.clear();
        std::string::operator=(str);
        addToIBvect(size());
        return *this; 
    }

    template <class t>
    stringB& operator+=(t str){
        int currentSize = size();
        std::string::operator+=(str);
        addToIBvect(size() - currentSize);
        return *this;
    }

    stringB& append(const std::string& str);
    stringB& append(const std::string& str, size_t subpos, size_t sublen = npos);
    stringB& append(const char* s);
    stringB& append(const char* s, size_t n);
    stringB& append(size_t n, char c);

    template <class InputIterator>
    stringB& append(InputIterator first, InputIterator last){
        int currentSize = size();
        std::string::append(first, last);
        addToIBvect(size() - currentSize);
        return *this;
    }

    stringB& insert(size_t pos, const std::string& str);
    stringB& insert(size_t pos, const std::string& str, size_t subpos, size_t sublen = npos);
    stringB& insert(size_t pos, const char* s);
    stringB& insert(size_t pos, const char* s, size_t n);
    stringB& insert(size_t pos, size_t n, char c);

    iterator insert(const_iterator p, size_t n, char c);
    iterator insert(const_iterator p, char c);

    template <class InputIterator>
    iterator insert(iterator p, InputIterator first, InputIterator last);

    stringB& erase(size_t pos = 0, size_t len = npos);
    iterator erase(const_iterator p);
    iterator erase(const_iterator first, const_iterator last);

    stringB& replace(size_t pos, size_t len, const std::string& str);
    stringB& replace(const_iterator i1, const_iterator i2, const std::string& str);
    stringB& replace(size_t pos, size_t len, const std::string& str, 
    size_t subpos, size_t sublen = npos);
    stringB& replace(size_t pos, size_t len, const char* s);
    stringB& replace(const_iterator i1, const_iterator i2, const char* s);
    stringB& replace(size_t pos, size_t len, const char* s, size_t n);
    stringB& replace(const_iterator i1, const_iterator i2, const char* s, size_t n);
    stringB& replace(size_t pos, size_t len, size_t n, char c);
    stringB& replace(const_iterator i1, const_iterator i2, size_t n, char c);

    template <class InputIterator>
    stringB& replace(const_iterator i1, const_iterator i2, 
    InputIterator first, InputIterator last){
        std::string::replace(i1, i2, first, last);
        replaceInIBvect(i1 - begin(), i2 - i1, last - first);
        return *this;
    }



    void swap(std::string& str);

    void resize(size_t n);

    void clear();

    void push_back(char c);

    void pop_back();
    
    void printIds();

    int giveIdAt(int index);
    bool giveFlagAt(int index);

    void setFlagAt(int index);
    void setFlagAt(int index, bool newFlag);
};
