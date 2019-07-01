typedef struct redSubteCDT * redSubteADT;
typedef struct lineaCDT * lineaADT;
typedef struct estacionCDT * estacionADT;
typedef struct info * infoADT;

redSubteADT newRed();
void freeRed(redSubteADT r);
void pasajerosLinea(redSubteADT h);
void pasajerosPorDia(redSubteADT h);
void porcPasajeros(redSubteADT h);
void maxEst(redSubteADT h);
void agregarEstacion(infoADT e, redSubteADT red);
