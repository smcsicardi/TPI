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
  int t = peliculas_.longitud();
  int i = 0;
  while (i < t) {
    res.agregarAtras(peliculas_.iesimo(i).first);
    i++;
  }
  return res;
}

Lista<Sala> Cine::salasC() const{
  Lista<Sala> res;
  int t = peliculas_.longitud();
  int i = 0;
  while (i < t) {
    res.agregarAtras(peliculas_.iesimo(i).second);
    i++;
  }
  return res;
}

int Cine::espectadoresC(Sala s) const {
int i = 0;
while (true) {
    if (espectadores_.iesimo(i).first == s) {
        return espectadores_.iesimo(i).second;
        }
    i++;
    }
}

Sala Cine::salaC(const Nombre &p) const {
Sala res;
int i = 0;
int l = peliculas_.longitud();
while(i < l) {
    if (peliculas_.iesimo(i).first.nombreP() == p) {
        res = peliculas_.iesimo(i).second;
        }
    i++;
    }
    return res;
}

Lista<Ticket> Cine::ticketsVendidosSinUsarC() const {
Lista<Ticket> res;
int i = 0;
int l = ticketsVendidos_.longitud();
Lista<Ticket> sinUsar;
while (i < l) {
    if (!ticketsVendidos_.iesimo(i).usadoT()) {
        sinUsar.agregarAtras(ticketsVendidos_.iesimo(i));
        }
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
    int l = peliculas_.longitud();
    while (i < l) {
        if (peliculas_.iesimo(i).second == s) {
            peliculas_.eliminarPosicion(i);
            } else {
            i++;
        }
    }
}

void Cine::cerrarSalasC(int e){
int i = 0;
int l = salasC().longitud();
while (i < l) {
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
    cs.iesimo(i).cerrarSalasC(e);
    i++;
    }
}
