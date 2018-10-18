/*

	Noctis galactic guide / SET command.
	GOES Net Module.

*/

const double MAX_OBJECTS_PER_STAR = 80;

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <conio.h>
#include <math.h>
#include <dos.h>
#include <io.h>

//////////////////////////////////////////////////////////////////////////////

char   *situation_file  = "..\\DATA\\Current.BIN";

char   sync               = 1;		// 0
char   anti_rad           = 1;          // 1
char   pl_search          = 0;          // 2
char   field_amplificator = 0;          // 3
char   ilight             = 63;         // 4
char   ilightv            = 1;          // 5
char   charge             = 3;          // 6
char   revcontrols        = 0;          // 7
char   ap_targetting      = 0;          // 8
char   ap_targetted       = 0;          // 9
char   ip_targetting      = 0;          // 10
char   ip_targetted       = -1;		// 11
char   ip_reaching        = 0;          // 12
char   ip_reached         = 0;          // 13
char   ap_target_spin     = 0;          // 14
char   ap_target_r        = 0;          // 15
char   ap_target_g        = 0;          // 16
char   ap_target_b        = 0;          // 17
char   nearstar_spin      = 0;          // 18
char   nearstar_r         = 0;          // 19
char   nearstar_g         = 0;          // 20
char   nearstar_b         = 0;          // 21
char   gburst	          = 0;          // 22
char   menusalwayson      = 1;		// 23
char   depolarize  	  = 0;          // 24
int    sys                = 4;		// 25
int    pwr                = 15000;	// 27
int    dev_page           = 0;		// 29
int    ap_target_class    = 0;		// 31
int    f_ray_elapsed	  = 0;		// 33
int    nearstar_class     = 0;		// 35
int    nearstar_nop       = 0;		// 37
float  pos_x              = 0;		// 39
float  pos_y              = 0;		// 43
float  pos_z              = -500;	// 47
float  user_alfa          = 0;		// 51
float  user_beta          = 0;		// 55
float  navigation_beta    = 0;		// 59
float  ap_target_ray      = 0;		// 63
float  nearstar_ray       = 1000;	// 67
double dzat_x             = +3797120;
double dzat_y             = -4352112;
double dzat_z             = -925018;
double ap_target_x        = 0;
double ap_target_y        = 1E9;
double ap_target_z        = 0;
double nearstar_x         = 0;
double nearstar_y         = 1E9;
double nearstar_z         = 0;
double helptime           = 0;
double ip_target_initial_d= 0;
double requested_approach_coefficient = 1;
double current_approach_coefficient = 1;
double reaction_time      = 0.01;
char   fcs_status[11]     = "STANDBY";
int    fcs_status_delay   = 0;
int    psys               = 4;
double ap_target_initial_d= 0;
double requested_vimana_coefficient = 1;
double current_vimana_coefficient = 1;
double vimana_reaction_time = 0.01;
char   lithium_collector  = 0;
char   autoscreenoff	  = 0;
char   ap_reached         = 0;
int    lifter		  = 0;
double secs		  = 0;

void unfreeze ()
{
	int fh = _open (situation_file, 0);
	if (fh>-1) {
		_read (fh, &sync, 244);
		_close (fh);
	}
}

//////////////////////////////////////////////////////////////////////////////

unsigned char far *adaptor = (unsigned char far *) 0xA0000000;

