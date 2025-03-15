# Projekt z kursu systemy operacyjne 2
## Opis
Aplikacja implementuje problem jedzących filozofów.
Problem ucztujących filozofów jest prezentacją problemu synchronizacji pracujących współbieżnie procesów.
Pięciu filozofów siedzi przy stole i każdy wykonuje jedną z dwóch czynności – albo je, albo rozmyśla. Stół 
jest okrągły, przed każdym z nich znajduje się miska ze spaghetti, a pomiędzy każdą sąsiadującą parą filozofów 
leży widelec, a więc każda osoba ma przy sobie dwie sztuki – po swojej lewej i prawej stronie. Ponieważ jedzenie 
potrawy jest trudne przy użyciu jednego widelca, zakłada się, że każdy filozof korzysta z dwóch. Dodatkowo nie ma 
możliwości skorzystania z widelca, który nie znajduje się bezpośrednio przed daną osobą.

**Źródło - *[Wikipedia](https://pl.wikipedia.org/wiki/Problem_ucztuj%C4%85cych_filozof%C3%B3w)***

## Sposób rozwiązania
Skorzystano z rozwiązania przy użyciu hierarchii zasobów.
W ten sposób kolejność dostępu do zasobów jest ustalona przez określony porządek. a ich zwalnianie następuje 
w odwrotnej kolejności, oraz że dwa zasoby niepowiązane relacją porządku nie mogą zostać użyte przez jednego 
filozofa w tym samym czasie.
 W tym przykładzie oznaczmy zasoby (widelce) numerami od 1 do 5 – w ustalonym porządku – oraz ustalmy, że 
jednostki (filozofowie) zawsze najpierw podnoszą widelec oznaczony niższym numerem, a dopiero potem ten 
oznaczony wyższym. Następnie, zwracając widelce, najpierw oddają widelec z wyższym numerem, a potem z niższym. 
W tym wypadku, jeśli czterech filozofów jednocześnie podniesie swoje widelce z niższymi numerami, na stole 
pozostanie widelec z najwyższym numerem, przez co piąty filozof nie będzie mógł podnieść żadnego. Ponadto tylko
jeden filozof ma dostęp do widelca z najwyższym numerem, więc będzie on mógł jeść dwoma widelcami.

**Źródło - *[Wikipedia - Rozwiązanie przy użyciu hierarchii zasobów](https://pl.wikipedia.org/wiki/Problem_ucztuj%C4%85cych_filozof%C3%B3w)***

## Program
Program nie jest złożony. Składa się z jednej metody *philosopher* oraz funkji *main*.
W funkcji *main* pobieramy ilość filozofów, która jest przekazywana jako argument przy uruchamianiu programu.
Oprócz tego inicjalizujemy mutexy, i tworzymy wątki dla filozofów. Na końcu mutexy są niszczone.**
**W funkcji *philosopher* jest dokonana implementacja samego problemu. To w tej metodzie występuje wypisanie 
informacji, którzy filozofowie myślą, które widelce są pobierane oraz którzy filozfowie jedzą.

## Instrukcja uruchomienia projektu
### Aby uruchomić projekt należy konać następujące czynności:

- Sklonować projekt na swój lokalny komputer  
- Upewnij się że masz zainstalowanego *make* za pomocą komendy `which make` 
    - Jeśli nie masz zaintalowanego *make* użyj komendy `sudo apt-get install build-essential`
- Włącz terminal w katalogu twojego projektu i wpisz komendę `make`
- Na końcu użyj komendy `./Nazwa_twojego_projektu [liczba filozofów]`

## Wątki
-  ***philosophersThread* - reprezentuje każdego z filozofów w problemie "jedzących filozofów".**

Każdy filozof to osobny wątek wykonujący funkcję *philosopher*.
Wątki te są tworzone dynamicznie, a ich działanie polega na myśleniu, 
podnoszeniu widelców, jedzeniu i ponownym myśleniu w nieskończonej pętli. Dzięki mutexowi *pthread_mutex_t*
blokujemy i odblokowujemy dostęp do zasobów (widelców), aby zapobiec konfliktom i jednoczesnemu dostępowi.
Ich hierarchiczne blokowanie zapobiega deadlockom*

## Sekcje krytyczne
### W programie występują dwie sekcje krytyczne w fukncji *philosopher*
-  *waitForFork[]* - dwaj filozofowie mogą podnieść ten sam widelec w tym samym czasie.
-  *std::cout* - wątki mogą mieszać komunikaty na ekranie.
### Rozwiązanie:
- W przypadku tablicy *waitForFork[]* użyto *pthread_mutex_lock()* i *pthread_mutex_unlock()* dla każdego widelca.
co pozwala na zablokowanie i odblokowanie mutexu a tym samym uniknięcie jednoczesnego dostępu do zasobów.
- Dla *std::cout* sytuacja wygląda podobnie jak w przypadku widelcy. Wykorzystujemy dodatkowy mutex dla strumienia
wyjścia co pozwala uniknąć nakładania się tekstów.
