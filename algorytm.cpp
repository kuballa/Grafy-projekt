#include <cstdio>
#include <cstdio>
#include <queue>
#include <cstring>
#include <vector>
#include <iostream>
#include <fstream>
using namespace std;

int pojemnosc[5][5];
int miniety_przeplyw[5][5];
vector<int> graf[5];
int lista_rodzicow[5];       
int obecna_przepustowosc[5];  
//***************************************************************************************************************
int bfs(int wezel_zrodlo, int wezel_koniec)
{
    memset(lista_rodzicow, -1, sizeof(lista_rodzicow));
    memset(obecna_przepustowosc, 0, sizeof(obecna_przepustowosc));
    queue<int> kolejka;
    kolejka.push(wezel_zrodlo);
    lista_rodzicow[wezel_zrodlo] = -2;
    obecna_przepustowosc[wezel_zrodlo] = 999;
    while(!kolejka.empty())
    {
        int aktualny_wez = kolejka.front();
        kolejka.pop();
        for(int i=0; i<graf[aktualny_wez].size(); i++)
        {
            int koniec= graf[aktualny_wez][i];
            if(lista_rodzicow[koniec] == -1)
            {
                if(pojemnosc[aktualny_wez][koniec] - miniety_przeplyw[aktualny_wez][koniec] > 0)
                {
                    lista_rodzicow[koniec] = aktualny_wez;
                    obecna_przepustowosc[koniec] = min(obecna_przepustowosc[aktualny_wez], 
                    pojemnosc[aktualny_wez][koniec] - miniety_przeplyw[aktualny_wez][koniec]);
                    if(koniec == wezel_koniec)
                    {
                        return obecna_przepustowosc[wezel_koniec];
                    }
                    kolejka.push(koniec);
                }
            }
        }
    }
    return 0;
}
//***************************************************************************************************************
int EdmondsKarp(int wezel_zrodlo, int wezel_koniec)
{
    int max_przeplyw = 0;
    while(true)
    {
        int przeplyw = bfs(wezel_zrodlo, wezel_koniec);
        if (przeplyw == 0) 
        {
            break;
        }
        max_przeplyw += przeplyw;
        int aktualny_wez = wezel_koniec;
        while(aktualny_wez != wezel_zrodlo)
        {
            int poprzedni_wezel = lista_rodzicow[aktualny_wez];
            miniety_przeplyw[poprzedni_wezel][aktualny_wez] += przeplyw;
            miniety_przeplyw[aktualny_wez][poprzedni_wezel] -= przeplyw;
            aktualny_wez = poprzedni_wezel;
        }
    }
    return max_przeplyw;
}
//***************************************************************************************************************
int main()
{
    string linia;
    int licz_wezlow = 0, licz_krawedzi = 0;
    int pocz_przep = 0, kon_przep = 0;

    ifstream file { "file.txt" };
    if (!file.is_open()) 
    {
        return -1;
    }
    while(getline(file, linia))
    {
        licz_krawedzi++;
    }
    file.clear();
    file.seekg(0);
    for(int krawedz = 0; krawedz < licz_krawedzi; krawedz++)
    {
        int poczatek, koniec, waga;
        file >> poczatek;
        file >> koniec;
        file >> waga;
        pojemnosc[poczatek][koniec] = waga;
        graf[poczatek].push_back(koniec);
        graf[koniec].push_back(poczatek);
        if(licz_wezlow == koniec)
        {
            licz_wezlow = koniec + 1;
        }
        kon_przep = koniec;
    }
    
    int max_przeplyw = EdmondsKarp(0, kon_przep);
    cout << endl << endl << "Maksymalny przeplyw to: " << max_przeplyw << endl;
}