char digimap[65*5] = {
	 0, 0, 0, 0, 0, // 32. spazio vuoto
	 2, 2, 2, 0, 2, // 33. punto esclamativo
	 5, 0, 0, 0, 0, // 34. virgolette
	 0, 0, 3, 5, 5, // 35. cancelletto (rappresentato da una piccola n.)
	 2, 2, 6, 2, 2, // 36. sistro
	 1, 4, 2, 1, 4, // 37. percento
	 0, 0, 2, 0, 0, // 38. e commericale (non Š possibile visualizzarla)
	 0, 2, 2, 0, 0, // 39. apice
	 4, 2, 2, 2, 4, // 40. parentesi tonda aperta
	 1, 2, 2, 2, 1, // 41. parentesi tonda chiusa
	 0, 0, 7, 2, 2, // 42. asterisco
	 0, 2, 7, 2, 0, // 43. segno pi—
	 0, 0, 0, 2, 1, // 44. virgola
	 0, 0, 7, 0, 0, // 45. segno meno
	 0, 0, 0, 0, 2, // 46. punto
	 0, 4, 2, 1, 0, // 47. barra destrorsa
	 7, 5, 5, 5, 7, // 48. 0
	 3, 2, 2, 2, 7, // 49. 1
	 7, 4, 7, 1, 7, // 50. 2
	 7, 4, 6, 4, 7, // 51. 3
	 4, 6, 5, 7, 4, // 52. 4
	 7, 1, 7, 4, 7, // 53. 5
	 7, 1, 7, 5, 7, // 54. 6
	 7, 4, 4, 4, 4, // 55. 7
	 7, 5, 7, 5, 7, // 56. 8
	 7, 5, 7, 4, 4, // 57. 9
	 0, 2, 0, 2, 0, // 58. duepunti
	 0, 2, 0, 2, 1, // 59. punto e virgola
	 4, 2, 1, 2, 4, // 60. minore
	 0, 7, 0, 7, 0, // 61. uguale
	 1, 2, 4, 2, 1, // 62. maggiore
	 7, 4, 6, 0, 2, // 63. punto interrogativo
	 0, 2, 0, 0, 0, // 64. a commerciale (non visualizzabile)
	 7, 5, 7, 5, 5, // 65. A
	 7, 5, 3, 5, 7, // 66. B
	 7, 1, 1, 1, 7, // 67. C
	 3, 5, 5, 5, 3, // 68. D
	 7, 1, 3, 1, 7, // 69. E
	 7, 1, 3, 1, 1, // 70. F
	 7, 1, 5, 5, 7, // 71. G
	 5, 5, 7, 5, 5, // 72. H
	 2, 2, 2, 2, 2, // 73. I
	 4, 4, 4, 5, 7, // 74. J
	 5, 5, 3, 5, 5, // 75. K
	 1, 1, 1, 1, 7, // 76. L
	 7, 7, 5, 5, 5, // 77. M
	 5, 7, 7, 5, 5, // 78. N
	 7, 5, 5, 5, 7, // 79. O
	 7, 5, 7, 1, 1, // 80. P
	 7, 5, 5, 1, 5, // 81. Q
	 7, 5, 3, 5, 5, // 82. R
	 7, 1, 7, 4, 7, // 83. S
	 7, 2, 2, 2, 2, // 84. T
	 5, 5, 5, 5, 7, // 85. U
	 5, 5, 5, 5, 2, // 86. V
	 5, 5, 7, 7, 5, // 87. W
	 5, 5, 2, 5, 5, // 88. X
	 5, 5, 7, 2, 2, // 89. Y
	 7, 4, 2, 1, 7, // 90. Z
	 0, 0, 6, 2, 2, // 91. parentesi quadra aperta
	 0, 1, 2, 4, 0, // 92. barra sinistrorsa
	 2, 2, 6, 0, 0, // 93. parentesi quadra chiusa
	 2, 2, 2, 2, 2, // 94. ordinale femminile
	 0, 0, 0, 0, 7, // 95. sottolinea
	 1, 2, 0, 0, 0  // 96. accento
};

void areaclear (unsigned char far *dest, int x, int y,
		int x2, int y2, int l, int h, unsigned char pattern)
{
	unsigned p;

	if (x<0) x = 0;
	if (y<0) y = 0;

	if (x2>=320) x2 = 319;
	if (y2>=200) y2 = 199;

	if (x2>0) l = x2 - x;
	if (y2>0) h = y2 - y;

	if (x+l>=320) l = 320 - x;
	if (y+h>=200) h = 200 - y;

	if (l<1 || h<1) return;

	p = 320 * y + x;

	asm {	push es
		pusha
		pushf
		cld
		les di, dword ptr dest
		add di, p
		mov al, pattern
		db 0x66; shl ax, 8
		mov al, pattern
		db 0x66; shl ax, 8
		mov al, pattern
		db 0x66; shl ax, 8
		mov al, pattern }
ac_nextl: asm {	push di
		mov cx, l
		shr cx, 2
		jcxz ac_bytes
		db 0xf3 // rep stosd
		db 0x66
		db 0xab }
ac_bytes: asm { mov cx, l
		and cx, 3
		jcxz ac_endl
		rep stosb }
ac_endl:  asm { pop di
		add di, 320
		dec h
		jnz ac_nextl
		popf
		popa
		pop es }
}

