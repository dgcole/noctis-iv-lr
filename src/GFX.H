/*

	Primitive di disegno 2d per gfx. 320x200x256

*/

#ifndef __ASSEMBLY_H
#include <assembly.h>
#endif

#ifndef __ALLOC_H
#include <alloc.h>
#endif

#ifndef __GFX_H
#define __GFX_H

// Tabella per le scanline: attualmente gestite da ASSEMBLY.H

//unsigned riga[200];

//void initscanlines()
//{
//	int n;
//	for (n=0; n<200; n++)
//		riga[n] = 320 * n;
//}

// Tracciamento linee 2d.

int lwx = 0, upx = 319;
int lwy = 0, upy = 199;

long L;
long temp;

void Segmento (long x, long y,
	       long x2, long y2,
	       unsigned char colore,
	       char abrush)
{
	long ptr;
	long a, b;

	if (x==x2) {
		if (x<lwx) return;
		if (x>upx) return;
		if (y>y2) {
			temp = y;
			y = y2;
			y2 = temp;
		}
		if (y<lwy) y = lwy;
		if (y>upy) y = upy;
		y2++;
		if (y2<lwy) y2 = lwy;
		if (y2>upy) y2 = upy;
		ptr = riga[y] + x;
		L = 320; if (abrush) L *= abrush;
		while (ptr<riga[y2]) {
			adapted[ptr] = colore;
			ptr += L;
		}
		return;
	}

	a = x2-x;
	if (a<0) {
		temp = x2; x2 = x; x = temp;
		temp = y2; y2 = y; y = temp;
		a = x2-x;
	}

	L = a;
	b = y2-y;
	if (b>0) {
		if (b>L)
			L=b;
	}
	else {
		if (-b>L)
			L=-b;
	}
	L++;

	x *= 65536;
	y *= 65536;
	x2 *= 65536;
	a *= 65536; a /= L;
	b *= 65536; b /= L;

	if (abrush) {
		a *= abrush;
		b *= abrush;
	}

	int *xwrd = (int *) &x; xwrd ++;
	int *ywrd = (int *) &y; ywrd ++;

	/* Traccia il segmento tramite DMA. */
	while (x<x2) {
		if (*ywrd>lwy&&*ywrd<upy&&*xwrd>lwx&&*xwrd<upx) {
			ptr = riga[*ywrd] + *xwrd;
			adapted[ptr] = colore;
		}
		y += b;
		x += a;
	}
}

void Rettangolo (long x, long y, long l, long a,
		 unsigned char colore)
{
	Segmento (x, y, x+l, y, colore, 0);
	Segmento (x+l, y, x+l, y+a, colore, 0);
	Segmento (x+l, y+a, x, y+a, colore, 0);
	Segmento (x, y+a, x, y+1, colore, 0);
	if (x+l >= 0 && y+a >= 0 && x+l < 320 && y+a < 200) adapted[(y+a)*320+x+l] = colore;
}

void psico_Rettangolo (long x, long y, long l, long a,
		       unsigned char colore, char abrush)
{
	Segmento (x, y, x+l, y, colore, abrush);
	Segmento (x+l, y, x+l, y+a, colore, abrush);
	Segmento (x+l, y+a, x, y+a, colore, abrush);
	Segmento (x, y+a, x, y+1, colore, abrush);
	if (x+l >= 0 && y+a >= 0 && x+l < 320 && y+a < 200) adapted[(y+a)*320+x+l] = colore;
}

void Blocco (long x, long y, long l, long a,
	     unsigned char colore)
{
	if (x >= 320) return;
	if (x < 0) { l += x; x = 0; }
	if (x+l < 0) return;
	if (x+l >= 320) l = 320 - x;
	if (l <= 0) return;

	if (y >= 200) return;
	if (y < 0) { a += y; y = 0; }
	if (y+a < 0) return;
	if (y+a >= 200) a = 200 - y;
	if (a <= 0) return;

	unsigned ptr = 320*y + x;
	unsigned lim_x = ptr + l;
	unsigned lim_y = 320 * (y+a);

	while (ptr<lim_y) {
		while (ptr<lim_x) {
			adapted[ptr] = colore;
			ptr++;
		}
		lim_x += 320;
		ptr += 320;
		ptr -= l;
	}
}

