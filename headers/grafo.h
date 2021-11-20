#include <list>
#include <vector>
#include <iostream>
#include <stdio.h>
#ifndef GRAFO_H
#define GRAFO_H

class Grafo{
    public:
        int V=0;
        std::vector<std::list<float>> adj;
        float matriz_adj[11][11];
        void Criar();
        void addEdge(float, float, float);
        void CalculaMatrizAdj();
        void CalculaDistanciaCaminho(std::vector<Node>, double&) const;
        void PrintCaminho() const;
        void Print();
        void Clear();
};

#endif 

using namespace std;

void Grafo::Criar(){
    
    ifstream filein;
    filein.open("grafo.txt");
    filein>>V;
    cout<<matriz_adj;
    float vet[3];
    while(!filein.eof()){
        for(int i=0;i<3;i++){
            filein>>vet[i];
        }
        addEdge(vet[0], vet[1], vet[2]*100);
    }

}

void Grafo::addEdge(float u, float v, float wt){
    
    list<float> lista;
    lista.push_back(u);
    lista.push_back(v);
    lista.push_back(wt);
    adj.push_back(lista);

}

void Grafo::Print(){
       
    for (vector<list<float>>::iterator it = adj.begin(); it != adj.end(); ++it){
        for (list<float>::iterator it2 = it->begin(); it2 != it->end(); ++it2){
            printf("%.1f ",*it2);
        }
        cout << "\n";
    }

}

void Grafo::CalculaMatrizAdj(){

    for (int i=0; i<V; ++i){
        for (int j=0; j<V; ++j){
            matriz_adj[i][j]=0;
        }
    }

    
    int aux[2];
    int aux2;
    for (vector<list<float>>::iterator it = adj.begin(); it != adj.end(); ++it){
        int i=0;
        for (list<float>::iterator it2 = it->begin(); it2 != it->end(); ++it2){
            if (i == 2)
                aux2= *it2;
            else
                aux[i]= *it2;
            i++;
        }
        matriz_adj[aux[0]][aux[1]]= aux2;
        matriz_adj[aux[1]][aux[0]]= aux2;

    }


    cout<<"Matriz de adj:\n";
    
    for (int i=0; i<V; ++i){
        for (int j=0; j<V; ++j){
            cout << matriz_adj[i][j]<<" ";
        }
        cout << "\n";
    }    
}


void Grafo::CalculaDistanciaCaminho(vector<Node>caminho, double &distancia_caminho) const{

    if(caminho.size() > 2){
        for(int j=0; j<caminho.size()-1; ++j){
            distancia_caminho += matriz_adj[caminho[j].indicie][caminho[j+1].indicie];
        }
    }
}


void Grafo::PrintCaminho() const {

    double distancia_total_caminho = 0.0;
    int total_visitado = 0;
    for(int i=0; i<tamanho_populacao; ++i){
        if(uavs[i].caminho.size()>1){
            cout<<"UAV: " << i <<" caminho";
            double distancia_caminho = 0.0;
            for(int j=0; j<uavs[i].caminho.size(); ++j){
                cout << uavs[i].caminho[j].indicie<<" ";
            }
            CalculaDistanciaCaminho(uavs[i].caminho, distancia_caminho);
            distancia_total_caminho += distancia_caminho;
            cout << setprecision(1) << distancia_caminho<<".";
            cout << ", visited customer:" << uavs[i].caminho.size()-2;
            total_visitado += uavs[i].caminho.size()-2;
        }
        else{
            cout << "UAV" << i << "nao utilizado\n";
        }
    }
    cout << "total visitado: "<<total_visitado << "/" << V;
    cout << "distancia: "<< distancia_total_caminho <<"\n";
}


void Grafo::Clear(){

    adj.clear();

}