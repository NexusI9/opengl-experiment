//
//  VertexGroup.cpp
//  opengl-expe
//
//  Created by EL KHANTOUR Nassim on 11/11/2024.
//

#include "VertexGroup.hpp"
#include <iostream>
#include "../Utility/Math/delaunator.hpp"
#include "../Utility/Debugger.hpp"

void VertexGroup::addGroup(std::string name, VertexList vertices){
    
    //TODO: implement a name checker to avoir duplicate name
    VertexElement offset = indexOffset();
    
    //create new group
    VertexLayer temp({ .name = name, .list = vertices });
    
    //update list vertex index
    for(VertexElement i = 0; i < vertices.size(); i++) temp.list[i].index = offset + i;
    
    //push back to member group
    m_groups.push_back(temp);
}

VertexElement VertexGroup::indexOffset(std::string name){
    //get offset count
    VertexElement offset = 0;
    for(auto& group : m_groups){
        if(group.name == name) break;
        offset += group.list.size();
    }
    return offset;
    
}


VertexElement VertexGroup::indexOffset(){
    //get offset count
    VertexElement offset = 0;
    for(auto& group : m_groups) offset += group.list.size();
    return offset;
}

void VertexGroup::bridge(){
    
    /**
     Bridge each group serially from 0 to end.
     */
    for(int g = 0; g < m_groups.size() - 1; g++){
        
        VertexLayer& outer = m_groups[g];
        VertexLayer& inner = m_groups[g + 1];
        
        std::vector<int> pairedIndex;
        
        //If size is different, assign bigger group to outer and smaller to inner
        if(inner.list.size() != outer.list.size()){
            //smaller loop
             inner = m_groups[g].list.size() < m_groups[g + 1].list.size() ? m_groups[g] : m_groups[g + 1];
            //bigger loop
            outer = m_groups[g].list.size() > m_groups[g + 1].list.size() ? m_groups[g] : m_groups[g + 1];
        }

        
        for(int o = 0; o < outer.list.size(); o++){
            
            VertexList::Point outerPoint = outer.list[o];

            /*
             Opposite completion:
             First compare the distance between the next outer and inner point, and get the closest to avoid too thin and long triangles. (C)
             Then if it's the inner that's closer, then create a new trangle with outer circle index + 1
                  
             1. Join A -> B -> C (cause closer to D)
                  B—C
                 / /
                 A——————D
             
             2. Create opposite triangle A -> C -> D
                 B—C._
                / /   \
                A——————D
             */
            
            
        
        
            //edge case for end of vertex loop
            if(o == outer.list.size() - 1){
                
                //end loop triangle
                m_elements.push_back(outerPoint.index);
                m_elements.push_back(inner.list.front().index);
                m_elements.push_back(outer.list.front().index);
                
            }else{
            
                VertexList::Point innerPoint = inner.list.front();
                //get closest inner point
                if(o > 0){
                    innerPoint = getClosestPoint(inner.list, outerPoint.vertex.position);
                    pairedIndex.push_back(static_cast<int>(innerPoint.index));
                }
                
                //get next vertex
                VertexList::Point outerNext = outer.list[ (o+1) % outer.list.size() ];
                VertexList::Point innerNext = inner.list[ (innerPoint.index+1) % inner.list.size() ];

                //get A <-> D distance
                float outerDistance = glm::distance(outerPoint.vertex.position, outerNext.vertex.position);
                
                //get B <-> C distance
                float innerDistance = glm::distance(innerPoint.vertex.position, innerNext.vertex.position);
                
                VertexList::Point lastPoint = outerDistance < innerDistance ? outerNext : innerNext;
                

                m_elements.push_back(outerPoint.index); //Add first triangle point
                m_elements.push_back(innerPoint.index); //Add second triangle point
                m_elements.push_back(lastPoint.index); //Add third triangle point
                

                //Autocomplete opposite depending on distance configuration (A -> C -> D)
                if(outerDistance < innerDistance){
                    m_elements.push_back(outerNext.index);
                    m_elements.push_back(innerPoint.index);
                    m_elements.push_back(innerNext.index);
                }else{
                    m_elements.push_back(outerNext.index);
                    m_elements.push_back(outerPoint.index);
                    m_elements.push_back(innerNext.index);
                }
                
                //std::cout << o << ":\t" << outerPoint.index << "\t" << innerPoint.index << "\t" << innerNext.index << std::endl;
        
            }
            
        }
        
        //Detect orphan vertex that didn't got assigned during bridge
        for(int p = 0; p < inner.list.size(); p++){
            
            VertexList::Point& point = inner.list[p];
            
            bool orphan = true;
            for(auto& index : pairedIndex){
                if(point.index == index){
                    orphan = false;
                    break;
                }
            }
            
            if(orphan){
                
                //Get closest point of orphan next neighbour instead of orphan
                VertexList::Point endPoint =  inner.list[(p + 1) % inner.list.size()];
                VertexList::Point closestPoint = getClosestPoint(outer.list, endPoint.vertex.position);
                
                //std::cout << point.index << "\t" << endPoint.index << std::endl;
                
                VertexElement a = closestPoint.index;
                VertexElement b = point.index;
                VertexElement c = point.index + 1;
                
                //edge case for orphan at end of loop join back to the end of outer loop instead of i + 1
                if(point.index == inner.list.back().index){
                    a = inner.list.front().index;
                    b = outer.list.back().index;
                    c = point.index;
                    //std::cout << point.index << ": " << a << "\t" << b << "\t" << c << std::endl;
                }
                
                Triangle triangle(a,b,c);
                insertTriangle(m_elements, triangle);
 
               
            }

            
        }

        
    }
    
    /*std::cout << "-------" << std::endl;
    int a = 1;
    for(auto& i : m_elements){
        std::cout << i << "\t";
        if(a%3 == 0) std::cout << std::endl;
        a++;
    }
    std::cout << std::endl;*/
    
    std::reverse(m_elements.begin(), m_elements.end());
    
}

