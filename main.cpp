#include <iostream>

#include "pistone.h"
#include "svg.h"

using namespace std;

int main() {

    cout << "Inizializzazione pistone\n";

    Pistone* pistone = pist_init(200);

    cout << "Pistone inizializzato\n";

    cout << "Inizializzazione coordinate\n";

    Posizione* posizione = posiz_pist(200,200);

    cout << "Coordinate inizializzate\n";

    cout << "Creazione stringa\n";

    string s=svg_pist(pistone,posizione);

    cout << s << endl;

    s=svg(s);

    cout << s << endl;

    svg_to_file("pistone.svg",s);

    cout << "\nFine programma";
    return 0;
}