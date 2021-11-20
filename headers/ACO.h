#include <list>
#include <iostream>
#include <vector>
#include <random>
#include "demandas.h"
#ifndef ACO_H
#define ACO_H

class Colonia{
    public:

        const int tamanho_populacao = 5;//numero de agentes
        const int max_iteracao = 50; //numero maxino de iteracoes
        const double tau = 0.5; //valor inicial do feromonio
        const double alpha = 1; //valor exponencial do feromonio
        const double beta = 1; //valor do peso do feromonio
        const double ro = 0.05; //taxa de evaporacao do feromonio
        const double q = 1;
        double limiar = 0.5;
        int init = 99999;
        double** matriz_feromonio;
	    double** etha_matriz;
        vector<list<float> > demandas = demandas;
        Node* nodes;
        UAV_DLV1* uavs;
        Demandas* d;
        Colonia(std::vector<Node> demandas, UAV_DLV1* uavs, Grafo g);
        ~Colonia();
        void faz_movimento();
        //void Inicializa(auto demandas, auto uav);
        double GeraNoAleatorio() const;
        double CalculaProbalilidade(int, int) const;
        void AtualizaMatrizFeromonio(double&);
        void AtualizaLimiar();
        void Reseta();
        void Run();
        

};

#endif 

    using namespace std;

void Colonia::Run(){
    double menor_distancia = init;
    int n_demandas = demandas.size();

    for (int i=0; i < max_iteracao; ++i){
       faz_movimento();
       double distancia_total_caminho = 0.0;
       atualiza_matrix_feromonio(distancia_total_caminho);
       if(distancia_total_caminho < menor_distancia){
            menor_distancia = distancia_total_caminho;
            PrintCaminho();
       }
        AtualizaLimiar();
        Reseta();

    }
}


void Colonia::faz_movimento(){
    int indicie_uav = 0;
    while(!d->DemandasRealizadas()){
        if(uavs[indicie_uav].caminho().empty){
            uavs[indicie_uav]->AddNodeCaminho(&nodes[0], g.matriz_adj);
        }
        vector<pair<int ,int> > nos_possiveis;
        nos_possiveis.clear();
        while(nos_possiveis.empty()){
            for(int indicie_node=1; indicie_node < d->total_demandas; ++indicie_node){
                if(!nodes[indicie_node].realizada){
                    if(uavs[indicie_uav].ChacaPeso(nodes[indicie_node].peso))
                        if(uavs[indicie_uav].ChecaAlcance(nodes[indicie_node], g.matriz_adj)){
                            nos_possiveis.push_back(make_pair(uavs[indicie_uav].indicie_atual, indicie_node));
                        }
                    }       
                }
            }
        if(nos_possiveis.empty()){
            if(indicie_uav+1<tamanho_populacao){
                if(uavs[indicie_uav].indicie_atual != 0){
                    uavs[indicie_uav].AddNodeCaminho(&nodes[0], g.matriz_adj);
                }
                indicie_uav += 1;
            }
            else{
                cout << "nao foi possivel relizar todas as entregas.\n";
                break;
            }
        }
        else{
            int indicie_proximo_no;
            if(GeraNoAleatorio() < limiar){
                indicie_proximo_no = nos_possiveis[rand() % nos_possiveis.size()].second;
            }
            else{
                vector<double> ups, probs, soma_acumulada;
                double soma = 0.0;
                for(auto nos_possiveis : nos_possiveis){
                    double up = CalculaPropabilidade(nos_possiveis.first, nos_possiveis.second);
                    soma += up;
                    ups.push_back(up);
                }
                for (auto up : ups){
                    probs.push_back(up / soma);
                }
                soma_acumulada.push_back(probs.front());
                for(int i=0; i<probs.size()-1; ++i){
                    probs[i+1] += probs[i];
                    soma_acumulada.push_back(probs[i+1]);
                }
                int indicie_candidato, melhor_indicie;
                double candidato_v;
                double melhor_v = init;
                double r = GeraNoAleatorio();
                for(int x=0; x<soma_acumulada.size(); ++x){
                    if (r <= soma_acumulada[x]){
                        indicie_candidato = x;
                        candidato_v = soma_acumulada[x];
                        if(candidato_v < melhor_v){
                            melhor_indicie = indicie_candidato;
                            melhor_v = candidato_v;
                        }
                    }
                }
                if (melhor_v == init){
                    break;
                }
                indicie_proximo_no = nos_possiveis[melhor_indicie].second;
            }
        }
        uavs[indicie_uav].AddNodeCaminho(&nodes[indicie_proximo_no], g.matriz);
    }
    if(uavs[indicie_uav].indicie_atual !=0){
        uavs[indicie_uav].AddNodeCaminho(&nodes[0], g.matriz_adj)
    }
}

double Colonia::CalculaProbalilidade(int indicie_node_atual, int indicie_proximo_node) const{
    double ETAij = pow (matriz_etha[indicie_node_atual][indicie_proximo_node], beta);
    double TAUij = pow (matriz_feromonio[indicie_node_atual][indicie_proximo_node], alpha);
    return ETAij * TAUij;
}


double Colonia::GeraNoAleatorio() const{
    random_device aleatorio;
    mt19937 generator(aleatorio());
    uniform_real_distribution<double> distr(0, 1);
    return distr(generator);
}


void AtualizaMatrizFeromonio(double &distancia_total_caminho){

    for(int i=0; i < tamanho_populacao; ++i){
        double distancia_caminho = 0.0;
        g.CalculaDistanciaCaminho(uavs[i].caminho, distancia_caminho);
        distancia_total_caminho += distancia_caminho;
        for(int j=0; j<uavs[i].caminho.size(); ++j){
            if(j+1 != uavs[i].caminho.size()){
                matriz_feromonio[uavs[i].caminho[j].indicie][uavs[i].caminho[j+1].indicie] = 
                ro * matriz_feromonio[uavs[i].caminho[j].indicie][uavs[i].caminho[j+1].indicie] + 
                q / distancia_caminho;
            }
        }
    }
}

void Colonia::AtualizaLimiar(){
    limiar*=ro;
}

void Colonia::Reseta(){

    for(int i=0; i<tamanho_populacao; ++i){
        uavs[i].caminho.clear();
        uavs[i].carga = 4;
        uavs[i].indicie_atual = 0;
    }
    for(int i=0; i<V; ++i){
        nodes[i].realizada = false;
    }
}