std::vector<Vertex> VertexGroup::getVertex(){
    std::vector<Vertex> temp;
    for(auto& group : m_groups){
        for(auto& point : group.list) temp.push_back(point.vertex);
    };
    return temp;
}


std::vector<VertexElement> VertexGroup::getElement(){
    return m_elements;
}

VertexLayer* VertexGroup::getGroup(std::string name){
    for(auto& group : m_groups){
        if(group.name == name) return &group;
    }
    
    return nullptr;
}


VertexList::Point VertexGroup::getClosestPoint(VertexList const& haystack, glm::vec3 needle){
    
    VertexList::Point closestPoint = haystack.front();
    //get closest inner point
    for(int i = 0; i < haystack.size(); i++){
        
        VertexList::Point currentPoint = haystack[i];
        
        float newDistance = glm::distance(currentPoint.vertex.position, needle);
        float closestDistance = glm::distance(closestPoint.vertex.position, needle);
        
        if(newDistance < closestDistance) closestPoint = currentPoint;
    }
    
    return closestPoint;
    
}


void VertexGroup::insertTriangle(std::vector<VertexElement>& reference, Triangle triangle){
    
    /*
        L   M   N
        ----------
        A   B   C
        D   E   F
        ...
        
        Insert serially the triangle LMN in the Elements vector depending on each point value
        Compare if L > A && L < D, same for each triangle component
    
     */
    
    for(int r = 0; r < reference.size(); r+=3){
        
        VertexElement a = reference[r];
        VertexElement b = reference[r+1];
        VertexElement c = reference[r+2];
        
        if(triangle.a <= a && triangle.b <= b && triangle.c < c){
            reference.insert(reference.begin() + r, triangle.list, triangle.list + 3);
            return;
        }
        
    }
    
    //push at the end of array if didn't found
    reference.push_back(triangle.a);
    reference.push_back(triangle.b);
    reference.push_back(triangle.c);

}

void VertexGroup::fill(std::string groupName, FillMethod method){
    
    if(VertexLayer* layer = getGroup(groupName)){
        
        switch(method){
                
            case FillMethod::Triangle: {
                //Delaunator works on 2 dimension, need to flatten the vertex first
                std::vector<double> vertex = layer->list.toDouble(true, true, false);
                delaunator::Delaunator d(vertex);
                Vertex average = layer->list.average();
                VertexList fillList;
                int offset = indexOffset(groupName);
                
                for(std::size_t i = 0; i < d.triangles.size(); i+=3) {
                    
                    size_t indexA = d.triangles[i];
                    size_t indexB = d.triangles[i + 1];
                    size_t indexC = d.triangles[i + 2];
                    
                    /*Vertex vertexA = average;
                    Vertex vertexB = average;
                    Vertex vertexC = average;
                                        
                    vertexA.position = glm::vec3( d.coords[2 * indexA], d.coords[2 * indexA + 1], vertexA.position.z );
                    vertexB.position = glm::vec3( d.coords[2 * indexB], d.coords[2 * indexB + 1], vertexB.position.z );
                    vertexC.position = glm::vec3( d.coords[2 * indexC], d.coords[2 * indexC + 1], vertexC.position.z );
                    
                    //add new vertices to (future) group added after the loop
                    fillList.push_back(vertexA);
                    fillList.push_back(vertexB);
                    fillList.push_back(vertexC);*/
                    
                    //prepare elements to be added
                    Triangle triangle(static_cast<VertexElement>(offset + indexA),
                                      static_cast<VertexElement>(offset + indexB),
                                      static_cast<VertexElement>(offset + indexC));
                    
                    insertTriangle(m_elements, triangle);
                    std::cout << triangle.a << "\t" << triangle.b << "\t" << triangle.c << std::endl;
                };
                
                //Add new vertices
                //addGroup(std::string("fill ("+groupName+")"), fillList);

                
                break;
            }
                
            case FillMethod::Hexagone:
                
                break;
                
        }
        
    }else{
        std::cout << "Couldn't find any group named: " << groupName << ", fill aborted." << std::endl;
    }
    
    

    
}
