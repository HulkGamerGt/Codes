from reportlab.lib.pagesizes import A4
from reportlab.lib import colors
from reportlab.lib.units import cm, mm
from reportlab.lib.styles import getSampleStyleSheet, ParagraphStyle
from reportlab.lib.enums import TA_LEFT, TA_CENTER, TA_JUSTIFY, TA_RIGHT
from reportlab.platypus import (
    SimpleDocTemplate, Paragraph, Spacer, Table, TableStyle,
    HRFlowable, PageBreak, KeepTogether
)
from reportlab.platypus.flowables import Flowable
from reportlab.pdfgen import canvas
from reportlab.lib.colors import HexColor
import os

# ── Paleta de colores ────────────────────────────────────────
AZUL_OSCURO   = HexColor("#1A2E4A")   # encabezados principales
AZUL_MEDIO    = HexColor("#2E5C8A")   # encabezados secundarios
AZUL_CLARO    = HexColor("#4A90C4")   # acentos / líneas
CELESTE_BG    = HexColor("#EAF2FB")   # fondo de tablas cabecera
GRIS_TEXTO    = HexColor("#2C2C2C")   # texto principal
GRIS_SUAVE    = HexColor("#F5F7FA")   # fondo alterno tabla
GRIS_BORDE    = HexColor("#C5D0DC")   # bordes tabla
BLANCO        = colors.white
ACENTO_VERDE  = HexColor("#1B7A5E")   # ecuaciones / pseudocódigo borde
VERDE_BG      = HexColor("#EAF5F1")   # fondo bloque ecuación

PAGE_W, PAGE_H = A4

# ── Márgenes ────────────────────────────────────────────────
LEFT_MARGIN   = 2.8 * cm
RIGHT_MARGIN  = 2.8 * cm
TOP_MARGIN    = 2.5 * cm
BOTTOM_MARGIN = 2.5 * cm

# ═══════════════════════════════════════════════════════════════
# CANVAS con header/footer dinámico
# ═══════════════════════════════════════════════════════════════
class AcademicTemplate(canvas.Canvas):
    def __init__(self, filename, **kwargs):
        super().__init__(filename, **kwargs)
        self.pages = []
        self._saved_page_states = []

    def showPage(self):
        self._saved_page_states.append(dict(self.__dict__))
        self._startPage()

    def save(self):
        num_pages = len(self._saved_page_states)
        for state in self._saved_page_states:
            self.__dict__.update(state)
            self.draw_page_decorations(num_pages)
            super().showPage()
        super().save()

    def draw_page_decorations(self, total_pages):
        page_num = self._pageNumber

        # ── Barra superior ─────────────────────────────────
        self.setFillColor(AZUL_OSCURO)
        self.rect(0, PAGE_H - 1.6*cm, PAGE_W, 1.6*cm, fill=1, stroke=0)

        # Texto izquierdo en barra
        self.setFillColor(BLANCO)
        self.setFont("Helvetica-Bold", 8)
        self.drawString(LEFT_MARGIN, PAGE_H - 1.0*cm,
                        "Investigación de Operaciones · Logística Urbana")

        # Texto derecho en barra
        self.setFont("Helvetica", 8)
        self.drawRightString(PAGE_W - RIGHT_MARGIN, PAGE_H - 1.0*cm,
                             "Universidad · 2026")

        # Línea decorativa bajo barra
        self.setStrokeColor(AZUL_CLARO)
        self.setLineWidth(2)
        self.line(0, PAGE_H - 1.6*cm, PAGE_W, PAGE_H - 1.6*cm)

        # ── Línea lateral izquierda decorativa ─────────────
        if page_num > 1:
            self.setStrokeColor(AZUL_CLARO)
            self.setLineWidth(3)
            self.line(1.2*cm, BOTTOM_MARGIN + 0.5*cm,
                      1.2*cm, PAGE_H - 2.2*cm)

        # ── Footer ─────────────────────────────────────────
        self.setStrokeColor(GRIS_BORDE)
        self.setLineWidth(0.5)
        self.line(LEFT_MARGIN, BOTTOM_MARGIN + 0.4*cm,
                  PAGE_W - RIGHT_MARGIN, BOTTOM_MARGIN + 0.4*cm)

        self.setFillColor(AZUL_MEDIO)
        self.setFont("Helvetica", 7.5)
        self.drawString(LEFT_MARGIN, BOTTOM_MARGIN - 0.0*cm,
                        "Avance 1: Integración de Ciencias Básicas y Representación Cuantitativa")

        self.setFont("Helvetica-Bold", 8)
        self.setFillColor(AZUL_OSCURO)
        self.drawRightString(PAGE_W - RIGHT_MARGIN, BOTTOM_MARGIN - 0.0*cm,
                             f"Página {page_num} de {total_pages}")


