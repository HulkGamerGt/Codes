#include <stdio.h>

int Hora, Minutos, segundos ;
int Tiempo_seg = 0;
char sleep(int seconds);
int main()
{
  while (Tiempo_seg < 86400)
  {
     Hora = (Tiempo_seg / 3600);
     Minutos = (Tiempo_seg % 3600) / 60;
     segundos = (Tiempo_seg % 60);
     printf("%d:%d:%d\n", Hora, Minutos, segundos);

     Tiempo_seg = Tiempo_seg + 1;
     sleep(1);
  }
  return 0;
}