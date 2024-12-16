#include<iostream>
#include<random>
#include<fstream>

using namespace std;

string alfabeto = "abcdefghijklmnopqrstuvwxyz";
string vocales = "aeiou";
string consonantes = "bcdfghjklmnpqrstvwxyz";

char letra_aleatoria(){
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dist(0,25);
    return alfabeto[dist(gen)];
}

char vocal_aleatoria(){
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dist(0,4);
    return vocales[dist(gen)];
}

char consonate_aleatoria(){
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dist(0,20);
    return consonantes[dist(gen)];
}


string generar_cadena(int size){
    string resultado = "";
    for(int i = 0; i < size ; i++){
        resultado += letra_aleatoria();
    }
    return resultado;
}

string generar_caso_favorable(int size){
    string resultado = "";
    for(int i = 0; i < size; i++){
        if (i % 2 == 0) resultado += consonate_aleatoria();
        else resultado += vocal_aleatoria();
    }
    return resultado;
}

int main(){
    string nombre_fichero = "entrada.in";

    ofstream outfile(nombre_fichero);

    if(!outfile.is_open()){
        cerr << "Error al abrir el fichero para escritura" << endl;
        return 1;
    }

    outfile << generar_cadena(10e6)<< endl;
    outfile.close();
}
