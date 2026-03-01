print ("¡Bienvenido Jugador!")
nombre_jugador = input("Inserta tu nombre: ")
nombre_compañero = input("Inserta el nombre de tu compañero: ")
print

import time
import sys

print("\n" + "="*110)
arcana_art = r"""



                                             ████████╗██╗░░██╗███████╗
                                             ╚══██╔══╝██║░░██║██╔════╝
                                             ░░░██║░░░███████║█████╗░░
                                             ░░░██║░░░██╔══██║██╔══╝░░
                                             ░░░██║░░░██║░░██║███████╗
                                             ░░░╚═╝░░░╚═╝░░╚═╝╚══════╝

                                ██████╗░░█████╗░████████╗██╗░░██╗  ░█████╗░███████╗
                                ██╔══██╗██╔══██╗╚══██╔══╝██║░░██║  ██╔══██╗██╔════╝
                                ██████╔╝███████║░░░██║░░░███████║  ██║░░██║█████╗░░
                                ██╔═══╝░██╔══██║░░░██║░░░██╔══██║  ██║░░██║██╔══╝░░
                                ██║░░░░░██║░░██║░░░██║░░░██║░░██║  ╚█████╔╝██║░░░░░
                                ╚═╝░░░░░╚═╝░░╚═╝░░░╚═╝░░░╚═╝░░╚═╝  ░╚════╝░╚═╝░░░░░

                    ████████╗██╗░░██╗███████╗  ░█████╗░██████╗░░█████╗░░█████╗░███╗░░██╗░█████╗░
                    ╚══██╔══╝██║░░██║██╔════╝  ██╔══██╗██╔══██╗██╔══██╗██╔══██╗████╗░██║██╔══██╗
                    ░░░██║░░░███████║█████╗░░  ███████║██████╔╝██║░░╚═╝███████║██╔██╗██║███████║
                    ░░░██║░░░██╔══██║██╔══╝░░  ██╔══██║██╔══██╗██║░░██╗██╔══██║██║╚████║██╔══██║
                    ░░░██║░░░██║░░██║███████╗  ██║░░██║██║░░██║╚█████╔╝██║░░██║██║░╚███║██║░░██║
                    ░░░╚═╝░░░╚═╝░░╚═╝╚══════╝  ╚═╝░░╚═╝╚═╝░░╚═╝░╚════╝░╚═╝░░╚═╝╚═╝░░╚══╝╚═╝░░╚═╝

"""
def print_slow(text, speed=0.001):
    for char in text:
        sys.stdout.write(char)
        sys.stdout.flush()
        time.sleep(speed)

print_slow(arcana_art)
print("  ")
print("\n" + "="*110)
print("  ")
while True:

    preguntar = input(" ¿Comenzar Juego? ('Si o No') ").capitalize()

    if preguntar == "No":
        print("  ")
        print("\033[31m                  🤬 ¡PUES QUE TE JODAN¡ 🤬\033[0m")
        print("  ")
    elif preguntar == "Si":
        print("  ")
        print("\033[33m                     ✩ ¡GENIAL!✩\033[0m")
        break  

    else:
        print("\n\033[1;35m[?]\033[0m Esa opción no existe. Intenta de nuevo.")

import time
import sys

def narrar(texto):
    for letra in texto:
        sys.stdout.write(letra)
        sys.stdout.flush()
        time.sleep(0.04) 
    print()


