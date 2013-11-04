#include "pelicula.h"

Pelicula::Pelicula (Nombre n, Lista<Genero> gs, Lista<Actor> as, bool b) {
  nombre_ = n;
  generos_ = gs;
  actores_ = as;
  es3D_ = b;
}

string Pelicula::nombreP() const {
  return nombre_;
}
 
Lista<Genero> Pelicula::generosP() const {
  return generos_;
}
 
Lista<Actor> Pelicula::actoresP() const {
  return actores_;
}
 
bool Pelicula::es3DP() const {
  return es3D_;
}

Lista<pair<Genero,Lista<Pelicula> > > Pelicula::agruparPelisPorGeneroP(Lista<Pelicula> ps) const {

};

Lista<Pelicula> Pelicula::generarSagaDePeliculasP(Lista<Actor> as, Lista<Genero> gs, Lista<Nombre> nombres) const {
  Lista<Pelicula> res;
  int cant = nombres.longitud()
    , i = 0
    ;
  sacarGenerosRepConsec(gs);
  sacarActoresRepConsec(as);
  while (i < cant) {
    res.agregarAtras(Pelicula(nombres.iesimo(i), gs, as, false));
    i++;
  }
  return res;
}

//auxiliares

void Pelicula::sacarActoresRepConsec(Lista<Actor> &orig) {
  int l = orig.longitud() - 1
    , i = 0
    ;
  while (i < l) {
     if (orig.iesimo(i) == orig.iesimo(i+1)){
       orig.eliminarPosicion(i);
       l--;
     } else {
       i++;
     }
  }
}

void Pelicula::sacarGenerosRepConsec(Lista<Genero> &orig) {
  int l = orig.longitud() - 1
    , i = 0
    ;
  while (i < l) {
    if (orig.iesimo(i) == orig.iesimo(i+1)){
      orig.eliminarPosicion(i);
      l--;
    } else {
      i++;
    }
  }
}
