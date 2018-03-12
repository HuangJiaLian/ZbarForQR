CC = gcc
LIB = -lm -lzbar -lpng
decoder: main.c
	${CC} main.c -o  decoder ${LIB}

zbarimg: zbarimg.c
	${CC} zbarimg.c -o  zbarimg ${LIB}

scanimg: scan_image.c
	${CC} scan_image.c -o  scan_image ${LIB}

run:
	./decoder 1.png


clear:
	rm decoder