void wrouthud (unsigned x, unsigned y, unsigned l, char *text)
{
	int j, i, n;
	unsigned spot;

	n = 0; if (!l) l = 32767;
	spot = y * 320 + x;

	while (text[n] && n < l) {
		j = (text[n] - 32) * 5;
		for (i = 0; i < 5; i++) {
			if (digimap[j + i] & 1) adaptor[spot+0] = 191 - adaptor[spot+0];
			if (digimap[j + i] & 2) adaptor[spot+1] = 191 - adaptor[spot+1];
			if (digimap[j + i] & 4) adaptor[spot+2] = 191 - adaptor[spot+2];
			spot += 320;
		}
		spot -= 320 * 5;
		spot += 4;
		n++;
	}
}

void warn (char *text, int line)
{
	int w2 = strlen(text) * 2;

	areaclear (adaptor, 160 - w2 - 1, 100 + line * 8, 0, 0, w2*2 + 2, 8, 127);
	wrouthud (160 - w2, 100 + line * 8 + 1, NULL, text);
}

//////////////////////////////////////////////////////////////////////////////

char msgbuffer[77];
char *divider = "&&&&&&&&&&&&&&&&&&&&&";

void msg (char *string)
{
	int x;

	strcpy (msgbuffer, string);
	msgbuffer[21] = 0;
	printf (msgbuffer);

	x = strlen(msgbuffer);
	while (x < 21) {
		printf (" ");
		x++;
	}
}

double 	object_id = 12345;
char   	object_label[25];
double 	s_object_id = 12345;
char   	s_object_label[25];

double	subject_id = 12345;
double  idscale = 0.00001;

int	sts;
char	query;

long	round;
int 	i, fh, gh;
int 	analyzed_sectors_range;
char	*file = "..\\DATA\\STARMAP.BIN";
char    *comm = "..\\DATA\\COMM.BIN";

char	outbuffer[40];
char	textbuffer[40];
char	parbuffer[160];
char	nullbuffer[128];
char	objectname[21];
char	subjectname[21];

char find (char *starname)
{
	int p, n, ctc, found;
	ctc = strlen (starname);
	if (ctc > 20 || ctc <= 0) {
		msg ("INVALID OBJECT NAME.");
		return(0);
	}
	n = 0;
	found = 0;
	lseek (fh, 4, SEEK_SET);
	while (_read (fh, &s_object_id, 8) && _read (fh, &s_object_label, 24) == 24) {
		if (memcmp (&s_object_id, "Removed:", 8)) {
			if (!memcmp (s_object_label, starname, ctc)) {
				n++;
				memcpy (object_label, s_object_label, 24);
				object_id = s_object_id;
				memcpy (subjectname, object_label, 20);
				subject_id = object_id;
				if (object_label[21] == 'S') found = 1;
				if (object_label[21] == 'P') found = 2;
				p = 20;
				while (p >= 0) {
					if (s_object_label[p] != 32) {
						if (s_object_label[p] == starname[p])
							return (found);
						else
							break;
					}
					p--;
				}
			}
		}
	}
	if (!n)
		msg ("OBJECT NOT FOUND.");
	if (n > 1) {
		msg ("AMBIGUOUS SEARCH KEY:");
		msg ("PLEASE EXPAND NAME...");
		msg (divider);
		msg ("POSSIBLE RESULTS ARE:");
		msg (divider);
		lseek (fh, 4, SEEK_SET);
		while (_read (fh, &s_object_id, 8) && _read (fh, &s_object_label, 24) == 24) {
		if (memcmp (&s_object_id, "Removed:", 8) && !memcmp (s_object_label, starname, ctc)) {
			s_object_label[21] = 0;
			msg (s_object_label);
		}}
		msg (divider);
		found = 0;
	}
	return (found);
}

//////////////////////////////////////////////////////////////////////////////

const double deg = M_PI / 180;

#define qt_M_PI   4*M_PI/3

#define star_classes    12
#define planet_types    10
#define avgmoons        4
#define log2avgmoons	2
#define maxbodies	20 * avgmoons

char class_rgb[3*star_classes] = {
	63, 58, 40,
	30, 50, 63,
	63, 63, 63,
	63, 30, 20,
	63, 55, 32,
	32, 16, 10,
	32, 28, 24,
	10, 20, 63,
	63, 32, 16,
	48, 32, 63,
	40, 10, 10,
	00, 63, 63
};

