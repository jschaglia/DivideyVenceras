#include <iostream>
#include <vector>

using namespace std;


// Cadena de entrada para la primera prueba

string entrada = "";

/**
 * A la hora de simplificar código hemos decidido renombrar estas estructuras de datos
 * index : par de índices que representan una cadena
 * vi : vector de par de índices
 */
typedef pair<int,int> index;
typedef vector<index> vi;

/**
 * @brief función que determina si una letra es una vocal
 * @param c : char a evaluar
 * @return true si es vocal, false en caso contrario
 */

bool esVocal(char c){
    return (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u');
}

/**
 * @brief función que nos da la mitad de la cadena
 * @param a : par de índices que representan una cadena
 * @return entero que representa el índice de la mitad de la cadena
 */
int dividir(index a){
    return (a.first+a.second)/2;
}

/**
 * @brief función que determina la longitud de una subcadena
 * @param i : par de índices que representan una cadena
 * @return entero que representan la longitud de la cadena
 */
int longitud(index i){
    return (i.second-i.first+1);
}

/**
 * @brief función que determina si una subproblema es lo suficientemente pequeño
 * @param a : par de índices que representan una cadena
 * @return true si la cadena es de un tamaño igual o menor que 2, false en otro caso
 */
bool pequeno(index a){
    return (longitud(a) <= 2);
}

/**
 * @brief función que determina si una cadena es solución o no
 * @param a : par de índices que representan una cadena
 * @return el argumento a si es solución, en caso contrario, un par de índices que representan que la cadena no es solución
 */
index SolucionDirecta(index a){
    if (!esVocal(entrada[a.first]) && esVocal(entrada[a.second]))
            return a;
    else return {-1,-1};
}

/**
 * @brief función que concate dos subcadenas soluciones
 * @param s1 : par de índices que representan una cadena
 * @param s2 : par de índices que representan una cadena
 * @return par de índices que representan la concatenación de sendas cadenas s1 y s2
 */
index concatenar(index s1, index s2){
    return {s1.first,s2.second};
}


/**
 * @brief función que devuelve la cadena más larga entre varias
 * @param v vector de par de índices
 * @return par de índices que representan a la cadena más larga encontrada en el vector v
 */

index masLarga(vi v){
    index resultado = {-1,-1};

    for (index i : v){
        if (longitud(i) >= longitud(resultado))
            resultado = i;
    }

    return resultado;
}



/**
 * @brief función que extiende hacia la derecha una cadena
 * @param s1 : par de índices que representan una cadena
 * @return par de índices que representan la cadena extendida lo más posible hacia la derecha
 */

index extenderDerecha(index s1){
    bool flag = true;
    int i = s1.second + 1;
    index resultado = s1;
    while(flag){
        if(!esVocal(entrada[i]) && esVocal(entrada[i + 1])){
            resultado.second += 2;
            i += 2;
        }
        else flag = false;
    }
    return resultado;
}

/**
 * @brief función que extiende una cadena hacia la izquierda
 * @param s1 : par de índices que representan una cadena
 * @return par de índices que representan la cadena extendida lo más posible hacia la izquierda
 */

index extenderIzquierda(index s1){
    bool flag = true;
    int i = s1.first - 1;
    index resultado = s1;
    while(flag){
        if(esVocal(entrada[i]) && !esVocal(entrada[i - 1])){
            resultado.second -= 2;
            i -= 2;
        }
        else flag = false;
    }
    return resultado;
}

/**
 * @brief función combinar de la estructura divide y vencerás
 * @param s1 : par de índices que representan una cadena
 * @param s2 : par de índices que representan una cadena
 * @return cadena solución más larga entre s1 (izq), s2 (der), s3(frontera)
 */

index combinar(index s1, index s2, int m){
    /**
     * No hay continuidad en la frontera
     * consonante-consonante
     * vocal-vocal
     */
    if ((!esVocal(entrada[m]) && !esVocal(entrada[m+1])) || (esVocal(entrada[m]) && esVocal(entrada[m+1])) ){
        vi v;
        v.push_back(s1);
        v.push_back(s2);
        return masLarga(v);
    }

    /**
     * Hay continuidad en la frontera
     * consonante-vocal
     * vocal-consonante
     */

    else{
        // Si s1 toca la frontera
        if (s1.second == m){
            // Si s2 toca la frontera, devuelvo la concatenacion de ambos
            if (s2.first == m+1) return concatenar(s1,s2);
            // s2 no toca la frontera
            else{
                //Extiendo por la derecha s1 y devuelvo la cadena más larga (s1 o s2)
                s1 = extenderDerecha(s1);
                vi v;
                v.push_back(s1);
                v.push_back(s2);
                return masLarga(v);
            }
        }
        // s1 no toca frontera
        else {
            // s2 toca frontera
            if(s2.first == m+1){
                // Extiendo por la izquierda s2 y devuelvo la cadena más larga (s2 o s1)
                s2 = extenderIzquierda(s2);
                vi v;
                v.push_back(s1);
                v.push_back(s2);
                return masLarga(v);
            }
            // ni s1 ni s2 tocan fronteras, se mira la cadena frontera (m,m+1)
            else{
                index s3 = {m,m+1};
                // Extiendo s3 por ambos lados y devuelvo la cadena más larga (s3, s2 o s1)
                s3 = extenderIzquierda(s3);
                s3 = extenderDerecha(s3);
                vi v;
                v.push_back(s1);
                v.push_back(s2);
                v.push_back(s3);
                return masLarga(v);
            }
        }
    }
}


/**
 * @brief función que divide el problema en subproblemas y combina los resultado, devolviendo una cadena solución, en caso de existir
 * @param a : par de índices que representan una cadena
 * @return par de índices que representan la cadena solución, en caso de que la haya
 */

index dyv(index a){
    // Si el subproblema es lo suficientemente pequeño miro si es una solución válida
    if (pequeno(a)) return SolucionDirecta(a);
    else{
        // En caso contrario, divido el problema en dos subproblemas más pequeños
        int m = dividir(a);
        index s1 = dyv({a.first,m});
        index s2 = dyv({m+1,a.second});
        // Combino ambas subsolucion
        return combinar(s1,s2,m);
    }
}


int main(){    
    string cadena;
    cin >> cadena;
    if (cadena.length() == 0){
        cerr << "Cadena vacía. Saliendo..." << endl;
        exit(1);
    }
    entrada = cadena;
    index solucion = dyv({0,cadena.length()});
    cout << "La solución es: " << cadena.substr(solucion.first,longitud(solucion)) << "\nLa posición de comienzo de la solución es: " << solucion.first + 1 << endl;      
}