# Tema 2: Marele arhipelag Eao-Zinci [SDA]

# Descriere

- Arhipelagul Eao-Zinci din Orientul Indepartat este in plina dezvoltare. Fiecare insula din arhipelag
  produce zilnic o serie de resurse. Acestea sunt folosite local si/sau distribuite catre alte insule
  folosind flota aeriană Eao-Zinci.
- Rutele de transport sunt configurate in fiecare dimineata pentru a asigura distribuția optimă a
  resurselor (etapa de proiectare).
- Intrand in era automatizării, conducatorii arhipelagului doresc sa treacă la următorul pas si să poata
  sa-si distribuie resursele in cel mai eficient mod posibil (etapa de analiza).
- Mai mult, pentru a elimina potențialele conflicte in ce privește accesul la flota aeriana, in fiecare
  seara, avioanele sunt redistribuite între insule (etapa de gestiune).

# Obiective

1.  Înțelegerea conceptului de funcționare și implementarea structurilor de date (grafuri, algortmi de parcurgere grafuri, folosirea algoritmilor precum greedy, backtracking)

2.  Operarea cu structurile de date

3.  Implementarea funcționalităților practice care să folosească conceptele menționate anterior



# Rezolvare

# Autor: Coconu Robert-Iulian 

## Implementare

Programul citeste dintr-un fisier datele despre insulele aflate in arhipelag, precum si resursele acestora. Pentru cerinta de gestionare se adauga date suplimentare ce restructureaza legaturile dintre insule si ofera informatii despre avioanele aflate pe respectivele insule.

## Structuri de date folosite

1. Resursa: retine datele despre cate o resursa de pe o insula
2. Island: retine date despre o insula din arhipelag, precum numele acesteia, numarul de resurse, resursele, numarul de avioane, id-urile acesora si tolul avioanelor.
3. Arhipelag: stocheaza date despre insulele idn arhipelag. Arhipelagul a fost reprezentat ca un graf in rezolvarea probelmei. In structura este declarata matricea de adiacenta cu numarul de noduri si muchii.
4. Stack: este o stiva ce stocheaza cuvinte. Este folosita pentru a afisa in ordine crescatoare din punct de vedere lexicografic


## Rularea Programului

./avion fisier_input fisier_output


## Note

Toate blocurile de memorie ce au fost alocate au fost eliberate. Nu sunt scurgeri de memorie.
