# Ces cibles ne sont pas des vrais fichiers
.PHONY: clean, install, real-clean

# On désactive toutes les règles implicites
.SUFFIXES:

# Déclarations de constantes
CFLAGS = -O4 -W -Wall -Werror

# 
tp1: tp1.o tp1main.o
	gcc -o tp1 tp1.o tp1main.o
# Règle générique : $< == le fichier .c compilé
%.o: %.c
	gcc $(CFLAGS) -c -o $@ $<

clean:
	rm -f *.o

# Appel récursif à make avec ce Makefile
real-clean:
	make clean
	rm -f bin/prog.exe

# Appel récursif à make avec un Makefile dans un autre répertoire
install:
	mv prog.exe bin/
	make -C bin/ install
