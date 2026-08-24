import zipfile
import random

# ============================
# CONFIGURACIÓN
# ============================
cantidad = 30_000_000        # Puedes aumentarlo tanto como quieras
rango_min = 1
rango_max = 1_000_000
chunk_size = 10_000          # Números por bloque (para no saturar memoria)
# ============================

with zipfile.ZipFile('datos.zip', 'w', zipfile.ZIP_DEFLATED, compresslevel=9) as zf:
    with zf.open('datos.txt', 'w') as archivo:
        for _ in range(cantidad // chunk_size):
            bloque = [str(random.randint(rango_min, rango_max)) for _ in range(chunk_size)]
            archivo.write(('\n'.join(bloque) + '\n').encode('utf-8'))

        # Último bloque (si cantidad no es múltiplo de chunk_size)
        resto = cantidad % chunk_size
        if resto:
            bloque = [str(random.randint(rango_min, rango_max)) for _ in range(resto)]
            archivo.write(('\n'.join(bloque) + '\n').encode('utf-8'))

print("¡Listo! Archivo datos.zip creado.")