int class_ray[star_classes] = { 5000, 15000, 300, 20000, 15000, 1000, 3000,
				2000, 4000, 1500, 30000, 250 };

int class_rayvar[star_classes] = { 2000, 10000, 200, 15000, 5000, 1000, 3000,
				   500, 5000, 10000, 1000, 10 };

int class_act[star_classes] = { 2, 4, 1, 6, 5, 10, 100, 1, 2, 1, 10, 1 };

char class_planets[star_classes] = { 12, 18, 8, 15, 20, 3, 0, 1, 7, 20, 2, 5 };

char   nearstar_p_type       [maxbodies];
int    nearstar_p_owner	     [maxbodies];
char   nearstar_p_moonid     [maxbodies];
double nearstar_p_ring       [maxbodies];
double nearstar_p_tilt       [maxbodies];
double nearstar_p_ray        [maxbodies];
double nearstar_p_orb_ray    [maxbodies];
double nearstar_p_orb_seed   [maxbodies];
double nearstar_p_orb_tilt   [maxbodies];
double nearstar_p_orb_orient [maxbodies];
double nearstar_p_orb_ecc    [maxbodies];

int planet_possiblemoons[] = { 1, 1, 2, 3, 2, 2, 18, 2, 3, 20, 20 };

const double planet_orb_scaling=  5.0;
const double avg_planet_sizing =  2.4;
const double moon_orb_scaling  = 12.8;
const double avg_moon_sizing   =  1.8;

double avg_planet_ray[] = { 0.007, 0.003, 0.010, 0.011, 0.010,
			    0.008, 0.064, 0.009, 0.012, 0.125,
			    5.000 };

double laststar_x, laststar_y, laststar_z;
float  zrandom (int range) { return (random(range) - random(range)); }
double nearstar_identity;
int    nearstar_nob;

char isthere (double star_id)
{
	char warnbuffer[41];

	double laststar_id;

	double sidlow = star_id - idscale;
	double sidhigh = star_id + idscale;

	unsigned sx, sy, sz;

	unsigned visible_sectors_x = analyzed_sectors_range;
	unsigned visible_sectors_y = analyzed_sectors_range;
	unsigned visible_sectors_z = analyzed_sectors_range;

	long   	advance = 100000;
	long   	sect_x, sect_y, sect_z;

	long   	align_m = 100000 * visible_sectors_z;
	long   	align_e = 100000 * visible_sectors_y;

	sect_x = (dzat_x - visible_sectors_x*50000) / 100000; sect_x *= 100000;
	sect_y = (dzat_y - visible_sectors_y*50000) / 100000; sect_y *= 100000;
	sect_z = (dzat_z - visible_sectors_z*50000) / 100000; sect_z *= 100000;

	asm {	mov ax, visible_sectors_x
		mov sx, ax }
e_while:asm {	mov ax, visible_sectors_y
		mov sy, ax }
m_while:asm {	mov ax, visible_sectors_z
		mov sz, ax }
i_while:asm {	db 0x66, 0xBB, 0x50, 0xC3, 0x00, 0x00 // mov ebx, 50000
		db 0x66; mov ax, word ptr sect_x
		db 0x66; mov dx, word ptr sect_z
		db 0x66; add ax, dx
		db 0x66; mov cx, ax
		db 0x66; mov dx, ax
		db 0x66, 0x81, 0xE2, 0xFF, 0xFF, 0x01, 0x00 // and edx, 0x0001FFFF
		db 0x66; add dx, word ptr sect_x
		db 0x66; sub dx, bx
		db 0x66; mov word ptr laststar_x, dx
		db 0x66; imul dx
		db 0x66; add dx, ax
		db 0x66; add cx, dx
		db 0x66, 0x81, 0xE2, 0xFF, 0xFF, 0x01, 0x00 // and edx, 0x0001FFFF
		db 0x66; add dx, word ptr sect_y
		db 0x66; sub dx, bx
		db 0x66; mov word ptr laststar_y, dx
		db 0x66; mov ax, cx
		db 0x66; imul dx
		db 0x66; add dx, ax
		db 0x66, 0x81, 0xE2, 0xFF, 0xFF, 0x01, 0x00 // and edx, 0x0001FFFF
		db 0x66; add dx, word ptr sect_z
		db 0x66; sub dx, bx
		db 0x66; mov word ptr laststar_z, dx
		fild dword ptr laststar_x
		fst  laststar_x
		fmul idscale
		fild dword ptr laststar_y
		fst  laststar_y
		fmul idscale
		fild dword ptr laststar_z
		fst  laststar_z
		fmul idscale
		fmulp
		fmulp
		fst laststar_id
		fcomp sidlow
		fstsw ax
		sahf
		jb i_next
		fld laststar_id
		fcomp sidhigh
		fstsw ax
		sahf
		jb y_end }
i_next:	asm {	db 0x66; mov ax, word ptr advance
		db 0x66; add word ptr sect_z, ax
		dec sz
		jz i_end
		jmp i_while }
i_end:	  asm { db 0x66; mov dx, word ptr align_m
		db 0x66; sub word ptr sect_z, dx
		db 0x66; add word ptr sect_y, ax
		dec sy
		jz m_end
		jmp m_while }
m_end:	  asm { db 0x66; mov dx, word ptr align_e
		db 0x66; sub word ptr sect_y, dx
		db 0x66; add word ptr sect_x, ax
		dec sx
		jz e_end
		db 0x66; pusha }
		if (sts > 100) {
			sprintf (warnbuffer, "SLICE %d OF %d", visible_sectors_x - sx, visible_sectors_x);
			warn (warnbuffer, 0);
			while (kbhit()) {
				if (getch() == 27) {
					asm { db 0x66; popa }
					return (0);
				}
			}
		}
	  asm { db 0x66; popa
		jmp e_while }
e_end:	  return (0);
y_end:	  return (1);
}

