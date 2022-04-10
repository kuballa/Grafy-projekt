Wpisywanie grafu wpisujemy za pomocą listy sąsiedztwa do pliku file.txt
pierwsza kolumna oznacza wierzchołek z którego rozpoczynamy krawędź
druga kolumna oznacza wierzchołek na którym kończymy krawędź
trzecia kolumna oznacza wage tej krawędzi

np
            -----
            |   |
           .| 0 |.
          . |   | .
        5.  -----  .12
        .           .
       V             V
    -----           -----
    |   |     6     |   |
    | 1 |..........>| 2 |
    |   |           |   |
    -----           -----

to
0 1 5
0 2 12
1 2 6