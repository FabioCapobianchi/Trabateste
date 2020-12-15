all:
	gcc -g -Wall -o servidor servidor.c comuns.c
	gcc -g -Wall -o clififo clififo.c
	$(BASH)  ./ambVar.sh
servidor:
	gcc -c servidor.c
clififo:
	gcc -c clififo.c
clit:
	gcc -c comuns.c
clean:
	$(RM) servidor servidor.o comuns.o
	$(RM) clififo clififo.o
