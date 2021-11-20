#include <stdio.h>
#include <vector>
#ifndef UAV_H
#define UAV_H

class UAV_DLV1 {
    public:
        float alcance = 4;
        float carga = 2;
        int performance = 2;
        int velocidade = 32;
        
        int indicie_atual;

        Node* node = new Node;
        std::vector<Node> caminho;
        void PrintSpecs();
        void AddNodeCaminho(Node*, float**);
        bool ChacaPeso(float);
        bool ChecaAlcance(Node, float**);
        float AtualizaCapacidade(float);
        

};

class UAV_DLV2 {
    public:
        const float alcance = 10;
        const float carga = 8;
        const int performance = 5; //calcular
        const int velocidade = 50; //pesquisar
};

#endif 

using namespace std;

void UAV_DLV1::PrintSpecs(){
    printf("alcance: %f\n", alcance);
    printf("carga: %f\n", carga);
    printf("performance: %i\n", performance);
    printf("velocidade: %i\n", velocidade);
}


float UAV_DLV1::AtualizaCapacidade(float peso){
    float aux_carga = carga - peso; 
    return aux_carga;
}

bool UAV_DLV1::ChacaPeso(float peso){

    float is_ok = AtualizaCapacidade(peso);

    if (is_ok >= 0)
        return 1;

    else 
        return 0;
}

bool UAV_DLV1::ChecaAlcance(Node node, float** matriz){

    float aux_alcance = alcance - (matriz[indicie_atual][node.indicie]/100);
    if (aux_alcance < 0){
        return false;
    }
    else{
        return true;
    }

}



void UAV_DLV1::AddNodeCaminho(Node *node, float** matriz){

    caminho.push_back(*node);
    indicie_atual -= node->peso;
    alcance -= matriz[indicie_atual][node->destino];
    node->realizada = true;

}