# Graph Visualization and Processing Application

Această aplicație oferă utilizatorilor o interfață grafică pentru crearea, vizualizarea și procesarea grafurilor folosind algoritmi avansați. Aplicația suportă grafuri orientate și neorientate și este construită utilizând C++ cu biblioteca Qt.

## Caracteristici principale
- **Grafuri orientate și neorientate:** Setează orientarea grafului în funcție de necesități.
- **Algoritmi MST (Minimum Spanning Tree):**
  - Implementări pentru **Prim**, **Kruskal** și **Borůvka**.
  - Evidențierea muchiilor din MST în interfața grafică.
- **Gestionarea nodurilor și muchiilor:**
  - Adaugă noduri și muchii cu costuri definite de utilizator.
  - Previne suprapunerea nodurilor.
- **Verificare și procesare a grafului:**
  - Determinarea componentelor conexe.
  - Detectarea dacă graful este un arbore.
  - Identificarea rădăcinii grafului (dacă există).
- **Evidențierea arborilor generici și colorarea componentelor conexe.**

## Interfața grafică
- Creată cu **Qt**, interfața permite utilizatorilor să interacționeze vizual cu graful:
  - Adăugarea de noduri prin clic dreapta.
  - Selectarea nodurilor și conectarea acestora prin muchii cu un cost definit.
  - Butoane și opțiuni pentru diverse funcționalități (ex. rularea algoritmilor MST).
- Evidențierea diferitelor tipuri de muchii utilizând culori:
  - **MST (Borůvka):** Albastru.
  - **Arbori generici:** Roșu.
  - Restul muchiilor: Negru.

## Cum se utilizează
### Cerințe preliminare
- Instalează **Qt Framework**.
- Asigură-te că fișierele necesare, precum matricea de adiacență (`adjacency_matrix.txt`), sunt configurate corect.

### Configurare și compilare
1. Clonează acest repository:
   ```bash
   git clone https://github.com/username/graph-app.git
