#ifndef __redSubteADT_h_
  #define __redSubteADT_h_
  typedef struct redSubteCDT * redSubteADT;
  typedef struct lineaCDT * lineaADT;
  typedef struct estacionCDT * estacionADT;
  typedef struct info * infoADT;

  redSubteADT newRed();
  void freeRed(redSubteADT r);
  void pasajerosLinea(redSubteADT h);                           // Crea archivo query1.csv con los resultados. Cantidad total de pasajeros por línea de subte con 1+ movimientos.
  void pasajerosPorDia(redSubteADT h);                          // Crea archivo query2.csv con los resultados. Pasajeros por día de semana y período de día (diurno/nocturno).
  void porcPasajeros(redSubteADT h);                            // Crea archivo query3.csv con los resultados. Cantidad de pasajeros en cada línea de subte respecto del total de usuarios.
  void maxEst(redSubteADT h);                                   // Crea archivo query4.csv con los resultados. De cada línea de subte, la estación más concurrida.
  void agregarEstacion(infoADT e, redSubteADT red);
#endif
