# Aknakereső - Felhasználói dokumentáció

## Játék leírása

- A program egy klasszikus aknakereső játékot valósít meg. A játék célja, hogy a játékos felfedezze a mezőket anélkül, hogy aknára lépne. A mezők és aknák száma a nehezségi szinttől függően változik. Az aknák elhelyezkedése véletlenszerű.
- A játék időre megy, amennyiben a játékos felfedezi az összes mezőt aknák nélkül, megnyeri a játékot és felkerül a dicsőséglistára a megadott idővel és begépelt névvel.

## Megjelenés és vezérlés

### Menü
- A játék indításakor egy menü jelenik meg, ahol a játékos kiválaszthatja a nehézségi szintet (könnyű, közepes, nehéz), kiléphet a játékból vagy megnézheti a dicsőséglistákat.
- A dicsőséglista opción belül nehézségi szint alapján választhatóak ki az eredmények.
- A nehézségi szintek a következőképpen vannak definiálva:
  - Könnyű: 9x9 mező, 10 akna
  - Közepes: 16x16 mező, 40 akna
  - Nehéz: 30x16 mező, 99 akna
- A menüben a játékos a billentyűzet segítségével navigálhat (fel/le nyilak) és a `Enter` gombbal választhat.
- A kijelölt opciót egy `>` és fehér háttér jelöli.


### Játék felület
- A kiválasztott nehézségi szint után a játék elindul.
- A felső részen az irányítások és a játék állapota (aknák száma) látható.
- Az alsó részen a játéktábla jelenik meg, ahol a mezők és aknák helyzete látható.
- A játék konzolos alkalmazásként fut, és a játékos a billentyűzet segítségével navigálhat a mezők között.
- Pontos jelölések:
  - Nem felderített mező: `#`
  - Felderített mező (nincs környező akna): `.`
  - Felderített mező (környező aknák száma): `1-8`
  - Aknára lépés: `X` (játék vége)
  - Jelölt akna: `f`
  - Játékos pozícióját fehér háttér jelöli

- Pontos utasítások:
  - Mozgás: nyilak (fel, le, balra, jobbra)
  - Mező felfedése: `1`
  - Mező megjelölése aknaként: `2`
  - Kilépés a játékból: `q`

- Ha tábla határán túl lép a játékos, a pozíció a tábla másik oldalán folytatódik.

### Dicsőséglista

- A dicsőséglista az összes eredményt eltárolja. Minden bejegyzés tartalmazza a játékos nevét, időt és nehézséget.
- Menüből kiválasztva (nehézségenként külön), táblázatos formában (név, idő). A legjobb 10 eredmény jelenik meg.
- Győzelem után név bekérése (max. 20 karakter).