void extract_ap_target_infos ()
{
	srand (ap_target_x/100000*ap_target_y/100000*ap_target_z/100000);

	ap_target_class = random (star_classes);
	ap_target_ray = ((float)class_ray[ap_target_class] + (float)random(class_rayvar[ap_target_class])) * 0.001;

	ap_target_r = class_rgb[3*ap_target_class+0];
	ap_target_g = class_rgb[3*ap_target_class+1];
	ap_target_b = class_rgb[3*ap_target_class+2];

	ap_target_spin = 0;
	if (ap_target_class==11) ap_target_spin = random (30) + 1;
	if (ap_target_class==7) ap_target_spin = random (12) + 1;
	if (ap_target_class==2) ap_target_spin = random (4) + 1;
}

void prepare_nearstar ()
{
	int    n, c, q, r, s, t;
	double key_radius;

	nearstar_class = ap_target_class;
	nearstar_x = ap_target_x;
	nearstar_y = ap_target_y;
	nearstar_z = ap_target_z;
	nearstar_ray = ap_target_ray;
	nearstar_spin = ap_target_spin;
	nearstar_r = ap_target_r;
	nearstar_g = ap_target_g;
	nearstar_b = ap_target_b;

	nearstar_identity = nearstar_x/100000*nearstar_y/100000*nearstar_z/100000;

	srand ((long)nearstar_x%10000*(long)nearstar_y%10000*(long)nearstar_z%10000);

	nearstar_nop = random (class_planets[nearstar_class] + 1);

	for (n=0; n<nearstar_nop; n++) {
		nearstar_p_owner[n]	 = -1;
		nearstar_p_orb_orient[n] = (double) deg * (double) random (360);
		nearstar_p_orb_seed[n]   = 3 * (n*n+1) * nearstar_ray + (float) random (300 * nearstar_ray) / 100;
		nearstar_p_tilt[n]       = zrandom (10*nearstar_p_orb_seed[n]) / 500;
		nearstar_p_orb_tilt[n]   = zrandom (10*nearstar_p_orb_seed[n]) / 5000;
		nearstar_p_orb_ecc[n]    = 1 - (double) random (nearstar_p_orb_seed[n] + 10*fabs(nearstar_p_orb_tilt[n])) / 2000;
		nearstar_p_ray[n]        = (double) random (nearstar_p_orb_seed[n]) * 0.001 + 0.01;
		nearstar_p_ring[n]	 = zrandom (nearstar_p_ray[n]) * (1 + (double) random (1000) / 100);
		if (nearstar_class != 8)
			nearstar_p_type[n] = random (planet_types);
		else {
			if (random(2)) {
				nearstar_p_type[n] = 10;
				nearstar_p_orb_tilt[n] *= 100;
			}
			else
				nearstar_p_type[n] = random (planet_types);
		}
		if (nearstar_class==2||nearstar_class==7||nearstar_class==15)
			nearstar_p_orb_seed[n] *= 10;
	}

	if (!nearstar_class) {
		if (random(4)==2) nearstar_p_type[2] = 3;
		if (random(4)==2) nearstar_p_type[3] = 3;
		if (random(4)==2) nearstar_p_type[4] = 3;
	}

	for (n=0; n<nearstar_nop; n++) {
		switch (nearstar_class) {
			case 2: while (nearstar_p_type[n]==3)
					nearstar_p_type[n] = random (10);
				break;
			case 5: while (nearstar_p_type[n]==6||
				       nearstar_p_type[n]==9)
					nearstar_p_type[n] = random (10);
				break;
			case 7:	nearstar_p_type[n] = 9;
				break;
			case 9: while (nearstar_p_type[n]!=0&&
				       nearstar_p_type[n]!=6&&
				       nearstar_p_type[n]!=9)
					nearstar_p_type[n] = random (10);
				break;
			case 11:while (nearstar_p_type[n]!=1&&
				       nearstar_p_type[n]!=7)
					nearstar_p_type[n] = random (10);
		}
	}

	for (n=0; n<nearstar_nop; n++) {
		switch (nearstar_p_type[n]) {
			case 0:
				if (random(8))
					nearstar_p_type[n] ++;
				break;
			case 3:
				if ((n<2)||(n>6)||(nearstar_class&&random(4))) {
					if (random(2))
						nearstar_p_type[n]++;
					else
						nearstar_p_type[n]--;
				}
				break;
			case 7:
				if (n<7) {
					if (random(2))
						nearstar_p_type[n] --;
					else
						nearstar_p_type[n] -= 2;
				}
				break;
		}
	}

	nearstar_nob = nearstar_nop;

	if (nearstar_class==2||nearstar_class==7||nearstar_class==15)
		goto no_moons;

	for (n=0; n<nearstar_nop; n++) {
		// (t=) Numero di satelliti per pianeta.
		s = nearstar_p_type[n];
		if (n < 2) {
			t = 0;
			if (s == 10)
				t = random (3);
		}
		else
			t = random (planet_possiblemoons[s] + 1);
		if (nearstar_nob + t > maxbodies)
			t = maxbodies - nearstar_nob;
		for (c=0; c<t; c++) {
			q 			 = nearstar_nob + c;
			nearstar_p_owner[q]	 = n;
			nearstar_p_moonid[q]	 = c;
			nearstar_p_orb_orient[q] = (double) deg * (double) random (360);
			nearstar_p_orb_seed[q]   = (c*c+4) * nearstar_p_ray[n] + (float) zrandom (300 * nearstar_p_ray[n]) / 100;
			nearstar_p_tilt[q]       = zrandom (10*nearstar_p_orb_seed[q]) / 50;
			nearstar_p_orb_tilt[q]   = zrandom (10*nearstar_p_orb_seed[q]) / 500;
			nearstar_p_orb_ecc[q]    = 1 - (double) random (nearstar_p_orb_seed[q] + 10*fabs(nearstar_p_orb_tilt[q])) / 2000;
			nearstar_p_ray[q]        = (double) random (nearstar_p_orb_seed[n]) * 0.05 + 0.1;
			nearstar_p_ring[q]	 = 0;
			nearstar_p_type[q]       = random (planet_types);
			r = nearstar_p_type[q];
			if (r==9 && s != 10) r = 2;
			if (r==6 && s < 9) r = 5;
			if (n > 7 && random(c)) r = 7;
			if (n > 9 && random(c)) r = 7;
			if (r==2 || r==3 || r==4 || r==8) {
				if (s != 6 && s < 9)
					r = 1;
			}
			if (r==3 && s < 9) {
				if (n > 7)
					r = 7;
				if (nearstar_class && random(4))
					r = 5;
				if (nearstar_class == 2 ||
				    nearstar_class == 7 ||
				    nearstar_class == 11)
					r = 8;
			}
			if (r==7 && n <= 5) r = 1;
			if ((nearstar_class==2||nearstar_class==5||
			     nearstar_class==7||nearstar_class==11)
			     && random(n)) r = 7;
			nearstar_p_type[q] = r;
		}
		nearstar_nob += t;
	}

no_moons:
	key_radius = nearstar_ray * planet_orb_scaling;
	if (nearstar_class == 8) key_radius *= 2;
	if (nearstar_class == 2) key_radius *= 16;
	if (nearstar_class == 7) key_radius *= 18;
	if (nearstar_class == 11) key_radius *= 20;
	for (n=0; n<nearstar_nop; n++) {
		nearstar_p_ray[n] = avg_planet_ray[nearstar_p_type[n]]
				  + avg_planet_ray[nearstar_p_type[n]] * zrandom (100) / 200;
		nearstar_p_ray[n] *= avg_planet_sizing;
		nearstar_p_orb_ray[n] = key_radius + key_radius * zrandom (100) / 500;
		nearstar_p_orb_ray[n] += key_radius * avg_planet_ray[nearstar_p_type[n]];
		if (n < 8)
			key_radius += nearstar_p_orb_ray[n];
		else
			key_radius += 0.22 * nearstar_p_orb_ray[n];
	}

	n = nearstar_nop;
	while (n < nearstar_nob) {
		q = 0;
		c = nearstar_p_owner[n];
		key_radius = nearstar_p_ray[c] * moon_orb_scaling;
		while (n<nearstar_nob && nearstar_p_owner[n] == c) {
			nearstar_p_ray[n] = avg_planet_ray[nearstar_p_type[n]]
					  + avg_planet_ray[nearstar_p_type[n]] * zrandom (100) / 200;
			nearstar_p_ray[n] *= avg_moon_sizing;
			nearstar_p_orb_ray[n] = key_radius + key_radius * zrandom (100) / 250;
			nearstar_p_orb_ray[n] += key_radius * avg_planet_ray[nearstar_p_type[n]];
			if (q < 2) key_radius += nearstar_p_orb_ray[n];
			if (q >= 2 && q < 8) key_radius += 0.12 * nearstar_p_orb_ray[n];
			if (q >= 8) key_radius += 0.025 * nearstar_p_orb_ray[n];
			q++;
			n++;
		}
	}

	for (n = 0; n < nearstar_nop; n++) {
		nearstar_p_ring[n] = 0.75 * nearstar_p_ray[n] * (2 + random(3));
		s = nearstar_p_type[n];
		if (s != 6 && s != 9) {
			if (random(5))
				nearstar_p_ring[n] = 0;
		}
		else {
			if (random(2))
				nearstar_p_ring[n] = 0;
		}
	}
}

