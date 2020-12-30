# Pracownia 1 z Języków Programowania - Julia Majkowska
## Struktura
Parser i lexer zostały zaczerpnięte z kodu dołączonego do 11 rozdziału TAPL i zmodyfikowane na potrzeby zadania.Moduł support został wprost zaczerpnięty z tego rozdziału.  

Moduł syntax definiuje typy rozszerzonych wyrażeń lambda z użytymi indeksami De Bruijina , prostych wyrażeń arytmetycznych z indeksami oraz wynikowych prostych wyrażeń z nazywanymi zmiennymi. W tym module jest również zdefiniowane odcukrzanie wyrażeń o rozszerzonej składni do prostych oraz printery. 

Moduł core definiuje redukcję do weak head normal form, iteracyjną redukcję wyrażenia oraz porównywanie termów. Redukcja do weak head normal form jest implementacją uogólnionej orginalnej maszyny Krivina. Redukcje obsługują również wyrażenia zawierające zmienne wolne.

Moduł main oraz makefile i .depend również zostały zaczerpnięte z TAPL i zmodyfikowany. 

## Kompilacja
make

## Uruchomienie
./f -i nazwa_pliku_wejsciowego -o nazwa_pliku_wyjsciowego