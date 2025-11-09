# Minesweeper - Félkész dokumentáció

## Indítás

### Előfeltételek
- **Windows**: MinGW GCC compiler + MSYS2
- **Linux**: GCC compiler

### Fordítás
- A Makefile mindkét platformon működik.
- Mivel a játék ANSI kódokat használ megjelenítéshez, Windows alatt érdemes MSYS2 terminált vagy powershellt használni.
- Powershellben lehet, hogy engedélyezni kell a ANSI kódok használatát.
- Ajánlott futtatás előtt a terminált törölni, illetve nagyítani a méretét. Ha nincs elég hely, a megjelenítés hibás lehet.
```bash
# Mappák létrehozása
mkdir -p bin
mkdir -p obj
# One-liner (összes forrás fájl fordítása egyszerre)
gcc -Wall -Wextra -I include src/main.c src/Board.c src/Tile.c src/Menu.c src/Display.c src/Timer.c -o bin/minesweeper.exe

# Make-vel (ha telepítve van)
make run
```

## Jelenlegi funkciók

- **Menü** - játék indítása, navigáció
- **Játékmenet** - alapvető funkciók (felfedés, zászlózás), navigáció, színes kirajzolás.
- **Játék logika**
  - Első kattintás garantáltan nem tartalmaz aknát
  - Az előfedett mezők mutatják a körülöttük lévő aknák számát
  - Nullás mezők rekurzívan felfedődnek
  - Nyerés: Összes biztonságos mező felfedése
  - Vesztés: Aknára kattintás

- **Platform kompatibilitás**
  - Windows: Arrow key kezelés (224 speciális kód)
  - Linux: ANSI escape szekvenciák (ESC [A/B/C/D)

- **Memória**
  - Dinamikus tábla generálás
  - Memória felszabadítás kilépéskor

- **Szerkezet**
  - Külön fájlok a különböző moduloknak
  - Fejlécek a funkciók deklarálásához
  - Érthető elnevezések, összetett adatszerkezetek
  - Makefile a fordításhoz és futtatáshoz

## Jövőbeli fejlesztések

- Timer (eltelt idő)
- Dicsőség lista idő és nehézség alapján
  - Győzelem esetén elkéri a játékos nevét
  - Mentés fájlba
  - Menüben megtekinthető listázás
- Custom nehézségnél figyelmeztetés, ha túl sok aknát választ a felhasználó
- Újrajátszhatóság

