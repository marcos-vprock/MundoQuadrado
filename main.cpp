#include <iostream>
#include <iomanip>
#include <ctime>
#include <conio.h>
#include <stdlib.h>
#include <locale.h>
#include <Windows.h>
#include <string>

#define c 10
#define l 10
#define n 12
#define p 2

using namespace std;

/*
MATRIZ DE ITENS:
1 - graveto
2 - pedra
3 - animal
4 - madeira
5 - fruta
6 - portal item - titânio
7 - portal item - pólvora
8 - portal item - isqueiro
9 - portal
10 - creeper
11 - bomba
*/

bool gameOn = 1, input=1, temPortal=0, portalLoop=1, dead = 0, skip = 0, inside=0;
char field[p][l][c];
int items[p][l][c], amount[n]={0,0,0,0,0,0,0,0,0,0,0,0}, posLfinalm, posCfinalm;
int linha, coluna, quadros=c*l, lenChar, portalProb;
int lenstick, lenrock, lenanimal, lentree, intFound, objetivo, treeOpt, loopOpt;
char colect;
int posL=l/2, posC=c/2, nextPosL, nextPosC;
string character;

void generateElement(int pcoord, int element, int elementQuant){
    srand(time(NULL));
    int ct = 0;
    while(ct<elementQuant){
        linha = rand()%l;
        coluna = rand()%c;
        if(items[pcoord][linha][coluna]==0){
            items[pcoord][linha][coluna] = element;
            ct++;
        }
    }
}

void listenInput(int matrix){
    char next;
    input=1;
    while(input){
        next = getch();
        switch(next){
        case 'a':
            if(posC-1<0){
                cout<<"Voce chegou na borda do mundo!"<<endl;
            }else{
                nextPosC = posC-1;
                nextPosL = posL;
                input = 0;
            }
            break;
        case 'd':
            if(posC+1==c){
                cout<<"Voce chegou na borda do mundo!"<<endl;
            }else{
                nextPosL = posL; 
                nextPosC = posC+1;
                input = 0;
            }
            break;
        case 'w':
            if(posL-1<0){
                cout<<"Voce chegou na borda do mundo!"<<endl;
            }else{
                nextPosL = posL-1;
                nextPosC = posC;
                input = 0;
            }
            break;
        case 's':
            if(posL+1==l){
                cout<<"Voce chegou na borda do mundo!"<<endl;
            }else{
                nextPosL = posL+1;
                nextPosC = posC;
                input = 0;
            }
            break;
        default:
            input = 0;
            break;
        }
    }

    //troca a posição do personagem
    field[matrix][posL][posC] = (items[matrix][posL][posC]==9) ? '@' : '*';
    posL = nextPosL;
    posC = nextPosC;
    field[matrix][posL][posC] = 'O';
}

void inventario(){
    cout<<endl<<endl<<"---- INVENTARIO ----"<<endl;
    cout<<"  GRAVETOS: "<<amount[1]<<endl;
    cout<<"  PEDRAS: "<<amount[2]<<endl;
    cout<<"  ANIMAIS: "<<amount[3]<<endl;
    cout<<"  MADEIRAS: "<<amount[4]<<endl;
    cout<<"  FRUTAS: "<<amount[5]<<endl;
    cout<<"  BOMBAS: "<<amount[11]<<endl;
    if(inside){
        cout<<endl<<"  TITANIOS: "<<amount[6]<<endl;
        cout<<"  POLVORAS: "<<amount[7]<<endl;
        cout<<"  ISQUEIROS: "<<amount[8]<<endl;
    }
}

void introPortal(){
    int option, luck;
    srand(time(NULL));
    system("cls");
    Sleep(500);
    cout<<"Voce foi transportado para o submundo :( "<<endl<<endl;
    system("pause");
    system("cls");
    Sleep(250);
    cout<<"Mas nao se desespere, temos uma solucao para voce"<<endl<<endl;
    Sleep(500);
    cout<<"A ESCOLHA E SUA:"<<endl;
    Sleep(250);
    cout<<"1 - Para entrar no submundo e completar uma missao (Cuidado com os Creepers)"<<endl;
    Sleep(250);
    cout<<"2 - Para testar a sua sorte. (morrer ou retornar ao mundo da luz)"<<endl;
    cin>>option;
    if (option == 2){
        luck = 1+rand()%100;
        if(luck<=80){
            dead = 1;
            skip = 1;
            gameOn = 0;
        }
    }else{
        system("cls");
        Sleep(250);
        cout<<"Encontre os elementos e construa a sua bomba para destruir a barreira entre os mundos!"<<endl<<endl;
        system("pause");
    }
}

