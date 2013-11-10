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
    i++;
  }
  return res;
}

Lista<Ticket> Ticket::cambiarSalaT(const Lista<Ticket> &ts, Sala vieja, Sala nueva) const {
  // Estado A
  int i = 0;
  // Estado B
  // Vale i == 0
  int l = ts.longitud();
  // Estado C
  // Vale l == |ts| ^ i == i@B (l no se modifica en ningun momento, es un reemplazo sintactico y ts es const.
  // Por lo tanto, en todo momento de la ejecucion de la implementacion lo asumimos igual a |ts|)
  // Implica i == 0
  Ticket nuevo = Ticket();
  // Estado D
  // Vale i == i@C
  // Implica i == 0
  Lista<Ticket> res;
  // Estado E
  // Vale i == i@D ^ res == []
  // Implica i == 0
  // Vale Pc: i == 0 ^ res == []
  // Implica I (Pc => I)
        /* i==0  ^ l>=0 (porque l es longitud de una lista), entonces vale W. (mirar el invariante aca abajo!)
        Como res es vacia, su longitud es 0. Luego, vale X.
        Como i == 0, tanto Y como Z son 'para todo' de lista vacia, por lo tanto valen.
        Como vale W^X^Y^Z, vale I
        */
  while (i < l) {
    /* I:  W:0 <= i <= l ^ X:|res| == i ^ Y:(V j <- [0..i), sala(ts[j])! = vieja)ts[j] == res[j] ^
        Z:(V j <- [0..i), sala(ts[j]) == vieja)pelicula(res[j]) == pelicula(ts[j]) ^ usado(ts[j]) ==
        usado(res[j]) ^ sala(res[j]) == nueva
    */
    // Variante v: l-i
    // B: i < l
    // Estado W1
    // Vale I ^ B
    nuevo = ts.iesimo(i);
    // Estado W2
    // Vale res == res@W1 ^ i == i@W1 ^ nuevo == ts[i] ^ I ^ B (porque no modificamos ninguna de las variables involucradas)
    // Pif: res == res@W1 ^ i == i@W1 ^ nuevo == ts[i] ^ I ^ B
    if (nuevo.salaT() == vieja){
        //Vale sala(nuevo) == vieja ^ nuevo == nuevo@W2 == ts[i]
      nuevo.sala_ = nueva;
        //Vale sala(nuevo) == nueva
    }
    // Estado W3
    // Vale i==i@W2==i@W1 ^ res==res@W2==res@W1
    /*Vale Q: (sala(ts[i]) != vieja ^ ts[i] == nuevo) v
    (sala(ts[i]) == vieja ^ sala(nuevo)==nueva ^ pelicula(nuevo) == pelicula(ts[i]) ^ usado(nuevo)==usado(ts[i]))
    (Vale (1):no(guarda) del if y nuevo sigue siendo igual a nuevo@W2, o vale (2):la guarda del if sobre nuevo@W2 (que es
    ts@W2[i@W2], que es ts[i] porque no lo modificamos), y nuevo pasa a tener la sala 'nueva' y conserva los observadores
    Pelicula y Usado de ts[i], ya que no los modificamos.)
    Vale W (no modificamos i)
    Vale X (no modificamos res ni i)
    Vale Y (no modificamos res en las posiciones [0..i) y ts es const)
    Vale Z (idem Y)
    Vale B (idem W)
    (estos 6 son la postcondicion del if, los separamos para mayor claridad)
    */
    res.agregarAtras(nuevo);
    // Estado W4
    // Vale res == res@W3 ++ [nuevo]
    // Vale i == i@w3 == i@w1
    // Vale Q (no modificamos nuevo ni ts)
    // Vale W ^ Y ^ Z
    // Vale |res| == |res@W3|+1 == i@W3 +1 == i@W1 +1
    // Implica res[i] == nuevo
    /* Implica (V j <- [0..i+1), sala(ts[j])! = vieja)ts[j] == res[j] ^
        (V j <- [0..i+1), sala(ts[j]) == vieja)pelicula(res[j]) == pelicula(ts[j]) ^ usado(ts[j]) ==
        usado(res[j]) ^ sala(res[j]) == nueva
        Porque valen Y y Z, y por Q, si sala(ts[i])==vieja, entonces pelicula(ts[i])== pelicula(nuevo) ==
        pelicula(res[i]), idem con usado, y nueva==sala(res[i]). Si, en cambio, sala(ts[i])!=vieja, entonces res[i] ==
        nuevo == ts[i]. Luego, tanto Y como Z valen para j tomado de [0..i+1)
    */
    i++;
    // Estado W5
    // Vale i==i@W4 + 1 ^ res == res@W4
    // Implica W (pues i era mayor a 0 y lo incrementamos, y era menor estricto que l y lo incrementamos en solo una unidad)
    // Implica X (pues |res| == |res@W4| == |res@W1| + 1 == i@W1 + 1 == i@W4 + 1 == i@W5)
    // Implica Y (porque su condicion valia hasta i@W1+1(ultimo comentario de W4), y por lo tanto vale hasta i@W5)
    // Implica Z (Idem Y)
    // Implica I (W^X^Y^Z)  (I^B (cuerpo) I ==> el cuerpo del ciclo preserva el invariante!)

    // El Variante decrece: v@W5 == l-i@W5 == l-(i@w1+1) == l-i@W1 -1 == v@w1-1 < v@w1
  }
    /*Qc: |res| == |ts| ^ (V j <- [0..|ts|), sala(ts[j])! = vieja)ts[j] == res[j] ^
         (V j <- [0..|ts|), sala(ts[j]) == vieja)pelicula(res[j]) == pelicula(ts[j]) ^ usado(ts[j]) ==
usado(res[j]) ^ sala(res[j]) == nueva
    */

    /*I^no(B) => Qc
        Porque no(B)== (i>=l) y W== (i<=l) implican i==l. Y por X, i==|res|. Luego, |res| == l == |ts|
        Como i == |ts|, por Y y Z del invariante vale el resto de Qc: (V j <- [0..|ts|), sala(ts[j])! = vieja)ts[j] ==
          res[j] ^ (V j <- [0..|ts|), sala(ts[j]) == vieja)pelicula(res[j]) == pelicula(ts[j]) ^ usado(ts[j]) ==
          usado(res[j]) ^ sala(res[j]) == nueva
     Por lo tanto, I ^ no(B) implica Qc. Wi! El ciclo es correcto!
    */
    //Tomamos cota c == 0. v<=c implica no(B) (l-i<=0 se traduce en l<=i, que es exactamente no(B)).
    //Como se cumplen las 5 condiciones, el ciclo termina y es correcto. Y somos felices.
  return res;
  // Estado Final
  // Vale Qc (no hay cambios en ninguna variable)
  // Implica mismaCantidad  (ya que |res| == |ts|)
  // Implica noCambianLosDeLaSalaNoVieja ^ losDeSalaViejaCambianSoloLaSala (son identicos a "el resto de Qc")

}

void Ticket::mostrar(std::ostream& os) const {
    os << "Pelicula: ";
    pelicula_.mostrar(os);
    os << ", Sala: " << sala_ << ", Usado: " << usado_;
}

void Ticket::guardar(std::ostream& os) const {
    os << "T (";
    pelicula_.guardar(os);
    os << ") " << sala_ << " " << (usado_? "V" : "F");
}

void Ticket::cargar (std::istream& is) {
    char p;

    is >> p; // P
    is >> p; // (
    pelicula_.cargar(is);
    is >> p; // )
    is >> sala_;
    is >> p; // usado
    usado_ = p == 'V';
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
  return res;
}
