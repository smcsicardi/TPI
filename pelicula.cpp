#include <iostream>
#include <fstream>
#include "pelicula.h"

Pelicula::Pelicula (Nombre n, Lista<Genero> gs, Lista<Actor> as, bool b) {
  nombre_ = n;
  generos_ = Pelicula::sacarGenerosRepConsec(gs);
  actores_ = Pelicula::sacarActoresRepConsec(as);
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
  int cant = nombres.longitud();
  int i = 0;
  while (i < cant) {
    res.agregarAtras(Pelicula(nombres.iesimo(i), gs, as, false));
    i++;
  }
  return res;
}

//auxiliares

Lista<Actor> Pelicula::sacarActoresRepConsec(Lista<Actor> orig) {
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
  return orig;
}

Lista<Genero> Pelicula::sacarGenerosRepConsec(Lista<Genero> orig) {
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
  return orig;
  }

void Pelicula::mostrar(std::ostream& os) const {
    os << "Nombre: " << nombre_ << ", Generos: " << generos_ << ", Actores: " << actores_ << ", 3D: " << es3D_;
}

void Pelicula::guardar(std::ostream& os) const {
    int i = 0;
    string generos, actores;
    os << "P |" << nombre_ << "| ";

    while (i < generos_.longitud()) {
        os << (i == 0 ? "[" : ", ") << "|" << generoToStr(generos_.iesimo(i)) << "|";
        i++;
    }
    os << "]";

    i = 0;
    while (i < actores_.longitud()) {
        os << (i == 0 ? "[" : ", ") << "|" << actores_.iesimo(i) << "|";
        i++;
    }
    os << "]";

    os << (es3D_ ? "V" : "F");
}

void Pelicula::cargar (std::istream& is){
    char p;
    string x;
    is >> p; // P
    is >> p; // |
    getline(is,nombre_,'|'); // sacamos el 2do pipe del nombre

    // generos
    is >> p; // [
    is >> p; // si la lista es vacia es un corchete, si no, es pipe y entra al while
    while ( p == '|') {
        getline(is, x, '|');
        generos_.agregarAtras(strToGenero(x));
        is >> p; // puede ser coma o corchete
        if (p == ',') {
            is >> p; // pipe
        }
    }


    // actores
    is >> p; // [
    is >> p; // si la lista es vacia es un corchete, si no, es pipe y entra al while
    while ( p == '|') {
        getline(is, x, '|');
        actores_.agregarAtras(x);
        is >> p; // puede ser coma o corchete
        if (p == ',') {
            is >> p; // pipe
        }
    }

    is >> p; // 3d

    es3D_ = p == 'V';
}

Genero Pelicula::strToGenero(string g) const {
    Genero r;
    if (g == "Aventura") r = Aventura;
    else if (g == "Comedia") r = Comedia;
    else if (g == "Drama") r = Drama;
    else if (g == "Romantica") r = Romantica;
    else r = Terror;

    return r;
}

string Pelicula::generoToStr(Genero g) const {
    string r;
    if (g == Aventura) r = "Aventura";
    else if (g == Comedia) r = "Comedia";
    else if (g == Drama) r = "Drama";
    else if (g == Romantica) r = "Romantica";
    else r = "Terror";

    return r;
}
