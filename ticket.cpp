#include "ticket.h"

using namespace std;

Ticket::Ticket(const Pelicula &p, Sala s, bool u) {
  pelicula_ = p;
  sala_ = s;
  usado_ = u;
}

const Pelicula & Ticket::peliculaT() const {
  return pelicula_;
}

Sala Ticket::salaT() const {
  return sala_;
}

bool Ticket::usadoT() const {
  return usado_;
}

void Ticket::usarT() {
  usado_ = true;
}

Pelicula Ticket::peliculaMenosVistaT(const Lista<Ticket> &ts) const {
  Pelicula res = ts.iesimo(0).peliculaT();
  int i = 1
    , l = ts.longitud()
    ;
  while (i < l) {
    if (cuentaTicketsUsados(ts.iesimo(i).peliculaT(),ts) < cuentaTicketsUsados(res,ts)) {
      res = ts.iesimo(i).peliculaT();
    }
    i++;
  }
  return res;
}

bool Ticket::todosLosTicketsParaLaMismaSalaT(const Lista<Ticket> &ts) const {
  bool res = true;
  int i = 0
    , l = ts.longitud() - 1
    ;
  while (i < l && res) {
    res = ts.iesimo(i).salaT() == ts.iesimo(i+1).salaT();
  }
  return res;
}

Lista<Ticket> Ticket::cambiarSalaT(const Lista<Ticket> &ts, Sala vieja, Sala nueva) const {
  int i = 0
    , l = ts.longitud()
    ;
  Ticket nuevo = Ticket();
  Lista<Ticket> res;
  while (i < l) {
    nuevo = ts.iesimo(i);
    if (nuevo.salaT() == vieja)
      nuevo.sala_ = nueva;
    res.agregarAtras(nuevo);
    i++;
  }
  return res;
}

//######## Auxiliares #########

int cuentaTicketsUsados(Pelicula p, Lista<Ticket> ts) {
  int res = 0
    , i = 0
    , l = ts.longitud()
    ;
  while (i < l) {
    Ticket t = ts.iesimo(i);
    if ( t.peliculaT() == p && t.usadoT())
      res++;
    i++;
  }
}
