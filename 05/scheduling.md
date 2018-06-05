# Aufagbe 5: Scheduling

## Shortest Job First
### Reihenfolge
1. E (18 Minuten)
2. B (20 Minuten)
3. C (25 Minuten)
4. D (28 Minuten)
5. A (30 Minuten)

### Mittlere Verweilzeit
T = (5 * 18 + 4 * 20 + 3 * 25 + 2 * 28 + 30) : 5

T = 66,2 Minuten


## First Come First Served
### Reihenfolge
Ist die Eingangsreihenfolge
1. A (30 Minuten)
2. B (20 Minuten)
3. C (25 Minuten)
4. D (28 Minuten)
5. E (18 Minuten)

### Mittlere Verweilzeit
T = (5 * 30 + 4 * 20 + 3 * 25 + 2 * 28 + 18) : 5

T = 75,8 Minuten


## Prioritätsgesteuertes Scheduling
### Reihenfolge
1. C (25 Minuten)
2. D (28 Minuten)
3. E (18 Minuten)
4. A (30 Minuten)
5. B (20 Minuten)

### Mittlere Verweilzeit
T = (5 * 25 + 4 * 28 + 3 * 18 + 2 * 30 + 20) : 5

T = 74,2 Minuten


## Round Robin - konstante Zeitscheibe, unabhänig von der Priorität
|         A         |   B   |   C   |   D   |    E   |              Zeit |
|:-----------------:|:-----:|:-----:|:-----:|:------:|------------------:|
|         30        |   20  |   25  |   28  | **18** |                 0 |
|         12        | **2** |   7   |   10  |        |       5 * 18 = 90 |
|         10        |       | **5** |   8   |        |   90 + 4 * 2 = 98 |
|         5         |       |       | **3** |        |  98 + 3 * 5 = 113 |
|       **2**       |       |       |       |        | 113 + 2 * 3 = 119 |
|                   |       |       |       |        | 119 + 1 * 2 = 121 |

### Mittlere Verweilzeit
T = (90 + 98 + 113 + 119 + 121) : 5

T = 108,2 Minuten

## Round Robin - Zeitscheibendauer proportional zur Priorität
|  A(2) |  B(1) |  C(5) |  D(4) |  E(3) | CPU-Anteile | Durchlaufzeit | Verweilzeit der im Durchlauf terminierten Prozesse |
|:-----:|:-----:|:-----:|:-----:|:-----:|------------:|--------------:|---------------------------------------------------:|
|   30  |   20  |   25  |   28  |   18  |             |               |                                                    |
|   20  |   15  |   -   |   8   |   3   |          15 |       75 min. |                                             T = 75 |
|   18  |   14  |       |   4   |   -   |          10 |       10 min. |                                   T = 75 + 10 = 85 |
|   16  |   13  |       |   -   |       |           7 |        7 min. |                                    T = 85 + 7 = 92 |
|   -   |   5   |       |       |       |           3 |       24 min. |                                  T = 92 + 24 = 116 |
|       |   -   |       |       |       |           1 |        5 min. |                                  T = 116 + 5 = 121 |

### Mittlere Verweilzeit
T = (75 + 85 + 92 + 116 + 121) : 5

T = 97,8 Minuten
