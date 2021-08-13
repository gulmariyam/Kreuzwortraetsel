compile: main.c main.h lib/crossword.c lib/crossword.h lib/list.c lib/list.h lib/word.c lib/word.h
	gcc main.c main.h lib/crossword.c lib/crossword.h lib/list.c lib/list.h lib/word.c lib/word.h -o words -Wall -Wmissing-prototypes  -Werror -std=c99 -g

clean:
	rm -f words
	rm -rf ausgabe
	rm -rf diff
	rm -rf valgrind

testausgabe: compile eingabe/0.txt eingabe/5.txt eingabe/10.txt eingabe/20.txt eingabe/50.txt
	mkdir -p ausgabe
	./words eingabe/0.txt ausgabe/0.txt
	./words eingabe/5.txt ausgabe/5.txt
	./words eingabe/10.txt ausgabe/10.txt
	./words eingabe/20.txt ausgabe/20.txt
	./words eingabe/50.txt ausgabe/50.txt

diff: clean compile testausgabe
	./diff.sh

valgrind_korrekte_eingabe: clean compile valgrind_korrekte_eingabe.sh
	./valgrind_korrekte_eingabe.sh

valgrind_fehlerhafte_eingabe: clean compile valgrind_fehlerhafte_eingabe.sh
	./valgrind_fehlerhafte_eingabe.sh

valgrind: valgrind_korrekte_eingabe valgrind_fehlerhafte_eingabe

run: diff valgrind
