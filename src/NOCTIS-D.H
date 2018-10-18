/*

	Inclusioni del c++

*/

#include <stdlib.h>
#include <string.h>
#include <alloc.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <dos.h>
#include <io.h>

/*

	Definizioni per NOCTIS.
	Tante.

*/

// area dati: 	lunghezza:	puntatore:	descrizione:

#define om_bytes      7340 // 	n_offsets_map	contiene "offsets.map",
			   //			(sfera concava in QT-VR).
#define gl_bytes     22586 //   n_globes_map	contiene "globes.map"
			   //			(sfera convessa in QT-VR).
			   //			texture superficie del mare.
#define gl_brest     10182 //   (indicativo)	resto dei bytes allocati per
			   //			n_globes_map in quanto questo
			   //			buffer viene usato anche per
			   //			la superficie del mare di 32K,
			   //			o altrimenti per il font 32x36
			   //			che serve al gestore di bordo.
#define st_bytes     64800 //	s_background    mappa superficie stelle;
			   //			mappa superficie satelliti;
			   //			mappa del cielo in superficie;
			   //			buffer di shading superficie.
#define pl_bytes     65552 // 	p_background	mappa planetaria dall'orbita;
			   // 			texture per il suolo.
#define ps_bytes     40000 //   p_surfacemap	piantina altimetrica superf.;
			   //			buffer temporaneo di lettura;
			   //			buffer aggiornamento schermi.
#define oc_bytes     40000 //   objectschart	mappa oggetti in superficie;
			   //			overlay per l'atmosfera.
#define sc_bytes     65540 //	adapted	      	la pagina video nascosta, pi—
			   //		        2 bytes (supporto per polymap)
			   //			darebbe 64002. Ma l'ho estesa
			   //			a 64Kb+4bytes per evitare lo
			   //			sconfinamento di "poly3d", una
			   //			funzione difettosa che non ho
			   //			n‚ tempo n‚ voglia di modifi-
			   //			care, al momento.
#define pv_bytes     20480 //   pvfile		data bank dinamica dei files
			   //			di grafica poligonale.
// ------------------------//
// totale bytes     334941 //	(memoria allocata dinamicamente)
// ------------------------//
// + 		    222099 //	(lunghezza max permessa programma NOCTIS.EXE)
// +		      6160 //	(stack)
// ------------------------//
// =	     (550K) 563200 //	(memoria richiesta in totale, come massimo)
//                 ========//                                               */

// Note a quei 550K: in teoria possono essere di pi—,
// ma se ne usasse effettivamente di pi— su molti sistemi
// potrebbe non trovare abbastanza memoria. E' un limite che
// pressappoco coincide con la massima estensione dei tre moduli
// di cui si compone l'eseguibile, e non dovrebbe essere superato.

// mappa del file stand-alone NOCTIS.EXE,
// --------------------------------------
// cui dev'essere aggiunto, dopo ogni compilazione, il file SUPPORTS.NCT
// contenente i seguenti files, nell'ordine riportato sotto (il punto tra
// nome ed estensione Š stato rimpiazzato da un sottolinea). i seguenti
// valori devono essere calcolati relativamente alla fine del file
// "SUPPORTS.NCT". il primo valore, quindi, riporta la lunghezza di
// tale file. Š consigliabile aggiungere files all'inizio del file,
// cosicch‚ per aggiungere la definizione qui sotto basta riportare
// l'opposto della lunghezza di SUPPORTS.NCT

#define off_digimap2	-60776
#define dm2_bytes	  9360

#define mammal_ncc	-51416

#define os_voidscrn	-48664
#define os_goescomm	-44704
#define os_logogoes	-40744

#define birdy_ncc	-36784
#define vehicle_ncc	-35782

#define header_bmp	-29980
#define offsets_map	-29926
#define globes_map	-22586

// Limiti, relativi al centro dello schermo, per i bastoncini 3D.

#define stk_lbx       -150
#define stk_lby        -90
#define stk_ubx        160
#define stk_uby         90

// Parametri di lavoro per "tdpolygs.h", la libreria 3D poligonale.

#define VERTICI_PER_POLIGONO 4

#define larghezza 306
#define altezza   180
#define x_centro  158
#define y_centro  100

#define lbx -larghezza/2 + x_centro
#define ubx larghezza/2 + x_centro
#define lby -altezza/2 + y_centro
#define uby altezza/2 + y_centro

// Quattro terzi di pigreco.

#define qt_M_PI   4*M_PI/3

// Tipi di pianeta e numero di classi stellari.

#define star_classes    12
#define planet_types    10
#define avgmoons        4
#define log2avgmoons	2
#define maxbodies	20 * avgmoons

// Codici identificativi degli oggetti sulla superficie dei pianeti.

#define ROCKS	0
#define VEGET	1
#define TREES	2
#define NOTHING 3

// Codici identificativi delle rovine (in tre stili di texture).

#define AF1     0x40
#define AF2     0x80
#define AF3     0xC0

// Assegnazione handles per i files PV.

#define vehicle_handle	0

#define bird_base	0
#define bird_result	1

#define mamm_base	2
#define mamm_result	3

// Struttura di un byte nella mappa oggetti di superficie (objectschart).

struct quadrant {
	unsigned nr_of_objects : 2;
	unsigned object0_class : 2;
	unsigned object1_class : 2;
	unsigned object2_class : 2;
};

// Struttura che identifica un poligono e i suoi vertici per le funzioni PV.

struct pvlist {
	unsigned polygon_id : 12;
	unsigned vtxflag_0  : 1;
	unsigned vtxflag_1  : 1;
	unsigned vtxflag_2  : 1;
	unsigned vtxflag_3  : 1;
};
