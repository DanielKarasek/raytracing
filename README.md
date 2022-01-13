# raytracing
V tomto projektu jsem dělal ray tracing v jazyce c++. Prímárně jde o projekt kde se učím konceptům. Core projektu využívá online knihy Raytracing in one weekend.
Ten se dále pokouším zefektivnit (zvýšení užití chache, jader nebo snížení režíí na dereference) a rozšířit, aby se dali raytracovat i modely využívající trojuhélníky.
V složce images lze nalézt průběžné obrázky z vývoje s popiskem.

## Spuštění
Pro spuštění je třeba c++20 (používám gcc 9.4, takže pokud máte novější tak změnte make z c++2a na c++20). Pomocí make run dojde k přeložení a spuštění.
Make clean vyčistí. A prostý make pouze složí. Za momentální rendrovaný obrázek(který je renderovaný) neručím. K získání je potřeba přesměrovat std výstup na soubor s koncovkou PPM. Pro rychlost je dobré v maku oddělat -g flag a nahradit -O2 flagem.