def build_pdf(output_path):
    doc = SimpleDocTemplate(
        output_path,
        pagesize=A4,
        leftMargin=LEFT_MARGIN,
        rightMargin=RIGHT_MARGIN,
        topMargin=TOP_MARGIN + 1.6*cm,   # espacio para la barra superior
        bottomMargin=BOTTOM_MARGIN + 0.8*cm,
        title="Avance 1 – Optimización de Rutas de Reparto en Talca",
        author="Proyecto de Curso Universitario",
        subject="Investigación de Operaciones · Logística Urbana"
    )

    # ── Estilos base ────────────────────────────────────────
    base = getSampleStyleSheet()

    def S(name, **kw):
        return ParagraphStyle(name, **kw)

    # Portada
    st_portada_titulo = S("PortadaTitulo",
        fontName="Helvetica-Bold", fontSize=22,
        textColor=AZUL_OSCURO, leading=30,
        alignment=TA_CENTER, spaceAfter=8)

    st_portada_sub = S("PortadaSub",
        fontName="Helvetica", fontSize=13,
        textColor=AZUL_MEDIO, leading=18,
        alignment=TA_CENTER, spaceAfter=6)

    st_portada_meta = S("PortadaMeta",
        fontName="Helvetica", fontSize=10,
        textColor=GRIS_TEXTO, leading=15,
        alignment=TA_CENTER, spaceAfter=4)

    st_portada_kw = S("PortadaKW",
        fontName="Helvetica-Oblique", fontSize=9,
        textColor=AZUL_MEDIO, leading=14,
        alignment=TA_CENTER)

    # Texto general
    st_body = S("Body",
        fontName="Helvetica", fontSize=10,
        textColor=GRIS_TEXTO, leading=15,
        alignment=TA_JUSTIFY, spaceAfter=7,
        spaceBefore=3)

    st_resumen = S("Resumen",
        fontName="Helvetica-Oblique", fontSize=9.5,
        textColor=HexColor("#3A3A3A"), leading=14,
        alignment=TA_JUSTIFY, spaceAfter=6,
        leftIndent=12, rightIndent=12)

    # Encabezados
    st_h1 = S("H1",
        fontName="Helvetica-Bold", fontSize=14,
        textColor=AZUL_OSCURO, leading=18,
        spaceBefore=18, spaceAfter=6,
        borderPad=0)

    st_h2 = S("H2",
        fontName="Helvetica-Bold", fontSize=11.5,
        textColor=AZUL_MEDIO, leading=16,
        spaceBefore=12, spaceAfter=4)

    st_h3 = S("H3",
        fontName="Helvetica-Bold", fontSize=10.5,
        textColor=ACENTO_VERDE, leading=14,
        spaceBefore=8, spaceAfter=3)

    # Ecuación
    st_eq = S("Ecuacion",
        fontName="Helvetica-Oblique", fontSize=10,
        textColor=HexColor("#1A1A1A"), leading=16,
        alignment=TA_CENTER, spaceAfter=4,
        spaceBefore=4)

    st_eq_label = S("EqLabel",
        fontName="Helvetica", fontSize=9,
        textColor=AZUL_MEDIO, leading=14,
        alignment=TA_RIGHT)

    # Pseudocódigo
    st_code = S("Code",
        fontName="Courier", fontSize=8.2,
        textColor=HexColor("#1A1A1A"), leading=13,
        leftIndent=6, spaceAfter=2)

    # Nota al pie / leyenda
    st_nota = S("Nota",
        fontName="Helvetica-Oblique", fontSize=8.5,
        textColor=HexColor("#555"), leading=12,
        alignment=TA_JUSTIFY, spaceAfter=5)

    # Caption tabla
    st_caption = S("Caption",
        fontName="Helvetica-Bold", fontSize=9,
        textColor=AZUL_OSCURO, leading=13,
        spaceBefore=8, spaceAfter=3)

    story = []

    # ════════════════════════════════════════════════════════
    # PORTADA
    # ════════════════════════════════════════════════════════
    story.append(Spacer(1, 1.5*cm))

    # Banda decorativa superior de portada
    portada_band = Table(
        [[""]],
        colWidths=[doc.width],
        rowHeights=[0.35*cm]
    )
    portada_band.setStyle(TableStyle([
        ("BACKGROUND", (0,0), (-1,-1), AZUL_CLARO),
        ("LINEBELOW", (0,0), (-1,-1), 4, AZUL_OSCURO),
    ]))
    story.append(portada_band)
    story.append(Spacer(1, 0.5*cm))

    story.append(Paragraph("AVANCE 1", S("Av1",
        fontName="Helvetica-Bold", fontSize=11,
        textColor=AZUL_CLARO, alignment=TA_CENTER,
        letterSpacing=4, spaceAfter=4)))

    story.append(Paragraph(
        "Integración de Ciencias Básicas<br/>y Representación Cuantitativa",
        st_portada_titulo))

    story.append(Spacer(1, 0.3*cm))

    # Línea separadora portada
    story.append(HRFlowable(width="70%", thickness=1.5,
                             color=AZUL_CLARO, hAlign="CENTER"))
    story.append(Spacer(1, 0.4*cm))

    story.append(Paragraph(
        "Modelo de Optimización de Rutas de Reparto para Logística Urbana",
        st_portada_sub))
    story.append(Paragraph(
        "Caso de Estudio: Ciudad de Talca, Región del Maule, Chile",
        S("CasoSub", fontName="Helvetica-Oblique", fontSize=11,
          textColor=AZUL_MEDIO, alignment=TA_CENTER, spaceAfter=16)))

    story.append(Spacer(1, 0.6*cm))

    # Caja de metadatos
    meta_data = [
        ["Asignatura:", "Investigación de Operaciones / Logística Urbana"],
        ["Nivel:",       "Proyecto de Curso Universitario"],
        ["Área:",        "Ciencias Básicas · Física Aplicada · IO"],
        ["Fecha:",       "Septiembre 2026"],
    ]
    meta_table = Table(meta_data, colWidths=[3.5*cm, 10*cm])
    meta_table.setStyle(TableStyle([
        ("FONTNAME",    (0,0), (0,-1), "Helvetica-Bold"),
        ("FONTNAME",    (1,0), (1,-1), "Helvetica"),
        ("FONTSIZE",    (0,0), (-1,-1), 9.5),
        ("TEXTCOLOR",   (0,0), (0,-1), AZUL_OSCURO),
        ("TEXTCOLOR",   (1,0), (1,-1), GRIS_TEXTO),
        ("TOPPADDING",  (0,0), (-1,-1), 4),
        ("BOTTOMPADDING",(0,0), (-1,-1), 4),
        ("LINEBELOW",   (0,-1), (-1,-1), 0.5, GRIS_BORDE),
    ]))
    story.append(meta_table)
    story.append(Spacer(1, 0.8*cm))

    story.append(HRFlowable(width="70%", thickness=1.5,
                             color=AZUL_CLARO, hAlign="CENTER"))
    story.append(Spacer(1, 0.5*cm))

    story.append(Paragraph(
        "<b>Palabras clave:</b> VRP · optimización combinatoria · logística urbana · "
        "consumo energético · zonificación · Talca",
        st_portada_kw))

    story.append(PageBreak())

    # ════════════════════════════════════════════════════════
    # RESUMEN
    # ════════════════════════════════════════════════════════
    def seccion_h1(titulo, numero):
        """Retorna un bloque de encabezado H1 con línea y número."""
        elementos = []
        num_par = Paragraph(f"{numero}.", S("NumH1",
            fontName="Helvetica-Bold", fontSize=20,
            textColor=CELESTE_BG, leading=24,
            spaceBefore=16))
        tit_par = Paragraph(titulo, st_h1)
        elementos.append(num_par)
        elementos.append(tit_par)
        elementos.append(HRFlowable(width="100%", thickness=1,
                                    color=AZUL_CLARO, spaceAfter=6))
        return elementos

    # Bloque resumen con fondo
    res_texto = (
        "El presente informe constituye el primer avance de un proyecto orientado al diseño de un "
        "modelo de optimización de rutas de distribución de última milla (<i>last-mile delivery</i>) "
        "en el contexto urbano de la ciudad de Talca, Chile. Se desarrolla una abstracción espacial "
        "del territorio mediante un esquema de zonificación matricial estructurado sobre la Ruta 5 Sur "
        "como eje divisor, se formulan las restricciones de capacidad física del vehículo, se incorpora "
        "un modelo de consumo energético basado en mecánica clásica y se propone un esquema de "
        "penalizaciones viales para simular la fricción del tránsito urbano. La función objetivo integra "
        "simultáneamente la minimización del tiempo de ruta y la energía mecánica consumida. El enfoque "
        "adoptado es propio del Problema de Ruteo de Vehículos con Capacidad (<i>Capacitated VRP</i>, "
        "CVRP), consolidado en la literatura de Investigación de Operaciones (Eksioglu, Vural y Reisman, 2009)."
    )
    res_table = Table(
        [[Paragraph("<b>RESUMEN</b>", S("RTit",
            fontName="Helvetica-Bold", fontSize=10,
            textColor=AZUL_OSCURO, spaceAfter=4))],
         [Paragraph(res_texto, st_resumen)]],
        colWidths=[doc.width]
    )
    res_table.setStyle(TableStyle([
        ("BACKGROUND",   (0,0), (-1,-1), CELESTE_BG),
        ("BOX",          (0,0), (-1,-1), 1, AZUL_CLARO),
        ("LEFTPADDING",  (0,0), (-1,-1), 14),
        ("RIGHTPADDING", (0,0), (-1,-1), 14),
        ("TOPPADDING",   (0,0), (0,0),  10),
        ("BOTTOMPADDING",(0,-1),(-1,-1), 10),
    ]))
    story.append(res_table)
    story.append(Spacer(1, 0.5*cm))

    # ════════════════════════════════════════════════════════
    # SECCIÓN 1
    # ════════════════════════════════════════════════════════
    for e in seccion_h1("Introducción y Abstracción Espacial", 1):
        story.append(e)

    story.append(Paragraph("1.1 Contextualización del Problema", st_h2))
    story.append(Paragraph(
        "La distribución de última milla representa uno de los segmentos más costosos e ineficientes "
        "dentro de las cadenas de suministro modernas. En entornos urbanos de ciudades intermedias "
        "como Talca, la ausencia de infraestructura tecnológica avanzada —tales como APIs públicas de "
        "semáforos o sistemas de navegación en tiempo real con datos abiertos— obliga al diseño de "
        "modelos de aproximación que capturen la complejidad vial mediante abstracciones matemáticas "
        "manejables.", st_body))

    story.append(Paragraph(
        "El Problema de Ruteo de Vehículos (VRP) es, en su formulación más general, un problema de "
        "optimización combinatoria NP-difícil. Eksioglu, Vural y Reisman (2009) ofrecen una revisión "
        "taxonómica exhaustiva que define el VRP como la búsqueda de un conjunto de rutas de costo "
        "mínimo, donde cada ruta parte y regresa a un depósito central, cada cliente es visitado "
        "exactamente una vez, y la demanda total de cada ruta no supera la capacidad del vehículo "
        "asignado. Este marco teórico constituye el punto de partida del presente modelo.", st_body))

    story.append(Paragraph("1.2 Abstracción Territorial: Zonificación de Talca", st_h2))
    story.append(Paragraph(
        "La ciudad de Talca presenta una morfología urbana ortogonal característica, con un trazado "
        "de cuadrícula que facilita su abstracción en matrices regulares. Se utiliza la "
        "<b>Ruta 5 Sur</b> como eje estructural divisor del espacio urbano en dos sectores principales:", st_body))

    # Dos sectores
    sectores = [
        ["Sector Poniente (P)", "Zona urbanamente consolidada al oeste de la Ruta 5 Sur. Comprende el casco histórico y barrios residenciales tradicionales."],
        ["Sector Oriente (O)", "Zona de expansión hacia el este, sector Esmeralda. Corresponde a urbanizaciones más recientes con menor densidad vial."],
    ]
    t_sectores = Table(sectores, colWidths=[4*cm, doc.width - 4*cm])
    t_sectores.setStyle(TableStyle([
        ("FONTNAME",     (0,0), (0,-1), "Helvetica-Bold"),
        ("FONTNAME",     (1,0), (1,-1), "Helvetica"),
        ("FONTSIZE",     (0,0), (-1,-1), 9.5),
        ("TEXTCOLOR",    (0,0), (0,-1), AZUL_OSCURO),
        ("TEXTCOLOR",    (1,0), (1,-1), GRIS_TEXTO),
        ("BACKGROUND",   (0,0), (0,-1), CELESTE_BG),
        ("GRID",         (0,0), (-1,-1), 0.5, GRIS_BORDE),
        ("VALIGN",       (0,0), (-1,-1), "MIDDLE"),
        ("TOPPADDING",   (0,0), (-1,-1), 6),
        ("BOTTOMPADDING",(0,0), (-1,-1), 6),
        ("LEFTPADDING",  (0,0), (-1,-1), 8),
    ]))
    story.append(t_sectores)
    story.append(Spacer(1, 0.3*cm))

    story.append(Paragraph(
        "Cada sector se abstrae como una subcuadrícula de 3×3, generando un total de "
        "<b>18 zonas elementales</b> (9 por sector). Las zonas se denominan mediante el par "
        "ordenado (s, i, j), donde s ∈ {P, O} identifica el sector, e i, j ∈ {1, 2, 3} "
        "identifican la fila y columna de la subcuadrícula, respectivamente.", st_body))

    # ── Diagrama de Zonificación ──────────────────────────
    story.append(Paragraph("Figura 1: Diagrama de Zonificación de Talca", st_caption))

    zon_headers = [
        [Paragraph("<b>SECTOR PONIENTE (P)</b>", S("ZH", fontName="Helvetica-Bold",
            fontSize=9, textColor=BLANCO, alignment=TA_CENTER)),
         Paragraph("<b>[ RUTA 5 SUR ]</b>", S("ZH2", fontName="Helvetica-Bold",
            fontSize=8, textColor=BLANCO, alignment=TA_CENTER)),
         Paragraph("<b>SECTOR ORIENTE (O)</b>", S("ZH3", fontName="Helvetica-Bold",
            fontSize=9, textColor=BLANCO, alignment=TA_CENTER))],
    ]

    def zc(txt, bg=GRIS_SUAVE):
        return Paragraph(txt, S("ZC", fontName="Helvetica", fontSize=8.2,
                                textColor=GRIS_TEXTO, alignment=TA_CENTER))

    def zb(txt):
        return Paragraph(txt, S("ZB", fontName="Helvetica-Bold", fontSize=8.2,
                                textColor=AZUL_OSCURO, alignment=TA_CENTER))

    zon_data = zon_headers + [
        [zb("P-NorOeste\nP-Norte\nP-NorEste"),
         zc("▲\n▲\n▲"),
         zb("O-NorOeste\nO-Norte\nO-NorEste")],
        [zb("P-OesteCentro\nP-Centro\nP-EsteCentro"),
         zc("—\n—\n—"),
         zb("O-OesteCentro\nO-Centro\nO-EsteCentro")],
        [zb("P-SurOeste\nP-Sur\nP-SurEste"),
         zc("▼\n▼\n▼"),
         zb("O-SurOeste\nO-Sur\nO-SurEste")],
    ]

    cw_zon = [doc.width*0.46, doc.width*0.08, doc.width*0.46]
    t_zon = Table(zon_data, colWidths=cw_zon, rowHeights=[0.7*cm, 1.6*cm, 1.6*cm, 1.6*cm])
    t_zon.setStyle(TableStyle([
        ("BACKGROUND",    (0,0), (0,0),   AZUL_OSCURO),
        ("BACKGROUND",    (1,0), (1,0),   AZUL_CLARO),
        ("BACKGROUND",    (2,0), (2,0),   AZUL_MEDIO),
        ("BACKGROUND",    (0,1), (0,-1),  CELESTE_BG),
        ("BACKGROUND",    (1,1), (1,-1),  HexColor("#D0D0D0")),
        ("BACKGROUND",    (2,1), (2,-1),  HexColor("#EAF5F1")),
        ("BOX",           (0,0), (-1,-1), 2, AZUL_OSCURO),
        ("INNERGRID",     (0,0), (-1,-1), 0.5, GRIS_BORDE),
        ("VALIGN",        (0,0), (-1,-1), "MIDDLE"),
        ("TOPPADDING",    (0,0), (-1,-1), 5),
        ("BOTTOMPADDING", (0,0), (-1,-1), 5),
    ]))
    story.append(t_zon)
    story.append(Spacer(1, 0.15*cm))
    story.append(Paragraph(
        "Nota: La columna central representa la Ruta 5 Sur como eje divisor. "
        "Las flechas indican sentido de numeración de filas.", st_nota))
    story.append(Spacer(1, 0.3*cm))

    # Tablas de nomenclatura
    story.append(Paragraph("Tabla 1: Nomenclatura de Zonas — Sector Poniente", st_caption))
    t1_data = [
        [Paragraph("<b>Sector P</b>", S("TH", fontName="Helvetica-Bold", fontSize=9,
                   textColor=BLANCO, alignment=TA_CENTER)),
         Paragraph("<b>Col 1 (Norte)</b>", S("TH", fontName="Helvetica-Bold", fontSize=9,
                   textColor=BLANCO, alignment=TA_CENTER)),
         Paragraph("<b>Col 2 (Centro)</b>", S("TH", fontName="Helvetica-Bold", fontSize=9,
                   textColor=BLANCO, alignment=TA_CENTER)),
         Paragraph("<b>Col 3 (Sur)</b>", S("TH", fontName="Helvetica-Bold", fontSize=9,
                   textColor=BLANCO, alignment=TA_CENTER))],
        ["Fila 1 (Oeste)", "P-NorOeste", "P-Norte", "P-NorEste"],
        ["Fila 2 (Centro)", "P-OesteCentro", "P-Centro", "P-EsteCentro"],
        ["Fila 3 (Sur)", "P-SurOeste", "P-Sur", "P-SurEste"],
    ]

    def make_tabla(data, col_widths):
        t = Table(data, colWidths=col_widths)
        t.setStyle(TableStyle([
            ("BACKGROUND",    (0,0), (-1,0),  AZUL_OSCURO),
            ("TEXTCOLOR",     (0,0), (-1,0),  BLANCO),
            ("BACKGROUND",    (0,1), (0,-1),  CELESTE_BG),
            ("BACKGROUND",    (1,1), (-1,1),  GRIS_SUAVE),
            ("BACKGROUND",    (1,2), (-1,2),  BLANCO),
            ("BACKGROUND",    (1,3), (-1,3),  GRIS_SUAVE),
            ("FONTNAME",      (0,0), (-1,0),  "Helvetica-Bold"),
            ("FONTNAME",      (0,1), (0,-1),  "Helvetica-Bold"),
            ("FONTNAME",      (1,1), (-1,-1), "Helvetica"),
            ("FONTSIZE",      (0,0), (-1,-1), 9),
            ("TEXTCOLOR",     (0,1), (0,-1),  AZUL_OSCURO),
            ("GRID",          (0,0), (-1,-1), 0.5, GRIS_BORDE),
            ("ALIGN",         (0,0), (-1,-1), "CENTER"),
            ("VALIGN",        (0,0), (-1,-1), "MIDDLE"),
            ("TOPPADDING",    (0,0), (-1,-1), 5),
            ("BOTTOMPADDING", (0,0), (-1,-1), 5),
        ]))
        return t

    cw4 = [3.2*cm, (doc.width-3.2*cm)/3, (doc.width-3.2*cm)/3, (doc.width-3.2*cm)/3]
    story.append(make_tabla(t1_data, cw4))
    story.append(Spacer(1, 0.25*cm))

    story.append(Paragraph("Tabla 2: Nomenclatura de Zonas — Sector Oriente (Esmeralda)", st_caption))
    t2_data = [
        [Paragraph("<b>Sector O</b>", S("TH", fontName="Helvetica-Bold", fontSize=9,
                   textColor=BLANCO, alignment=TA_CENTER)),
         Paragraph("<b>Col 1 (Norte)</b>", S("TH", fontName="Helvetica-Bold", fontSize=9,
                   textColor=BLANCO, alignment=TA_CENTER)),
         Paragraph("<b>Col 2 (Centro)</b>", S("TH", fontName="Helvetica-Bold", fontSize=9,
                   textColor=BLANCO, alignment=TA_CENTER)),
         Paragraph("<b>Col 3 (Sur)</b>", S("TH", fontName="Helvetica-Bold", fontSize=9,
                   textColor=BLANCO, alignment=TA_CENTER))],
        ["Fila 1 (Oeste)", "O-NorOeste", "O-Norte", "O-NorEste"],
        ["Fila 2 (Centro)", "O-OesteCentro", "O-Centro", "O-EsteCentro"],
        ["Fila 3 (Sur)", "O-SurOeste", "O-Sur", "O-SurEste"],
    ]
    story.append(make_tabla(t2_data, cw4))
    story.append(Spacer(1, 0.3*cm))

    story.append(Paragraph("1.3 Fusión Dinámica de Zonas", st_h2))
    story.append(Paragraph(
        "Cuando una zona z<sub>k</sub> presenta una densidad de pedidos δ<sub>k</sub> inferior al "
        "umbral mínimo δ<sub>min</sub>, resulta ineficiente destinar un viaje exclusivo a dicha zona. "
        "En tal caso, el sistema la fusiona con la zona adyacente z<sub>k'</sub> de mayor densidad:", st_body))

    def eq_block(eq_text, numero):
        eq_row = Table(
            [[Paragraph(eq_text, st_eq),
              Paragraph(f"({numero})", S("EqN", fontName="Helvetica", fontSize=9.5,
                        textColor=AZUL_MEDIO, alignment=TA_RIGHT, leading=14))]],
            colWidths=[doc.width - 2*cm, 2*cm]
        )
        eq_row.setStyle(TableStyle([
            ("BACKGROUND",   (0,0), (-1,-1), VERDE_BG),
            ("BOX",          (0,0), (-1,-1), 1.5, ACENTO_VERDE),
            ("LEFTPADDING",  (0,0), (-1,-1), 16),
            ("RIGHTPADDING", (0,0), (-1,-1), 10),
            ("TOPPADDING",   (0,0), (-1,-1), 8),
            ("BOTTOMPADDING",(0,0), (-1,-1), 8),
            ("VALIGN",       (0,0), (-1,-1), "MIDDLE"),
        ]))
        return eq_row

    story.append(eq_block(
        "Si δ<sub>k</sub> &lt; δ<sub>min</sub>  →  z<sub>k</sub> ∪ z<sub>k'</sub>,    "
        "donde k' = argmax<sub>j ∈ A(k)</sub> δ<sub>j</sub>", "1"))
    story.append(Spacer(1, 0.2*cm))
    story.append(Paragraph(
        "donde A(k) representa el conjunto de zonas adyacentes a z<sub>k</sub> en la cuadrícula.", st_body))

    story.append(Paragraph("Tabla 3: Parámetros de Fusión Dinámica", st_caption))
    t3_data = [
        [Paragraph("<b>Parámetro</b>", S("TH", fontName="Helvetica-Bold", fontSize=9,
                   textColor=BLANCO, alignment=TA_CENTER)),
         Paragraph("<b>Símbolo</b>", S("TH", fontName="Helvetica-Bold", fontSize=9,
                   textColor=BLANCO, alignment=TA_CENTER)),
         Paragraph("<b>Valor de Referencia</b>", S("TH", fontName="Helvetica-Bold", fontSize=9,
                   textColor=BLANCO, alignment=TA_CENTER))],
        ["Umbral mínimo de densidad", "δ_min", "3 pedidos / zona"],
        ["Distancia máxima de fusión", "d_max (fusión)", "1 celda adyacente"],
        ["Criterio de selección", "—", "Mayor δ_j entre adyacentes"],
    ]
    cw3 = [8*cm, 4*cm, doc.width - 12*cm]
    story.append(make_tabla(t3_data, cw3))

    story.append(PageBreak())

    # ════════════════════════════════════════════════════════
    # SECCIÓN 2
    # ════════════════════════════════════════════════════════
    for e in seccion_h1("Algoritmo de Clasificación en Bodega", 2):
        story.append(e)

    story.append(Paragraph("2.1 Descripción General", st_h2))
    story.append(Paragraph(
        "Antes de iniciar la ruta de despacho, el sistema ejecuta un <b>algoritmo de clasificación "
        "en bodega</b> (<i>warehouse sorting algorithm</i>) que organiza los paquetes según dos "
        "criterios jerarquizados:", st_body))
    story.append(Paragraph("1.  <b>Criterio primario:</b> Zona de destino (agrupación geográfica).", st_body))
    story.append(Paragraph(
        "2.  <b>Criterio secundario:</b> Masa del paquete en orden descendente (de mayor a menor "
        "peso), dentro de cada zona.", st_body))
    story.append(Paragraph(
        "Este algoritmo garantiza que el vehículo cargue los paquetes en el orden inverso de "
        "entrega: los primeros paquetes en ser entregados deben estar al frente, y corresponden "
        "a los más pesados de cada zona visitada primero.", st_body))

    story.append(Paragraph("2.2 Pseudocódigo del Algoritmo", st_h2))

    # Bloque pseudocódigo
    pseudo_lines = [
        ("ALGORITMO", "Helvetica-Bold", AZUL_OSCURO),
        ("ClasificacionBodega(pedidos, zonas)", "Helvetica-BoldOblique", AZUL_MEDIO),
        ("─" * 64, "Helvetica", GRIS_BORDE),
        ("ENTRADA:", "Helvetica-Bold", ACENTO_VERDE),
        ("  pedidos  : lista {id, masa_kg, zona_destino}", "Courier", GRIS_TEXTO),
        ("  zonas    : lista de zonas ordenadas por secuencia de ruta", "Courier", GRIS_TEXTO),
        ("SALIDA:", "Helvetica-Bold", ACENTO_VERDE),
        ("  secuencia_carga : lista ordenada para carga al vehículo", "Courier", GRIS_TEXTO),
        ("─" * 64, "Helvetica", GRIS_BORDE),
        ("INICIO", "Helvetica-Bold", AZUL_OSCURO),
        ("  // Paso 1: Calcular densidad por zona", "Courier-Oblique", HexColor("#777")),
        ("  PARA CADA zona z EN zonas HACER", "Courier", GRIS_TEXTO),
        ("      δ(z) ← COUNT(pedidos donde zona_destino = z)", "Courier", GRIS_TEXTO),
        ("      m_total(z) ← SUM(masa_kg donde zona_destino = z)", "Courier", GRIS_TEXTO),
        ("  FIN PARA", "Courier", GRIS_TEXTO),
        ("  // Paso 2: Fusión dinámica de zonas con baja densidad", "Courier-Oblique", HexColor("#777")),
        ("  PARA CADA zona z EN zonas HACER", "Courier", GRIS_TEXTO),
        ("      SI δ(z) < δ_min ENTONCES", "Courier", GRIS_TEXTO),
        ("          z' ← adyacente(z) con MAX δ", "Courier", GRIS_TEXTO),
        ("          fusionar(z, z');  REGISTRAR evento_fusion(z, z')", "Courier", GRIS_TEXTO),
        ("      FIN SI", "Courier", GRIS_TEXTO),
        ("  FIN PARA", "Courier", GRIS_TEXTO),
        ("  // Paso 3: Verificar restricción capacidad total", "Courier-Oblique", HexColor("#777")),
        ("  M_total ← SUM(masa_kg de todos los pedidos)", "Courier", GRIS_TEXTO),
        ("  SI M_total > 1000 ENTONCES", "Courier", GRIS_TEXTO),
        ("      LANZAR excepción('Sobrepeso: capacidad excedida')", "Courier", HexColor("#B22222")),
        ("  FIN SI", "Courier", GRIS_TEXTO),
        ("  // Paso 4: Ordenar zonas según secuencia de ruta óptima", "Courier-Oblique", HexColor("#777")),
        ("  zonas_ordenadas ← ordenar_por_ruta(zonas)", "Courier", GRIS_TEXTO),
        ("  // Paso 5: Dentro de cada zona, ordenar por masa DESC", "Courier-Oblique", HexColor("#777")),
        ("  secuencia_carga ← lista_vacía", "Courier", GRIS_TEXTO),
        ("  PARA CADA zona z EN zonas_ordenadas (orden inverso) HACER", "Courier", GRIS_TEXTO),
        ("      paquetes_z ← filtrar(pedidos, zona_destino = z)", "Courier", GRIS_TEXTO),
        ("      paquetes_z ← ordenar_DESC(paquetes_z, campo=masa_kg)", "Courier", GRIS_TEXTO),
        ("      secuencia_carga.agregar(paquetes_z)", "Courier", GRIS_TEXTO),
        ("  FIN PARA", "Courier", GRIS_TEXTO),
        ("  RETORNAR secuencia_carga", "Courier-Bold", AZUL_OSCURO),
        ("FIN", "Helvetica-Bold", AZUL_OSCURO),
    ]

    pseudo_rows = []
    for line, font, color in pseudo_lines:
        pseudo_rows.append([Paragraph(line, S("PL",
            fontName=font, fontSize=8, textColor=color,
            leading=12, leftIndent=0))])

    pseudo_table = Table(pseudo_rows, colWidths=[doc.width - 0.4*cm])
    pseudo_table.setStyle(TableStyle([
        ("BACKGROUND",    (0,0), (-1,-1), HexColor("#F8F9FC")),
        ("BOX",           (0,0), (-1,-1), 2, AZUL_OSCURO),
        ("LINEAFTER",     (0,0), (0,-1), 4, AZUL_CLARO),
        ("TOPPADDING",    (0,0), (-1,-1), 2),
        ("BOTTOMPADDING", (0,0), (-1,-1), 2),
        ("LEFTPADDING",   (0,0), (-1,-1), 10),
        ("RIGHTPADDING",  (0,0), (-1,-1), 8),
    ]))
    story.append(pseudo_table)
    story.append(Spacer(1, 0.35*cm))

    story.append(Paragraph("2.3 Ejemplo Ilustrativo", st_h2))
    story.append(Paragraph("Tabla 4: Pedidos de Ejemplo con Datos Hipotéticos (Talca)", st_caption))

    t4_hdr = [Paragraph(f"<b>{h}</b>", S("TH", fontName="Helvetica-Bold", fontSize=8.5,
              textColor=BLANCO, alignment=TA_CENTER)) for h in
              ["ID Pedido", "Masa (kg)", "Zona Destino", "Tipo de Vía"]]
    t4_data = [t4_hdr,
        ["P001", "45,0", "P-Centro", "Principal"],
        ["P002", "12,5", "P-Centro", "Principal"],
        ["P003", "38,0", "P-Norte", "Local"],
        ["P004", "7,0", "P-Norte", "Local"],
        ["P005", "55,0", "O-Centro", "Principal"],
        ["P006", "22,0", "O-Centro", "Principal"],
        ["P007", "2,5", "O-SurOeste *", "Local"],
        ["P008", "3,0", "O-SurEste *", "Local"],
        [Paragraph("<b>TOTAL</b>", S("TB", fontName="Helvetica-Bold", fontSize=9,
                   textColor=AZUL_OSCURO)), "185,0 kg", "—", "—"],
    ]
    cw_t4 = [2.5*cm, 3*cm, 6*cm, doc.width - 11.5*cm]
    t4 = Table(t4_data, colWidths=cw_t4)
    t4.setStyle(TableStyle([
        ("BACKGROUND",    (0,0), (-1,0),  AZUL_OSCURO),
        ("TEXTCOLOR",     (0,0), (-1,0),  BLANCO),
        ("BACKGROUND",    (0,-1),(-1,-1), CELESTE_BG),
        ("ROWBACKGROUNDS",(0,1), (-1,-2), [GRIS_SUAVE, BLANCO]),
        ("FONTNAME",      (0,1), (-1,-1), "Helvetica"),
        ("FONTSIZE",      (0,0), (-1,-1), 9),
        ("ALIGN",         (0,0), (-1,-1), "CENTER"),
        ("VALIGN",        (0,0), (-1,-1), "MIDDLE"),
        ("GRID",          (0,0), (-1,-1), 0.5, GRIS_BORDE),
        ("TOPPADDING",    (0,0), (-1,-1), 5),
        ("BOTTOMPADDING", (0,0), (-1,-1), 5),
    ]))
    story.append(t4)
    story.append(Paragraph(
        "* P007 y P008 pertenecen a zonas con δ = 1 &lt; δ_min = 3, "
        "por lo que se fusionan con O-Sur (δ = 4).", st_nota))
    story.append(Spacer(1, 0.25*cm))

    story.append(Paragraph("Tabla 5: Secuencia de Carga Post-Algoritmo", st_caption))
    t5_hdr = [Paragraph(f"<b>{h}</b>", S("TH", fontName="Helvetica-Bold", fontSize=8.5,
              textColor=BLANCO, alignment=TA_CENTER)) for h in
              ["Orden de Carga", "ID Pedido", "Masa (kg)", "Zona", "Nota"]]
    t5_data = [t5_hdr,
        ["1° (fondo)", "P007 / P008", "5,5", "O-Sur (fusionada)", "Última entrega"],
        ["2°", "P006", "22,0", "O-Centro", "—"],
        ["3°", "P005", "55,0", "O-Centro", "1° en O-Centro"],
        ["4°", "P004", "7,0", "P-Norte", "—"],
        ["5°", "P003", "38,0", "P-Norte", "1° en P-Norte"],
        ["6°", "P002", "12,5", "P-Centro", "—"],
        [Paragraph("<b>7° (frente)</b>", S("TB", fontName="Helvetica-Bold", fontSize=8.5,
                   textColor=AZUL_OSCURO)), "P001",
         Paragraph("<b>45,0</b>", S("TB", fontName="Helvetica-Bold", fontSize=8.5,
                   textColor=AZUL_OSCURO)),
         "P-Centro",
         Paragraph("<b>PRIMERA ENTREGA</b>", S("TB", fontName="Helvetica-Bold", fontSize=8,
                   textColor=ACENTO_VERDE))],
    ]
    cw_t5 = [2.8*cm, 2.8*cm, 2.5*cm, 4.2*cm, doc.width - 12.3*cm]
    t5 = Table(t5_data, colWidths=cw_t5)
    t5.setStyle(TableStyle([
        ("BACKGROUND",    (0,0),  (-1,0),  AZUL_OSCURO),
        ("TEXTCOLOR",     (0,0),  (-1,0),  BLANCO),
        ("BACKGROUND",    (0,-1), (-1,-1), HexColor("#E8F5E9")),
        ("ROWBACKGROUNDS",(0,1),  (-1,-2), [GRIS_SUAVE, BLANCO]),
        ("FONTNAME",      (0,1),  (-1,-1), "Helvetica"),
        ("FONTSIZE",      (0,0),  (-1,-1), 9),
        ("ALIGN",         (0,0),  (-1,-1), "CENTER"),
        ("VALIGN",        (0,0),  (-1,-1), "MIDDLE"),
        ("GRID",          (0,0),  (-1,-1), 0.5, GRIS_BORDE),
        ("TOPPADDING",    (0,0),  (-1,-1), 5),
        ("BOTTOMPADDING", (0,0),  (-1,-1), 5),
    ]))
    story.append(t5)

    story.append(PageBreak())

    # ════════════════════════════════════════════════════════
    # SECCIÓN 3
    # ════════════════════════════════════════════════════════
    for e in seccion_h1("Formulación Cuantitativa", 3):
        story.append(e)

    story.append(Paragraph("3.1 Restricción de Capacidad de Carga", st_h2))
    story.append(Paragraph(
        "Sea P = {1, 2, …, n} el conjunto de paquetes a entregar, y m<sub>i</sub> la masa del "
        "paquete i en kilogramos. La restricción fundamental de capacidad del vehículo se expresa como:", st_body))

    story.append(eq_block("Σ m<sub>i</sub>  ≤  1 000 kg      (∀ i ∈ P)", "1"))
    story.append(Spacer(1, 0.2*cm))
    story.append(Paragraph(
        "Esta restricción define el modelo como una instancia del <b>CVRP</b> "
        "(<i>Capacitated VRP</i>). La violación de la ecuación (1) implica la necesidad de dividir "
        "los pedidos en múltiples rutas o vehículos.", st_body))

    story.append(Paragraph("3.2 Masa Variable del Vehículo en el Tiempo", st_h2))
    story.append(Paragraph(
        "Sea M<sub>0</sub> la masa total del vehículo vacío y M<sub>carga</sub>(0) = Σ m<sub>i</sub> "
        "la carga inicial total. En el instante t de la ruta, habiendo ya entregado los paquetes "
        "D(t) ⊆ P, la masa combinada vehículo-carga es:", st_body))

    story.append(eq_block("M(t) = M<sub>0</sub> + Σ m<sub>i</sub>     para i ∉ D(t)", "2"))
    story.append(Spacer(1, 0.2*cm))
    story.append(Paragraph(
        "M(t) es una función <b>monótonamente decreciente</b> a lo largo de la ruta, dado que en "
        "cada entrega se descarga al menos un paquete (M<sub>0</sub> ≈ 1.500–3.500 kg para furgones "
        "urbanos típicos).", st_body))

    story.append(Paragraph("3.3 Física del Consumo: Resistencia al Rodamiento", st_h2))
    story.append(Paragraph(
        "La principal contribución física del modelo es la relación entre la masa del vehículo y "
        "el trabajo mecánico requerido para desplazarlo. La <b>fuerza de resistencia al rodamiento</b> "
        "F<sub>r</sub> actúa opuesta al sentido del movimiento:", st_body))

    story.append(eq_block("F<sub>r</sub>(t) = μ<sub>r</sub> · M(t) · g", "3"))
    story.append(Spacer(1, 0.2*cm))

    # Tabla de parámetros físicos
    params_data = [
        [Paragraph("<b>Símbolo</b>", S("TH", fontName="Helvetica-Bold", fontSize=9,
                   textColor=BLANCO, alignment=TA_CENTER)),
         Paragraph("<b>Descripción</b>", S("TH", fontName="Helvetica-Bold", fontSize=9,
                   textColor=BLANCO, alignment=TA_CENTER)),
         Paragraph("<b>Valor / Unidad</b>", S("TH", fontName="Helvetica-Bold", fontSize=9,
                   textColor=BLANCO, alignment=TA_CENTER))],
        ["μ_r", "Coeficiente de resistencia al rodamiento", "0,010 – 0,015 (adimensional)"],
        ["M(t)", "Masa total vehículo + carga en instante t", "[kg]  — según Ec. (2)"],
        ["g", "Aceleración de gravedad", "9,81 m/s²"],
        ["F_r(t)", "Fuerza de resistencia al rodamiento", "[N]"],
    ]
    cw_p = [2*cm, 9*cm, doc.width - 11*cm]
    params_t = Table(params_data, colWidths=cw_p)
    params_t.setStyle(TableStyle([
        ("BACKGROUND",    (0,0), (-1,0),  AZUL_OSCURO),
        ("TEXTCOLOR",     (0,0), (-1,0),  BLANCO),
        ("ROWBACKGROUNDS",(0,1), (-1,-1), [GRIS_SUAVE, BLANCO]),
        ("FONTNAME",      (0,1), (0,-1),  "Helvetica-Bold"),
        ("FONTNAME",      (1,1), (-1,-1), "Helvetica"),
        ("FONTSIZE",      (0,0), (-1,-1), 9),
        ("ALIGN",         (0,0), (0,-1),  "CENTER"),
        ("VALIGN",        (0,0), (-1,-1), "MIDDLE"),
        ("GRID",          (0,0), (-1,-1), 0.5, GRIS_BORDE),
        ("TOPPADDING",    (0,0), (-1,-1), 5),
        ("BOTTOMPADDING", (0,0), (-1,-1), 5),
    ]))
    story.append(params_t)
    story.append(Spacer(1, 0.2*cm))

    story.append(Paragraph(
        "El <b>trabajo mecánico</b> W realizado contra la resistencia al rodamiento al recorrer "
        "el tramo de longitud d<sub>ij</sub> entre el nodo i y el nodo j es:", st_body))
    story.append(eq_block(
        "W<sub>ij</sub>(t) = F<sub>r</sub>(t) · d<sub>ij</sub> = "
        "μ<sub>r</sub> · M(t) · g · d<sub>ij</sub>", "4"))

    story.append(Paragraph("3.4 Justificación Física de la Estrategia 'Pesado Primero'", st_h2))
    story.append(Paragraph(
        "La estrategia de entregar primero los paquetes más pesados se justifica minimizando el "
        "trabajo mecánico total acumulado. Sea S = (s<sub>1</sub>, s<sub>2</sub>, …, s<sub>n</sub>) "
        "la secuencia de entregas y d<sub>k</sub> la longitud del tramo k-ésimo. El trabajo total es:", st_body))
    story.append(eq_block(
        "W<sub>total</sub> = μ<sub>r</sub> · g · Σ<sub>k=1..n</sub> M(t<sub>k</sub>) · d<sub>k</sub>", "5"))
    story.append(Spacer(1, 0.15*cm))

    # Bloque de proposición
    prop_block = Table(
        [[Paragraph(
            "<b>Proposición:</b> Si los tramos d<sub>k</sub> son aproximadamente iguales "
            "(supuesto de homogeneidad espacial en zonas adyacentes), entonces el orden que minimiza "
            "W<sub>total</sub> es aquel que entrega primero los paquetes de mayor masa.<br/><br/>"
            "<b>Demostración informal:</b> Suponga dos paquetes A y B con m<sub>A</sub> &gt; m<sub>B</sub> "
            "y tramos iguales d. Si se entrega A antes que B, el trabajo del segundo tramo es "
            "proporcional a M<sub>0</sub> + m<sub>B</sub>. Si se invierte el orden, el trabajo del "
            "segundo tramo es proporcional a M<sub>0</sub> + m<sub>A</sub> &gt; M<sub>0</sub> + m<sub>B</sub>. "
            "Por tanto, la secuencia A → B consume menos energía mecánica. □",
            S("Prop", fontName="Helvetica", fontSize=9.5, textColor=GRIS_TEXTO,
              leading=14, alignment=TA_JUSTIFY))]],
        colWidths=[doc.width]
    )
    prop_block.setStyle(TableStyle([
        ("BACKGROUND",   (0,0), (-1,-1), HexColor("#FFF8E7")),
        ("BOX",          (0,0), (-1,-1), 1.5, HexColor("#D4A017")),
        ("LEFTPADDING",  (0,0), (-1,-1), 14),
        ("RIGHTPADDING", (0,0), (-1,-1), 14),
        ("TOPPADDING",   (0,0), (-1,-1), 10),
        ("BOTTOMPADDING",(0,0), (-1,-1), 10),
    ]))
    story.append(prop_block)
    story.append(Spacer(1, 0.25*cm))

    story.append(Paragraph("3.5 Energía Total Consumida", st_h2))
    story.append(Paragraph(
        "Integrando la potencia mecánica a lo largo de la ruta completa, la energía total "
        "consumida se estima como:", st_body))
    story.append(eq_block(
        "E<sub>total</sub> = Σ<sub>(i,j)∈R</sub> [ μ<sub>r</sub> · M<sub>ij</sub> · g · d<sub>ij</sub>  "
        "+  ½ · M<sub>ij</sub> · v<sub>ij</sub><super>2</super> · α<sub>ij</sub> ]", "6"))
    story.append(Spacer(1, 0.15*cm))
    story.append(Paragraph(
        "donde R es el conjunto de arcos recorridos, v<sub>ij</sub> es la velocidad en el tramo "
        "(i,j) y α<sub>ij</sub> ∈ {0,1} es un indicador de aceleración significativa (semáforos, "
        "ceda el paso). El primer término captura el consumo por rodamiento; el segundo, el consumo "
        "por aceleración tras detenciones.", st_body))

    story.append(PageBreak())

    # ════════════════════════════════════════════════════════
    # SECCIÓN 4
    # ════════════════════════════════════════════════════════
    for e in seccion_h1("Abstracción del Tránsito (Penalizaciones Viales)", 4):
        story.append(e)

    story.append(Paragraph("4.1 Motivación", st_h2))
    story.append(Paragraph(
        "En Chile, los datos en tiempo real sobre fases semafóricas no están disponibles como "
        "APIs públicas abiertas para uso generalizado. Frente a esta limitación, el modelo adopta "
        "el enfoque de <b>velocidades efectivas diferenciadas</b> y <b>penalizaciones de tiempo "
        "fijas</b>, consistente con metodologías de simplificación del tráfico urbano ampliamente "
        "documentadas en la literatura de VRP (Eksioglu et al., 2009).", st_body))

    story.append(Paragraph("4.2 Velocidades Efectivas", st_h2))
    story.append(Paragraph(
        "El tiempo base de recorrido del tramo (i,j) de longitud d<sub>ij</sub> se calcula como:", st_body))
    story.append(eq_block(
        "t<sub>ij</sub><super>base</super> = d<sub>ij</sub> / v<sub>ef</sub><super>(ij)</super>", "7"))
    story.append(Spacer(1, 0.15*cm))
    story.append(Paragraph("donde la velocidad efectiva depende del tipo de vía:", st_body))
    story.append(eq_block(
        "v<sub>ef</sub><super>(ij)</super> = { 35 km/h  si vía principal (arterial)\n"
        "                               { 20 km/h  si vía local (pasaje o calle menor)", "8"))

    story.append(Paragraph("4.3 Penalizaciones de Tiempo Fijas", st_h2))
    story.append(Paragraph(
        "Sobre el tiempo base se adicionan penalizaciones discretas Δt<sub>k</sub> "
        "que capturan eventos viales de impacto conocido:", st_body))
    story.append(eq_block(
        "t<sub>ij</sub><super>total</super> = t<sub>ij</sub><super>base</super> + "
        "Σ<sub>k</sub> Δt<sub>k</sub> · 1<sub>k</sub><super>(ij)</super>", "9"))

    story.append(Paragraph("Tabla 6: Penalizaciones Viales del Modelo", st_caption))
    t6_hdr = [Paragraph(f"<b>{h}</b>", S("TH", fontName="Helvetica-Bold", fontSize=8.5,
              textColor=BLANCO, alignment=TA_CENTER)) for h in
              ["Evento Vial", "Símbolo", "Penalización Δt", "Justificación"]]
    t6_data = [t6_hdr,
        ["Viraje a la izquierda", "Δt_L", "+30 segundos", "Espera por tráfico opuesto"],
        ["Cruce de Ruta 5 Sur", "Δt_R5", "+3 minutos", "Semáforo largo + tráfico de alta velocidad"],
        ["Paradero escolar", "Δt_E", "+1 minuto", "Zona de velocidad reducida obligatoria"],
        ["Zona de carga/descarga", "Δt_C", "+2 minutos", "Maniobras de estacionamiento"],
        ["Viraje a la derecha (principal)", "Δt_R", "+15 segundos", "Ceda el paso peatonal"],
    ]
    cw_t6 = [4.5*cm, 2.5*cm, 3*cm, doc.width - 10*cm]
    t6 = Table(t6_data, colWidths=cw_t6)
    t6.setStyle(TableStyle([
        ("BACKGROUND",    (0,0), (-1,0),  AZUL_OSCURO),
        ("TEXTCOLOR",     (0,0), (-1,0),  BLANCO),
        ("ROWBACKGROUNDS",(0,1), (-1,-1), [GRIS_SUAVE, BLANCO]),
        ("FONTNAME",      (0,1), (-1,-1), "Helvetica"),
        ("FONTSIZE",      (0,0), (-1,-1), 9),
        ("ALIGN",         (0,0), (-1,-1), "CENTER"),
        ("VALIGN",        (0,0), (-1,-1), "MIDDLE"),
        ("GRID",          (0,0), (-1,-1), 0.5, GRIS_BORDE),
        ("TOPPADDING",    (0,0), (-1,-1), 5),
        ("BOTTOMPADDING", (0,0), (-1,-1), 5),
    ]))
    story.append(t6)
    story.append(Spacer(1, 0.3*cm))

    story.append(Paragraph("4.4 Ejemplo de Cálculo de Tiempo de Tramo", st_h2))
    story.append(Paragraph(
        "<b>Tramo ejemplo:</b> Bodega (sector sur) → P-Centro. Distancia: 3,2 km por vía "
        "principal, con 1 cruce de Ruta 5 Sur y 2 virajes a la izquierda.", st_body))

    calc_data = [
        [Paragraph("<b>Componente</b>", S("TH", fontName="Helvetica-Bold", fontSize=9,
                   textColor=BLANCO, alignment=TA_CENTER)),
         Paragraph("<b>Cálculo</b>", S("TH", fontName="Helvetica-Bold", fontSize=9,
                   textColor=BLANCO, alignment=TA_CENTER)),
         Paragraph("<b>Resultado</b>", S("TH", fontName="Helvetica-Bold", fontSize=9,
                   textColor=BLANCO, alignment=TA_CENTER))],
        ["Tiempo base", "3,2 km ÷ 35 km/h = 0,0914 h", "5,49 min"],
        ["Cruce Ruta 5 Sur", "Δt_R5 = +3,00 min", "+3,00 min"],
        ["2 virajes a la izq.", "2 × 0,50 min = +1,00 min", "+1,00 min"],
        [Paragraph("<b>TIEMPO TOTAL</b>", S("TB", fontName="Helvetica-Bold", fontSize=9,
                   textColor=AZUL_OSCURO)),
         "5,49 + 3,00 + 1,00",
         Paragraph("<b>9,49 min</b>", S("TB", fontName="Helvetica-Bold", fontSize=9,
                   textColor=ACENTO_VERDE))],
    ]
    cw_calc = [5*cm, 7*cm, doc.width - 12*cm]
    t_calc = Table(calc_data, colWidths=cw_calc)
    t_calc.setStyle(TableStyle([
        ("BACKGROUND",    (0,0), (-1,0),  AZUL_OSCURO),
        ("TEXTCOLOR",     (0,0), (-1,0),  BLANCO),
        ("BACKGROUND",    (0,-1),(-1,-1), CELESTE_BG),
        ("ROWBACKGROUNDS",(0,1), (-1,-2), [GRIS_SUAVE, BLANCO]),
        ("FONTNAME",      (0,1), (-1,-1), "Helvetica"),
        ("FONTSIZE",      (0,0), (-1,-1), 9),
        ("ALIGN",         (0,0), (-1,-1), "CENTER"),
        ("VALIGN",        (0,0), (-1,-1), "MIDDLE"),
        ("GRID",          (0,0), (-1,-1), 0.5, GRIS_BORDE),
        ("TOPPADDING",    (0,0), (-1,-1), 5),
        ("BOTTOMPADDING", (0,0), (-1,-1), 5),
    ]))
    story.append(t_calc)
    story.append(Spacer(1, 0.25*cm))

    story.append(Paragraph("Tabla 7: Comparación de Tiempos de Tramo por Tipo de Vía", st_caption))
    t7_hdr = [Paragraph(f"<b>{h}</b>", S("TH", fontName="Helvetica-Bold", fontSize=8,
              textColor=BLANCO, alignment=TA_CENTER)) for h in
              ["Tramo", "Long.", "Vía", "t base", "Penalizaciones", "t total"]]
    t7_data = [t7_hdr,
        ["Bodega → P-Centro", "3,2 km", "Principal", "5,49 min", "+3 min (R5) + 1 min (2×Izq)", "9,49 min"],
        ["P-Centro → P-Norte", "1,5 km", "Local", "4,50 min", "+0,5 min (1×Izq)", "5,00 min"],
        ["P-Norte → O-Centro", "2,8 km", "Principal", "4,80 min", "+3 min (R5)", "7,80 min"],
        ["O-Centro → O-Sur", "1,1 km", "Local", "3,30 min", "—", "3,30 min"],
        ["O-Sur → Bodega", "4,0 km", "Principal", "6,86 min", "+3 min (R5)", "9,86 min"],
        [Paragraph("<b>TOTAL</b>", S("TB", fontName="Helvetica-Bold", fontSize=8.5,
                   textColor=AZUL_OSCURO)),
         "12,6 km", "—", "24,95 min", "+7,50 min",
         Paragraph("<b>35,45 min</b>", S("TB", fontName="Helvetica-Bold", fontSize=8.5,
                   textColor=ACENTO_VERDE))],
    ]
    cw_t7 = [4*cm, 1.5*cm, 2*cm, 2*cm, 4.5*cm, doc.width - 14*cm]
    t7 = Table(t7_data, colWidths=cw_t7)
    t7.setStyle(TableStyle([
        ("BACKGROUND",    (0,0),  (-1,0),  AZUL_OSCURO),
        ("TEXTCOLOR",     (0,0),  (-1,0),  BLANCO),
        ("BACKGROUND",    (0,-1), (-1,-1), CELESTE_BG),
        ("ROWBACKGROUNDS",(0,1),  (-1,-2), [GRIS_SUAVE, BLANCO]),
        ("FONTNAME",      (0,1),  (-1,-1), "Helvetica"),
        ("FONTSIZE",      (0,0),  (-1,-1), 8.5),
        ("ALIGN",         (0,0),  (-1,-1), "CENTER"),
        ("VALIGN",        (0,0),  (-1,-1), "MIDDLE"),
        ("GRID",          (0,0),  (-1,-1), 0.5, GRIS_BORDE),
        ("TOPPADDING",    (0,0),  (-1,-1), 4),
        ("BOTTOMPADDING", (0,0),  (-1,-1), 4),
    ]))
    story.append(t7)

    story.append(PageBreak())

    # ════════════════════════════════════════════════════════
    # SECCIÓN 5
    # ════════════════════════════════════════════════════════
    for e in seccion_h1("Función Objetivo del Modelo Mínimo", 5):
        story.append(e)

    story.append(Paragraph("5.1 Variables de Decisión", st_h2))
    story.append(Paragraph(
        "Sea x<sub>ij</sub> ∈ {0, 1} la variable binaria que toma el valor 1 si el vehículo "
        "recorre el arco (i,j) en la solución, y 0 en caso contrario. El conjunto de nodos es "
        "V = {0, 1, …, N}, donde el nodo 0 representa la bodega y los nodos 1, …, N representan "
        "los puntos de entrega.", st_body))

    story.append(Paragraph("5.2 Función Objetivo Bicriterio", st_h2))
    story.append(Paragraph(
        "El modelo minimiza simultáneamente el tiempo total de ruta y la energía mecánica "
        "consumida, ponderados por coeficientes λ<sub>T</sub> y λ<sub>E</sub>:", st_body))
    story.append(eq_block(
        "min  Z  =  λ<sub>T</sub> · T<sub>total</sub>  +  λ<sub>E</sub> · E<sub>total</sub>      "
        "con  λ<sub>T</sub> + λ<sub>E</sub> = 1", "10"))
    story.append(Spacer(1, 0.15*cm))

    story.append(Paragraph("<b>Expansión de los componentes:</b>", st_h3))
    story.append(eq_block(
        "T<sub>total</sub> = Σ<sub>(i,j)∈A</sub> x<sub>ij</sub> · "
        "[ d<sub>ij</sub> / v<sub>ef</sub><super>(ij)</super> + Σ<sub>k</sub> Δt<sub>k</sub> · "
        "1<sub>k</sub><super>(ij)</super> ]", "11"))
    story.append(Spacer(1, 0.1*cm))
    story.append(eq_block(
        "E<sub>total</sub> = Σ<sub>(i,j)∈A</sub> x<sub>ij</sub> · "
        "μ<sub>r</sub> · M<sub>ij</sub> · g · d<sub>ij</sub>", "12"))
    story.append(Spacer(1, 0.15*cm))
    story.append(Paragraph("La función objetivo expandida resulta:", st_body))
    story.append(eq_block(
        "min Z = λ<sub>T</sub> Σ x<sub>ij</sub> [ d<sub>ij</sub>/v<sub>ef</sub> + Σ Δt<sub>k</sub> · 1<sub>k</sub> ]  "
        "+  λ<sub>E</sub> Σ x<sub>ij</sub> · μ<sub>r</sub> · M<sub>ij</sub> · g · d<sub>ij</sub>", "13"))

    story.append(Paragraph("5.3 Restricciones del Modelo", st_h2))

    restricciones = [
        ("R1 — Capacidad máxima:",
         "Σ m<sub>i</sub> · x<sub>ij</sub>  ≤  1 000 kg,     ∀ j ∈ V", "14"),
        ("R2 — Cada nodo visitado exactamente una vez:",
         "Σ<sub>i∈V</sub> x<sub>ij</sub>  =  1,     ∀ j ∈ V \\ {0}", "15"),
        ("R3 — Conservación de flujo (continuidad de ruta):",
         "Σ<sub>j∈V</sub> x<sub>ij</sub>  =  Σ<sub>j∈V</sub> x<sub>ji</sub>,     ∀ i ∈ V", "16"),
        ("R4 — Eliminación de sub-rutas (restricción MTZ):",
         "u<sub>i</sub> - u<sub>j</sub> + N · x<sub>ij</sub>  ≤  N - 1,     ∀ i,j ∈ V\\{0}, i ≠ j", "17"),
        ("R5 — Dominio de variables:",
         "x<sub>ij</sub> ∈ {0, 1},     u<sub>i</sub> ≥ 0,     ∀ (i,j) ∈ A", "18"),
    ]

    for label, formula, num in restricciones:
        story.append(Paragraph(f"<b>{label}</b>", S("RL",
            fontName="Helvetica-Bold", fontSize=9.5,
            textColor=AZUL_OSCURO, spaceBefore=8, spaceAfter=2)))
        story.append(eq_block(formula, num))
        story.append(Spacer(1, 0.1*cm))

    story.append(Paragraph("5.4 Escenarios de Calibración de Ponderadores", st_h2))
    story.append(Paragraph("Tabla 8: Escenarios de Ponderación de la Función Objetivo", st_caption))

    t8_hdr = [Paragraph(f"<b>{h}</b>", S("TH", fontName="Helvetica-Bold", fontSize=9,
              textColor=BLANCO, alignment=TA_CENTER)) for h in
              ["Escenario", "λ_T", "λ_E", "Interpretación"]]
    t8_data = [t8_hdr,
        ["E1: Tiempo prioritario", "0,80", "0,20", "Máxima velocidad de entrega"],
        ["E2: Energía prioritaria", "0,20", "0,80", "Máxima eficiencia de combustible"],
        ["E3: Balance equitativo", "0,50", "0,50", "Compromiso entre ambos criterios"],
        ["E4: Solo tiempo (TSP)", "1,00", "0,00", "TSP clásico ponderado"],
    ]
    cw_t8 = [5*cm, 2*cm, 2*cm, doc.width - 9*cm]
    t8 = Table(t8_data, colWidths=cw_t8)
    t8.setStyle(TableStyle([
        ("BACKGROUND",    (0,0), (-1,0),  AZUL_OSCURO),
        ("TEXTCOLOR",     (0,0), (-1,0),  BLANCO),
        ("ROWBACKGROUNDS",(0,1), (-1,-1), [GRIS_SUAVE, BLANCO]),
        ("FONTNAME",      (0,1), (-1,-1), "Helvetica"),
        ("FONTSIZE",      (0,0), (-1,-1), 9),
        ("ALIGN",         (0,0), (-1,-1), "CENTER"),
        ("VALIGN",        (0,0), (-1,-1), "MIDDLE"),
        ("GRID",          (0,0), (-1,-1), 0.5, GRIS_BORDE),
        ("TOPPADDING",    (0,0), (-1,-1), 5),
        ("BOTTOMPADDING", (0,0), (-1,-1), 5),
    ]))
    story.append(t8)
    story.append(Spacer(1, 0.35*cm))

    story.append(Paragraph("5.5 Diagrama del Flujo del Modelo Completo", st_h2))

    # Diagrama de flujo como tabla visual
    flujo_items = [
        (AZUL_OSCURO, BLANCO, "ENTRADA DEL SISTEMA",
         "Lista de pedidos: { id, masa_kg, dirección, zona_destino }"),
        (AZUL_MEDIO, BLANCO, "PASO 1 — Clasificación en Bodega",
         "Cálculo de δ(z) · Fusión dinámica · Verificación Σmᵢ ≤ 1000 kg · Ordenamiento DESC"),
        (ACENTO_VERDE, BLANCO, "PASO 2 — Construcción del Grafo Vial",
         "Nodos: Bodega ∪ Zonas · Arcos (i,j): dᵢⱼ, tipo de vía, penalizaciones · tᵢⱼ = dᵢⱼ/vₑf + ΣΔtₖ"),
        (HexColor("#7B3F00"), BLANCO, "PASO 3 — Optimización (Función Objetivo)",
         "min Z = λ_T · T_total + λ_E · E_total  |  Sujeto a restricciones R1–R5"),
        (HexColor("#2E7D32"), BLANCO, "SALIDA — Ruta Óptima",
         "Secuencia: Bodega → z₁ → z₂ → … → zₙ → Bodega  |  Métricas: T_total, E_total, Z"),
    ]

    for bg, fg, titulo, desc in flujo_items:
        row = Table(
            [[Paragraph(f"<b>{titulo}</b>", S("FT", fontName="Helvetica-Bold", fontSize=9.5,
                        textColor=fg, leading=14)),
              Paragraph(desc, S("FD", fontName="Helvetica", fontSize=9,
                                textColor=fg, leading=13))]],
            colWidths=[4.5*cm, doc.width - 4.5*cm]
        )
        row.setStyle(TableStyle([
            ("BACKGROUND",   (0,0), (0,0),   bg),
            ("BACKGROUND",   (1,0), (1,0),   HexColor("#" + "".join(f"{min(255, int(c*255) + 60):02x}"
                                                        for c in bg.rgb()))),
            ("TOPPADDING",   (0,0), (-1,-1), 8),
            ("BOTTOMPADDING",(0,0), (-1,-1), 8),
            ("LEFTPADDING",  (0,0), (-1,-1), 10),
            ("RIGHTPADDING", (0,0), (-1,-1), 10),
            ("VALIGN",       (0,0), (-1,-1), "MIDDLE"),
            ("LINEBELOW",    (0,0), (-1,-1), 2, BLANCO),
        ]))
        story.append(row)

    story.append(PageBreak())

    # ════════════════════════════════════════════════════════
    # SECCIÓN 6 — REFERENCIAS
    # ════════════════════════════════════════════════════════
    for e in seccion_h1("Referencias Bibliográficas", 6):
        story.append(e)

    refs = [
        ("Eksioglu, B., Vural, A. V., & Reisman, A.",
         "(2009).",
         "The vehicle routing problem: A taxonomic review.",
         "Computers & Industrial Engineering, 57(4), 1472–1483.",
         "https://doi.org/10.1016/j.cie.2009.05.009"),

        ("Toth, P., & Vigo, D. (Eds.).",
         "(2002).",
         "The vehicle routing problem.",
         "Society for Industrial and Applied Mathematics (SIAM).",
         "https://doi.org/10.1137/1.9780898718515"),

        ("Bektas, T., & Laporte, G.",
         "(2011).",
         "The pollution-routing problem.",
         "Transportation Research Part B: Methodological, 45(8), 1232–1250.",
         "https://doi.org/10.1016/j.trb.2011.02.004"),

        ("Demir, E., Bektaş, T., & Laporte, G.",
         "(2014).",
         "The bi-objective pollution-routing problem.",
         "European Journal of Operational Research, 232(3), 464–478.",
         "https://doi.org/10.1016/j.ejor.2013.08.002"),

        ("Pillac, V., Gendreau, M., Guéret, C., & Medaglia, A. L.",
         "(2013).",
         "A review of dynamic vehicle routing problems.",
         "European Journal of Operational Research, 225(1), 1–11.",
         "https://doi.org/10.1016/j.ejor.2012.08.015"),

        ("Kuo, Y.",
         "(2010).",
         "Using simulated annealing to minimize fuel consumption for the time-dependent vehicle routing problem.",
         "Computers & Industrial Engineering, 59(1), 157–165.",
         "https://doi.org/10.1016/j.cie.2010.03.012"),

        ("Laporte, G.",
         "(2009).",
         "Fifty years of vehicle routing.",
         "Transportation Science, 43(4), 408–416.",
         "https://doi.org/10.1287/trsc.1090.0301"),

        ("Mercer, A., & Toth, P.",
         "(1992).",
         "Time dependent vehicle routing problems: Formulations, properties and heuristic algorithms.",
         "Transportation Science, 26(3), 185–200.",
         ""),
    ]

    for i, (autores, anio, titulo, revista, doi) in enumerate(refs):
        doi_text = f"  {doi}" if doi else ""
        ref_text = (
            f"<b>{autores}</b> {anio} <i>{titulo}</i> "
            f"{revista}{doi_text}"
        )
        ref_par = Paragraph(ref_text, S("Ref",
            fontName="Helvetica", fontSize=9,
            textColor=GRIS_TEXTO, leading=13.5,
            leftIndent=24, firstLineIndent=-24,
            spaceAfter=8, alignment=TA_JUSTIFY))

        num_par = Table([[Paragraph(f"[{i+1}]", S("RefN",
                fontName="Helvetica-Bold", fontSize=9,
                textColor=AZUL_MEDIO, alignment=TA_CENTER)),
                ref_par]],
            colWidths=[0.8*cm, doc.width - 0.8*cm])
        num_par.setStyle(TableStyle([
            ("VALIGN",       (0,0), (-1,-1), "TOP"),
            ("TOPPADDING",   (0,0), (-1,-1), 2),
            ("BOTTOMPADDING",(0,0), (-1,-1), 2),
            ("LEFTPADDING",  (0,0), (-1,-1), 0),
            ("RIGHTPADDING", (0,0), (-1,-1), 0),
            ("LINEBELOW",    (0,0), (-1,-1), 0.3, GRIS_BORDE),
        ]))
        story.append(num_par)

    story.append(Spacer(1, 0.5*cm))

    # Nota metodológica final
    nota_final = Table(
        [[Paragraph(
            "<b>Nota metodológica:</b> Los valores numéricos presentados en las tablas de ejemplo "
            "(masas, distancias, tiempos) son hipotéticos y sirven exclusivamente para ilustrar el "
            "funcionamiento del modelo. La calibración con datos reales de pedidos de Talca se "
            "realizará en fases posteriores del proyecto.",
            S("NF", fontName="Helvetica-Oblique", fontSize=9,
              textColor=HexColor("#444"), leading=13, alignment=TA_JUSTIFY))]],
        colWidths=[doc.width]
    )
    nota_final.setStyle(TableStyle([
        ("BACKGROUND",   (0,0), (-1,-1), GRIS_SUAVE),
        ("BOX",          (0,0), (-1,-1), 1, GRIS_BORDE),
        ("LEFTPADDING",  (0,0), (-1,-1), 12),
        ("RIGHTPADDING", (0,0), (-1,-1), 12),
        ("TOPPADDING",   (0,0), (-1,-1), 10),
        ("BOTTOMPADDING",(0,0), (-1,-1), 10),
    ]))
    story.append(nota_final)

    # ── Build ────────────────────────────────────────────────
    doc.build(story, canvasmaker=AcademicTemplate)
    print(f"PDF generado: {output_path}")


if __name__ == "__main__":
    out = "/mnt/user-data/outputs/Avance1_Optimizacion_Rutas_Talca.pdf"
    build_pdf(out)