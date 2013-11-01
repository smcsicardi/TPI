#include "pelicula.h"
 
Pelicula::nuevaP (Nombre n, Lista<Genero> gs, Lista<Actor> as, bool b) {
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

Lista<(Genero,Lista<Pelicula>)> Pelicula::agruparPelisPorGeneroP (Lista<Pelicula> ps) {
  Lista<Genero> losGeneros = agregar(agregar(agregar(agregar(agregar(Terror,Lista<Generos>),Drama),Comedia),Aventura),Acción)
  Lista<(Genero,Lista<Pelicula>)> res = Lista<>
  
  while(losGeneros.longitud > 0) {
   
  }
}
