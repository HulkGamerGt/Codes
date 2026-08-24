% Parte 1. Crear la base de conocimiento

pelicula(toy_story, estados_unidos).
pelicula(sherk, estados_unidos).
pelicula(machuca, chile).
pelicula(no, chile).
pelicula(el_agente_topo, chile).
pelicula(gladiador, estados_unidos).

% Parte 3. Crear una regla

pelicula_chilena(A) :-pelicula(A, chile).

% Parte 4. Modificar la base sin cambiar la regla

pelicula(cars, india).
pelicula(cars_2, chile).

% ?- pelicula_chilena(A).
% A = machuca ;
% A = no ;
% A = el_agente_topo ;
% A = cars_2.

% Parte 6. Desafío

genero(cars, animacion).
genero(no, drama).
genero(el_agente_topo, policial).
genero(toy_story, animacion).

% 67 ?- pelicula_animada(A).
% A = cars ;
% A = toy_story.

% Comprueba tu regla con al menos dos consultas: una que entregue true y otra que entregue false.

% 68 ?- pelicula_animada(no).
% false.
% 69 ?- pelicula_animada(toy_story).
% true.

pelicula_animada(A) :-genero(A, animacion).

% Parte 7. Preguntas de cierre

% 1. ¿Cuál es la diferencia entre un hecho y una regla?
%   R: Que un hecho es algo que no puede ser cambiado, es como es y no se puede modificar.
$      En cambio una regla es algo que se debe de respetar y no pasarse por encima, es el que valida
$      o impide el poder realizar algun tipo de accion en el programa

% 2. ¿Dónde se escriben los hechos y las reglas?
%   R:  Se escriben dentro de un archivo de código fuente terminada en .pl

% 3. ¿Dónde realizamos las consultas?
%   R: En mi caso desde la terminal (CMD) o tambien se puede realizar desde la aplicacion de "SWI-Prolog"

% 4. ¿Qué ventaja observas al usar una regla en vez de escribir cada conclusión como un hecho?
%   R: Que de lo que entinedo de la logica, que si en algun momento se necesita cambiar la logica del
%      programa cambiando una regla seria mas facil de automatizar un problema que hacerlo a mano cada cosa 
%      (haciendolo cada cosa a amno merefiero a hacerlo uno por uno, en cambio el otro podria hacer algun tipo)
%      (de ciclo para poder solucionar un problema                                                            )