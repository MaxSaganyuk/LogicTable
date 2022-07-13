#include "stringB.h"

void stringB::addToIBvect(int amount){
    for(int i = 0; i < amount; ++i){
        protoIB.id = idCount++;
        protoIB.flag = false;
        IBvect.push_back(protoIB);
    }
}

void stringB::insertToIBvect(int pos, int amount){
    for(int i = 0; i < amount; ++i){
        protoIB.id = idCount++;
        protoIB.flag = false;
        IBvect.insert(IBvect.begin() + pos + i, protoIB);
    }
    //std::cout << "Inserted" << "\n";
}

void stringB::eraseInIBvect(int pos, int amount){
    for(int i = 0; i < amount; ++i){
        IBvect.erase(IBvect.begin() + pos);
    }
    //std::cout << "Erased" << "\n";
}

void stringB::replaceInIBvect(int pos, int eraseAmount, int insertAmount){
    eraseInIBvect(pos, eraseAmount);
    insertToIBvect(pos, insertAmount);
}

void stringB::pop_backIBvectTimes(int amount){
    for(int i = 0; i < amount; ++i) IBvect.pop_back();
}

stringB::stringB() : std::string() { };
stringB::stringB(const std::string& sB) : std::string(sB)       { addToIBvect(size()); }
stringB::stringB(const char* s) : std::string(s)                { addToIBvect(size()); }
stringB::stringB(const char* s, size_t n) : std::string(s, n)   { addToIBvect(size()); }
stringB::stringB(size_t n, char c) : std::string(n, c)          { addToIBvect(size()); }
stringB::stringB(std::string&& str) noexcept : std::string(str) { addToIBvect(size()); }

stringB::stringB(const std::string sB, size_t pos, size_t len) 
: std::string(sB, pos, len)                            { addToIBvect(size()); }

stringB& stringB::append(const std::string& str){
    int currentSize = size();
    std::string::append(str);
    addToIBvect(size() - currentSize);
    return *this;
}
stringB& stringB::append(const std::string& str, size_t subpos, size_t sublen){
    int currentSize = size();
    std::string::append(str, subpos, npos);
    addToIBvect(size() - currentSize);
    return *this;
}
stringB& stringB::append(const char* s){
    int currentSize = size();
    std::string::append(s);
    addToIBvect(size() - currentSize);
    return *this;
}
stringB& stringB::append(const char* s, size_t n){
    int currentSize = size();
    std::string::append(s, n);
    addToIBvect(size() - currentSize);
    return *this;
}
stringB& stringB::append(size_t n, char c){
    int currentSize = size();
    std::string::append(n, c);
    addToIBvect(size() - currentSize);
    return *this;
}

stringB& stringB::insert(size_t pos, const std::string& str){
    int currentSize = size();
    std::string::insert(pos, str);
    insertToIBvect(pos, size() - currentSize);
    return *this;
}
stringB& stringB::insert(size_t pos, const std::string& str, size_t subpos, size_t sublen){
    int currentSize = size();
    std::string::insert(pos, str, subpos, npos);
    insertToIBvect(pos, size() - currentSize);
    return *this;
}
stringB& stringB::insert(size_t pos, const char* s){
    int currentSize = size();
    std::string::insert(pos, s);
    insertToIBvect(pos, size() - currentSize);
    return *this;
}
stringB& stringB::insert(size_t pos, const char* s, size_t n){
    int currentSize = size();
    std::string::insert(pos, s, n);
    insertToIBvect(pos, size() - currentSize);
    return *this;
}
stringB& stringB::insert(size_t pos, size_t n, char c){
    int currentSize = size();
    std::string::insert(pos, n, c);
    insertToIBvect(pos, size() - currentSize);
    return *this;
}
std::string::iterator stringB::insert(const_iterator p, size_t n, char c){
    int currentSize = size();
    iterator pRet = std::string::insert(p, n, c);
    insertToIBvect(p - begin(), size() - currentSize);
    return pRet;
}
std::string::iterator stringB::insert(const_iterator p, char c){
    int currentSize = size();
    iterator pRet = std::string::insert(p, c);
    insertToIBvect(p - begin(), size() - currentSize);
    return pRet;
}
template <class InputIterator>
std::string::iterator stringB::insert(iterator p, InputIterator first, InputIterator last){
    int currentSize = size();
    iterator pRet = std::string::insert(p, first, last);
    insertToIBvect(p - begin(), size() - currentSize);
    return pRet;
}

