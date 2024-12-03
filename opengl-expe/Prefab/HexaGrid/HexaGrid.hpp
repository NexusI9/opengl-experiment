//
//  Grid.hpp
//  opengl-expe
//
//  Created by EL KHANTOUR Nassim on 23/11/2024.
//

#ifndef HexaGrid_hpp
#define HexaGrid_hpp

#include <stdio.h>
#include <glm/gtc/type_ptr.hpp>

#include "../../Backend/VBO.hpp"
#include "../../Backend/VAO.hpp"
#include "../../Mesh/VertexList.hpp"
#include "../../Material/Shader.hpp"
#include "../../Material/CustomMaterial.hpp"
#include "../../Utility/Constant.h"

#include "../../Model/Hexagon.hpp"
#include "../Prefab.h"

using HexUnit = int;

struct CubeCoordinate{
    HexUnit q = 0;
    HexUnit r = 0;
    HexUnit s = 0;
    
    CubeCoordinate operator+(const CubeCoordinate& coo){
        return{
            .q = q + coo.q,
            .r = r + coo.r,
            .s = s + coo.s
        };
    }
    
    CubeCoordinate& operator+=(const CubeCoordinate& coo){
        q += coo.q;
        r += coo.r;
        s += coo.s;
        return *this;
    }
    
    CubeCoordinate operator+(const HexUnit& v){
        return{
            .q = q + v,
            .r = r + v,
            .s = s + v
        };
    }
    
    CubeCoordinate& operator+=(const HexUnit& v){
        q += v;
        r += v;
        s += v;
        return *this;
    }
    
    
    CubeCoordinate operator-(const CubeCoordinate& coo){
        return{
            .q = q - coo.q,
            .r = r - coo.r,
            .s = s - coo.s
        };
    }
    
    CubeCoordinate& operator-=(const CubeCoordinate& coo){
        q -= coo.q;
        r -= coo.r;
        s -= coo.s;
        return *this;
    }
    
    CubeCoordinate operator-(const HexUnit& v){
        return{
            .q = q - v,
            .r = r - v,
            .s = s - v
        };
    }
    
    CubeCoordinate& operator-=(const HexUnit& v){
        q -= v;
        r -= v;
        s -= v;
        return *this;
    }
    
    CubeCoordinate operator*(const CubeCoordinate& coo){
        return{
            .q = q * coo.q,
            .r = r * coo.r,
            .s = s * coo.s
        };
    }
    
    CubeCoordinate& operator*=(const CubeCoordinate& coo){
        q *= coo.q;
        r *= coo.r;
        s *= coo.s;
        return *this;
    }
    
    CubeCoordinate operator*(const HexUnit& v){
        return{
            .q = q * v,
            .r = r * v,
            .s = s * v
        };
    }
    
    CubeCoordinate& operator*=(const HexUnit& v){
        q *= v;
        r *= v;
        s *= v;
        return *this;
    }

};

struct AxialCoordinate{
    HexUnit q;
    HexUnit r;
    
    CubeCoordinate toCubeCoordinate(){
        return{
            .q = q,
            .r = r,
            .s = - q - r
        };
    }
};

struct Dimension{
    int x = 5;
    int y = 5;
    
    Dimension() = default;
    Dimension(int xd, int yd):x(xd),y(yd){}
};

struct HexaTile{
    CubeCoordinate cubeCoordinate;
    glm::vec3      worldCoordinate;
    float          radius;
    bool           active = true;
};





struct CubeDirection{
    
    HexUnit innerRadius = 0;
    HexUnit outerRadius = 0;
    
    static constexpr CubeCoordinate EAST       = {  1,  0, -1  };
    static constexpr CubeCoordinate SOUTH_EAST = {  0,  1, -1  };
    static constexpr CubeCoordinate SOUTH_WEST = { -1,  1,  0  };
    static constexpr CubeCoordinate WEST       = { -1,  0,  1  };
    static constexpr CubeCoordinate NORTH_WEST = {  0, -1,  1  };
    static constexpr CubeCoordinate NORTH_EAST = {  1, -1,  0  };
    
    CubeDirection(HexUnit radius):outerRadius(radius){};
};



class HexaGrid : public Prefab{
  
public:
    
    HexaGrid(int x, int y, const HexUnit radius = 1.0f);
    ~HexaGrid(){};
    void trim(VertexList boundary);
    
private:
    
    Dimension             m_dimension;
    const float           m_radius;
    const float           m_innerRadius;
    std::vector<HexaTile> m_tiles;

    
    HexaTile addTile(CubeCoordinate origin, CubeCoordinate direction);
    glm::vec3 toWorldCoordinate(CubeCoordinate coo, glm::vec3 origin = glm::vec3(0.0f));

    CustomMaterial m_material = CustomMaterial({.vertexShader = (std::string)(ROOT_DIR + "/Material/Shader/hexagrid.vert"),
        .fragmentShader = (std::string)(ROOT_DIR + "/Material/Shader/hexagrid.frag")
    });
    
    void build();
    
};

#endif /* Grid_hpp */
