#include "cine.h"

using namespace std;

Cine::Cine(Nombre n) {
  nombre_ = n;
  peliculas_ = Lista<pair<Pelicula, Sala> >();
  espectadores_ = Lista<pair<Sala, int> >();
  ticketsVendidos_ = Lista<Ticket>();
  salasSinUsar_ = Lista<Sala>();
}

string Cine::nombreC() const {
  return nombre_;
}

Lista<Pelicula> Cine::peliculasC() const {
  Lista<Pelicula> res;
  int t = peliculas_.longitud()
    , i = 0;
  while (i < t) {
    res.agregarAtras(peliculas_.iesimo(i).first);
    i++;
  }
  return res;
}

Lista<Sala> Cine::salasC() const{
  Lista<Sala> res;
  int i = 0;
  while (i < peliculas_.longitud()) {
    res.agregarAtras(peliculas_.iesimo(i).second);
    i++;
  }
  i = 0;
  while (i < salasSinUsar_.longitud()) {
    res.agregarAtras(salasSinUsar_.iesimo(i));
    i++;
  }
  return res;
}

int Cine::espectadoresC(Sala s) const {
  int i = 0;
  while (true) {
    if (espectadores_.iesimo(i).first == s)
      return espectadores_.iesimo(i).second;
    i++;
  }
}

Sala Cine::salaC(const Nombre &p) const {
  Sala res;
  int i = 0
    , l = peliculas_.longitud()
    ;
  while(i < l) {
    if (peliculas_.iesimo(i).first.nombreP() == p)
      res = peliculas_.iesimo(i).second;
    i++;
  }
  return res;
}

Lista<Ticket> Cine::ticketsVendidosSinUsarC() const {
Lista<Ticket> res;
  int i = 0, l = ticketsVendidos_.longitud();
  Lista<Ticket> sinUsar;
  while (i < l) {
    if (!ticketsVendidos_.iesimo(i).usadoT())
      sinUsar.agregarAtras(ticketsVendidos_.iesimo(i));
    i++;
  }
  return sinUsar;
}

void Cine::abrirSalaC(Sala s) {
  salasSinUsar_.agregarAtras(s);
  espectadores_.agregarAtras(pair<Sala,int>(s,0));
}

void Cine::agregarPeliculaC(const Pelicula &c, Sala s) {
  peliculas_.agregarAtras(pair<Pelicula,Sala>(c,s));
  salasSinUsar_.eliminarPosicion(salasSinUsar_.posicion(s));
}

void Cine::cerrarSalaC(Sala s){
  salasC().eliminarPosicion(salasC().posicion(s));
  int i = 0;
  while (i < peliculas_.longitud()) {
    if (peliculas_.iesimo(i).second == s) {
      peliculas_.eliminarPosicion(i);
    } else {
      i++;
    }
  }
}

void Cine::cerrarSalasC(int e) {
  int i = 0;
  while (i < salasC().longitud()) {
    Sala sala = salasC().iesimo(i);
    if (espectadoresC(sala) < e) {
      cerrarSalaC(sala);
    }
    i++;
  }
}

void Cine::cerrarSalasDeLaCadenaC(Lista<Cine> &cs, int e) const {
  int i = 0;
  int l = cs.longitud();
  while (i < l) {
    Cine cine = cs.iesimo(i);
    cine.cerrarSalasC(e);
    i++;
  }
}

Pelicula Cine::peliculaC(Sala s) const{
    int i = 0;
    int l = peliculas_.longitud();
    Pelicula res;
    while (i < l) {
        if (peliculas_.iesimo(i).second == s) {
            res = peliculas_.iesimo(i).first;
        }
        i++;
    }
    return res;
}

Ticket Cine::venderTicketC(const Nombre &p) {
    int i = 0;
    int l = peliculas_.longitud();
    Ticket res;
    while (i < l) {
        if (peliculas_.iesimo(i).first.nombreP() == p) {
            res = Ticket(peliculas_.iesimo(i).first, Cine::salaC(p), false);
        }
        i++;
    }
    ticketsVendidos_.agregarAtras(res);
    return res;
}

Pelicula Cine::pasarA3DUnaPeliculaC(Nombre n) {
    int i = 0;
    int l = peliculas_.longitud();
    Pelicula res;
    Lista<pair<Pelicula, Sala> > peList;
    while (i < l) {
        Pelicula peliI = peliculas_.iesimo(i).first;
        if (peliI.nombreP() != n) {
            peList.agregarAtras(peliculas_.iesimo(i));
        } else {
            res = Pelicula(n,peliI.generosP(),peliI.actoresP(),true);
            peList.agregarAtras(pair<Pelicula, Sala>(res,salaC(n)));
            }
        i++;
    }
    peliculas_ = peList;
    return res;
}