//////////////////////////////////////////////////////////////////////////////

long fpart (double id, char *label)
{
	long	fpart, no;
	int	attempts = 0;
	double	multiplier = 1E9;

	if (label[21] == 'P') {
		no  = label[23] - '0';
		no += 10 * (label[22] - '0');
		id -= no;
	}

	id = fabs(id);

	do {
		double lid = floor(id);
		fpart = multiplier * ((double)id - (double)lid);
		multiplier *= 1000;
		attempts++;
	} while (fpart < 1E6 && attempts < 44);

	return (fpart);
}

void settarget ()
{
	int	ch;
	int	planet_nr;
	double 	star_id;
	long	fp_star_check;
	long	fp_object_check;

	if (query == 2) {
		planet_nr  = object_label[23] - '0';
		planet_nr += 10 * (object_label[22] - '0');
		star_id    = object_id - planet_nr;
	}
	else
		star_id = object_id;

	if (!isthere (star_id)) {
		msg (subjectname);
		msg ("IS OUT OF RANGE");
		return;
	}
	else
		fp_star_check = fpart (star_id, "F-PARTTESTSTARLABEL Sxx");

	if (query == 2) {
		if (laststar_x < nearstar_x - idscale || laststar_x > nearstar_x + idscale)
			goto notpartofthissystem;
		if (laststar_y < nearstar_y - idscale || laststar_y > nearstar_y + idscale)
			goto notpartofthissystem;
		if (laststar_z < nearstar_z - idscale || laststar_z > nearstar_z + idscale)
			goto notpartofthissystem;
		ap_target_x = laststar_x;
		ap_target_y = laststar_y;
		ap_target_z = laststar_z;
		extract_ap_target_infos ();
		prepare_nearstar ();
		lseek (fh, 4, SEEK_SET);
		while (_read (fh, &object_id, 8) && _read (fh, &object_label, 24) == 24) {
			fp_object_check = fpart (object_id, object_label);
			if (memcmp (&object_id, "Removed:", 8) && fp_object_check == fp_star_check && object_id > star_id + 1 - idscale && object_id <= star_id + MAX_OBJECTS_PER_STAR + idscale) {
			if (!memcmp (object_label, subjectname, strlen(subjectname))) {
				planet_nr  = object_label[23] - '0';
				planet_nr += 10 * (object_label[22] - '0');
				ch = _creat (comm, 0);
				if (ch > -1) {
					_write (ch, &planet_nr, 2);
					_close (ch);
					msg ("LOC. TARGET DATA SENT");
					msg ("BEGIN IN-SYSTEM DRIVE");
				}
				else
					msg ("COMMUNICATION ERROR.");
				return;
			}}
		}
	    notpartofthissystem:
		msg ("PLANET NOT FOUND AS");
		msg ("PART OF THIS SYSTEM.");
		sprintf (textbuffer, "PLEASE USE %cPAR%c TO", 34, 34);
		msg (textbuffer);
		msg ("FIND PARSIS FOR THE");
		msg ("CORRESPONDING STAR.");
	}
	else {
		ch = _creat (comm, 0);
		if (ch > -1) {
			_write (ch, &laststar_x, 8);
			_write (ch, &laststar_y, 8);
			_write (ch, &laststar_z, 8);
			_close (ch);
			msg ("REM. TARGET DATA SENT");
			msg ("STARTING VIMANA DRIVE");
		}
		else
			msg ("COMMUNICATION ERROR.");
	}
}

