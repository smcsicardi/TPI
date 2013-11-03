#include "cine.h"

using namespace std;

Cine::Cine(Nombre n) {
  nombre_ = n;
  peliculas_ = Lista();
  ticketsVendidos_ = Lista();
  salasSinUsar_ = Lista();
}

Nombre Cine::nombreC() {
  return nombre_;
}

Lista<Pelicula> Cine::peliculasC() {
  Lista<Pair<Pelicula, Sala> > res;
  t = peliculas_.longitud;
  i = 0;
  while (i < t) {
    res.agregarAtras(peliculas_.iesimo(i).first);
    i++;
  }
  return res;
}

Lista<Sala> Cine::salasC() {
  Lista<Pair<Pelicula, Sala> > res;
  t = peliculas_.longitud;
  i = 0;
  while (i < t) {
    res.agregarAtras(peliculas_.iesimo(i).second);
    i++;
  }
  return res;
}

int Cine::espectadoresC(Sala s) {
  
}
