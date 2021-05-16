//
// Created by migue on 11/05/2021.
//

#ifndef WASTE_APP_GRAPHLOADER_H
#define WASTE_APP_GRAPHLOADER_H

#include "Graph.h"
#include "MapPoint.h"
#include <string>
#include <fstream>


using namespace std;

template <class T> class GraphLoader {
    Graph<T> readGraphFromFiles(string nodesFile,string edgesFile,string tagsFile){
        Graph<T> graph;

        fstream nFile,eFile,tFile;
        nFile.open(nodesFile,ios::in);
        eFile.open(edgesFile,ios::in);
        tFile.open(tagsFile,ios::in);
        int typesTags,numberElements;
        string type;
        tFile>>typesTags;
        while(typesTags!=0){
            tFile>>type;
            if(type=='Recycle'){

            }
            tFile>>numberElements;
            typesTags--;
        }


        double x,y;

        return graph;
    }

    Graph<T> loadNodes(string nodesFile,Graph<T> *graph){

        int numberNodes;
        nFile>>numberNodes;
        while(!nFile.eof()){
            Vertex<T> vertex;
            vertex
            nFile>>
        }

    }
};


#endif //WASTE_APP_GRAPHLOADER_H
