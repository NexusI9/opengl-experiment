//
//  Template.h
//  opengl-expe
//
//  Created by EL KHANTOUR Nassim on 08/10/2024.
//

#ifndef Template_h
#define Template_h

#include <utility>

template <typename T, typename... Args>
T* createInstance(Args&&... args){
    return new T(std::forward<Args>(args)...);
}

#endif /* Template_h */
