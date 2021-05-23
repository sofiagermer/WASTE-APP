//
// Created by sofia on 23/05/21.
//

#ifndef WASTE_APP_ANALYSIS_H
#define WASTE_APP_ANALYSIS_H



#include "../Graph/Graph.h"

class Analysis {
private:

public:
    static void preprocessingAnalysisTarjan();
    static void preprocessingAnalysisKosaraju();
    static void aStarAnalysis(Graph graph);
    static void aStarVsDijkstra(Graph graph);
    static void dijkstraAnalysis(Graph graph);

};



#endif //WASTE_APP_ANALYSIS_H
