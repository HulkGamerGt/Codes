"""
Genera el grafico del MST del Ejercicio 1 a partir de los datos REALES
producidos por la ejecucion del programa en C (grafo_ejercicio1.csv y
resultado_ejercicio1.txt), sin usar coordenadas ni pesos ilustrativos.
"""
import csv
import re
import matplotlib.pyplot as plt

RUTA_CSV = "/home/claude/proyecto_grafos/resultados/grafo_ejercicio1.csv"
RUTA_TXT = "/home/claude/proyecto_grafos/resultados/resultado_ejercicio1.txt"

# --------- 1. Leer nodos reales (id, nombre, lat, lon) desde el CSV ---------
nodos = {}  # nombre -> (id, lat, lon)
with open(RUTA_CSV, encoding="utf-8") as f:
    lector = csv.reader(f)
    next(lector)  # encabezado: id,nombre,lat,lon
    for fila in lector:
        if len(fila) < 4:
            break  # se llego a la linea vacia antes de la matriz
        id_nodo, nombre, lat, lon = fila
        nodos[nombre] = (int(id_nodo), float(lat), float(lon))

# --------- 2. Leer las aristas reales del MST (seccion "Prim") -------------
with open(RUTA_TXT, encoding="utf-8") as f:
    contenido = f.read()

bloque = contenido.split("--- Arbol de Expansion Minima (Prim) ---")[1]
bloque = bloque.split("Numero de aristas:")[0]

patron = re.compile(r"^\s*(.+?)\s+--\s+(.+?)\s+peso=([\d.]+) km", re.MULTILINE)
aristas = []
for linea in bloque.strip().splitlines():
    m = re.match(r"^\s*(.+?)\s+--\s+(.+?)\s+peso=([\d.]+) km", linea)
    if m:
        origen, destino, peso = m.group(1).strip(), m.group(2).strip(), float(m.group(3))
        aristas.append((origen, destino, peso))

peso_total = sum(p for _, _, p in aristas)
print(f"Aristas leidas: {len(aristas)}, peso total = {peso_total:.4f} km")

# --------- 3. Graficar ---------
fig, ax = plt.subplots(figsize=(10, 12))

# Dibujar aristas del MST
for origen, destino, _ in aristas:
    _, lat1, lon1 = nodos[origen]
    _, lat2, lon2 = nodos[destino]
    ax.plot([lon1, lon2], [lat1, lat2], color="#4C72B0", linewidth=2, zorder=1)

# Dibujar nodos
for nombre, (id_nodo, lat, lon) in nodos.items():
    ax.scatter(lon, lat, s=380, color="#C44E52", edgecolor="black",
               linewidth=1.2, zorder=2)
    ax.annotate(str(id_nodo), (lon, lat), color="white", fontsize=9,
                fontweight="bold", ha="center", va="center", zorder=3)

ax.set_title(
    "Ejercicio 1 — Árbol de Expansión Mínima (MST)\n"
    f"25 Puntos de Interés de Talca — datos reales de la ejecución (peso total {peso_total:.3f} km)",
    fontsize=13, fontweight="bold"
)
ax.set_xlabel("Longitud")
ax.set_ylabel("Latitud")
ax.grid(True, linestyle="--", alpha=0.4)

# Leyenda manual
from matplotlib.lines import Line2D
from matplotlib.patches import Circle
elementos_leyenda = [
    Line2D([0], [0], color="#4C72B0", linewidth=2,
           label=f"Aristas del MST ({len(aristas)} aristas, peso total {peso_total:.3f} km)"),
    Line2D([0], [0], marker="o", color="w", markerfacecolor="#C44E52",
           markeredgecolor="black", markersize=14, label="Nodos (POIs), numerados 0–24"),
]
ax.legend(handles=elementos_leyenda, loc="lower right", fontsize=9)

plt.tight_layout()
plt.savefig("/home/claude/graficos/ejercicio1_mst.png", dpi=150)
print("Grafico guardado en /home/claude/graficos/ejercicio1_mst.png")