void psico_Blocco (long x, long y, long l, long a,
	     unsigned char colore)
{
	if (x >= 320) return;
	if (x < 0) { l += x; x = 0; }
	if (x+l < 0) return;
	if (x+l >= 320) l = 320 - x;
	if (l <= 0) return;

	if (y >= 200) return;
	if (y < 0) { a += y; y = 0; }
	if (y+a < 0) return;
	if (y+a >= 200) a = 200 - y;
	if (a <= 0) return;

	unsigned ptr = 320*y + x;
	unsigned lim_x = ptr + l;
	unsigned lim_y = 320 * (y+a);

	colore -= a/2;

	while (ptr<lim_y) {
		while (ptr<lim_x) {
			adapted[ptr] = colore;
			ptr++;
		}
		lim_x += 320;
		ptr += 320;
		ptr -= l;
		colore++;
	}
}

// Bitmap 6x6 uppercase font (53 colonne per 28 righe).

unsigned char font[65][6] = {
0, 0, 0, 0, 0, 0, // Spazio.
8, 8, 8, 8, 0, 8, // Punto esclamativo.
20, 20, 0, 0, 0, 0, // Virgolette.
0, 20, 62, 20, 62, 20, // Cancelletto.
0, 0, 0, 0, 0, 0, // Dollaro (manca, Š un separatore verticale).
36, 4, 8, 8, 16, 18, // Percento.
0, 28, 34, 62, 32, 28, // E commerciale (rappresentata da una e minuscola).
4, 8, 0, 0, 0, 0, // Apice.
4, 8, 8, 8, 8, 4, // Parentesi tonda aperta.
16, 8, 8, 8, 8, 16, // Parentesi tonda chiusa.
40, 16, 40, 0, 0, 0, // Asterisco.
8, 8, 62, 8, 8, 0, // Pi—.
0, 0, 0, 0, 4, 8, // Virgola.
0, 0, 62, 0, 0, 0, // Meno.
0, 0, 0, 0, 0, 8, // Punto.
4, 4, 8, 8, 16, 16, // Barra.
28, 34, 42, 42, 34, 28, // Zero.
4, 12, 4, 4, 4, 14, // Uno.
28, 34, 4, 8, 16, 62, // Due.
28, 2, 28, 2, 34, 28, // Tre.
2, 6, 10, 18, 63, 2, // Quattro.
30, 16, 28, 2, 2, 60, // Cinque.
14, 16, 60, 34, 34, 28, // Sei.
62, 34, 4, 4, 8, 8, // Sette.
28, 34, 28, 34, 34, 28, // Otto.
28, 34, 34, 30, 4, 56, // Nove.
0, 8, 0, 0, 8, 0, // Duepunti.
0, 8, 0, 8, 8, 16, // Punto e virgola.
4, 8, 16, 8, 4, 0, // Minore.
0, 0, 30, 0, 30, 0, // Uguale.
16, 8, 4, 8, 16, 0, // Maggiore.
28, 34, 2, 4, 0, 4, // Punto interrogativo.
63, 63, 63, 63, 63, 63, // Chiocciola (Š un blocco unico).
28, 34, 34, 62, 34, 34, // A.
60, 34, 60, 34, 34, 60, // B.
28, 34, 32, 32, 34, 28, // C.
60, 34, 34, 34, 34, 60, // D.
62, 32, 48, 32, 32, 62, // E.
62, 32, 48, 32, 32, 32, // F.
28, 34, 32, 38, 34, 28, // G.
34, 34, 62, 34, 34, 34, // H.
8, 8, 8, 8, 8, 8, // I.
6, 2, 2, 2, 34, 28, // J.
34, 36, 56, 40, 36, 34, // K.
32, 32, 32, 32, 32, 62, // L.
34, 54, 42, 34, 34, 34, // M.
34, 50, 42, 38, 34, 34, // N.
28, 34, 34, 34, 34, 28, // O.
60, 34, 34, 60, 32, 32, // P.
28, 34, 34, 34, 36, 26, // Q.
60, 34, 34, 60, 34, 34, // R.
28, 32, 28, 2, 2, 28, // S.
62, 8, 8, 8, 8, 8, // T.
34, 34, 34, 34, 34, 28, // U.
34, 34, 34, 20, 20, 8, // V.
34, 34, 42, 42, 54, 34, // W.
34, 20, 8, 20, 34, 34, // X.
34, 34, 20, 8, 8, 8, // Y.
62, 2, 4, 8, 16, 62, // Z.
0, 4, 4, 31, 14, 4, // Parentesi quadra aperta (freccetta gi—).
8, 8, 4, 4, 2, 2, // Barra rovescia.
4, 14, 31, 4, 4, 0, // Parentesi quadra chiusa (freccetta su).
34, 38, 38, 46, 26, 2, // Ordinale femminile (Š il simbolo dei micron).
0, 0, 0, 0, 0, 63, // Sottolinea.
8, 4, 0, 0, 0, 0 // Accento.
// qui andrebbero le minuscole.
};