void creeper(){
    int quest1, quest2, questResp;
    srand(time(NULL));
    cout<<endl<<endl<<"   DAMAGE!!"<<endl<<endl;
    cout<<"VOCE ENCONTROU UM CREEPER!!"<<endl<<endl;
    quest1 = 1+rand()%10;
    quest2 = 1+rand()%10;
    Sleep(200);
    cout<<"Para nao morrer de a resposta para esta conta (EM MENOS DE 5 SEGUNDOS):"<<endl<<endl;
    system("pause");
    cout<<"  "<<quest1<<" + "<<quest2<<" ?";

    clock_t t=0;
    t = clock();
    cin>>questResp;
    t = clock() - t;
    if((((float)t)/CLOCKS_PER_SEC) > 5.0 || (questResp != (quest1 + quest2))){
        dead = 1;
        skip = 1;
        gameOn = 0;
        portalLoop = 0;
    }
    items[1][posL][posC] = 0;
}

void goPortal(){ 
    int quantIsq=1, quantPol=5, quantTit=4;
    //salva a posição que o jogador entrou no portal
    posLfinalm = posL;
    posCfinalm = posC;
    amount[6] = amount[7] = amount[8] = 0;
    srand(time(NULL));
    int portalMission = 1+rand()%3;
    int nextPosL, nextPosC;
    char next;

    introPortal();

    while(!skip){
        inside = 1;
        for(int i=0; i<l; i++){
            for(int j=0; j<c; j++){
                items[1][i][j];
                field[1][i][j]='-';
            }
        }
        //titânio = 6
        generateElement(1, 6, 5);
        //pólvora = 7
        generateElement(1, 7, 10);
        //isqueiro = 8
        generateElement(1, 8, 2);
        //creeper = 10
        generateElement(1, 10, 3);

        portalLoop = 1;
        while(portalLoop){
            system("cls");
        
            field[1][posL][posC] = 'O';

            for(int i=0; i<l; i++){
                for(int j=0; j<c; j++){
                    cout<<setw(3)<<field[1][i][j];
                }
                cout<<endl;
            }
            
            //objetivo
            cout<<"---------------------------------"<<endl;
            cout<<character<<", seu objetivo sera coletar:"<<endl;
            cout<<"1 Isqueiro"<<endl<<"5 Polvoras"<<endl<<"4 titanio"<<endl;
            cout<<"---------------------------------"<<endl;

            //inventario
            inventario();

            //pega o input dado
            listenInput(1);

            intFound = items[1][posL][posC];
            if(intFound!=0){
                colect = 'n';
                switch (intFound){
                    case 6:
                        cout<<"Voce achou um TITANIO!"<<endl<<"Deseja coletar o item? (s/n)"<<endl;
                        colect = getch();
                        break;
                    case 7:
                        cout<<"Voce achou uma POLVORA!"<<endl<<"Deseja coletar o item? (s/n)"<<endl;
                        colect = getch();
                        break;
                    case 8:
                        cout<<"Voce achou um ISQUEIRO!"<<endl<<"Deseja coletar o item? (s/n)"<<endl;
                        colect = getch();
                        break;
                    case 10:
                        creeper();
                        break;
                    default:
                        colect='n';
                        break;
                }
                if (colect == 's'){
                    items[1][posL][posC] = 0;
                    amount[intFound]++;
                }
            }
            if (amount[6]>=quantTit && amount[7]>=quantPol && amount[8]>=quantIsq){
                Sleep(500);
                system("cls");
                cout<<"VOCE CONSEGUI."<<endl<<"VOLTE AO SEU MUNDO E TERMINE OS SEUS OBJETIVOS!"<<endl<<endl;
                portalLoop = 0;
                amount[11]++;
                system("pause");
                system("cls");
                system("color f7");
                Sleep(400);
            }
        }
        posL = posLfinalm;
        posC = posCfinalm;
        skip = 1;
    }
    inside = 0;
}