narrar(f"\n\033[36m[>]\033[0m Era un dia como cualquier otro en elmplaneta ... disfrutabas de la tarde, el sol se escondia bajo las montañas en un fascinante atardecer")
narrar("poco despues el cielo estaba completamente oscuro, pero unas luces en cielo comenzaron a hacercarse cada vez más, acompañado de un temblor.")
narrar(f"\nLas luces terminan de bajar y te das cuenta que son naves extraterrestres.Las demas personas se quedan viendo pero \033[36m{nombre_compañero}\033[0m y tu huyen")
narrar("lejos de ese lugar. Mientras corren escuchan disparos de blaster, explosiones y gritos de desesperacion")
print("  ")
narrar("Logran ocultarse detras de un auto y observan sin poder hacer nada...")
print("  ")
print("\n" + "="*110)
arcana_art = r""" 
⠀⠀⢀⣀⣀⣀⣀⣾⡯⠽⣍⠐⠓⢶⣶⣚⣒⠲⠶⢖⣂⠤⣄⣀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣠⡤⠤⠤⣀⣀⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⢰⣊⣋⣉⣏⠭⠉⠉⢁⣀⣈⣉⣈⣀⠉⢹⣉⣒⣤⠀⠀⠤⠉⠲⠬⡉⠲⢤⠤⢄⣀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⡠⠖⠒⠒⡲⠤⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⡴⢖⡛⢋⡉⠭⠠⠛⢀⣉⠘⣋⣒⡤⣄⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠉⠉⠛⠫⢭⡥⠶⠶⢖⣲⣾⣎⠄⠋⣛⣿⠀⣀⣁⡤⣀⠒⣒⠒⠚⠛⠛⠓⠤⠤⠉⣴⣦⣀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣾⢠⣀⣀⣠⠃⠠⠽⣄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠉⠓⠚⢟⣻⡧⣖⣦⣆⣢⠽⡶⠶⠚⠉⠉⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠙⠱⣄⣂⠕⠂⠠⠤⡤⠉⣉⡁⠛⠒⠒⠒⣒⣒⠒⢖⡛⠉⠙⠓⠶⠶⠒⠀⠺⢗⠤⣄⡀⠀⠀⠀⠀⠀⠀⠀⢠⢻⢇⣇⢀⣨⡤⢛⣆⢸⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠐⠈⠻⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠘⠳⠴⢒⣠⣮⣄⡠⣒⣁⣭⣿⣯⣽⣤⣤⣤⡤⢬⠾⣉⡉⠱⣶⣶⡶⠚⠛⠂⠉⠁⠀⠀⠀⠀⠀⠀⠀⠀⢿⡗⢮⠽⠖⡖⠁⣿⣯⣀⢀⣖⣲⣒⣦⢄⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⠘⠀⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠁⠉⠉⠉⠉⠉⠙⠚⠛⠛⠋⠈⠁⠉⠉⠉⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡹⣆⢃⠀⠃⣼⢞⡥⣿⠋⢀⠤⠤⣄⠉⠙⠢⡄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢠⠀⠀⠃⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⢴⣒⣟⣱⠾⠿⠿⢿⣿⠯⠔⢯⡉⠁⠀⠀⠈⠓⠠⠤⣸⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡄⠀⠀⢸⠀⠀⠀⠀⢀⠴⠒⢒⠶⢄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢠⠋⢠⡏⣡⠛⠣⡝⠋⠁⠀⢀⡠⠊⢷⣀⣠⡴⡖⠛⠛⠲⣦⡷⡄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠘⠀⠀⠀⢀⡟⠀⠀⡌⢀⡜⢧⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡼⢀⣾⠢⡀⠀⢠⠀⠀⣀⠔⠁⠀⠀⢀⢿⡁⠀⠸⡀⠀⠀⢸⢷⡙⢦⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠆⠀⠀⠈⢷⣳⠶⡯⠃⣧⣿⡀⢀⣀⣀⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠷⡏⢻⠀⠈⣢⣜⡓⠶⢥⣀⣀⣀⡴⠃⠈⣇⢀⢖⣻⣷⡲⢬⡀⠳⣄⠨⣷⠦⠄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣀⣀⣨⣾⡆⣡⢮⣜⡿⡟⠉⣠⠐⠛⠣⣄⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣀⣀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡇⠘⡗⡎⠁⠤⠤⠤⠄⢀⠏⢨⠛⠢⢄⣨⠟⠋⣁⣀⡜⠉⠹⡄⠈⠳⡌⠓⢤⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢠⢿⢍⠓⣭⣿⣟⠛⠉⡩⠓⠳⡜⠀⠑⠂⠀⠚⡆⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⣥⠗⡄⢱⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣰⠓⠒⢻⡘⡀⠀⠀⣀⡀⢸⡠⠃⠀⣀⣠⡿⢒⠋⠀⠀⢱⢠⣀⡷⠀⠀⠙⠢⣄⠾⡷⠂⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣯⢵⣵⢞⠻⣏⡪⣝⠥⡀⠀⠀⢘⡖⠤⡔⠒⠺⡞⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⣀⠴⠶⡒⢲⣿⡿⠫⢾⡿⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⠴⠚⠯⣵⣖⡒⣷⡅⢋⠉⠉⡇⠀⢨⢋⣉⣠⢤⠇⠌⠀⠀⡐⠁⢩⠟⠈⢆⠀⠀⠀⠙⢇⡙⠢⣄⠀⠀⠀⠀⠀⠀⠀⢀⡴⠾⢿⡷⠾⡿⢄⡉⠢⣕⡾⣦⡖⠁⢹⡀⡸⣄⣀⡇⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⢴⣃⡤⠂⡹⠖⠻⢟⣛⠾⡝⠱⡄⢀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⡏⠀⡤⠤⡄⢳⠋⣽⢷⠼⠤⠤⢷⠶⠓⢺⠀⣠⠾⠭⣄⡀⠸⡀⣠⠏⠀⡄⠀⠣⡀⠀⠀⠀⠱⢄⠀⠙⢦⠀⠀⠀⠀⢰⠧⠄⠐⠿⣄⠩⣪⣷⣷⣦⣟⠉⠢⢝⢻⣲⣿⡛⠛⠛⢽⢢⠀⠀⠀⠀⠀⠀
⠀⠀⣠⠃⢀⣨⡽⡁⠀⢀⣀⡇⠀⢹⠞⢳⣿⣿⣯⣐⣢⣄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡜⢀⠜⢀⠔⣇⣼⠀⣧⢸⡆⠀⠀⠸⡄⢀⣸⡾⠓⠖⢢⠄⡙⣦⠟⠁⠀⠀⠈⢆⠀⠹⡄⠀⠀⠀⠀⠱⡄⠈⢧⡀⠀⠀⠘⠶⣢⡤⠾⠋⣿⠋⠀⣽⡇⡏⣿⣟⢺⢿⣻⣛⢧⣤⠐⢺⡸⠀⠀⠀⠀⠀⠀
⢀⠞⡹⢭⡷⢏⠀⠘⣴⠋⠤⢼⣦⠞⢥⡞⣽⠿⠏⠙⠚⠛⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣜⣉⣁⡀⣧⡞⠁⢸⣴⣿⡏⠓⠛⠋⠉⠉⢩⣟⡇⢸⠤⣇⣰⢉⣓⣤⡀⠀⠀⠀⠈⢦⠀⠈⠢⡀⠀⠀⠀⠈⠲⡒⠛⠓⠀⠀⠀⠀⠀⠀⡤⢼⣉⣸⣸⣇⣉⣠⠽⢦⣧⣿⣄⣷⠿⡙⢭⡀⠀⠀⠀⠀⠀⠀
⢸⠉⡖⡼⢁⣸⠤⣹⠈⡐⢒⢾⠇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢠⠏⠉⡍⢻⠋⠀⢀⡰⠋⠙⢸⡀⠀⠀⢀⣶⢿⣿⡟⠿⡻⠻⠿⣯⡀⠈⠙⢵⣄⠀⠀⠈⠳⡀⠀⠈⠢⡈⢢⡀⠀⠹⣄⠀⠀⠀⠀⠀⠀⠠⠇⢚⠀⡇⠀⠀⡷⠋⠉⢉⣟⣿⣿⠋⠳⣄⡑⢬⣷⠀⠀⠀⠀⠀
⠸⡴⢤⡁⡜⡆⠀⣏⢹⠁⠘⡞⣷⠀⠀⠀⠀⠀⠀⢀⠔⠊⢍⡓⢦⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣿⡀⡿⣏⡸⠀⢠⠞⠉⠉⡆⠑⢷⡀⣴⣟⣽⡋⠁⠤⣲⠏⠀⠀⠀⣳⣄⠀⠀⠙⣢⠀⠀⠀⠙⠂⢀⡀⠹⡦⢭⣦⡀⠈⣧⠀⠀⠀⠀⠀⠀⣷⣯⣏⠉⠉⠹⡥⠴⠊⠀⢹⠚⣷⣀⠀⢨⠿⣍⡉⠀⠀⠀⠀⠀
⠀⣇⢠⣾⣜⡙⠛⠼⡏⠉⠉⣽⣼⠀⠀⠀⠀⠀⢰⡋⠀⠠⣦⣼⣾⣷⣄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⣿⠛⠉⢷⣄⡎⠀⠀⡰⢁⣠⡴⠛⠓⣾⡿⠃⠀⠀⢠⢰⡐⣔⢢⣽⣧⣵⡄⠀⠘⣇⠀⢀⠀⠀⠨⡏⠑⠚⠀⠀⠘⠲⣜⢦⡀⠀⠀⢠⠋⢉⠦⡘⣆⠀⠀⣧⡄⠰⠶⠀⢹⣯⡏⠙⢥⡚⠀⠉⠒⢤⡀⠀⠀
⠀⠀⠁⢀⡏⢹⠒⢠⢹⣤⡜⣁⠧⠱⡀⠀⠀⠀⠘⣿⣘⠶⢵⠟⠛⣮⢧⠤⡄⣀⡀⠀⠀⠀⠀⠀⠀⣰⡇⠀⠀⢠⠞⠛⢓⠾⠛⠊⢁⡀⠤⣴⢿⡿⣠⠆⣧⡾⠋⠉⠚⢿⡻⡿⣗⣿⡿⡛⠛⠒⠮⢿⣒⡒⠼⣦⡀⠀⠀⠀⠀⠀⠉⠛⠦⠀⣼⢀⡌⠀⠀⠉⢓⣯⣹⣦⣴⣬⠃⠀⣿⡹⡒⡶⢷⡀⠀⠐⢄⠈⢢⠀
⠀⠀⠀⠸⣄⡸⠀⣌⡞⢳⣄⣀⠀⠓⢣⠀⠀⠀⠀⠉⡿⠧⣄⠄⣰⣟⡼⠘⡄⠀⠈⠒⢄⠀⠀⠀⢠⡟⠀⠀⢀⡼⢵⣒⣇⠀⠀⠀⠀⣀⣶⠃⠈⠙⠟⢿⣁⡁⣠⡴⠂⢈⣿⢀⣇⢸⡝⢱⠂⠤⣀⠀⠀⠉⡑⢦⡀⠀⠀⠀⠀⠀⠀⠀⠀⢀⡏⠀⠀⠀⠀⠤⡞⠉⡷⡧⣉⣀⣴⡪⢯⠧⡟⡀⠜⡟⢦⣄⡀⠁⢈⠇
⠀⠀⠀⠀⣷⠕⠲⢤⠇⠀⠉⢆⠂⣀⠜⢦⠀⠀⠀⠀⠳⣀⡼⡟⠛⠉⢱⠀⠳⣤⣀⡀⠀⢱⠀⢀⣾⠁⢀⣀⣞⡀⠀⢸⠸⠊⠳⣠⠞⠁⢹⣆⠀⠀⠀⡞⡙⢷⢀⣄⣤⣘⣾⠏⢀⠇⣷⠈⢆⠀⠀⠈⢰⠊⠤⠭⠟⠢⡀⠀⠀⠀⠀⠀⠀⡸⠶⢦⡀⠀⢀⢼⠀⢸⠛⢶⡗⠯⠭⠔⢻⣶⠃⡇⢣⣇⢌⡲⠬⣾⠃⠀
⠀⠀⢀⠔⢻⠀⢀⠟⠀⠀⠀⢈⠿⢥⡇⢸⠀⠀⠀⠀⠀⠈⢹⠈⠒⠂⠁⠀⠀⠀⠀⢏⡠⠃⢀⡾⠁⠀⢸⠀⠀⠉⢹⡘⠋⢓⡶⠁⠀⠀⠀⠻⢣⣄⠀⣧⠈⢣⡹⣿⣤⠾⣥⡶⠃⢠⡏⢷⠾⡂⢠⠀⡆⢀⠀⠀⢀⠜⠹⣵⢦⠀⠀⠀⢰⠁⠀⢠⠓⢢⠞⣼⠫⢾⠀⢸⡙⢆⠀⡰⠃⣿⠀⠡⠀⠙⠒⢾⠋⠁⠀⠀
⠀⠀⢸⢀⢤⣉⢹⠀⠀⠀⠀⢾⠀⢀⣌⣽⠀⠀⠀⠀⠀⠀⠈⠓⠤⣤⠀⠒⠲⣇⣀⠘⣆⡴⠟⠁⠀⠀⢸⡀⠀⠀⠀⣯⠩⠤⢧⠀⠀⠀⠀⠀⠀⠙⠙⢞⢾⡀⠓⣏⢯⠑⠀⢻⡄⢳⠁⡴⠃⠀⠀⠣⣇⣸⠀⠀⠈⠀⢀⠟⠀⡗⣄⠀⢸⢆⣠⠜⠒⡻⣄⠟⢆⡢⣇⠸⣇⠀⠛⠀⢸⡏⠀⠀⠀⠀⡰⢸⡀⠀⠀⠀
⠀⠀⠸⠈⠀⢀⠎⠀⠀⠀⠀⠘⡦⢀⠀⡇⠀⠀⠀⠀⠀⠀⠀⠀⣰⣝⣂⣄⣒⣊⣉⠭⢿⡀⠀⠀⠀⠀⢀⣧⣀⣠⠎⠀⡠⠂⣸⠀⠀⠀⠀⠀⠀⠀⠀⠈⣿⢷⡀⢱⠉⠳⢄⢧⣼⡏⡰⠠⠤⠄⠒⠊⢙⡯⣍⣁⣀⣠⡮⢂⡼⠁⠘⡆⢸⠒⠒⠠⠊⢀⣯⠶⢤⣒⣻⡆⢻⣄⠀⣀⣾⠁⠀⠀⠀⠔⠁⠀⣇⠀⠀⠀
⠀⠀⡧⣗⣢⠞⠀⠀⠀⠀⠀⠀⡇⠘⢖⣇⠀⠀⠀⠀⣀⠔⠚⠉⠀⢝⢑⣺⠽⠓⠢⢄⠀⣇⠀⠀⠀⠀⠸⡇⠀⠀⢠⠊⠀⡠⡿⠀⠀⠀⠀⠀⠀⠀⠀⠀⠉⠀⠙⣮⡗⠤⣈⠣⢿⡤⠁⠘⡤⠀⠒⠊⡇⢰⡜⢙⢿⣗⡚⠋⠀⣠⠚⠀⢸⠀⠀⡇⣰⠏⡽⠀⠀⢀⡇⢧⠀⠈⠛⠋⠀⠀⠀⠀⠀⠀⠀⢰⢸⡄⠀⠀
⠀⢠⠏⠠⠌⢧⠀⠀⠀⠀⠀⢀⡏⢒⡥⠌⠢⡄⢀⠜⠁⠀⠀⠀⢀⡴⠉⠀⠀⢀⡀⠀⢀⣏⣳⠀⠀⠀⠀⡇⠀⠀⡌⢠⠊⡴⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠸⡿⣄⠠⢍⣈⢻⣦⠤⠴⣀⡀⠤⠒⠉⢀⠞⢸⢹⣤⢤⡎⠀⠀⠀⣸⣀⡠⠃⢸⠀⡇⠀⢀⡜⠀⣏⣣⠑⠂⠤⠤⠤⠤⠔⠊⣁⠊⠁⠀⡇⠀⠀
⠀⠈⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠁⡇⠀⠑⠤⠠⣤⡎⠀⠀⠀⢀⡠⢽⢖⠛⡄⠛⢦⡀⠀⢠⡇⠀⠀⠃⡌⣸⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢣⠘⣷⠤⠄⠀⡹⢷⣤⡤⠐⠂⡁⠔⠉⢀⠀⣸⣽⣿⠃⠀⠀⣠⠗⠒⢤⣠⢼⣴⣓⡒⣾⠴⠚⠛⠭⣉⣐⠒⠒⣒⠲⠏⠉⠉⠉⠀⢼⠁⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠤⠽⠦⠤⠶⠿⠿⠷⠤⠤⠤⠥⠶⠚⠳⠞⠓⠚⠛⠁⢀⠼⠀⠠⢼⠀⠃⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣼⣴⣍⡗⠢⠤⣀⣀⣈⣙⣳⠶⠶⢶⣾⠟⢛⡩⢧⠘⣧⡀⣎⣁⣉⣀⣀⣦⣴⡋⢀⠈⡣⠀⠀⠂⢄⣀⠀⠉⣩⠔⠊⠉⢩⠿⢍⡒⣌⡇⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢰⡷⠶⢤⣄⢀⢙⡦⢷⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⠴⠊⠁⠫⣒⠽⢆⣀⣈⡄⠀⠀⠀⠤⠒⢉⣔⣊⣁⣀⠀⢷⠈⢷⡀⠈⠉⠁⠀⢸⣷⢱⠙⠊⠁⠀⠒⠠⠤⣀⡈⢠⠏⡀⠀⠀⠫⣄⡀⢩⣹⢇⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⡴⠪⠤⢄⣀⡹⠚⡇⠀⢸⡀⠀⠀⠀⠀⠀⠀⠀⠀⢀⡴⠊⠁⠀⠀⠀⠄⣀⠑⠢⡑⠠⠛⡄⠠⢄⣶⠿⠍⠉⠠⡉⠙⢍⣻⠆⠈⠻⣦⡀⠀⠀⠀⢻⠋⠀⠀⠒⡲⡶⢒⠒⢲⢻⡟⠁⠀⠀⠀⠀⢀⣨⡿⢇⠘⡄⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⡏⠓⠠⠤⠐⠊⢡⣠⣤⣧⣠⡴⠇⠀⠀⠀⠀⠀⠀⢀⡴⠋⠀⠀⠀⠀⠀⠀⠀⠀⠉⠑⠮⣕⡀⠑⢚⣉⠀⠀⠀⠀⠀⠀⡱⢄⢻⠙⣆⠀⠈⠻⣦⣀⠐⠚⠓⠶⠤⠴⠾⠶⠿⠚⠓⢾⣇⡀⠀⠀⠈⠉⢁⣨⣃⣼⠴⠇⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠐⠛⠛⠒⠒⠒⠒⠒⠋⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢠⠋⡀⠀⠀⠀⠀⠀⠉⠉⠉⠉⠉⣉⡽⢾⠛⢲⠥⢄⡀⠀⠀⠀⠀⡰⠁⢀⣿⠑⡘⠦⡀⠀⠀⠙⠳⣦⣀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠉⠉⠉⠋⠉⠉⠉⠉⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢿⠀⠈⠀⢄⠀⠀⠀⣠⡶⠒⢛⠋⢁⠄⣸⠀⢸⣆⠀⠀⠀⠀⠀⣔⡀⢤⡞⠋⢢⢱⠀⠘⡆⠀⠀⠀⠀⠑⠓⢖⣤⣀⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣠⣤⣬⣦⣀⠐⢂⠬⠒⢊⣕⣡⣴⣷⣶⣿⣿⣿⣿⣿⡇⠀⠀⠀⠀⠀⠀⣠⠇⡇⣰⣿⣾⠶⠾⠶⠶⠤⠀⠀⠀⠀⠀⠀⠁⠛⠻⠶⠶⠶⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠀⠀⠀⠀⠀⠀⠀⠀⠻⢷⣤⣄⣀⣀⣒⣉⣤⣾⠟⠉⠉⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠉⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
""" 
def print_slow(text, speed=0.0001):
    for char in text:
        sys.stdout.write(char)
        sys.stdout.flush()
        time.sleep(speed)

