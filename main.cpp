#include <iostream>
#include <stdlib.h>
#include <fstream>

#include "headers/grafo.h"
#include "headers/demandas.h"
#include "headers/uav.h"
#include "headers/ACO.h"



using namespace std;


int main()
{
    //inicializa o grafo
    int tamanho=0, i;
    float n;
    Grafo
    * g = new Grafo;
    UAV_DLV1* u1 = new UAV_DLV1;
    Demandas* d = new Demandas;
 //   Colonia c;
    g->Criar();

    g->Print();
    g->CalculaMatrizAdj();


    //printa specs do uav
    u1->PrintSpecs();

    //inicializa das demandas aleatorias
    int ndemandas = 20;
    d->GeraDemandas(ndemandas);

    return 0;

}