stringB& stringB::erase(size_t pos, size_t len){
    std::string::erase(pos, len);
    eraseInIBvect(pos, len);
    return *this;
}

std::string::iterator stringB::erase(const_iterator p){
    iterator pRet = std::string::erase(p);
    eraseInIBvect(p - begin(), 1);
    return pRet;
}

std::string::iterator stringB::erase(const_iterator first, const_iterator last){
    iterator pRet = std::string::erase(first, last);
    eraseInIBvect(first - begin(), last - first);
    return pRet;
}

stringB& stringB::replace(size_t pos, size_t len, const std::string& str){
    std::string::replace(pos, len, str);
    replaceInIBvect(pos, len, str.size());
    return *this;
}
stringB& stringB::replace(const_iterator i1, const_iterator i2, const std::string& str){
    std::string::replace(i1, i2, str);
    replaceInIBvect(i1 - begin(), i2 - i1, str.size());
    return *this;
}
stringB& stringB::replace(size_t pos, size_t len, const std::string& str, 
size_t subpos, size_t sublen){
    std::string::replace(pos, len, str, subpos, sublen);
    replaceInIBvect(pos, len, sublen);
    return *this;
}
stringB& stringB::replace(size_t pos, size_t len, const char* s){
    std::string::replace(pos, len, s);
    replaceInIBvect(pos, len, strlen(s));
    return *this;
}
stringB& stringB::replace(const_iterator i1, const_iterator i2, const char* s){
    std::string::replace(i1, i2, s);
    replaceInIBvect(i1 - begin(), i2 - i1, strlen(s));
    return *this;
}
stringB& stringB::replace(size_t pos, size_t len, const char* s, size_t n){
    std::string::replace(pos, len, s, n);
    replaceInIBvect(pos, len, n);
    return *this;
}
stringB& stringB::replace(const_iterator i1, const_iterator i2, const char* s, size_t n){
    std::string::replace(i1, i2, s, n);
    replaceInIBvect(i1 - begin(), i2 - i1, n);
    return *this;
}
stringB& stringB::replace(size_t pos, size_t len, size_t n, char c){
    std::string::replace(pos, len, n, c);
    replaceInIBvect(pos, len, n);
    return *this;
}
stringB& stringB::replace(const_iterator i1, const_iterator i2, size_t n, char c){
    std::string::replace(i1, i2, n, c);
    replaceInIBvect(i1 - begin(), i2 - i1, n);
    return *this;
}

void stringB::swap(std::string& str){
    std::string::swap(str);
    IBvect.clear();
    addToIBvect(size());
}

void stringB::resize(size_t n){
    if(n > size()) addToIBvect(n - size());
    else           pop_backIBvectTimes(size() - n);
    std::string::resize(n);
}

void stringB::clear(){
    std::string::clear();
    IBvect.clear();
}

void stringB::push_back(char c){
    std::string::push_back(c);
    addToIBvect(1);
}

void stringB::pop_back(){
    std::string::pop_back();
    pop_backIBvectTimes(1);
}

stringB operator+(stringB            lhs, char                rhs){ return (lhs += rhs); }
stringB operator+(stringB            lhs, const char*         rhs){ return (lhs += rhs); }
stringB operator+(stringB            lhs, const std::string&  rhs){ return (lhs += rhs); }

stringB operator+(char               lhs, stringB             rhs){ 
    std::string s;
    s = lhs;
    return rhs.insert(0, s); 
}
stringB operator+(const char*        lhs, stringB             rhs){ 
    std::string s;
    s = lhs;
    return rhs.insert(0, s);  
}
stringB operator+(const std::string& lhs, stringB             rhs){ 
    std::string s;
    s = lhs;
    return rhs.insert(0, s); 
}

void stringB::printIds() {
    for(int i = 0; i < IBvect.size(); ++i) std::cout << IBvect[i].id << " ";
    std::cout << "\n";
}

void stringB::printFlags(){
    for(int i = 0; i < IBvect.size(); ++i) std::cout << IBvect[i].flag << " ";
    std::cout << "\n";
}

int stringB::giveIdAt(int index)     { return (IBvect[index].id); }
bool stringB::giveFlagAt(int index)  { return (IBvect[index].flag); }
void stringB::setFlagAt(int index) {IBvect[index].flag = !IBvect[index].flag; }
void stringB::setFlagAt(int index, bool newFlag) { IBvect[index].flag = newFlag; }