Ticket Cine::ingresarASalaC(Sala s, const Ticket &t) {
    int i = 0, e;
    Ticket r = t;

    while (i < espectadores_.longitud()) {
        if (espectadores_.iesimo(i).first == s) {
            e = espectadores_.iesimo(i).second;
            espectadores_.eliminarPosicion(i);
            espectadores_.agregar(pair<Sala, int>(s,e + 1));
            }
        i++;
    }
    i = 0;
    while (i < ticketsVendidos_.longitud()) {
        if (ticketsVendidos_.iesimo(i).salaT() == s) {
            ticketsVendidos_.eliminarPosicion(i);
            i == ticketsVendidos_.longitud();
        }
        i++;
    }
    r.usarT();
    return r;
}




void Cine::mostrar(std::ostream& os) const {
    int i = 0;
    os << "Nombre: " << nombre_ << endl << "Salas y espectadores de cada una: " << espectadores_ << endl
       << "Peliculas: ";

    while (i < peliculas_.longitud()) {
        peliculas_.iesimo(i).first.mostrar(os);
        os <<"Sala: " << peliculas_.iesimo(i).second;
        i++;
    }
    os << endl << "Tickets Vendidos";
    i = 0;
    while (i < ticketsVendidos_.longitud()) {
        ticketsVendidos_.iesimo(i).mostrar(os);
        i++;
    }
    os << endl << "Salas sin usar: " << salasSinUsar_;
}

void Cine::guardar(std::ostream& os) const {
    int i = 0, j, k;
    os << "C |" << nombre_ << "| [";
    while (i < salasSinUsar_.longitud()){
        os << (i == 0 ? "" : ", ") << salasSinUsar_.iesimo(i);
        i++;
    }
    os << "] [";

    i = 0;
    while (i < espectadores_.longitud()){
        pair<Sala, int> e = espectadores_.iesimo(i);
        os << (i == 0 ? "" : ", ") << "(" << e.first << "," << e.second << ")";
        i++;
    }
    os << "] [";

    i = 0;

    while (i < salasC().longitud()) {  //por cada sala
        j = 0;
        k = 0;
        while (j < ticketsVendidos_.longitud()) {
            Ticket t = ticketsVendidos_.iesimo(j);
            if (t.salaT() == salasC().iesimo(i)) {
                k++;
            }
            j++;
        }
        if (k!=0){
        os << (i == 0 ? "" : ", ") << "(" << salasC().iesimo(i) << "," << k << ")";
        }
        i++;
    }
    os << "] [";

    i = 0;
    while (i < peliculas_.longitud()) {
        pair<Pelicula,Sala> p = peliculas_.iesimo(i);
        os << (i == 0 ? "" : ", ") << "(" << p.second << ", (";
        p.first.guardar(os);
        os << "))";
        i++;
    }
    os << "]";
}

void Cine::cargar (std::istream& is){
    char p;
    int s, e, x, t,
    i = 0;
    Ticket tt;
    Pelicula peli;
    pair<Sala, int> sala;
    Lista<Ticket> preTickets;

    is >> p; // C
    is >> p; // |
    getline(is,nombre_,'|'); // nombre y saca el |

    is >> p; // [
    if (is.peek() != ']') {
        while ( p != ']') {
            is >> x;
            salasSinUsar_.agregarAtras(x);
            is >> p; // , o ]
        }
    } else {
        is >> p;
    }

    is >> p; // [
    is >> p; // ( ó ]
    while (p == '(') {
        is >> s; // saca la sala
        is >> p; // saca la coma
        is >> e; // saca los espectadores

        sala = pair<Sala, int>(s,e);
        espectadores_.agregarAtras(sala);
        is >> p; // )
        is >> p; // , o ]
        if (p == ',') is >> p; // (
    }



    is >> p; // [
    is >> p; // (

    while (p == '(') {
        is >> x; // Saca la sala, es un int
        is >> p; // Saca la coma
        is >> t; // Saca la CANTIDAD de tickets sin usar
        Cine c;
         // Aca agrego un ticket por cada ticket sin usar en t
        while (i < t) {
             tt = Ticket(peli,x,false);
             preTickets.agregarAtras(tt);
             i++;
         }
        i = 0;
        is >> p; // )
        is >> p; // , o ]
    }

    is >> p; // [
    is >> p; // (

    while (p == '(') {
        is >> s; // saca hasta la coma de la dupla: es la sala de la peli
        is >> p; // ,
        is >> p; // (
        peli.cargar(is);
        peliculas_.agregarAtras(pair<Pelicula, Sala>(peli,s)); //sacamos la peli
        is >> p; // )
        is >> p; // )
        is >> p; // es una coma o un corchete
        if (p == ',') is >> p;
    }
    while (i<preTickets.longitud()) {
        int j = 0;
        while (j<peliculas_.longitud()) {
            if (peliculas_.iesimo(j).second == preTickets.iesimo(i).salaT()) {
                peli = peliculas_.iesimo(j).first;
            }
            j++;
        }
        tt = Ticket(peli,preTickets.iesimo(i).salaT(),false);
        ticketsVendidos_.agregarAtras(tt);
        i++;
    }
}
