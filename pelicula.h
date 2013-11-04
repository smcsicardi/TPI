#ifndef PELICULA_H_
#define PELICULA_H_

#include "lista.h"
#include "tipos.h"
#include <utility>

class Pelicula {
 public:
  Pelicula(){}
  Pelicula(Nombre n, Lista<Genero> gs, Lista<Actor> as, bool b);
  string nombreP() const;
  Lista<Genero> generosP() const;
  Lista<Actor> actoresP() const;
  bool es3DP() const;
  Lista<std::pair<Genero,Lista<Pelicula> > > agruparPelisPorGeneroP(Lista<Pelicula> ps) const;
  Lista<Pelicula> generarSagaDePeliculasP(Lista<Actor> as, Lista<Genero> gs, Lista<Nombre> nombres) const;


  bool operator==(const Pelicula &otraPeli) const {
      return nombre_ == otraPeli.nombre && generos_ == otraPeli.generos_ && actores_ == otraPeli.actores_;
  }

  void mostrar(std::ostream& os) const;
  void guardar(std::ostream& os) const;
  void cargar (std::istream& is);

 private:
  Nombre nombre_;
  Lista<Genero> generos_;
  Lista<Actor> actores_;
  bool es3D_;
};


//ERROR ERROR ERROR ERROR ERROR ERROR ERROR ERROR ERROR
// Acordemosnos de preguntar si esto se puede. Marto puto ERROR ERROR ERROR ERROR

void sacarActoresRepConsec(Lista<string> orig);
void sacarGenerosRepConsec(Lista<Genero> orig);

std::ostream & operator<<(std::ostream & os,const Pelicula & p);
std::istream & operator>>(std::istream & is, Pelicula & p);

#endif // PELICULA_H_