print_slow(arcana_art)
print("  ")
print("\n" + "="*110)

import time
import sys

def narrar(texto):
    for letra in texto:
        sys.stdout.write(letra)
        sys.stdout.flush()
        time.sleep(0.04) 
    print()




narrar(f"\nTe subes a una nave para escapar junto a \033[36m{nombre_compañero}\033[0m, pero un misil los intercepta y se desvían del camino")
narrar("cayendo en una luna cercana que posee una estación de servicio...")

print("\n") 

narrar("Buscas el botiquín de la nave pero está vacío, te colocas un traje para temperaturas bajas")
narrar("y sales de tu nave. Ahí en la estación tienen un almacén con varias cosas, así que decides preguntarle al encargado.")

print("  ")
while True:

    preguntar = input("\033[33m Pregunta por ('Botiquin o Reparacion'):\033[0m ").capitalize()

    if preguntar == "Botiquin":
        print("  ")
        narrar("\033[31m[-]\033[0mNo hay botiquin :(")
        print("  ")
    elif preguntar == "Reparacion":
        print("  ")
        narrar("\033[92m[+]\033[0m¡El mecánico reparará tu nave!")
        narrar(f"\n\033[92m[+]\033[0mTu nave fue reparada!, ademas el encargado te menciono sobre un planeta que tiene lo mas avanzado en medicina y pueden curar a \033[36m{nombre_compañero}\033[0m por completo")

        break  

    else:
        print("  ")
        narrar("\n\033[1;35m[?]\033[0m Esa opción no existe. Intenta de nuevo.")