int main(){
    system("color 0F");
    //nome do personagem
    system("cls");
    cout<<"Vamos comecar!"<<endl<<"Escolha o nome do seu personagem..."<<endl;
    cin>>character;
    lenChar = character.length();
    character[0] = (character[0]>=97 && character[0]<=122) ? char(character[0]-32):character[0];

    temPortal = 0;
    //definição de objetivo
    system("cls");
    cout<<endl<<"Seja bem-vindo, "<<character<<"!!"<<endl;
    cout<<"QUAL O SEU OBJEIVO FINAL?"<<endl<<"1 - Luz e calor"<<endl<<"2 - Comida"<<endl<<"3 - Construcao"<<endl;
    cin>>objetivo;

    // geração dos itens
    for (int i=0; i<p; i++){
        for (int j=0; j<l; j++){
            for(int k=0; k<c; k++){
                items[i][j][k] = 0;
            }
        }
    }

    //geração do portal
    srand(time(NULL));
    portalProb = 1+rand()%100;
    if (portalProb<=50){
        generateElement(0, 9, 3);
    }
    
    //gravetos = 1
    lenstick = quadros/100*20;
    generateElement(0, 1, lenstick);

    //pedra = 2
    lenrock = quadros/100*10;
    generateElement(0, 2, lenrock);

    //animal = 3
    lenanimal = quadros/100*5;
    generateElement(0, 3, lenanimal);

    //arvores = 4
    lentree = quadros/100*10;
    generateElement(0, 4, lentree);

    //verifica se tem portal
    for(int i=0; i<l; i++){
        for(int j=0; j<c; j++){
            if(items[0][i][j]==9){
                temPortal = 1;
                break;
            }
        }
    }

    // geração do mundo
    for (int i=0; i<p; i++){
        for (int j=0; j<l; j++){
            for(int k=0; k<c; k++){
                field[i][j][k] = '-';
            }
        }
    }
    field[0][posL][posC] = 'O';

    //saída
    gameOn = 1;
    while(gameOn){
        system("color 0f");
        system("cls");
        cout << setw((c + 7)) << "Mundo Quadrado" << endl;

        //printa o mundo
        for (int i=0; i<l; i++){
            for (int j=0; j<c; j++){
                cout<<setw(3)<<field[0][i][j];
            }
            cout<<endl;
        }

        //imprime o objetivo
        cout<<endl<<endl;
        cout<<"---------------------------------"<<endl;
        cout<<(temPortal==1)?"TEM":"NAO TEM";
        cout<<" PORTAL!"<<endl;
        cout<<character<<", seu objetivo sera coletar:"<<endl;
        switch(objetivo){
            case 1:
                cout<<"4 gravetos"<<endl<<"2 pedras"<<endl;
                break;
            case 2: 
                cout<<"1 animal"<<endl<<"1 fruta"<<endl;
                break;
            case 3:
                cout<<"8 pedras"<<endl<<"4 madeiras"<<endl;
        }
        cout<<"---------------------------------"<<endl;
        cout<<endl;

        //imprime o inventario
        inventario();

        //delimita o mundo e move o personagem
        listenInput(0);

        //quando acha um elemento
        intFound = items[0][posL][posC];
        if(intFound!=0){
            colect = 'n';
            switch (intFound){
                case 1:
                    cout<<"Voce achou um GRAVETO!"<<endl<<"Deseja coletar o item? (s/n)"<<endl;
                    colect = getch();
                    break;
                case 2:
                    cout<<"Voce achou uma PEDRA!"<<endl<<"Deseja coletar o item? (s/n)"<<endl;
                    colect = getch();
                    break;
                case 3:
                    cout<<"Voce achou um ANIMAL!"<<endl<<"Deseja coletar o item? (s/n)"<<endl;
                    colect = getch();
                    break;
                case 4:
                    cout<<"Voce achou um ARVORE"<<endl<<"Deseja coletar o item? (s/n)"<<endl;
                    colect = getch();
                    if(colect =='s'){
                        cout<<"O que voce quer coletar?"<<endl<<"0 - madeira"<<endl<<"1 - fruta"<<endl;
                        treeOpt = getch();
                        intFound = (treeOpt == '1') ? 5 : 4;
                    }
                    break;
                case 9:
                    system("cls");
                    system("color 4f");
                    cout<<"VOCE ESTA SENDO DIRECIONADO PARA OUTRA DIMENSAO"<<endl;
                    system("pause");
                    goPortal();
                    skip = 0;
                    break;
            }
            if (colect == 's'){
                items[0][posL][posC] = 0;
                amount[intFound]++;
            }
        }

        //fim do objetivo?
        switch(objetivo){
            case 1:
                if (amount[1]>=4 && amount[2]>=2){
                    gameOn = 0;
                }
                break;
            case 2:
                if (amount[3]>=1 && amount[5]>=1){
                    gameOn = 0;
                }
                break;
            case 3:
                if (amount[2]>=8 && amount[4]>=4){
                    gameOn = 0;
                }
    }

    //tela final e jogar outra vez
    if(dead){
        system("cls");
        for (int i=0; i<3; i++){
            system("color 5f");
            Sleep(50);
            system("color 4f");
            Sleep(50);
        }
        Sleep(100);
        system("color 6f");
        Sleep(300);
        system("color ef");
        Sleep(700);
        system("color f4");
        system("cls");
        for(int i=0; i<60; i++){
            cout<<"YOU DIED"<<endl;
            Sleep(50);
        }
        system("pause");
    }else if(gameOn == 0){
        Sleep(300);
        system("cls");
        Sleep(300);
        system("color f4");
        cout<<setw(3)<<"Voce completou os seus objetivos!!"<<endl;
        system("pause");
    }
    }
}