unsigned char pwr2[8] = { 1, 2, 4, 8, 16, 32, 64, 128 };

#define NORMALE  0
#define ITALICO  1
#define NERETTO  2
#define CENTRATO 3
#define ALL_DX   4

void Testo (long x, long y, char far *messaggio,
	    unsigned char colore, unsigned stile)
{
	unsigned char r, i, v;
	unsigned incr = 314;
	unsigned char flag;
	unsigned c = 0;
	unsigned _ptr;
	char bit;

	if (stile==ITALICO) incr = 313;
	if (stile==ALL_DX|stile==CENTRATO) {
		flag = 0; while (messaggio[flag]) flag++;
		if (stile==ALL_DX)
			x += 319 - 6*flag;
		else
			x += (319 - 6*flag) / 2;
	}

	unsigned ptr = 320*y + x;

	while (messaggio[c]>31) {
		_ptr = ptr;
		i = messaggio[c] - 32;
		flag = 0;
		ripeti:
		for (r=0; r<6; r++) {
			v = font[i][r];
			for (bit=5; bit>=0; bit--) {
				// disattivazione limite necessaria x AVP
				// e programmi simili, non permessa per
				// programmi come CERTAPPR con scorrimento
				// dei campi.
				//if (x >= 0 && x < 320 && y >= 0 && y < 200) {
					if (messaggio[c]=='$') {
						/* Per elenchi AVP, come separatore. */
						if (bit>1&&bit<5) {
							adapted[ptr] = 255 - (ptr >> 10) - 2 * (bit-1);
							adapted[ptr+320] = adapted[ptr];
						}
					}
					if (v&pwr2[bit]) adapted[ptr] = colore;
				//}
				ptr++;
				x++;
			}
			ptr += incr;
			x -= 6;
		}
		if (!flag&&stile==NERETTO) {
			ptr = _ptr + 1;
			flag = 1;
			goto ripeti;
		}
		ptr = _ptr + 6;
		x += 6;
		y++;
		c++;
	}
}

void Copia (unsigned char far *dest, unsigned char far *sorg, unsigned x, unsigned y, int l, int a)
{
	// ds:si partenza
	// es:di arrivo

	if (l<2) return;
	if (a<1) return;

	if (l%2) l++;
	l /= 2;

	asm {
		push ax
		push bx
		push cx
		push dx
		push es
		push ds
		push si
		push di
		pushf
		cld
	}

	x = 320*y + x;
	_BX = x + 320*a;
	_AX = x; _DX = l;

	asm {
		lds si, dword ptr sorg
		les di, dword ptr dest
		add bx, si
		add si, ax
		add di, ax
		mov ax, 320
		sub ax, dx
		sub ax, dx
	}

chiclo:	asm {
		cmp si, bx
		jnb fine
		mov cx, dx
	    rep	movsw
		add si, ax
		add di, ax
		jmp chiclo
	}

fine:	asm {
		popf
		pop di
		pop si
		pop ds
		pop es
		pop dx
		pop cx
		pop bx
		pop ax
	}
}

void halfbrite (int x, int y, int l, int a, char incr)
{
	int c, k;

	for (c=x; c<x+l; c++) {
		for (k=y; k<y+a; k++)
			adapted[c+riga[k]] += incr;
	}
}

void tx (int x, int y, char *t, char attrib)
{
	Testo (x+1, y+1, t, 0, attrib);
	Testo (x, y, t, 64, attrib);
}

#endif