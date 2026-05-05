import numpy as np
import matplotlib.pyplot as plt

# ===================== PARÁMETROS GENERALES =====================
g_tierra = 9.8          # m/s²
g_luna   = 1.62         # m/s²
v0_max   = 25.0         # m/s
y0       = 0.0          # altura inicial
angulos  = [20, 30, 45, 60, 80]   # grados
distancia_objetivo = 47.0  # metros hasta el centro del campo

# ===================== FUNCIONES CLÁSICAS =====================
def tiempo_vuelo(v0, theta_rad, g):
    """Calcula t_v resolviendo y(t)=0 con y0=0"""
    return 2 * v0 * np.sin(theta_rad) / g

def alcance(v0, theta_rad, g):
    tv = tiempo_vuelo(v0, theta_rad, g)
    return v0 * np.cos(theta_rad) * tv

def altura_max(v0, theta_rad, g):
    t_sub = v0 * np.sin(theta_rad) / g
    return v0 * np.sin(theta_rad) * t_sub - 0.5 * g * t_sub**2

def posicion_x(v0, theta_rad, t):
    return v0 * np.cos(theta_rad) * t

def posicion_y(v0, theta_rad, t, g):
    return v0 * np.sin(theta_rad) * t - 0.5 * g * t**2

# ===================== SIMULACIÓN PARA LOS 5 ÁNGULOS =====================
print("=" * 70)
print("TABLA DE RESULTADOS (v0 = 25 m/s, Tierra)")
print("=" * 70)
print(f"{'Ángulo(°)':<10}{'t_v (s)':<12}{'Alcance (m)':<15}{'Altura máx (m)':<15}")
print("-" * 70)

for ang in angulos:
    theta = np.radians(ang)
    tv = tiempo_vuelo(v0_max, theta, g_tierra)
    R = alcance(v0_max, theta, g_tierra)
    H = altura_max(v0_max, theta, g_tierra)
    print(f"{ang:<10}{tv:<12.3f}{R:<15.2f}{H:<15.2f}")

# Determinar el mejor ángulo para el arquero (más cercano a 47 m)
errores = [abs(alcance(v0_max, np.radians(a), g_tierra) - distancia_objetivo) for a in angulos]
mejor_idx = np.argmin(errores)
mejor_angulo = angulos[mejor_idx]
print(f"\nEl ángulo que más se acerca a {distancia_objetivo} m es {mejor_angulo}° "
      f"con alcance {alcance(v0_max, np.radians(mejor_angulo), g_tierra):.2f} m.")

# ===================== PREGUNTA 4: Variar v0 con theta=45° =====================
print("\n" + "=" * 70)
print("VARIACIÓN DE VELOCIDAD INICIAL (theta = 45°, Tierra)")
print("=" * 70)
print(f"{'v0 (m/s)':<12}{'t_v (s)':<12}{'Alcance (m)':<15}")
print("-" * 70)
theta_fijo = np.radians(45)
for v in [25, 20, 15]:
    tv = tiempo_vuelo(v, theta_fijo, g_tierra)
    R = alcance(v, theta_fijo, g_tierra)
    print(f"{v:<12}{tv:<12.3f}{R:<15.2f}")

# ===================== PREGUNTA 5: Cálculo exacto 50 m =====================
print("\n" + "=" * 70)
print("PARA ALCANZAR EXACTAMENTE 50 m EN LA TIERRA (minimizando v0)")
print("=" * 70)
v0_50 = np.sqrt(50 * g_tierra)  # para theta=45°
theta_50 = 45
print(f"Velocidad necesaria: {v0_50:.2f} m/s, Ángulo: {theta_50}°")

# ===================== PREGUNTA 6: Luna =====================
print("\n" + "=" * 70)
print("LANZAMIENTO EN LA LUNA (v0=22.14 m/s, theta=45°)")
print("=" * 70)
tv_luna = tiempo_vuelo(v0_50, np.radians(45), g_luna)
R_luna = alcance(v0_50, np.radians(45), g_luna)
H_luna = altura_max(v0_50, np.radians(45), g_luna)
print(f"Tiempo de vuelo: {tv_luna:.2f} s")
print(f"Alcance: {R_luna:.2f} m")
print(f"Altura máxima: {H_luna:.2f} m")

# ===================== GRÁFICOS PARA EL MEJOR ÁNGULO (20°) =====================
# Elegimos la trayectoria de 20° con v0=25 m/s
theta_plot = np.radians(mejor_angulo)  # 20°
tv = tiempo_vuelo(v0_max, theta_plot, g_tierra)
t_puntos = np.linspace(0, tv, 6)   # 6 puntos equidistantes

x_puntos = posicion_x(v0_max, theta_plot, t_puntos)
y_puntos = posicion_y(v0_max, theta_plot, t_puntos, g_tierra)
vx_puntos = np.full_like(t_puntos, v0_max * np.cos(theta_plot))
vy_puntos = v0_max * np.sin(theta_plot) - g_tierra * t_puntos

# Gráficos separados
plt.figure(figsize=(8,6))
plt.plot(t_puntos, x_puntos, 'o-', color='blue')
plt.title('Posición horizontal vs tiempo')
plt.xlabel('Tiempo (s)')
plt.ylabel('x (m)')
plt.grid(True)
plt.savefig('pos_x_vs_t.png', dpi=200)
plt.close()

plt.figure(figsize=(8,6))
plt.plot(t_puntos, y_puntos, 'o-', color='red')
plt.title('Posición vertical vs tiempo')
plt.xlabel('Tiempo (s)')
plt.ylabel('y (m)')
plt.grid(True)
plt.savefig('pos_y_vs_t.png', dpi=200)
plt.close()

plt.figure(figsize=(8,6))
plt.plot(t_puntos, vx_puntos, 'o-', color='green')
plt.title('Velocidad horizontal vs tiempo')
plt.xlabel('Tiempo (s)')
plt.ylabel('$v_x$ (m/s)')
plt.grid(True)
plt.savefig('vel_x_vs_t.png', dpi=200)
plt.close()

plt.figure(figsize=(8,6))
plt.plot(t_puntos, vy_puntos, 'o-', color='orange')
plt.title('Velocidad vertical vs tiempo')
plt.xlabel('Tiempo (s)')
plt.ylabel('$v_y$ (m/s)')
plt.grid(True)
plt.savefig('vel_y_vs_t.png', dpi=200)
plt.close()

print("\nGráficos guardados: pos_x_vs_t.png, pos_y_vs_t.png, vel_x_vs_t.png, vel_y_vs_t.png")
print("Listo para insertar en el informe LaTeX.")