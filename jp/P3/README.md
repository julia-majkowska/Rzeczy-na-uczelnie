# Pracownia 2 z Języków Programowania - Julia Majkowska

## Obsługiwane wyrażenia
Program obługuje rachunek lambda z typami prostymi rozszerzonym o wyjątki, liczby naturalne (reprezentowane jako ocamlowe liczby) z dodawaniem, odejmowaniem i mnożeniem i przyrównywaniem dwóch liczb, wartości boolowskie, fix oraz if. 

## Struktura
Parser i lexer zostały zaczerpnięte z kodu dołączonego do 11 rozdziału TAPL i zmodyfikowane na potrzeby zadania. Moduł support został wprost zaczerpnięty z tego rozdziału.  

Moduł syntax definiuje typy obsługiwanych wyrażeń w rachunku lambda z typami, wartości oraz printery. Wyjątki oraz zmienne są oznaczane indeksami de Bruijina.

Moduł core definiuje redukcję do weak head normal form za pomocą semantyki dużych kroków ze środowiskiem oraz type checking ( bez śledzenie wyjątków). Para fix wraz z domknięciem została dodany do poprawnych wartości i jest ewaluowana leniwie przy odczytywaniu jej ze środowiska. 

Moduł main oraz makefile i .depend również zostały zaczerpnięte z TAPL i zmodyfikowane. Program oddczytuje pierwsze poprawne wyrażenie z pliku wejściowego wykonuje próbę typowania wyrażenia, jeśli wyrażenie ma typ wywołuje ewaluację. 

## Kompilacja
make

## Uruchomienie
./f -i nazwa_pliku_wejsciowego -o nazwa_pliku_wyjsciowego
Przykładowe wyrażenia można znaleźć w pliku test.f