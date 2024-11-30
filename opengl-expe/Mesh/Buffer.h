//
//  Buffer.h
//  opengl-expe
//
//  Created by EL KHANTOUR Nassim on 28/11/2024.
//

#ifndef Buffer_h
#define Buffer_h
#include <unordered_map>
#include <string>

template <typename T>
class Buffer{
    
public:
    
    Buffer() = default;
    ~Buffer(){}
    
    void push(const std::string& name, T value){
        if(name != DEFAULT_NAME) data[name] = value;
    }
    
    T* find(const std::string& name){
        auto iterator = data.find(name);
        return iterator != data.end() ? &iterator->second : nullptr;
    }
    
    T& origin(){
        return data.find(DEFAULT_NAME)->second;
    }
    
    void init(T buffer){
        data.find(DEFAULT_NAME)->second = buffer;
    }
    
    
private:
    const std::string DEFAULT_NAME= "ORIGIN";
    std::unordered_map<std::string, T> data = { { DEFAULT_NAME, T() } };
    
};


#endif /* Buffer_h */
