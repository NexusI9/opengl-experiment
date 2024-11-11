//
//  Vertex.h
//  opengl-expe
//
//  Created by EL KHANTOUR Nassim on 21/09/2024.
//

#ifndef Vertex_h
#define Vertex_h
#include <glm/glm.hpp>
#include <string>
#include <vector>

struct Vertex{
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec3 color;
    glm::vec2 texUV;
    
    Vertex operator+(const Vertex& v) const{
        return {
            .position = position + v.position,
            .normal = normal + v.normal,
            .color = color + v.color,
            .texUV = texUV + v.texUV
        };
    }
    
    Vertex& operator+=(const Vertex& v) {
        position += v.position;
        normal += + v.normal;
        color += v.color;
        texUV += v.texUV;
        return *this;
    }
    
    Vertex operator-(const Vertex& v) const{
        return {
            .position = position - v.position,
            .normal = normal - v.normal,
            .color = color - v.color,
            .texUV = texUV - v.texUV
        };
    }
    
    Vertex& operator-=(const Vertex& v) {
        position -= v.position;
        normal -= v.normal;
        color -= v.color;
        texUV -= v.texUV;
        return *this;
    }
    
    Vertex operator*(const Vertex& v) const{
        return {
            .position = position * v.position,
            .normal = normal * v.normal,
            .color = color * v.color,
            .texUV = texUV * v.texUV
        };
    }
    
    Vertex& operator*=(const Vertex& v) {
        position *= v.position;
        normal *= v.normal;
        color *= v.color;
        texUV *= v.texUV;
       return *this;
    }
    
    Vertex operator*(const float& n) const{
        return {
            .position = position * n,
            .normal = normal * n,
            .color = color * n,
            .texUV = texUV * n
        };
    }
    
    Vertex& operator*=(const float& n) {
        position *= n;
        normal *= n;
        color *= n;
        texUV *= n;
        return *this;
    }
    
    Vertex operator/(const Vertex& v) const{
        return {
            .position = position / v.position,
            .normal = normal / v.normal,
            .color = color / v.color,
            .texUV = texUV / v.texUV
        };
    }
    
    Vertex& operator/=(const Vertex& v) {
        position /= v.position;
        normal /= v.normal;
        color /= v.color;
        texUV /= v.texUV;
        return *this;
    }
    
    Vertex operator/(const float& n) const{
        return {
            .position = position / n,
            .normal = normal / n,
            .color = color / n,
            .texUV = texUV / n
        };
    }
    
    Vertex& operator/=(const float& n) {
        position /= n;
        normal /= n;
        color /= n;
        texUV /= n;
        return *this;
    }
};

using VertexElement = int;
using VertexCluster = std::vector<Vertex>;

#endif /* Vertex_h */
