#include <iostream>
#include <stdio.h>
#include <limits.h>
#include <cstdlib>
#include <cstdio>
using namespace std;

#include <vector>
#include <set>
int zinS(int t[],const set<int> s1){
	for(int i=0;i<100;i++){
		if(t[i]!=INT_MAX){
			if(s1.find(i)==s1.end())
			{
				return 1;
			}
		}
	}
}
int dij(int initial,int final,int matrix[100][100],int t[],set<int> V){
	int i;
	for(i=0;i<100;i++){
		t[i]=INT_MAX;
	}
	for(i=0;i<100;i++){
		t[i]=matrix[initial][i];
	}
	t[initial]=0;
	set<int> s1;//checked nodes
	int v;
	s1.insert(initial);
	while(s1!=V&& zinS(t,s1)&&s1.find(final)==s1.end()){
		int min=INT_MAX;
		for(i=0;i<100;i++){
		if(s1.find(i)==s1.end()){
			if(t[i]<min){
				min=t[i];
				v = i;
			}
		}
	}
		s1.insert(v);
		for(i=0;i<100;i++){
			if(matrix[v][i]!=INT_MAX){
			if(s1.find(i)==s1.end()){
				if(t[i]>t[v]+matrix[v][i]){
					t[i]=t[v]+matrix[v][i];
				}
			}
		}
		}
}
  return t[final];
}

void printa_tabela (int nodo_inicial,int t[],set<int> S, set<int> V)
{
    set<int>::iterator iter;
    set<int>::iterator iter2;
    //Tabela de distancias
    cout << nodo_inicial << "\t0\n";
    //Printa os nodos e suas distancias calculadas no instante T

    for(iter2=V.begin(); iter2!=V.end();iter2++)
    {
        if((*iter2)!=nodo_inicial)
        {
            if(t[(*iter2)] == INT_MAX)
            {
                cout << (*iter2) << "\tINFINITO\n";
            }
            else
            {
                cout << (*iter2) << "\t" << t[(*iter2)] << "\n";
            }
        }

    }
    //Fim tabelas distancias
    //Maneira de printar o conjunto S
    cout << "\nConjunto S: ";
    for(iter=S.begin(); iter!=S.end(); iter++)
    {
        cout<<(*iter)<< " ";
    }
    cout << "\n\n";
}


//Segunda versão de Djisktra (versão passo a passo)
int dij_2(int initial,int final,int matrix[100][100],int t[],set<int> V){
	int i;
	int nodo_inicial, count_table;
	count_table = 0;
	nodo_inicial = initial;
	//Zera a tabela de distancias
	for(i=0;i<100;i++){
		t[i]=INT_MAX;
	}
	//Coloca os valores de distancias correspondentes na tabela de distancias t
	for(i=0;i<100;i++){
		t[i]=matrix[initial][i];
	}
	//Primeira distancia do nodo de partida ate ele mesmo é zero
	t[initial]=0;
	set<int> s1;//checked nodes
	set<int>::iterator iter; //Ferramentas de iteração
	int v;  //open set
	int vanterior=103;

	s1.insert(initial); //Marca o nodo corrente como visitado
	//Bloco pra chamar a printada das distancias
	cout << "T" << count_table << "\n\n";
	count_table++;
    printa_tabela(nodo_inicial,t,s1,V);
    cin.get();
    //FIM BLOCO

	//Se o nodo não foi visitado e ele foi inserido na matriz, procura o vertice de menor custo
	while(s1!=V&& zinS(t,s1)&&s1.find(final)==s1.end()&&v!=vanterior){
		vanterior=v;
		int min=INT_MAX;
		for(i=0;i<100;i++){
		if(s1.find(i)==s1.end()){
			if(t[i]<min){
				min=t[i];
				v = i;
			}
		}
	}
        //Pega o vertice de menor custo e insere na tabela de visitados e atualiza as distancias
		s1.insert(v);
		for(i=0;i<100;i++){
			if(matrix[v][i]!=INT_MAX){
            //Atualiza a tabela de distancias
			if(s1.find(i)==s1.end()){
				if(t[i]>t[v]+matrix[v][i]){
					t[i]=t[v]+matrix[v][i];
				}
			}
		}
		}

    //Bloco pra chamar a printada das distancias
	//cout << "T" << count_table << "\n\n";
	count_table++;
    printa_tabela(nodo_inicial,t,s1,V);
    //cin.get();
    //FIM BLOCO

}
  return t[final];
}

int main(){

  FILE *fp;
  char *FileName;
  fp = fopen("inst22n.dat","r");
  int matrix[100][100];
  int n,m;
  set<int> V; //V armazena o par de vertices X,Y a serem conectados com seu respectivo peso
  int x,y,weight;
  fscanf(fp,"%i %i",&n,&m);
  int i;
  for(i=0;i<100;i++){
  	for(int j=0;j<100;j++){
  		matrix[i][j]=INT_MAX;
  		matrix[j][i]=INT_MAX;
  	}
  }
  for(i=0;i<m;i++){
    fscanf(fp,"%i %i %i\n",&x,&y,&weight);
    V.insert(x);
    V.insert(y);
    printf("x:%i\n",x);
    printf("y:%i\n",y);
    matrix[x][y] = weight;
    matrix[y][x] = weight;
  }
  printf("%i %i \n\n",n,m);
  /*while(opcao!=0){
  printf("1:Algoritimo Simples  2:Algortimo passo a passo 0:para\n");
  scanf("%i",&opcao);
  }*/
  int t[100];
  int ini, fim;
  int opcao = 0;
  int distance;
  cout << "Digite o nodo de partida e o de chegada \n";
  scanf("%d%d",&ini, &fim);
  cout << "\n";
  cout << "1 - Executar Djisktra normalmente\n2 - Executar Djisktra passo a passo\n";
  scanf("%d",&opcao);
  switch(opcao)
  {
      case 1:
        distance=dij(ini,fim,matrix,t,V);
        printf("%i\n",distance);
        break;
      case 2:
        distance=dij_2(ini,fim,matrix,t,V);
        printf("%i\n",distance);
        break;
      default:
        cout << "Opcao Invalida\n";
  }

  return 1;
}


