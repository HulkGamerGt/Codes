"""
Genera el grafico del circuito TSP del Ejercicio 2 (Prueba 1, alpha=0.3,
200 iteraciones) a partir de los datos REALES producidos por la ejecucion
del programa en C (grafo_ejercicio2.csv y resultado_ejercicio2.txt).
"""
import csv
import re
import matplotlib.pyplot as plt
from matplotlib.lines import Line2D

RUTA_CSV = "/home/claude/proyecto_grafos/resultados/grafo_ejercicio2.csv"
RUTA_TXT = "/home/claude/proyecto_grafos/resultados/resultado_ejercicio2.txt"

# --------- 1. Leer nodos reales (id, nombre, lat, lon) desde el CSV ---------
nodos_por_nombre = {}   # nombre -> (id, lat, lon)
nodos_por_id = {}       # id -> (nombre, lat, lon)
with open(RUTA_CSV, encoding="utf-8") as f:
    lector = csv.reader(f)
    next(lector)
    for fila in lector:
        if len(fila) < 4:
            break
        id_nodo, nombre, lat, lon = fila
        id_nodo = int(id_nodo)
        nodos_por_nombre[nombre] = (id_nodo, float(lat), float(lon))
        nodos_por_id[id_nodo] = (nombre, float(lat), float(lon))

# --------- 2. Definir las 5 zonas segun el orden real de carga (10 nodos c/u) ---
# El programa main_ejercicio2.c carga, en este orden exacto: Zona 0 (Centro/UCM,
# ids 0-9), Zona 1 (Sur, ids 10-19), Zona 2 (Norte, ids 20-29),
# Zona 3 (Oriente, ids 30-39), Zona 4 (Poniente, ids 40-49).
zona_de_id = {}
nombres_zona = {
    0: "Zona 0 - Centro/UCM",
    1: "Zona 1 - Sur/Universidad de Talca",
    2: "Zona 2 - Norte/Terminal",
    3: "Zona 3 - Oriente/Mall",
    4: "Zona 4 - Poniente",
}
for id_nodo in nodos_por_id:
    zona_de_id[id_nodo] = id_nodo // 10

colores_zona = {
    0: "#4C72B0",  # azul
    1: "#55A868",  # verde
    2: "#DD8452",  # naranjo
    3: "#8172B2",  # morado
    4: "#C44E52",  # rojo
}

# --------- 3. Leer el circuito real de la Prueba 1 (orden de nombres visitados) ---
with open(RUTA_TXT, encoding="utf-8") as f:
    contenido = f.read()

bloque = contenido.split("PRUEBA 1: GRASP")[1]
bloque = bloque.split("--- Circuito GRASP (TSP) ---")[1]
bloque = bloque.split("Distancia total del circuito:")[0]

distancia_match = re.search(r"Distancia total del circuito:\s*([\d.]+) km",
                             contenido.split("PRUEBA 1: GRASP")[1])
distancia_total = float(distancia_match.group(1))

orden_nombres = []
for linea in bloque.strip().splitlines():
    m = re.match(r"^\s*\d+\.\s+(.+?)(\s+\(retorno\))?\s*$", linea)
    if m:
        orden_nombres.append(m.group(1).strip())

print(f"Paradas leidas (incluyendo retorno): {len(orden_nombres)}")
print(f"Distancia total real: {distancia_total:.4f} km")

# Convertir la secuencia de nombres a secuencia de ids
orden_ids = [nodos_por_nombre[nombre][0] for nombre in orden_nombres]

# --------- 4. Graficar ---------
fig, ax = plt.subplots(figsize=(12, 14))

# Dibujar las flechas del recorrido en el orden exacto del circuito
for i in range(len(orden_ids) - 1):
    id_origen = orden_ids[i]
    id_destino = orden_ids[i + 1]
    _, lat1, lon1 = nodos_por_id[id_origen]
    _, lat2, lon2 = nodos_por_id[id_destino]

    ax.annotate(
        "", xy=(lon2, lat2), xytext=(lon1, lat1),
        arrowprops=dict(arrowstyle="-|>", color="#808080", lw=1.4,
                         shrinkA=10, shrinkB=10, alpha=0.85),
        zorder=1
    )

# Dibujar nodos, coloreados por zona
for id_nodo, (nombre, lat, lon) in nodos_por_id.items():
    zona = zona_de_id[id_nodo]
    es_ucm = (id_nodo == 0)

    if es_ucm:
        ax.scatter(lon, lat, s=600, marker="*", color=colores_zona[zona],
                   edgecolor="black", linewidth=1.5, zorder=3)
    else:
        ax.scatter(lon, lat, s=380, color=colores_zona[zona],
                   edgecolor="black", linewidth=1.0, zorder=2)

    ax.annotate(str(id_nodo), (lon, lat), color="white", fontsize=8,
                fontweight="bold", ha="center", va="center", zorder=4)

ax.set_title(
    "Ejercicio 2 — Circuito TSP (GRASP, α=0.3, 200 iteraciones)\n"
    f"50 Ubicaciones en 5 Zonas de Talca — datos reales de la ejecución "
    f"(distancia total {distancia_total:.3f} km)",
    fontsize=13, fontweight="bold"
)
ax.set_xlabel("Longitud")
ax.set_ylabel("Latitud")
ax.grid(True, linestyle="--", alpha=0.4)

# Leyenda manual
elementos_leyenda = [
    Line2D([0], [0], color="#808080", linewidth=1.4,
           label="Orden de visita (circuito GRASP + 2-opt)"),
]
for zona_id in range(5):
    elementos_leyenda.append(
        Line2D([0], [0], marker="o", color="w", markerfacecolor=colores_zona[zona_id],
               markeredgecolor="black", markersize=12, label=nombres_zona[zona_id])
    )
elementos_leyenda.append(
    Line2D([0], [0], marker="*", color="w", markerfacecolor=colores_zona[0],
           markeredgecolor="black", markersize=18, label="Nodo 0: UCM (inicio/fin)")
)
ax.legend(handles=elementos_leyenda, loc="upper left", fontsize=9)

plt.tight_layout()
plt.savefig("/home/claude/graficos/ejercicio2_tsp.png", dpi=150)
print("Grafico guardado en /home/claude/graficos/ejercicio2_tsp.png")
