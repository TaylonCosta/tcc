#include <list>
#include <vector>
#include <iostream>
#include <stdio.h>
#include <random>
#include <iomanip>
#ifndef DEMANDAS_H
#define DEMANDAS_H

class Node{
    public:
        int destino, indicie;
        float peso;
        bool realizada;
};


class Demandas{
    public:
        int total_demandas;
        std::vector<Node> demandas;
        void GeraDemandas(int n);
        void addLinhaDemanda(int x, int j, float p);
        void Print();
        bool DemandasRealizadas();
};

#endif 

    using namespace std;

    constexpr int FLOAT_MIN = 0.5;
    constexpr int FLOAT_MAX = 2;

void Demandas::addLinhaDemanda(int idx, int nodeentrega, float peso){

    Node node;
    node.destino = nodeentrega;
    node.indicie = idx;
    node.peso = peso;
    node.realizada = 0;
    demandas.push_back(node);

}


void Demandas::GeraDemandas(int n){
    
    random_device rd;
    default_random_engine eng(rd());
    uniform_real_distribution<> distr(FLOAT_MIN, FLOAT_MAX);
    srand(time(NULL));

    total_demandas = n;
    int rnode;
    float rpeso=0;

    for(int i=0; i<n; ++i){
        
        rnode = rand() % 10 + 1;
        cout << setprecision(2);
        rpeso = distr(eng);
        addLinhaDemanda(i, rnode, rpeso);
    }
}

void Demandas::Print(){

    for (vector<Node>::iterator it = demandas.begin(); it != demandas.end(); ++it){
            cout << "indicie" << it->indicie << " ";
            cout << "entrega" << it->destino << " ";
            cout << "peso" << it->peso << "\n";
    }

}

bool Demandas::DemandasRealizadas(){

    for(int i=0; i<total_demandas; ++i){
        if(!demandas[i].realizada){
            return false;
        }
    }
}