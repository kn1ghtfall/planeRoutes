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

## Functii folosite


1. proictare() : Cerinta 1 a problemei, sunt introduse comenzi ce descriu schimbarile produse asupra arhipelagului. 

    - [conexiune IslandX IslandY] : Se va afisa OK daca exista conexiune directa intre cele doua insule si NO in caz contrar

    - [legatura IslandX] : se cere legatura directa a Insulei X cu celelate insule din arhipelag
        - OBS: In cazul in care nu exista nicio legatura NU se afiseaza nimic.

    - [adauga_zbor IslandX IslandY cost] : se va adauga un drum direct de durata cost intre Insula X si Insula Y
        - OBS: cost reprezinta durata in minute.

    - [anulare_zbor IslandX IslandY]: se va sterge drumul direct intre Insula X si Insula Y

    - [max_resurse]: se va afisa numarul de resurse distincte de pe tot arhipelagul, urmat de numele resurselor separate printr-un spatiu in ordine lexicografica

    - [max_cantitate resursa]: se va afisa insula (respectiv insulele) cu cantitatea cea mai mare de resursa disponibila

2. analiza() : Cerinta 2 a problemei, se calculeaza durata parcurgerii unui drum de la o insula la alta intr-un timp cat mai scurt. Aici se analizeaza eficenta drumurilor.
    - [drum_zbor IslandX IslandY] : se cere afisarea drumului cel mai scurt (din punct de vedere al duratei) de la Insula X la Insula Y.    
        - OBS: In cazul in care NU exista drum se va afisa NO

    - [timp_zbor IslandX IslandY]: se cere afisarea duratei minime in conditii de
    distribuire instanta
        - OBS: In cazul in care NU se poate determina timpul zborului se va afisa INF.

    - [min_zbor IslandX IslandY]: se cere afisarea duratei minime in conditiile
    adaugarii stationarii pe insulele intermediare pana la Insula Y


3. gestiunea() : Cerinta 3 a problmei, rezolvata prin backtracking. Sunt generate permutarile avioanelor ce sunt in surplus pe una din insulele arhipelagului. Se afiseaza toate modurile in care celelalte insule ar putea primi aceste avioane, insulele vecine avand prioritate in fata celor mai indepartate.
    - Nu trebuie distribuit niciun avion => Se va afisa input-ului de la cerinta curenta (nr insule,
    toleranta, etc - exact in forma gasita in fisierul date.in)
    - Exista un numar prea mare de avioane, iar problema nu poate fi rezolvata => Se va afisa
    mesajului: ,,Stack overflow!"
    - O insula distribuie avioane celor cu care se afla in legatura directa => Se va afisa fiecare
    aranjament posibil pentru fiecare insula
    - Mai multe insule distribuie avioane, dar nu intra in conflict => Similar punctul anterior
    - Mai multe insule distribuie avioane, dar intra in conflit => prioritatea este data de ordinea
    insulelor, in mod crescator
    - O insula distribuie avioane, dar insulele cu care este conectata nu au capacitatea necesara sa
    accepte atatea avioane => in ordine crescatoare, in functie de legaturi, prima insula o sa distribuie
    avioane pentru a facilita locurile necesare
    - Mai multe insule distribuie avioane, dar insulele cu care sunt conectate nu au capacitate sa le
    primeasca.

4. Functii pentru a rezolva cerintele 1, 2, 3 precum algortmul lui Dijkstra, stive ce stocheaza cuvinte si functii ce deschid fisiere pentru citire sau scriere.

## Rularea Programului

./avion fisier_input fisier_output


## Note

Toate blocurile de memorie ce au fost alocate au fost eliberate. Nu sunt scurgeri de memorie.