void main ()
{
	asm {	xor	ax, ax
		mov	es, ax
		cmp	byte ptr es:[0x449], 0x13
		je	startup }

	printf ("\nGalactic Organization of Explorers and Stardrifters (G.O.E.S)\n");
	printf ("-------------------------------------------------------------\n");
	printf ("This is a GOES NET module and must be run from a stardrifter.\n");
	printf ("Please use the onboard computer console to run this module.\n");
	printf ("\n\t- GOES NET onboard microsystem, EPOC 6011 REVISION 2\n");
	return;

	startup:
	if (_argc<2) {
		msg ("________USAGE________");
		msg ("ST OBJECTNAME");
		msg ("ST OBJECTNAME:RANGE");
		msg ("^^^^^^^^^^^^^^^^^^^^^");
		msg ("PLEASE RUN AGAIN,");
		msg ("SPECIFYING PARAMETERS");
		msg (divider);
		msg ("(ST REVISION 6011/28)");
		return;
	}
	else {
		msg ("LOOKING FOR TARGET...");
		msg (divider);
	}

	fh = _open (file, 4);
	if (fh == -1) {
		msg ("STARMAP NOT AVAILABLE");
		return;
	}

	i = 2;
	strcpy (parbuffer, _argv[1]);
	while (i < _argc) {
		strcat (parbuffer, " ");
		strcat (parbuffer, _argv[i]);
		i++;
	}

	i = 0;
	while (parbuffer[i]) {
		if (parbuffer[i] == '_')
			parbuffer[i] = 32;
		i++;
	}

	i = 0;
	while (i < 21 && parbuffer[i] != ':' && parbuffer[i] != 0) {
		objectname[i] = parbuffer[i];
		i++;
	}

	if (parbuffer[i] != ':')
		analyzed_sectors_range = 100;
	else {
		sts = atoi (parbuffer + i + 1);
		if (sts <= 2 || sts > 10000)
			analyzed_sectors_range = 100;
		else
			analyzed_sectors_range = sts;
	}

	unfreeze ();
	if (sts > 100) warn ("SCANNING THE GALAXY: ESC TO STOP", -1);

	strupr (parbuffer);
	strupr (objectname);
	objectname[i] = 0;
	query = find (objectname);
	if (query) {
		if (query==1) msg ("SUBJECT: STAR;");
		if (query==2) msg ("SUBJECT: PLANET;");
		sprintf (outbuffer, "NAME: %s", subjectname);
		msg (outbuffer);
		msg ("_____________________");
		settarget ();
	}

	_close (fh);
}