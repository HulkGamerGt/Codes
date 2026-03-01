print ("¡Bienvenido Jugador!")
nombre_jugador = input("Inserta tu nombre: ")
nombre_compañero = input("Inserta el nombre de tu compañero: ")
print("  ")
print("  ")
print ("The Path of the Arcana")
print("\n" + "="*30)
print(f"\nEstabas tranquilo en tu planeta cuando de pronto llegan invasores a atacar!, {nombre_compañero} Fue herido de gravedad.")
print(f"\nTe subes a una nave para escapar junto a {nombre_compañero}, pero un misil los intercepta y se desvian del camino")
print("cayendo en una luna cercana que posee una estacion de servicio")
print("  ")
print("  ")
print("Buscas el botiquin de la nave pero esta vacio, te colocas un traje para temperaturas bajas")
print("y sales de tu nave. Ahí en la estacion tienen un almacen con varias cosas, asi que decides preguntarle al encargado")

print("  ")
while True:

    preguntar = input("Pregunta por ('Botiquin o Reparacion')").capitalize()

    if preguntar == "Botiquin":
        print("  ")
        print("No hay botiquin :(")
        
    elif preguntar == "Reparacion":
        print("  ")
        print("¡El mecánico reparará tu nave!")
        break  

    else:
        print("\n[?] Esa opción no existe. Intenta de nuevo.")
print("  ")
print(f"\n Tu nave fue reparada!, ademas el encargado te menciono sobre un planeta que tiene lo mas avanzado en medicina y pueden curar a {nombre_compañero} por completo")


tiene_estimulante = False 

while True:
    print("\n" + "="*30)
    preguntar = input("¿Qué deseas hacer? (Explorar / Seguir): ").capitalize()

    if preguntar == "Explorar":
        print("\n[+] ¡Encontraste un estimulante entre los escombros!")
        tiene_estimulante = True 
        
    elif preguntar == "Seguir":
        
       
        if tiene_estimulante == True:
            print(f"\n[!] Durante el viaje {nombre_compañero} se debilita, pero usas el estimulante.")
            print("¡Lograste darle mas tiempo para poder llegar a tu destino.")
            break 
        else:
            print(f"\n[!] Durante el viaje {nombre_compañero} se debilita y no tienes medicina...")
            print("Tu compañero no logro resistir y ha muerton sin mas fuerzas en mitad del espacio.")
            print("GAME OVER")
            break 
            
    else:
        print("\n[?] Esa opción no existe. Intenta de nuevo.")