print("  ")

print("\n" + "="*110)
tiene_estimulante = False 

while True:
    
    preguntar = input("\033[33m ¿Qué deseas hacer? (Explorar / Seguir):\033[0m  ").capitalize()

    if preguntar == "Explorar":
        narrar("\n\033[92m[+]\033[0m¡Encontraste un estimulante entre los escombros!")
        print("  ")
        tiene_estimulante = True 
        
    elif preguntar == "Seguir":
        
       
        if tiene_estimulante == True:
            narrar(f"\n\033[92m[!]\033[0mDurante el viaje \033[36m{nombre_compañero}\033[0m se debilita, pero usas el estimulante.")
            narrar("\033[92m[+]\033[0m¡Lograste darle mas tiempo para poder llegar a tu destino.")
            break 
        else:
            narrar(f"\n\033[31m[!]\033[0mDurante el viaje \033[36m{nombre_compañero}\033[0m se debilita y no tienes medicina...")
            narrar("\033[31m[-]\033[0mTu compañero no logro resistir y ha muerton sin mas fuerzas en mitad del espacio.")
            print("  ")
            narrar("\033[31mGAME OVER\033[0m")
            break 
            
    else:
        print("  ")
        narrar("\n\033[1;35m[?]\033[0m Esa opción no existe. Intenta de nuevo.")

print("\n" + "="*110)
print("  ")
narrar("En camino al planeta, revisas el mapa de coordenadas viendo que aun faltan unas cuantas UA (Unidad Astronomica) para llegar")
narrar("\033[31m[!]\033[0m De pronto sientes un estruendo en la nave... ¡Has sido abordado por piratas espaciales, debes actuar rapido!")

print("  ")
narrar(f"\n\033[36m[>]{nombre_jugador}\033[0m:¡Necesito algo para defenderme!")
print("  ")
while True:
    
    preguntar = input("Buscar en (Almacen / Maleta): ").capitalize()

    if preguntar == "Almacen":
        print("  ")
        narrar("\n\033[31m[!]\033[0m ¡En el almacen te topastee con los piratas!")
        
    elif preguntar == "Maleta":
        print("  ")
        narrar("\n\033[92m[+]\033[0m ¡En la maleta encontrazte una llave inglesa!")
        break  

    else:
        print("  ")
        narrar("\n\033[1;35m[?]\033[0m Esa opción no existe. Intenta de nuevo.")

