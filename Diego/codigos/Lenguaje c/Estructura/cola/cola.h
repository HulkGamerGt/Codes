struct Nodo {
    int info;
    struct Nodo * sig;
};

typedef struct Nodo * TipoCola;

extern TipoCola cola_vacia(void);
extern int es_cola_vacia(TipoCola cola);
extern TipoCola inserta_por_cabeza(TipoCola cola, int valor );
extern TipoCola inserta_por_cola(TipoCola cola, int valor );
extern TipoCola borra_cabeza(TipoCola cola);
extern TipoCola borra_cola(TipoCola cola);
extern int longitud_cola(TipoCola cola);
extern void muestra_cola(TipoCola cola);
extern int pertenece(TipoCola cola, int valor );
extern TipoCola borra_primera_ocurrencia(TipoCola cola, int valor );
extern TipoCola borra_valor (TipoCola cola, int valor );
extern TipoCola inserta_en_posicion(TipoCola cola, int pos, int valor );
extern TipoCola inserta_en_orden(TipoCola cola, int valor );
extern TipoCola concatena_colas(TipoCola a, TipoCola b);
extern TipoCola libera_cola(TipoCola cola);
