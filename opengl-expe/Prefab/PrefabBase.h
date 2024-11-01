//
//  PrefabBase.h
//  opengl-expe
//
//  Created by EL KHANTOUR Nassim on 27/10/2024.
//

#ifndef PrefabBase_h
#define PrefabBase_h

#include "../Mesh/MeshGroup.hpp"


class PrefabBase{
  
public:
    
    PrefabBase() = default;
    ~PrefabBase(){};
    
    MeshGroup* getMesh(){ return m_mesh; }
    
    
protected:
    
    MeshGroup* m_mesh = new MeshGroup();

};

#endif /* PrefabBase_h */
