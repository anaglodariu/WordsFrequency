Pasi in implementare:
- generarea tabelei Hash 
- alocarea memoriei si initializarea structurii pentru subelement (in care am cuvantul citit si frecventa lui)
- crearea in vectorul de pointeri TLG (v) din tabela Hash a listelor in care am ca informatie in fiecare celula structura pentru element (in care am lungimea cuvantului citit si lista (in care voi avea ca informatie in fiecare celula structura pentru subelement))
- crearea atat a listelor, cat si a sublistelor se face prin inserarea directa in acestea conform unei reguli de comparare (functiile CmpDupaLung si CmpSubListe)
- functia CmpDupaLung creeaza o lista ordonata crescator dupa lungimea cuvintelor citite
- functia CmpSubListe creeaza o lista ordonata descrescator dupa frecventa cuvintelor citite, iar cuvintele cu frecventa egala sunt ordonate lexicografic
- la eliberarea memoriei din tabela Hash, distrug mai intai fiecare sublista din fiecare lista ( dau free la informatia din celula si apoi la celula ) , dupa distrug si listele la fel

Punctaj obtinut la rularea pe calculatorul propriu:

ana@DESKTOP-RPATT8R:~/sda/tema1$ ./check.sh 
gcc -Wall -g functiiLG.c functii-tabHash.c testHash.c -o tema1

                          = Tema 1 SD HashTable =

[in0.txt]...........................................passed  [05/85]
[VALGRIND: in0.txt].................................passed  [02/85]
[in1.txt]...........................................passed  [05/85]
[VALGRIND: in1.txt].................................passed  [02/85]
[in2.txt]...........................................passed  [05/85]
[VALGRIND: in2.txt].................................passed  [02/85]
[in3.txt]...........................................passed  [10/85]
[VALGRIND: in3.txt].................................passed  [02/85]
[in4.txt]...........................................passed  [10/85]
[VALGRIND: in4.txt].................................passed  [02/85]
[in5.txt]...........................................passed  [10/85]
[VALGRIND: in5.txt].................................passed  [02/85]
[in6.txt]...........................................passed  [10/85]
[VALGRIND: in6.txt].................................passed  [02/85]
[in7.txt]...........................................passed  [10/85]
[VALGRIND: in7.txt].................................passed  [02/85]
[in8.txt]...........................................passed  [10/85]
[VALGRIND: in8.txt].................................passed  [02/85]
[in9.txt]...........................................passed  [10/85]
[VALGRIND: in9.txt].................................passed  [02/85]

                                           Total: [105/85]