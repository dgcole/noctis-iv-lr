//////////////////////////////////////////////////////////////////////////////
//									    //
//				      *					    //
//				  Pitagora				    //
//		       intelligent triangles renderer			    //
//	     * the fastest and final solution to 3d rendering *		    //
//									    //
//		          (c)1999 Home Sweet Pixel			    //
//	     Born for Noctis - my little darling space program!		    //
//									    //
//////////////////////////////////////////////////////////////////////////////

#ifndef	__Pitagora_H
#define __Pitagora_H

/// Introduction. ////////////////////////////////////////////////////////////

//	Pitagora is a small 3D engine.
//	Its basic idea consists in using ONLY 3D-triangles to show
//	everything needed in a complex scenery. This allows a very massive
//	quantity of logical optimizations and reduces the CPU usage to very
//	little more than filling in the spaces on the screen...

//	This version of Pitagora, designed for Noctis, supports the standard
//	MCGA display (320 x 200 with 256 colors, 1 byte per pixel), but can
//	be easily manipulated and optimized for any other display, as
//	described from within the "linefill" function.
//	Also, it doesn't have functions to display the output directly.
//	Instead, it's supposed to draw on a memory buffer (of 320x200,
//	or 64000 bytes) which then has to be "shooted" to the video
//	memory with a fast copy operation (i.e. rep movsd).
//	Yes, you may let pitagora draw directly on the video memory,
//	by simply leaving "display" as it is by default, and just
//	opening the MCGA screen (asm mov ax, 0x13 / int 0x10), but
//	it's not recommended. You'd see any polygon laying behind
//	another one "flickering" on the screen, and you wouldn't be able
//	to use superimposed effects, like for example translucent surfaces.
//	Last but not least, drawing directly is much slower, because the
//	video memory chips are not directly connected to the motherboard.
//	Anyway you may draw something on the video memory just to try it...

//	Here's the piece of code that will open an MCGA standard screen.
//	Just place it at the beginning on your main() program, removing
//	the "remark" symbols (//). You will then have to close graphics mode
//	before quitting the main program: just put the same code at the end
//	of main() and change 0x13 to 0x03. This will re-open color text mode.
//
//		asm {	mov	ax, 0x13
//			int	0x10 }
//
//	Further infos on VESA displays and VGA screens managing may be found
//	within some other documents. That's not the purpose of this file.

//	But, apart from those limits, Pitagora is a VERY fast engine:
//	yes, it's not been optimized to the top, but it doesn't really
//	need it, unless you're gonna build a million-triangles world.

/// Extending the code. //////////////////////////////////////////////////////

//	The real gap is represented by a latch of depth sorting: since Noctis
//	does this on its own, Pitagora doesn't consider polygon sorting,
//	BSP trees or whatever else... but, since the number of polygons
//	that can be managed is very high, I discourage whoever interested
//	from using a bubble-sort or even a quicksort routine. What it really
//	needs is a bit of Z-buffering. And, of course, as fast as possible.
//	May look difficult, but it isn't really, and it'd fit Pitagora needs.

/// Notes: ///////////////////////////////////////////////////////////////////

//	You really don't need many instructions. The most important thing
//	to respect is vectors representation: there is a conventional way
//	to fix the vertexs of a triangle so that you can determine which
//	is its visible side, the orientation of its texture, and any other
//	thing implying 3D vectors analysis (shading is one of those, BTW).

//	If you had this triangle (from its visible side), its vertexs
//	would be passed to the functions in the following order:

//                                  2
//                                  *
//                               .       .
//                            .               .
//                         .                       .
//                    1 *    .   .   .   .   .   .   .  * 3

//	Basically, you need passing them always in clockwise order.
//	There would be no problems if you changed which is the first vertex,
//	as long as you mantain that order: if not, the visible side would
//	be the other one and things like textures and shading would be
//	misinterpreted by the engine's functions.

//	Especially for textures, they will always fit the polygon starting
//	from the first vertex to the second one (horizontally for the bitmap)
//	and from the first vertex to the third one (along the bitmap's
//	vertical axis). Special filling handlers running "backwards"
//	(i.e. from right to left instead that left to right, as normal),
//	which have the purpose of outputting a "clean" texturing by avoiding
//	negative integers (resulting in a loss of precision) will not work
//	properly using the wrong order, and the texture may therefore look
//	"blurried" especially when seen at high angles. Some approximation
//	still remains, for it is connected to the tracing mechanism, which
//	divides each scanline in a few horizontal "spans" of a given size.
//	The size of the spans can be changed if you change the definitions
//	for "spanlength" and "spanshifts" (accordingly); shorter spans will
//	result in slower - but more accurate - graphics, and vice versa.

/// Needed C++ maths. ////////////////////////////////////////////////////////

#ifndef __FLOAT_H
#include <float.h>
#endif

#ifndef __MATH_H
#include <math.h>
#endif

/// Display control. /////////////////////////////////////////////////////////

#define VIDEOptr	0xA0000000;	/* FAR ptr to video memory map.	  */

unsigned char huge *display =
(unsigned char huge *) VIDEOptr;	/* Pointer to output memory area. */
unsigned char huge *vid_map =
(unsigned char huge *) VIDEOptr;	/* Pointer to video memory map.   */

long  lbxl =   0, lbyl =   0;		/* Display viewport lower bounds. */
long  ubxl = 320, ubyl = 200;		/* Display viewport upper bounds. */
long  lbxa =-160, lbya =-100;		/* Absolute versions of lbx/lby.  */
long  ubxa = 160, ubya = 100;           /* Absolute versions of ubx/uby.  */

double center_x  = 160, center_y  = 100; /* Display center coordinates.	  */
long  icenter_x = 160, icenter_y = 100; /* Integer version of the above.  */

/// 3D conversions control. //////////////////////////////////////////////////

const double 	deg = M_PI / 180;		/* deg2rad conv. factor.  */

double 		alpha=0, beta =0, gamma=0;	/* View pitch/yaw/roll.	  */
double 		cam_x=0, cam_y=0, cam_z=0;	/* Viewpoint coords.	  */

double 		dpp 	= 100;	/* Distance from plane of projection. 	  */
double 		inv_dpp = .01;	/* Inverse of previous value.		  */

double 		opt_tcosbeta  = 1;	     /* Optimized trigonometrics. */
double 		opt_tsinbeta  = 0;           /* Optimized trigonometrics. */
double 		opt_tcosalpha = 1;           /* Optimized trigonometrics. */
double 		opt_tsinalpha = 0;           /* Optimized trigonometrics. */
double 		opt_tcosgamma = 1;           /* Optimized trigonometrics. */
double 		opt_tsingamma = 0;           /* Optimized trigonometrics. */

/// Texture mapping parameters. //////////////////////////////////////////////

const TXTR_XSIZE  =	 		256; 	/* Texture width, pixels  */
const TXTR_YSIZE  =   	       		128; 	/* Texture height, pixels */
double EMU_K	  =	                 16; 	/* FPU emulation constant */
long  H_MATRIXS   =	         	 16; 	/* Texture repeating (X)  */
long  V_MATRIXS   =	         	 16; 	/* Texture repeating (Y)  */
double XCOEFF      =  	        EMU_K / dpp; 	/* Commodity value. 	  */
double YCOEFF      =  	        EMU_K / dpp; 	/* Commodity value.	  */
long  XSIZE       =  TXTR_XSIZE * H_MATRIXS; 	/* Tx. size calibration.  */
long  YSIZE       =  TXTR_YSIZE * V_MATRIXS; 	/* Tx. size calibration.  */
double XSIZEf      =                   XSIZE; 	/* double version of XSIZE */
double YSIZEf      =                   YSIZE; 	/* double version of YSIZE */

double x_antialias = 1.0; 		/* Texture antialiasing X factor. */
double y_antialias = 1.0;               /* Texture antialiasing Y factor. */
double z_antialias = 1.0;               /* Texture antialiasing Z factor. */

double t_center_x = center_x - 1;	/* True screencenter for texture. */
double t_center_y = center_y - 1;       /* True screencenter for texture. */

/// Texture mapping temporary data. //////////////////////////////////////////

typedef	unsigned int WORD;

double hx, hy, hz;	/* Texture's horizontal drift per pixel.	*/
double vx, vy, vz;	/* Texture's vertical drift per pixel.		*/
double ox, oy, oz;	/* Origin of texture's UV-space.     		*/

WORD  patword = 31;	/* Pattern word used in plain fill.		*/
WORD  mapeffect = 0;	/* Special texture mapping effects switch.	*/
unsigned int huge* txm; /* Pointer to texture's bitmap memory area.	*/

/// Standard scan vectors. ///////////////////////////////////////////////////

unsigned long	scan[200]  = {      0L*2,   320L*2,   640L*2,   960L*2,  1280L*2,  1600L*2,
				 1920L*2,  2240L*2,  2560L*2,  2880L*2,  3200L*2,  3520L*2,
				 3840L*2,  4160L*2,  4480L*2,  4800L*2,  5120L*2,  5440L*2,
				 5760L*2,  6080L*2,  6400L*2,  6720L*2,  7040L*2,  7360L*2,
				 7680L*2,  8000L*2,  8320L*2,  8640L*2,  8960L*2,  9280L*2,
				 9600L*2,  9920L*2, 10240L*2, 10560L*2, 10880L*2, 11200L*2,
				11520L*2, 11840L*2, 12160L*2, 12480L*2, 12800L*2, 13120L*2,
				13440L*2, 13760L*2, 14080L*2, 14400L*2, 14720L*2, 15040L*2,
				15360L*2, 15680L*2, 16000L*2, 16320L*2, 16640L*2, 16960L*2,
				17280L*2, 17600L*2, 17920L*2, 18240L*2, 18560L*2, 18880L*2,
				19200L*2, 19520L*2, 19840L*2, 20160L*2, 20480L*2, 20800L*2,
				21120L*2, 21440L*2, 21760L*2, 22080L*2, 22400L*2, 22720L*2,
				23040L*2, 23360L*2, 23680L*2, 24000L*2, 24320L*2, 24640L*2,
				24960L*2, 25280L*2, 25600L*2, 25920L*2, 26240L*2, 26560L*2,
				26880L*2, 27200L*2, 27520L*2, 27840L*2, 28160L*2, 28480L*2,
				28800L*2, 29120L*2, 29440L*2, 29760L*2, 30080L*2, 30400L*2,
				30720L*2, 31040L*2, 31360L*2, 31680L*2, 32000L*2, 32320L*2,
				32640L*2, 32960L*2, 33280L*2, 33600L*2, 33920L*2, 34240L*2,
				34560L*2, 34880L*2, 35200L*2, 35520L*2, 35840L*2, 36160L*2,
				36480L*2, 36800L*2, 37120L*2, 37440L*2, 37760L*2, 38080L*2,
				38400L*2, 38720L*2, 39040L*2, 39360L*2, 39680L*2, 40000L*2,
				40320L*2, 40640L*2, 40960L*2, 41280L*2, 41600L*2, 41920L*2,
				42240L*2, 42560L*2, 42880L*2, 43200L*2, 43520L*2, 43840L*2,
				44160L*2, 44480L*2, 44800L*2, 45120L*2, 45440L*2, 45760L*2,
				46080L*2, 46400L*2, 46720L*2, 47040L*2, 47360L*2, 47680L*2,
				48000L*2, 48320L*2, 48640L*2, 48960L*2, 49280L*2, 49600L*2,
				49920L*2, 50240L*2, 50560L*2, 50880L*2, 51200L*2, 51520L*2,
				51840L*2, 52160L*2, 52480L*2, 52800L*2, 53120L*2, 53440L*2,
				53760L*2, 54080L*2, 54400L*2, 54720L*2, 55040L*2, 55360L*2,
				55680L*2, 56000L*2, 56320L*2, 56640L*2, 56960L*2, 57280L*2,
				57600L*2, 57920L*2, 58240L*2, 58560L*2, 58880L*2, 59200L*2,
				59520L*2, 59840L*2, 60160L*2, 60480L*2, 60800L*2, 61120L*2,
				61440L*2, 61760L*2, 62080L*2, 62400L*2, 62720L*2, 63040L*2,
				63360L*2, 63680L*2 };

/// Video initialization functions. //////////////////////////////////////////

unsigned char VgaInfoBlock[256];
unsigned char ModeInfoBlock[256];
unsigned char OEMprevmodecode;

long 	      VRAM_granularity = 65536;
long 	      VRAM_total       = 65536;
long	      VRAM_pages       = 1;

#define	LORES565	0x10E	// directcolor (RGB 5-6-5) low-res mode code
#define HIRES565	0x111	// directcolor (RGB 5-6-5) hi-res mode code

char video_page_select (char videopage)
{
	/* Selects a video memory page to be mapped at 0xA000. */

	asm {   mov dl, videopage
		mov ax, 0x4f05
		xor dh, dh
		mov bx, 1
		int 0x10 }

	return (_AL);
}

char openvesa (unsigned mode_code)
{
	/* Opens a VESA video mode (if available).
		Returns 1 if successful, 0 if failed. */

	unsigned char far *current_video_mode = (unsigned char far *)0x449;
	OEMprevmodecode = current_video_mode[0];
	char vesa_err = 0;

	asm {   push	es
		push	ds
		pop	es
		lea	di, VgaInfoBlock
		mov	ax, 0x4F00
		int	0x10
		pop	es
		cmp	ax, 0x004F
		je 	vib_ok
		mov	vesa_err, 1 }
vib_ok: if (vesa_err) return (0);
	if ( VgaInfoBlock[0]!='V' ||
	     VgaInfoBlock[1]!='E' ||
	     VgaInfoBlock[2]!='S' ||
	     VgaInfoBlock[3]!='A' ) return (0);

	VRAM_total   = (unsigned int)VgaInfoBlock[18];
	VRAM_total <<= 16;

	asm {   push	es
		push	ds
		pop	es
		lea	di, ModeInfoBlock
		mov	cx, mode_code
		mov	ax, 0x4F01
		int	0x10
		pop	es
		cmp	ax, 0x004F
		je 	mib_ok
		mov	vesa_err, 1 }
mib_ok: if (vesa_err) return (0);

	VRAM_granularity   = (unsigned int)ModeInfoBlock[4];
	VRAM_granularity <<= 10;

	asm {	mov	bx, mode_code
		mov	ax, 0x4F02
		int	0x10
		cmp	ax, 0x004F
		je 	gphxok
		mov	vesa_err, 1 }

gphxok: if (vesa_err) return (0);
	switch (mode_code) {
		case LORES565: VRAM_pages =  640L*200L; break;
		case HIRES565: VRAM_pages = 2048L*768L; break;
		default:       VRAM_pages = 65536L;     break;
	}
	if (VRAM_pages > VRAM_total) VRAM_pages = VRAM_total;
	VRAM_pages /= VRAM_granularity;

	if (video_page_select(0) != 0x4F)
		return (0);
	else
		return (1);
}

void cleardisplay ()
{
	asm {	les	di, dword ptr display
		shr	di, 4
		mov	ax, es
		add	ax, di
		mov	es, ax
		xor	di, di
		mov	cx, 16384
		db 0x66; xor ax, ax	// xor eax, eax
		db 0xF3, 0x66, 0xAB	// rep stosd
		mov	dx, es
		add	dx, 0x1000
		mov	es, dx
		mov	cx, 16384
		db 0xF3, 0x66, 0xAB }	// rep stosd
}

void LOW2HIGH (unsigned char huge *source)
{
	/* A function that spreads the source screen (in low resolution)
	   on to a wider screen (in high resolution). Useful for display
	   emulation when low-res truecolor not supported.

	   usage: LOW2HIGH (source); */

	unsigned long VRG = VRAM_granularity;

	unsigned page   = (40 * 1280) / VRAM_granularity;
	unsigned ofs    = (40 * 1280) % VRAM_granularity;

	video_page_select (page);

	asm {	pusha
		push	es
		push	ds
		db 0x66;xor di, di		// XOR EDI, EDI
		lds	di, vid_map
		les	si, source
		add	di, ofs
		mov     bx, 160
		mov	cx, 0xFA00
		db 0x66;push bp 		// PUSH EBP
		db 0x66;mov bp, word ptr VRG }	// MOV EBP, VRG
slcopy:	asm {   mov	ax, es:[si+0]
		mov	dx, es:[si+2]
		add	si, 4
		jnc	samesg
		push	ax
		mov	ax, es
		add	ax, 0x1000
		mov	es, ax
		pop	ax }
samesg: asm {	mov	[di+0], ax
		dec	bx
		mov	[di+4], dx
		jnz	noline
		mov	bx, 320
		sub	si, 640
		jnc	noline
		push	ax
		mov	ax, es
		sub	ax, 0x1000
		mov	es, ax
		pop	ax }
noline: asm {	mov	[di+2], ax
		mov	[di+6], dx
		db 0x66, 0x83, 0xC7, 0x08	// ADD EDI, 08h
		db 0x66;cmp di, bp          	// CMP EDI, VRG (alias EBP)
		jb	samepg
		db 0x66;sub di, bp          	// SUB EDI, VRG (alias EBP)
		db 0x66;pop bp			// POP EBP
		push	bx
		inc	page
		mov	dx, page
		mov	ax, 0x4F05
		mov	bx, 1
		int	0x10
		pop	bx
		db 0x66;push bp  		// PUSH EBP
		db 0x66;mov bp, word ptr VRG }	// MOV EBP, VRG
samepg:	asm {   dec 	cx
		jnz	slcopy
		db 0x66;pop bp			// POP EBP
		pop	ds
		pop	es
		popa }
}

void showframe (unsigned char huge *source)
{
	unsigned long VRG = VRAM_granularity;
	unsigned long framesize = 0x1F400;

	asm     push	ds

	asm {	les	di, dword ptr vid_map
		shr	di, 4
		mov	ax, es
		add	ax, di
		mov	es, ax
		lds	si, dword ptr source
		shr	si, 4
		mov	ax, ds
		add	ax, si
		mov	ds, ax }

	asm {	db 0x66;mov cx, word ptr framesize
		mov	dx, 0x0000 }

cont:	asm {   db 0x66;push cx
		push	dx
		mov	ax, 0x4f05
		mov	bx, 0x0001
		int	0x10
		db 0x66;mov cx, word ptr VRG
		db 0x66;shr cx, 2
		xor	si, si
		xor	di, di
		db 0xF3, 0x66, 0xA5	// rep movsd
		db 0x66;mov dx, word ptr VRG
		db 0x66;shr dx, 4
		mov	ax, ds
		add	ax, dx
		mov	ds, ax
		pop	dx
		inc	dx
		db 0x66;pop cx
		db 0x66;sub cx, word ptr VRG
		jc	stop
		jnz	cont }

stop:	asm	pop	ds
}

void closevesa ()
{
	/* Turns the video mode back to previous video mode using OEM. */

	asm {	mov 	al, OEMprevmodecode
		xor	ah, ah
		int 	0x10 }
}

void colortextmode ()
{
	/* Forces the video system to open the standard color text mode,
	   for use when switching back to the previous mode code results
	   in something which doesn't fit DOS requirements. */

	asm {	mov	ax, 0x03
		int	0x10 }
}

/// Engine initialization functions. /////////////////////////////////////////

void initpitagora ()
{
	/* That's just to be called before using any other functions
	   from this file. Sure they may work anyways, but some doubleing
	   point failures like "partial loss of precision" or "integer
	   overflow", which can be totally ignored, may slow down
	   calculations or break the program all of a sudden.
	   By doing so, we allow the FPU using its internal error handling
	   procedures, which are also very smart or so I thought. */

        _control87 (MCW_EM, MCW_EM); // Disable all floating Point Exceptions.
	_control87 (RC_CHOP, MCW_RC); // Set "chop" rounding mode.
}

/// Display control functions. ///////////////////////////////////////////////

void setviewport (long x_center, long y_center, long vp_width, long vp_height)
{
	/* Adjusts the 3D viewport to a specific region of the display.
	   The default viewport covers the screen in full, and the
	   perspective center corresponds to the screen's center.
	   Since this version of Pitagora is designed to fit MCGA displays,
	   you may set the viewport anywhere but beyond the limits of the
	   said display (320 x 200 with 256 colors), or the system may crash.
	   Shrinking the viewport may help placing additional graphics
	   on the screen, but I think it wouldn't speed up the engine
	   that much, since the filling routines are fast enough
	   and the speed definitely depends from the number of
	   triangles contained in the scenery.
	   Pitagora, however, is capable of managing about
	   500000 simple triangles per second on most Pentiums. */

	center_x   = x_center;
	center_y   = y_center;
	icenter_x  = x_center;
	icenter_y  = y_center;
	t_center_x = x_center - 1;
	t_center_y = y_center - 1;

	lbxa	   = - vp_width  / 2;
	lbya	   = - vp_height / 2;
	ubxa	   =   vp_width  / 2;
	ubya	   =   vp_height / 2;

	lbxl	   = lbxa + center_x;
	lbyl	   = lbya + center_y;
	ubxl	   = ubxa + center_x;
	ubyl	   = ubya + center_y;
}

/// Viewpoint manipulation. //////////////////////////////////////////////////

double fwd_x, fwd_y, fwd_z;	/* Movement vector. */

void forward (double delta)
{
	/* Moves the viewpoint by "delta" units, following the pitch,
	   yaw and roll angles (alpha, beta and gamma). In effects,
	   gamma is not used as it doesn't affect the direction
	   given by the first two angles.

	   The function also returns the three components of the
	   movement vector, called "fwd_x", "fwd_y" and "fwd_z":
	   this is useful when considering inertia and composite
	   movements, thus allowing more realistic simulations.

	   There's no "backward" function: just use negative deltas.

	   For any other movements, you can directly modify the
	   "cam_x", "cam_y" and "cam_z" variables. No further
	   operations are needed. */

	fwd_x = -delta * opt_tsinbeta * opt_tcosalpha;
	fwd_z =  delta * opt_tcosbeta * opt_tcosalpha;
	fwd_y =  delta * opt_tsinalpha;

	cam_x += fwd_x;
	cam_y += fwd_y;
	cam_z += fwd_z;
}

void force (double delta)
{
	/* Does the same as the previous function, but doesn't
	   effectively change the position of the viewpoint:
	   useful to find out "pure" components, without
	   altering our position in space. You may simply
	   add those values to cam_x, cam_y and cam_z later,
	   or perform some more complex calculations with them. */

	fwd_x = -delta * opt_tsinbeta * opt_tcosalpha;
	fwd_z =  delta * opt_tcosbeta * opt_tcosalpha;
	fwd_y =  delta * opt_tsinalpha;
}

void change_angle_of_view ()
{
	/* To change one or more of the alpha/beta/gamma (pitch/yaw/roll)
	   angles, the main program can change them directly, specifying
	   any doubleing point value in degrees. Then, by calling this
	   function, all of the related internal maths are updated. */

	opt_tcosalpha = cos (alpha*deg);
	opt_tsinalpha = sin (alpha*deg);
	opt_tcosbeta  = cos (beta *deg);
	opt_tsinbeta  = sin (beta *deg);
	opt_tcosgamma = cos (gamma*deg);
	opt_tsingamma = sin (gamma*deg);
}

/// 3D to 2D conversions manipulation. ///////////////////////////////////////

void change_txm_repeating_mode (long h_matrixs, long v_matrixs)
{
	/* The size of the visible part of the textures can vary from
	   1 to 1024: it is espressed in 1/16th of a standard texture.
	   Now, since a standard texture is (as a convention) supposed
	   to be 256x256 pixels, by changing the V_MATRIXS and H_MATRIXS
	   values you can determine another size that may fit your needs.
	   Obviously, the default values are H_MATRIXS = V_MATRIXS = 16,
	   which will correctly show a 256x256-pixels-texture.
	   If, as an example, you set H_MATRIXS = 8, the texture would
	   result made of 128x256 pixels. However, the vertical lookup
	   index always gets an intrinsic shift of 8 bits, so don't forget
	   to ALIGN each line of your textures to the nearest 256-bytes
	   boundary, or you'll get the wrong alignment when H_MATRIXS
	   is different from 16.

	   By the way: if you are using a standard texture (256x256),
	   you can easily repeat the texture on a large polygon by setting
	   H_MATRIXS and/or V_MATRIXS to values that are greater than 16,
	   upto 1024, with no additional computations and loss of speed.
	   I must say this mechanism, however, would give wrong results
	   when using shaded or depth-buffered polygons, so don't use
	   repeating textures on such polygons. */

	H_MATRIXS = h_matrixs;
	V_MATRIXS = v_matrixs;
	XSIZE     = TXTR_XSIZE * H_MATRIXS;
	YSIZE     = TXTR_YSIZE * V_MATRIXS;
	XSIZEf    = XSIZE;
	YSIZEf    = YSIZE;
}

void change_camera_lens (double DPP)
{
	/* To change the lens of the virtual camera, the caller can set
	   "dpp" to any value but negatives and below 1: the smallest is
	   that value, the greatest are the distortions due to perspective
	   conversions. Usually "dpp" gives a normal appearence to 3D objects
	   when it's set to the display's height. Smallest values give
	   "wide-field" cameras, and vice versa. The default value is 100,
	   half the height of an MCGA screen: that's quite a wide-field.
	   Once "dpp" is modified, this function must be called.

	   "inv_dpp" is 1 / dpp: since "dpp" is a divisor in many situations,
	   its inverse allows multiplying instead of dividing. On a Pentium,
	   this means 3 cycles instead of 39. */

	dpp = DPP;

	if (dpp <= 1) dpp = 1;

	inv_dpp = 1 / dpp;

	XCOEFF  = EMU_K * inv_dpp;
	YCOEFF  = EMU_K * inv_dpp;

	change_angle_of_view ();
}

/// Scanline tracing handlers. ///////////////////////////////////////////////
//
//	These functions are called from an assembly "NEAR CALL", not from C++
//	Thus, they have to avoid executing the "RETF" the compiler may put
//	at the end of each function depending on the memory model.
//	This is done by placing a near "RET" instruction before the "RETF".
//	Well it's a way to workaround the problem, but it's the only SAFE
//	way I actually know to put a fast routing table into C++ code.
//
//	The last handler, it isn't really: it's some sort of "inline" buffer
//	placed within CS, containing the addresses to each filling routine,
//	arranged to be always near (16-bit) pointers.
//
//////////////////////////////////////////////////////////////////////////////
//
//	It shouldn't be very hard to build other filling routines: they are
//	all called by "linefill", using a common registers layout. That is:
//
//		CX (on entry)	    =	number of pixels forming the line;
//		ES:[DI]		    =	pointer to the first byte of the line;
//		ES (segment)	    = 	segment of the "display" memory area;
//
//	Also you may need some other data about the line you're gonna fill.
//	Here's what "linefill" can provide to each handler:
//
//		lscancode (global)  =	Y coordinate on the screen (0..199);
//		linestart (global)  =	X coordinate of starting point;
//		linefinish (global) =	X coordinate of last point.
//
//	Finally, a few rules custom handlers have to follow, mainly due to
//	optimization skills used to call the handlers as fast as possible.
//	You can do anything but what I forbidden below.
//	You might:
//
//		- Declare your handler as a "void near ... (void)" function:
//		  in most cases, there's no need to declare it as a near
//		  function, but just for sure...
//		- On entry, the first line of your handler should be:
//			asm	mov	sp, previous_sp
//		  which will prevent the stack layout from being altered
//		  by the C++ calling convention and/or silly values saved
//		  on the stack by many compilers.
//		- Always execute a near "ret" instruction when you're done.
//		  This will avoid executing the rest of the code: the C++
//		  will always expect your function has been called from
//		  a C++ function call, not directly from inline assembly.
//		- Never change the BP register unless you will restore it
//		  before returning: it's used by the C++ calling convention to
//		  access local variables saved on the stack on functions call.
//		- Never change the lscancode/linestart/linefinish variables
//		  ("linefill" loops rely on them being left as they were).
//		- Neither pass parameters to the handlers, nor returning
//		  some values back to the caller. Since the caller is not a
//		  C++ routine, they wouldn't work and would probably crash.
//		- Never change the segments you're working on, unless you
//		  really know what you're doing. ES may be changed however,
//		  since it's reloaded between calls to any of the handlers.
//		  FS and GS, if you can get to them, are not used and can
//		  be freely used by the handlers.
//		- Write a SLIM and FAST routine, since it would occur for
//		  upto 64000 times, depending on how many pixels formed
//		  the shape we were filling.
//
//////////////////////////////////////////////////////////////////////////////

long lscancode  = 0;	/* Integer coords of scanline to be filled: Y. 	    */
long linestart  = 0;	/* Integer coords of scanline to be filled: StartX. */
long linefinish = 0;	/* Integer coords of scanline to be filled: EndX.   */

unsigned previous_sp;	/* Preserved stack pointer for handlers calling.    */

#define evenizer 0xFFFE /* (bitmask) Byte-To-Word offsets alignment.	    */
#define prehalve 0xF7DE	/* (bitmask) Prepares a pixel color to be halved.   */
#define redcompo 0xF800 /* (bitmask) Extracts pixel's red component.	    */
#define grncompo 0x07E0 /* (bitmask) Extracts pixel's green component.	    */
#define blucompo 0x001F /* (bitmask) Extracts pixel's blue component.	    */
#define red_blue 0xF81F /* (bitmask) Extracts both red and blue components. */

#define redbyte  0xF8 	/* (bitmask) Extracts pixel's red component.	    */
#define blubyte  0x1F 	/* (bitmask) Extracts pixel's blue component.	    */

/// / // / // / // / // / // / // / // / // / // / // / // / // / // / // / //

void near plain () {
	asm	mov	sp, previous_sp
	asm	mov	ax, patword	/* Standard monochrome fill. */
	asm 	rep	stosw
	asm	ret			/* Return from near call, not far. */
}

void near brilliant () {
	asm {	mov	sp, previous_sp
		mov	ax, patword		// get pattern for gradient...
		and	ax, redcompo		// AH = RED COMPONENT
		mov	al, byte ptr patword	//
		and	al, blucompo		// AL = BLUE COMPONENT
		mov     dx, patword		//
		and	dx, grncompo		// DX = GREEN COMPONENT
		push	ds
		push	es
		pop	ds }
fill:	asm {	mov	bx, [di]
		add	di, 2
		and	bx, red_blue
		add	bh, ah
		jnc	Rblow
		mov	bh, redbyte }
Rblow:	asm {	add	bl, al
		cmp	bl, blubyte
		jbe	Bblow
		mov	bl, blubyte }
Bblow:	asm {	mov	si, [di]
		and	si, grncompo
		add	si, dx
		cmp	si, grncompo
		jbe	Gblow
		mov	si, grncompo }
Gblow:	asm {	or	bx, si
		dec	cx
		mov	[di-2], bx
		jnz	fill
		pop	ds
		ret } }			/* Return from near call, not far. */

/// / // / // / // / // / // / // / // / // / // / // / // / // / // / // / //

#define spanlength   16	/* Length of each horizontal span of textured area.*/
#define spanshifts    4 /* Bitwise shifting (for UV indexs) = log2(spanlen)*/

double _x, _y, _z, _k;	/* Texturing filler temporary data.		   */
double fx, fy, fz;	/* Forward drift multiplied by length of span.     */
double one = 1.0;	/* Constant value, used instead of fld1 (slower).  */
long   u, v;		/* Classic lookup indexs in texturing.		   */

/// / // / // / // / // / // / // / // / // / // / // / // / // / // / // / //

void near forw_texture () {
	asm {   mov	sp, previous_sp
		push	bp			// it's needed, therefore save
		mov	ax, word ptr txm[2]	// load texture map address
		mov	bx, word ptr txm[0]	// get offset too
		shr	bx, 4			// translate offset
		add	ax, bx			// paragraph alignment
		db 	0x8e, 0xe0		// mov fs, ax (FS = texture)
		mov	ax, cx			// preserve number of pixels
	/* forward texturing Z-calculation sequence */
		fild 	linestart
		fsub 	t_center_x
		fld	st(0)
		fld	st(0)
		fmul 	hz
		fild 	lscancode
		fsub 	t_center_y
		fmul 	vz
		faddp
		fadd 	oz
		fst 	_z
	/* texturing handlers common init tail */
		fdivr 	one
		fstp 	_k
		fmul 	hx
		fild 	lscancode
		fsub 	t_center_y
		fmul 	vx
		faddp
		fadd 	ox
		fstp 	_x
		fmul 	hy
		fild 	lscancode
		fsub 	t_center_y
		fmul 	vy
		faddp
		fadd 	oy
		fst 	_y
		fmul 	YSIZEf
		fmul 	_k
		fld 	_x
		fmul 	XSIZEf
		fmul 	_k
		fxch
		fistp 	v
		fistp 	u }
	/* texturing handlers common span-cycle */
  span: asm {   cmp 	ax, 0			// test for end of scanline
		jg  	again			// if greater than 0, go on
		pop	bp			// which was previously saved
		ret }				/* Return from near call. */
 again:	asm {	cmp 	ax, spanlength
		jge  	compl
		mov 	cl, al
		jmp 	unfin }
 compl: asm 	mov 	cl, spanlength
 unfin: asm {	fld   	_z	       	       	// 1 cycle   stack: z
		fadd  	fz                     	// 1 cycle   stack: z+k3
		fld   	_x	       	       	// 1 cycle   stack: x, z+k3
		fadd  	fx                     	// 1 cycle   stack: x+k1, z+k3
		fxch                   	       	// no time   stack: z+k3, x+k1
		fst   	_z                     	// 2 cycles  stack: z+k3, x+k1
		fxch                   	       	// no time   stack: x+k1, z+k3
		fst   	_x                     	// 2 cycles  stack: x+k1, z+k3
		fxch                   	       	// no time   stack: z+k3, x+k1
		fdivr 	one            	       	// 39 cycles stack: k4, x+k1
		sub 	ax, spanlength		// ³
		push	ax		       	// ³while FPU is working
       db 0x66; mov 	ax, word ptr u         	// ³for 39 cycles (fdivr),
       db 0x66; mov 	dx, word ptr v         	// ³this group takes nothing.
		push 	ds            	       	// ³
		fxch                   	       	// no time   stack: x+k1, k4
		fmul  	XSIZEf         		// 1 cycle   stack: x..., k4
		fld   	_y                     	// 1 cycle   stack: y, x..., k4
		fadd  	fy	       		// 1 cycle   stack: y+k2, x..., k4
		fst   	_y               	// 3 cycles  stack: y+k2, x..., k4
		fmul  	YSIZEf        		// 1 cycle   stack: y..., x..., k4
		fxch                   		// no time   stack: x..., y..., k4
		fmul  	st, st(2)        	// 1 cycle   stack: u, y..., k4
		fxch                   		// no time   stack: y..., u, k4
		fmul  	st, st(2)        	// 1 cycle   stack: v, u, k4
		fxch                   		// no time   stack: u, v, k4
		fistp 	u              		// 6 cycles  stack: v, k4
		fistp 	v              		// 6 cycles  stack: k4
		ffree 	st			// 1 cycle   stack: nothing
/*     db 0x66; mov 	si, word ptr v
       db 0x66; mov 	bp, word ptr u
       db 0x66; sub 	si, dx
       db 0x66; sub 	bp, ax
       db 0x66; sar 	si, spanshifts
		push	es
       db 0x66; sar 	bp, spanshifts
		pop	ds }
	// normal texturing span-filling procedure
 flood:	asm {	mov 	bh, dh			// 1 (Pentium cycles)
		add 	dx, si			// * (= pairable)
		mov 	bl, ah			// 1
		add 	ax, bp			// *
		and	bx, evenizer		// 1
		add	di, 2			// *
		db 	0x64, 0x8B, 0x1F 	// 1+PFX+AGI (mov bx, fs:[bx])
		dec 	cl			// *
		mov   	[di-2], bx 		// 1
		jnz 	flood	  		// * (7 cycles, theoretically)
		pop 	ds
		pop	ax
		jmp 	span } } */
       db 0x66; mov 	si, word ptr v
       db 0x66; mov 	bp, word ptr u
       db 0x66; sub 	si, dx
       db 0x66; sub 	bp, ax
       db 0x66; sar 	si, spanshifts
		push	es
       db 0x66; sar 	bp, spanshifts
		pop	ds
       db 0x66; shl	dx, 16
       db 0x66; shl	si, 16
		mov	dx, ax
		mov	si, bp }
	// normal texturing span-filling procedure
 flood:	asm {	mov 	bl, dh			// 1 (Pentium cycles)
		db 0x66; rol dx, 16
		mov 	bh, dh			// 1
		db 0x66; rol dx, 16
		and	bx, evenizer		// 1
		db 0x66; add dx, si		// * (= pairable)
		add	di, 2			// *
		db 	0x64, 0x8B, 0x1F 	// 1+PFX+AGI (mov bx, fs:[bx])
		dec 	cl			// *
		mov   	[di-2], bx 		// 1
		jnz 	flood	  		// * (7 cycles, theoretically)
		pop 	ds
		pop	ax
		jmp 	span } }

void near back_texture () {
	asm {   mov	sp, previous_sp
		push	bp			// it's needed, therefore save
		mov	ax, word ptr txm[2]	// load texture map address
		mov	bx, word ptr txm[0]	// get offset too
		shr	bx, 4			// translate offset
		add	ax, bx			// paragraph alignment
		db 	0x8e, 0xe0		// mov fs, ax (FS = texture)
		mov	ax, cx			// preserve number of pixels
	/* backward filling: starts from the end */
		add	di, cx
		add	di, cx
		dec	di
		dec	di
		fld	t_center_x
		fisub	linefinish
		fld	st(0)
		fld	st(0)
		fmul 	hz
		fild 	lscancode
		fsub 	t_center_y
		fmul 	vz
		faddp
		fadd 	oz
		fst 	_z
	/* texturing handlers common init tail */
		fdivr 	one
		fstp 	_k
		fmul 	hx
		fild 	lscancode
		fsub 	t_center_y
		fmul 	vx
		faddp
		fadd 	ox
		fstp 	_x
		fmul 	hy
		fild 	lscancode
		fsub 	t_center_y
		fmul 	vy
		faddp
		fadd 	oy
		fst 	_y
		fmul 	YSIZEf
		fmul 	_k
		fld 	_x
		fmul 	XSIZEf
		fmul 	_k
		fxch
		fistp 	v
		fistp 	u }
	/* texturing handlers common span-cycle */
  span: asm {   cmp 	ax, 0			// test for end of scanline
		jg  	again			// if greater than 0, go on
		pop	bp			// which was previously saved
		ret }				/* Return from near call. */
 again:	asm {	cmp 	ax, spanlength
		jge  	compl
		mov 	cl, al
		jmp 	unfin }
 compl: asm 	mov 	cl, spanlength
 unfin: asm {	fld   	_z	       	       	// 1 cycle   stack: z
		fadd  	fz                     	// 1 cycle   stack: z+k3
		fld   	_x	       	       	// 1 cycle   stack: x, z+k3
		fadd  	fx                     	// 1 cycle   stack: x+k1, z+k3
		fxch                   	       	// no time   stack: z+k3, x+k1
		fst   	_z                     	// 2 cycles  stack: z+k3, x+k1
		fxch                   	       	// no time   stack: x+k1, z+k3
		fst   	_x                     	// 2 cycles  stack: x+k1, z+k3
		fxch                   	       	// no time   stack: z+k3, x+k1
		fdivr 	one            	       	// 39 cycles stack: k4, x+k1
		sub 	ax, spanlength		// ³
		push	ax		       	// ³while FPU is working
       db 0x66; mov 	ax, word ptr u         	// ³for 39 cycles (fdivr),
       db 0x66; mov 	dx, word ptr v         	// ³this group takes nothing.
		push 	ds            	       	// ³
		fxch                   	       	// no time   stack: x+k1, k4
		fmul  	XSIZEf         		// 1 cycle   stack: x..., k4
		fld   	_y                     	// 1 cycle   stack: y, x..., k4
		fadd  	fy	       		// 1 cycle   stack: y+k2, x..., k4
		fst   	_y               	// 3 cycles  stack: y+k2, x..., k4
		fmul  	YSIZEf        		// 1 cycle   stack: y..., x..., k4
		fxch                   		// no time   stack: x..., y..., k4
		fmul  	st, st(2)        	// 1 cycle   stack: u, y..., k4
		fxch                   		// no time   stack: y..., u, k4
		fmul  	st, st(2)        	// 1 cycle   stack: v, u, k4
		fxch                   		// no time   stack: u, v, k4
		fistp 	u              		// 6 cycles  stack: v, k4
		fistp 	v              		// 6 cycles  stack: k4
		ffree 	st			// 1 cycle   stack: nothing
       db 0x66; mov 	si, word ptr v
       db 0x66; mov 	bp, word ptr u
       db 0x66; sub 	si, dx
       db 0x66; sub 	bp, ax
       db 0x66; sar 	si, spanshifts
		push	es
       db 0x66; sar 	bp, spanshifts
		pop	ds }
	/* normal texturing span-filling procedure */
 flood:	asm {	mov 	bh, dh			// 1 (Pentium cycles)
		add 	dx, si			// * (= pairable)
		mov 	bl, ah			// 1
		add 	ax, bp			// *
		and	bx, evenizer		// 1
		sub	di, 2			// *
		db 	0x64, 0x8B, 0x1F 	// 1+PFX+AGI (mov bx, fs:[bx])
		dec 	cl			// *
		mov   	[di+2], bx 		// 1
		jnz 	flood	  		// * (7 cycles, theoretically)
		pop 	ds
		pop	ax
		jmp 	span } }

/// / // / // / // / // / // / // / // / // / // / // / // / // / // / // / //

void near forw_gradient () {
	asm {   mov	sp, previous_sp
		push	bp			// it's needed, therefore save
		mov	ax, word ptr txm[2]	// load texture map address
		mov	bx, word ptr txm[0]	// get offset too
		shr	bx, 4			// translate offset
		add	ax, bx			// paragraph alignment
		db 	0x8e, 0xe0		// mov fs, ax (FS = texture)
		mov	ax, cx			// preserve number of pixels
	/* forward texturing Z-calculation sequence */
		fild 	linestart
		fsub 	t_center_x
		fld	st(0)
		fld	st(0)
		fmul 	hz
		fild 	lscancode
		fsub 	t_center_y
		fmul 	vz
		faddp
		fadd 	oz
		fst 	_z
	/* gradient filling does not ignore pattern */
		mov	cx, patword		// get pattern for gradient...
		and	cx, prehalve		// cut least significant bits
		shr	cx, 1			// divide components by two
		db 0x64, 0x89, 0x0E, 0x04, 0x00 // mov fs:[4], cx
	/* texturing handlers common init tail */
		fdivr 	one
		fstp 	_k
		fmul 	hx
		fild 	lscancode
		fsub 	t_center_y
		fmul 	vx
		faddp
		fadd 	ox
		fstp 	_x
		fmul 	hy
		fild 	lscancode
		fsub 	t_center_y
		fmul 	vy
		faddp
		fadd 	oy
		fst 	_y
		fmul 	YSIZEf
		fmul 	_k
		fld 	_x
		fmul 	XSIZEf
		fmul 	_k
		fxch
		fistp 	v
		fistp 	u }
	/* texturing handlers common span-cycle */
  span: asm {   cmp 	ax, 0			// test for end of scanline
		jg  	again			// if greater than 0, go on
		pop	bp			// which was previously saved
		ret }				/* Return from near call. */
 again:	asm {	cmp 	ax, spanlength
		jge  	compl
		mov 	cl, al
		jmp 	unfin }
 compl: asm 	mov 	cl, spanlength
 unfin: asm {	fld   	_z	       	       	// 1 cycle   stack: z
		fadd  	fz                     	// 1 cycle   stack: z+k3
		fld   	_x	       	       	// 1 cycle   stack: x, z+k3
		fadd  	fx                     	// 1 cycle   stack: x+k1, z+k3
		fxch                   	       	// no time   stack: z+k3, x+k1
		fst   	_z                     	// 2 cycles  stack: z+k3, x+k1
		fxch                   	       	// no time   stack: x+k1, z+k3
		fst   	_x                     	// 2 cycles  stack: x+k1, z+k3
		fxch                   	       	// no time   stack: z+k3, x+k1
		fdivr 	one            	       	// 39 cycles stack: k4, x+k1
		sub 	ax, spanlength		// ³
		push	ax		       	// ³while FPU is working
       db 0x66; mov 	ax, word ptr u         	// ³for 39 cycles (fdivr),
       db 0x66; mov 	dx, word ptr v         	// ³this group takes nothing.
		push 	ds            	       	// ³
		fxch                   	       	// no time   stack: x+k1, k4
		fmul  	XSIZEf         		// 1 cycle   stack: x..., k4
		fld   	_y                     	// 1 cycle   stack: y, x..., k4
		fadd  	fy	       		// 1 cycle   stack: y+k2, x..., k4
		fst   	_y               	// 3 cycles  stack: y+k2, x..., k4
		fmul  	YSIZEf        		// 1 cycle   stack: y..., x..., k4
		fxch                   		// no time   stack: x..., y..., k4
		fmul  	st, st(2)        	// 1 cycle   stack: u, y..., k4
		fxch                   		// no time   stack: y..., u, k4
		fmul  	st, st(2)        	// 1 cycle   stack: v, u, k4
		fxch                   		// no time   stack: u, v, k4
		fistp 	u              		// 6 cycles  stack: v, k4
		fistp 	v              		// 6 cycles  stack: k4
		ffree 	st			// 1 cycle   stack: nothing
       db 0x66; mov 	si, word ptr v
       db 0x66; mov 	bp, word ptr u
       db 0x66; sub 	si, dx
       db 0x66; sub 	bp, ax
       db 0x66; sar 	si, spanshifts
		push	es
       db 0x66; sar 	bp, spanshifts
		pop	ds }
	/* gradient texturing span-filling procedure */
 flood:	asm {	mov 	bh, dh			// 1 (Pentium cycles)
		add 	dx, si			// * (= pairable)
		mov 	bl, ah			// 1
		add 	ax, bp			// *
		and	bx, evenizer		// 1
		add	di, 2			// *
		db 	0x64, 0x8B, 0x1F 	// 1+PFX+AGI (mov bx, fs:[bx])
		and	bx, prehalve		// 1
		shr	bx, 1			// 1
		db 0x64, 0x03, 0x1E, 0x04, 0x00 // 1+PFX (add bx, fs:[4])
		mov   	[di-2], bx 		// 1
		dec 	cl			// *
		jnz 	flood	  		// 1 (14 cycles)
		pop 	ds
		pop	ax
		jmp 	span } }

void near back_gradient () {
	asm {   mov	sp, previous_sp
		push	bp			// it's needed, therefore save
		mov	ax, word ptr txm[2]	// load texture map address
		mov	bx, word ptr txm[0]	// get offset too
		shr	bx, 4			// translate offset
		add	ax, bx			// paragraph alignment
		db 	0x8e, 0xe0		// mov fs, ax (FS = texture)
		mov	ax, cx			// preserve number of pixels
	/* backward filling: starts from the end */
		add	di, cx
		add	di, cx
		dec	di
		dec	di
		fld	center_x
		fisub	linefinish
		fld	st(0)
		fld	st(0)
		fmul 	hz
		fild 	lscancode
		fsub 	center_y
		fmul 	vz
		faddp
		fadd 	oz
		fst 	_z
	/* gradient filling does not ignore pattern */
		mov	cx, patword		// get pattern for gradient...
		and	cx, prehalve		// cut least significant bits
		shr	cx, 1			// divide components by two
		db 0x64, 0x89, 0x0E, 0x04, 0x00 // mov fs:[4], cx
	/* texturing handlers common init tail */
		fdivr 	one
		fstp 	_k
		fmul 	hx
		fild 	lscancode
		fsub 	center_y
		fmul 	vx
		faddp
		fadd 	ox
		fstp 	_x
		fmul 	hy
		fild 	lscancode
		fsub 	center_y
		fmul 	vy
		faddp
		fadd 	oy
		fst 	_y
		fmul 	YSIZEf
		fmul 	_k
		fld 	_x
		fmul 	XSIZEf
		fmul 	_k
		fxch
		fistp 	v
		fistp 	u }
	/* texturing handlers common span-cycle */
  span: asm {   cmp 	ax, 0			// test for end of scanline
		jg  	again			// if greater than 0, go on
		pop	bp			// which was previously saved
		ret }				/* Return from near call. */
 again:	asm {	cmp 	ax, spanlength
		jge  	compl
		mov 	cl, al
		jmp 	unfin }
 compl: asm 	mov 	cl, spanlength
 unfin: asm {	fld   	_z	       	       	// 1 cycle   stack: z
		fadd  	fz                     	// 1 cycle   stack: z+k3
		fld   	_x	       	       	// 1 cycle   stack: x, z+k3
		fadd  	fx                     	// 1 cycle   stack: x+k1, z+k3
		fxch                   	       	// no time   stack: z+k3, x+k1
		fst   	_z                     	// 2 cycles  stack: z+k3, x+k1
		fxch                   	       	// no time   stack: x+k1, z+k3
		fst   	_x                     	// 2 cycles  stack: x+k1, z+k3
		fxch                   	       	// no time   stack: z+k3, x+k1
		fdivr 	one            	       	// 39 cycles stack: k4, x+k1
		sub 	ax, spanlength		// ³
		push	ax		       	// ³while FPU is working
       db 0x66; mov 	ax, word ptr u         	// ³for 39 cycles (fdivr),
       db 0x66; mov 	dx, word ptr v         	// ³this group takes nothing.
		push 	ds            	       	// ³
		fxch                   	       	// no time   stack: x+k1, k4
		fmul  	XSIZEf         		// 1 cycle   stack: x..., k4
		fld   	_y                     	// 1 cycle   stack: y, x..., k4
		fadd  	fy	       		// 1 cycle   stack: y+k2, x..., k4
		fst   	_y               	// 3 cycles  stack: y+k2, x..., k4
		fmul  	YSIZEf        		// 1 cycle   stack: y..., x..., k4
		fxch                   		// no time   stack: x..., y..., k4
		fmul  	st, st(2)        	// 1 cycle   stack: u, y..., k4
		fxch                   		// no time   stack: y..., u, k4
		fmul  	st, st(2)        	// 1 cycle   stack: v, u, k4
		fxch                   		// no time   stack: u, v, k4
		fistp 	u              		// 6 cycles  stack: v, k4
		fistp 	v              		// 6 cycles  stack: k4
		ffree 	st			// 1 cycle   stack: nothing
       db 0x66; mov 	si, word ptr v
       db 0x66; mov 	bp, word ptr u
       db 0x66; sub 	si, dx
       db 0x66; sub 	bp, ax
       db 0x66; sar 	si, spanshifts
		push	es
       db 0x66; sar 	bp, spanshifts
		pop	ds }
	/* gradient texturing span-filling procedure */
 flood:	asm {	mov 	bh, dh			// 1 (Pentium cycles)
		add 	dx, si			// * (= pairable)
		mov 	bl, ah			// 1
		add 	ax, bp			// *
		and	bx, evenizer		// 1
		sub	di, 2			// *
		db 	0x64, 0x8B, 0x1F 	// 1+PFX+AGI (mov bx, fs:[bx])
		and	bx, prehalve		// 1
		shr	bx, 1			// 1
		db 0x64, 0x03, 0x1E, 0x04, 0x00 // 1+PFX (add bx, fs:[4])
		mov   	[di+2], bx 		// 1
		dec 	cl			// *
		jnz 	flood	  		// 1 (14 cycles)
		pop 	ds
		pop	ax
		jmp 	span } }

/// / // / // / // / // / // / // / // / // / // / // / // / // / // / // / //
//
//	When writing the default handlers, I followed a certain scheme
//	to organize the codes, so that the bits of the code can contain
//	all informations about the attributes of each surface. Here it is:
//
//	ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ handler code ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
//	ÚÄÄÄÄÄÄÄ unused ÄÄÄÄÄÄÄ¿ÚÄÄÄ effect ÄÄÄ¿ÚÄ type flags Ä¿ÚÄ(**)Ä¿
// BIT:	 15  14  13  12  11  10   9   8   7   6   5   4   3   2   1   0
// VALUE:                        512 256 128 64  32  16   8   4   2   1
//	ÚÄÄ¿ÚÄÄ¿ÚÄÄ¿ÚÄÄ¿ÚÄÄ¿ÚÄÄ¿Ú Ä¿Ú Ä¿ÚÄÄ¿ÚÄÄ¿Ú Ä¿Ú Ä¿ÚÄÄ¿ÚÄÄ¿ÚÄÄ¿ÚÄÄ¿
//	ÀÄÄÙÀÄÄÙÀÄÄÙÀÄÄÙÀÄÄÙÀÄÄÙÀÄ ÙÀÄ ÙÀÄÄÙÀÄÄÙÀÄ ÙÀÄ ÙÀÄÄÙÀÄÄÙÀÄÄÙÀÄÄÙ
//		      translucent Ù   ³   ³   ³   ³   ³   ³   ³   ÀÄÄÄ´
//			  transparent Ù   ³   ³   ³   ³   ³   ³       ³
//			        brilliant Ù   ³   ³   ³   ³   ³       ³
//			             gradient Ù   ³   ³   ³   ³       ³
//			    activate depth raster Ù   ³   ³   ³       ³
//				    superimpose shade Ù   ³   ³       ³
//				            apply texture Ù   ³       ³
//				          fill backward (***) Ù       ³
//								      ³
//                   (**) 16/32-bit pointers alignment (will be zero) Ù
//
//	(**)  unused and alignment bits: will be all zeroed before tracing.
//	(***) fill backward: automatically asserted when needed.
//
//	- fragmented bit boxes not active yet -
//
/// / // / // / // / // / // / // / // / // / // / // / // / // / // / // / //

#define allocated_codes     	 36
#define forbiddenbitsmask    0x03F8

#define PLAIN      		  0
#define BACKWARD		  4
#define	TEXTURE     		  8
#define GRADIENT     		 64
#define BRILLIANT     		128

unsigned long filling_router[allocated_codes] = {

	/* Filling routines offset (internal routing table). */

	//	Filler offset:		//     Code	//    Verse	//

	(unsigned)plain,		/* mapeffect = 0000 	->	*/
	(unsigned)plain,		/* mapeffect = 0004 	->	*/
	(unsigned)forw_texture,		/* mapeffect = 0008 	->	*/
	(unsigned)back_texture,		/* mapeffect = 0012 	<-	*/
	(unsigned)0,                   	/* mapeffect = 0016 	->	*/
	(unsigned)0,                  	/* mapeffect = 0020 	<-	*/
	(unsigned)0,                   	/* mapeffect = 0024 	->	*/
	(unsigned)0,                    /* mapeffect = 0028 	<-	*/
	(unsigned)0,                   	/* mapeffect = 0032 	->	*/
	(unsigned)0,                  	/* mapeffect = 0036 	<-	*/
	(unsigned)0,                   	/* mapeffect = 0040 	->	*/
	(unsigned)0,                    /* mapeffect = 0044 	<-	*/
	(unsigned)0,                   	/* mapeffect = 0048 	->	*/
	(unsigned)0,                  	/* mapeffect = 0052 	<-	*/
	(unsigned)0,                   	/* mapeffect = 0056 	->	*/
	(unsigned)0,                    /* mapeffect = 0060 	<-	*/
	(unsigned)plain,        	/* mapeffect = 0064 	->	*/
	(unsigned)plain,	        /* mapeffect = 0068 	->	*/
	(unsigned)forw_gradient,	/* mapeffect = 0072 	->	*/
	(unsigned)back_gradient, 	/* mapeffect = 0076 	<-	*/
	(unsigned)0,                   	/* mapeffect = 0080 	->	*/
	(unsigned)0,                   	/* mapeffect = 0084 	->	*/
	(unsigned)0,                   	/* mapeffect = 0088 	->	*/
	(unsigned)0,                   	/* mapeffect = 0092 	->	*/
	(unsigned)0,                   	/* mapeffect = 0096 	->	*/
	(unsigned)0,                   	/* mapeffect = 0100 	->	*/
	(unsigned)0,                   	/* mapeffect = 0104 	->	*/
	(unsigned)0,                   	/* mapeffect = 0108 	->	*/
	(unsigned)0,                   	/* mapeffect = 0112 	->	*/
	(unsigned)0,                   	/* mapeffect = 0116 	->	*/
	(unsigned)0,                   	/* mapeffect = 0120 	->	*/
	(unsigned)0,                   	/* mapeffect = 0124 	->	*/
	(unsigned)brilliant,      	/* mapeffect = 0128 	->	*/
	(unsigned)brilliant,      	/* mapeffect = 0132 	->	*/
	(unsigned)brilliant,      	/* mapeffect = 0136 	->	*/ //forw_brilliant
	(unsigned)brilliant       	/* mapeffect = 0140 	<-	*/ //back_brilliant

};

/// / // / // / // / // / // / // / // / // / // / // / // / // / // / // / //

long lastlimit = 65280;

void linefill ()
{
	/* It's called internally, to trace a single scanline: don't worry
	   if it's not inline: there is no real need of such optimization.

	   Also, by keeping it as a separate function, we can easily export
	   the code to other contests, since this is the only function
	   which is device-dependent, apart from the filling routines.

	   In real mode, 0x66 prefixes toggle operands' size to 32-bit.
	   I'm afraid the C++ inline assembler seems not to support them.
	   They'd be removed in a protected mode environment. Lines like
	   "db 0x66; mov ax, word ptr scanline" would then become
	   "mov eax, dword ptr scanline". */

		asm {	db 	0x66
			mov	ax, word ptr linestart
			db	0x66
			cmp	ax, word ptr linefinish
			jle	ordered
			db	0x66
			xchg	ax, word ptr linefinish
			db	0x66
			mov	word ptr linestart, ax }
       ordered:	asm {	db	0x66
			mov	ax, word ptr ubxl
			db	0x66
			cmp	ax, word ptr linestart
			jg	h_clip_low }
			return;
    h_clip_low: asm {	db	0x66
			mov	ax, word ptr lbxl
			db	0x66
			cmp	ax, word ptr linefinish
			jle	h_clip_high }
			return;
   h_clip_high:	asm {	db	0x66
			mov	ax, word ptr lbxl
			db	0x66
			cmp	ax, word ptr linestart
			jle	h_clip_left
			db	0x66
			mov	word ptr linestart, ax }
   h_clip_left: asm {	db	0x66
			mov	ax, word ptr ubxl
			db	0x66
			cmp	ax, word ptr linefinish
			jg	h_clip_right
			db	0x66
			dec	ax
			db	0x66
			mov	word ptr linefinish, ax }
  h_clip_right:	asm {   db 0x66;xor di, di
			mov	si, word ptr lscancode
			les	di, dword ptr display
			shl	si, 2
			db 0x66;add di, word ptr scan[si]
			db 0x66;cmp di, word ptr lastlimit
			jbe 	frompagezero
			db 0x66;sub di, word ptr lastlimit
			mov	ax, es
			add	ax, 0x0FF0
			mov	es, ax }
  frompagezero:	asm {	mov	ax, word ptr linestart
			add	di, ax
			mov	cx, word ptr linefinish
			add	di, ax
			sub	cx, word ptr linestart
			inc	cx
			mov	si, mapeffect
			mov	previous_sp, sp
			sub	previous_sp, 2
			call	word ptr filling_router[si] }
}

/// Engine core functions. ///////////////////////////////////////////////////

void trifill (long  x1, long  y1, long  x2,
	      long  y2, long  x3, long  y3)
{
	/* It's called internally: fills a triangle.
	   (Notice no outlines are determined before filling the shape:
	   this is one of the many advantages of those magic triangles.) */

	long  t0x, t0y;		/* Coordinates of top vertex    (T0 vertex) */
	long  b1x, b1y;  	/* Coordinates of middle vertex (B1 vertex) */
	long  b2x, b2y;		/* Coordinates of bottom vertex (B2 vertex) */

	double t0b1_drift;	/* Variation of X from vertexs T0 to B1.    */
	double t0b2_drift;       /* Variation of X from vertexs T0 to B2.    */
	double b1b2_drift;       /* Variation of X from vertexs B1 to B2.    */

	double sx, ex;		/* Start-X / End-X for each scanline.	    */

	double out;		/* Height of fragment laying above top line */

	/* The function begins by fixing three points, which form a standard
	   scheme of the given triangle. Relatively to how they appear on the
	   screen, the points are called T0 (highest point of the triangle),
	   B1 (which lies between T0 and B2), and B2 itself, which is the
	   bottom end of the shape. X coordinates need not to be sorted
	   in any way: that's performed by "linefill". */

	/* But first, it has to pay attention for particular triangles,
	   by performing some special handling when the triangle looks
	   pratically like a single horizontal line. */

		if (y1 == y2 && y2 == y3) {
			b1x = x1;
			if (x2 < b1x) b1x = x2;
			if (x3 < b1x) b1x = x3;
			b2x = x1;
			if (x2 > b2x) b2x = x2;
			if (x3 > b2x) b2x = x3;
			lscancode  = y1;
			linestart  = b1x;
			linefinish = b2x;
			linefill ();
			return;
		}

	/* This section finds T0, B1 and B2 as explained. */

		if (y1 <= y2 && y1 <= y3) {
			t0x = x1;
			t0y = y1;
			if (y2 <= y3) {
				b1x = x2;
				b1y = y2;
				b2x = x3;
				b2y = y3;
			}
			else {
				b1x = x3;
				b1y = y3;
				b2x = x2;
				b2y = y2;
			}
			goto nowfill;
		}

		if (y2 <= y1 && y2 <= y3) {
			t0x = x2;
			t0y = y2;
			if (y1 <= y3) {
				b1x = x1;
				b1y = y1;
				b2x = x3;
				b2y = y3;
			}
			else {
				b1x = x3;
				b1y = y3;
				b2x = x1;
				b2y = y1;
			}
			goto nowfill;
		}

		if (y3 <= y1 && y3 <= y2) {
			t0x = x3;
			t0y = y3;
			if (y1 <= y2) {
				b1x = x1;
				b1y = y1;
				b2x = x2;
				b2y = y2;
			}
			else {
				b1x = x2;
				b1y = y2;
				b2x = x1;
				b2y = y1;
			}
		}

	/* Finally the triangle is filled. */

	/* Optimization note:

		linestart/linefinish (integer-startX/integer-endX) are
		converted with a simple fist (doubleing point integer store)
		and stored as integer doublewords. This won't check for
		overflows, but will work much faster than the C++ function
		@FTOL, which by the way would mean a FAR CALL occurrence. */

       nowfill:	sx         = t0x;
		ex         = t0x;
		lscancode  = t0y;

		t0b2_drift = (double)(b2x - t0x) / (double)(b2y - t0y);
		b1b2_drift = (double)(b2x - b1x) / (double)(b2y - b1y);

		if (t0y == b1y) {
			sx = b1x;
			// clip top
			if (t0y < lbyl) {
				lscancode = lbyl;
				out = lbyl - t0y;
				sx += b1b2_drift * out;
				ex += t0b2_drift * out;
			}
			// clip bottom
			if (b2y >= ubyl) b2y = ubyl - 1;
		}
		else {
			t0b1_drift = (double)(b1x - t0x) / (double)(b1y - t0y);
			// clip top
			if (t0y < lbyl) {
				lscancode = lbyl;
				if (b1y < lbyl) {
					sx  = b1x + b1b2_drift * (lbyl - b1y);
					ex += t0b2_drift * (lbyl - t0y);
				}
				else {
					out = lbyl - t0y;
					sx += t0b1_drift * out;
					ex += t0b2_drift * out;
				}
			}
			// clip bottom
			if (b1y >= ubyl) b1y = ubyl - 1;
			if (b2y >= ubyl) b2y = ubyl - 1;
			// trace from t0 to b1
			asm fld   sx;
			asm fistp linestart;
			asm fld   ex;
			asm fistp linefinish;
			while (lscancode < b1y) {
				linefill ();
				asm {	fld 	t0b1_drift
					fadd	sx
					fist	linestart
					fstp	sx
					fld	t0b2_drift
					fadd	ex
					fist	linefinish
					fstp	ex }
				lscancode++;
			}
		}

		// trace from b1 to b2
		asm fld   sx;
		asm fistp linestart;
		asm fld   ex;
		asm fistp linefinish;
		while (lscancode <= b2y) {
			linefill ();
			asm {	fld 	b1b2_drift
				fadd	sx
				fist	linestart
				fstp	sx
				fld	t0b2_drift
				fadd	ex
				fist	linefinish
				fstp	ex }
			lscancode++;
		}

}

void triangle (double x1, double y1, double z1,
	       double x2, double y2, double z2,
	       double x3, double y3, double z3)
{

	/* This is the most important function: it must be called from
	   the main program, each time there's the need to trace a 3D
	   triangle. The function is to be called "as is", except when
	   the triangle has some special effects on (see below for this).
	   This is also the fastest function of the engine's core:
	   it uses a special case-sensitive z-clipping which is
	   pratically performed in no time, and it really avoids
	   all unneeded maths whatsoever. All the work which can't
	   be avoided has been highly optimized.
	   Pitagora's force is mainly given by the absence of
	   redundant code whenever possible (no loops in calculations). */

	double xx, yy, zz, aux;	/* Auxiliary variables. 		*/
	double aux1, aux2, aux3; /* Differential conversion factors.	*/

	double rx1, ry1, rz1;	/* Adjusted coordinates for vertex #1. 	*/
	double rx2, ry2, rz2;    /* Adjusted coordinates for vertex #2. 	*/
	double rx3, ry3, rz3;    /* Adjusted coordinates for vertex #3. 	*/
	double x_a, y_a;		/* Anchor vertex coords (Z-clipping).	*/
	char  vf1, vf2, vf3;	/* Visibility flag for each vertex. 	*/
	char  vvcount;		/* Visible-vertexs counter.		*/

	/* Optimization notes:

	      >	z_a is in reality useless, because it'd be always assigned
		to the "dpp" value, which means that the perspective
		conversion factor given by dpp / z_a would always
		be 1, so it's been cutted from the z-clipping.
	      > the scan conversion of a fully visible polygon has been
		optimized for faster removal of polygons laying out of
		the physical screen plane. also, it's been translated
		to assembly so that we can let the FPU translate
		doubleing point values to integers with a FIST.
	      > z-clipped polygons are not optimized that way, just
		because they're nearly always a small chunk of polygons. */

	long  sx1a, sy1a;	/* Screen coords: 1st tri, 1st vertex.	*/
	long  sx2a, sy2a;       /* Screen coords: 1st tri, 2nd vertex.	*/
	long  sx3a, sy3a;       /* Screen coords: 1st tri, 3rd vertex.	*/
	long  sx1b, sy1b;       /* Screen coords: 2nd tri, 1st vertex.	*/
	long  sx2b, sy2b;       /* Screen coords: 2nd tri, 2nd vertex.	*/
	long  sx3b, sy3b;       /* Screen coords: 2nd tri, 3rd vertex.	*/

	/* Adjusting coordinates to viewpoint given by cam_x;cam_y;cam_z
	   at angles given by alpha;beta;gamma - inizializing rx#/ry#/rz#
	   and setting vf# to mean "corresponding vertex is visible". */

		asm {	mov 	vf1, 0
			mov 	vf2, 0
			mov 	vf3, 0
			mov	vvcount, 0 }

      _1_start: asm {	fld 	z1
			fsub 	cam_z
			fst 	zz
			fmul 	opt_tsinbeta
			fld 	x1
			fsub 	cam_x
			fst 	xx
			fmul 	opt_tcosbeta
			faddp
			fstp 	rx1
			fld 	zz
			fmul 	opt_tcosbeta
			fld 	xx
			fmul 	opt_tsinbeta
			fsubp
			fst 	aux
			fmul 	opt_tcosalpha
			fld 	y1
			fsub 	cam_y
			fst 	yy
			fmul 	opt_tsinalpha
			faddp
			fst 	rz1
			fcomp 	dpp
			fstsw 	ax
			fld 	yy
			fmul 	opt_tcosalpha
			fld 	aux
			fmul 	opt_tsinalpha
			fsubp
			fst 	aux
			fmul 	opt_tcosgamma
			fld 	rx1
			fmul 	opt_tsingamma
			fsubp
			fstp 	ry1
			fld 	aux
			fmul 	opt_tsingamma
			fld 	rx1
			fmul 	opt_tcosgamma
			faddp
			fstp 	rx1
			sahf
			jbe 	_1_end_
			or 	vf1, 1
			inc	vvcount }
       _1_end_: asm {	fld 	z2
			fsub 	cam_z
			fst 	zz
			fmul 	opt_tsinbeta
			fld 	x2
			fsub 	cam_x
			fst 	xx
			fmul 	opt_tcosbeta
			faddp
			fstp 	rx2
			fld 	zz
			fmul 	opt_tcosbeta
			fld 	xx
			fmul 	opt_tsinbeta
			fsubp
			fst 	aux
			fmul 	opt_tcosalpha
			fld 	y2
			fsub 	cam_y
			fst 	yy
			fmul 	opt_tsinalpha
			faddp
			fst 	rz2
			fcomp 	dpp
			fstsw 	ax
			fld 	yy
			fmul 	opt_tcosalpha
			fld 	aux
			fmul 	opt_tsinalpha
			fsubp
			fst 	aux
			fmul 	opt_tcosgamma
			fld 	rx2
			fmul 	opt_tsingamma
			fsubp
			fstp 	ry2
			fld 	aux
			fmul 	opt_tsingamma
			fld 	rx2
			fmul 	opt_tcosgamma
			faddp
			fstp 	rx2
			sahf
			jbe 	_2_end_
			or 	vf2, 1
			inc	vvcount }
       _2_end_: asm {	fld 	z3
			fsub 	cam_z
			fst 	zz
			fmul 	opt_tsinbeta
			fld 	x3
			fsub 	cam_x
			fst 	xx
			fmul 	opt_tcosbeta
			faddp
			fstp 	rx3
			fld 	zz
			fmul 	opt_tcosbeta
			fld 	xx
			fmul 	opt_tsinbeta
			fsubp
			fst 	aux
			fmul 	opt_tcosalpha
			fld 	y3
			fsub 	cam_y
			fst 	yy
			fmul 	opt_tsinalpha
			faddp
			fst 	rz3
			fcomp 	dpp
			fstsw 	ax
			fld 	yy
			fmul 	opt_tcosalpha
			fld 	aux
			fmul 	opt_tsinalpha
			fsubp
			fst 	aux
			fmul 	opt_tcosgamma
			fld 	rx3
			fmul 	opt_tsingamma
			fsubp
			fstp 	ry3
			fld 	aux
			fmul 	opt_tsingamma
			fld 	rx3
			fmul 	opt_tcosgamma
			faddp
			fstp 	rx3
			sahf
			jbe 	_3_end_
			or 	vf3, 1
			inc	vvcount }

	/* Checking visibility (quit if no vertexs are visible). */

       _3_end_:	if (!vvcount) return;

	/* Checking visibility (skip Z-clipping if all vertexs visible). */

		if (vvcount == 3) goto noZclipping;

	/* Performing case-sensitive Z-clipping, by calculating
	   an additional (fourth) vertex here called "anchor vertex". */

		if (vvcount == 1) {
			/* First case: only one vertex is visible.
			   The resulting shape is a triangle, and
			   there's no need for the anchor vertex. */
			if (vf1) {
				aux = (dpp - rz1)/(rz2 - rz1);
				rx2 = aux * (rx2 - rx1) + rx1;
				ry2 = aux * (ry2 - ry1) + ry1;
				rz2 = dpp;
				aux = (dpp - rz1)/(rz3 - rz1);
				rx3 = aux * (rx3 - rx1) + rx1;
				ry3 = aux * (ry3 - ry1) + ry1;
				rz3 = dpp;
				goto noZclipping;
			}
			if (vf2) {
				aux = (dpp - rz2)/(rz1 - rz2);
				rx1 = aux * (rx1 - rx2) + rx2;
				ry1 = aux * (ry1 - ry2) + ry2;
				rz1 = dpp;
				aux = (dpp - rz2)/(rz3 - rz2);
				rx3 = aux * (rx3 - rx2) + rx2;
				ry3 = aux * (ry3 - ry2) + ry2;
				rz3 = dpp;
				goto noZclipping;
			}
			if (vf3) {
				aux = (dpp - rz3)/(rz1 - rz3);
				rx1 = aux * (rx1 - rx3) + rx3;
				ry1 = aux * (ry1 - ry3) + ry3;
				rz1 = dpp;
				aux = (dpp - rz3)/(rz2 - rz3);
				rx2 = aux * (rx2 - rx3) + rx3;
				ry2 = aux * (ry2 - ry3) + ry3;
				rz2 = dpp;
				goto noZclipping;
			}
		}
		else {
			/* Second case: two vertexs are visible.
			   The resulting shape is a tetragon, and
			   there's the need for the anchor vertex. */
			if (!vf1) {
				aux = (dpp - rz3)/(rz1 - rz3);
				x_a = aux * (rx1 - rx3) + rx3;
				y_a = aux * (ry1 - ry3) + ry3;
				aux = (dpp - rz2)/(rz1 - rz2);
				rx1 = aux * (rx1 - rx2) + rx2;
				ry1 = aux * (ry1 - ry2) + ry2;
				rz1 = dpp;
				// Scan convert first triangle: 2..3..A
				aux  = dpp / rz2;
				sx1a = (rx2 * aux) + center_x;
				sy1a = (ry2 * aux) + center_y;
				aux  = dpp / rz3;
				sx2a = (rx3 * aux) + center_x;
				sy2a = (ry3 * aux) + center_y;
				sx3a = x_a + center_x;
				sy3a = y_a + center_y;
				// Scan convert second triangle: 1..2..A
				sx1b = rx1 + center_x;
				sy1b = ry1 + center_y;
				sx2b = sx1a;
				sy2b = sy1a;
				sx3b = sx3a;
				sy3b = sy3a;
				goto endZclipping;
			}
			if (!vf2) {
				aux = (dpp - rz1)/(rz2 - rz1);
				x_a = aux * (rx2 - rx1) + rx1;
				y_a = aux * (ry2 - ry1) + ry1;
				aux = (dpp - rz3)/(rz2 - rz3);
				rx2 = aux * (rx2 - rx3) + rx3;
				ry2 = aux * (ry2 - ry3) + ry3;
				rz2 = dpp;
				// Scan convert first triangle: 2..3..A
				sx1a = rx2 + center_x;
				sy1a = ry2 + center_y;
				aux  = dpp / rz3;
				sx2a = (rx3 * aux) + center_x;
				sy2a = (ry3 * aux) + center_y;
				sx3a = x_a + center_x;
				sy3a = y_a + center_y;
				// Scan convert second triangle: 1..3..A
				aux  = dpp / rz1;
				sx1b = (rx1 * aux) + center_x;
				sy1b = (ry1 * aux) + center_y;
				sx2b = sx2a;
				sy2b = sy2a;
				sx3b = sx3a;
				sy3b = sy3a;
				goto endZclipping;
			}
			if (!vf3) {
				aux = (dpp - rz1)/(rz3 - rz1);
				x_a = aux * (rx3 - rx1) + rx1;
				y_a = aux * (ry3 - ry1) + ry1;
				aux = (dpp - rz2)/(rz3 - rz2);
				rx3 = aux * (rx3 - rx2) + rx2;
				ry3 = aux * (ry3 - ry2) + ry2;
				rz3 = dpp;
				// Scan convert first triangle: 1..2..A
				aux  = dpp / rz1;
				sx1a = (rx1 * aux) + center_x;
				sy1a = (ry1 * aux) + center_y;
				aux  = dpp / rz2;
				sx2a = (rx2 * aux) + center_x;
				sy2a = (ry2 * aux) + center_y;
				sx3a = x_a + center_x;
				sy3a = y_a + center_y;
				// Scan convert second triangle: 2..3..A
				sx1b = sx2a;
				sy1b = sy2a;
				sx2b = rx3 + center_x;
				sy2b = ry3 + center_y;
				sx3b = sx3a;
				sy3b = sy3a;
			}
		}

	/* Tracing the tetragon resulting from the second case of the
	   Z-clipping section, which is splitted in two triangles. */

  endZclipping:	if (sx1a > ubxl && sx2a > ubxl && sx3a > ubxl) goto try2ndtriangle;
		if (sx1a <= lbxl && sx2a <= lbxl && sx3a <= lbxl) goto try2ndtriangle;
		if (sy1a > ubyl && sy2a > ubyl && sy3a > ubyl) goto try2ndtriangle;
		if (sy1a <= lbyl && sy2a <= lbyl && sy3a <= lbyl) goto try2ndtriangle;

		trifill (sx1a, sy1a, sx2a, sy2a, sx3a, sy3a);

 try2ndtriangle:if (sx1b > ubxl && sx2b > ubxl && sx3b > ubxl) return;
		if (sx1b <= lbxl && sx2b <= lbxl && sx3b <= lbxl) return;
		if (sy1b > ubyl && sy2b > ubyl && sy3b > ubyl) return;
		if (sy1b <= lbyl && sy2b <= lbyl && sy3b <= lbyl) return;

		trifill (sx1b, sy1b, sx2b, sy2b, sx3b, sy3b);

		return;

	/* Tracing a normal triangle, either when it was fully visible
	   or if it was corrected by the first case of the Z-clipping. */

   noZclipping:	/* Unoptimized C++ version */

	     /*	aux1 = dpp / rz1;
		sx1a = rx1 * aux1;
		aux2 = dpp / rz2;
		sx2a = rx2 * aux2;
		aux3 = dpp / rz3;
		sx3a = rx3 * aux3; */

		/* Assembly version, using fistp instead of @FTOL,
		   and avoiding redundand loads of auxiliary variables. */

		asm {	fld	dpp
			fdiv	rz1
			fst	aux1
			fld	dpp
			fdiv	rz2
			fst	aux2
			fld	dpp
			fdiv	rz3
			fst	aux3
			fmul	rx3
			fistp	sx3a
			fmul	rx2
			fistp	sx2a
			fmul	rx1
			fistp	sx1a }

		if (sx1a > ubxa && sx2a > ubxa && sx3a > ubxa) return;
		if (sx1a <= lbxa && sx2a <= lbxa && sx3a <= lbxa) return;

		/* Unoptimized C++ version */

	     /*	sy1a = ry1 * aux1;
		sy2a = ry2 * aux2;
		sy3a = ry3 * aux3; */

		/* Assembly version, using fistp instead of @FTOL. */

		asm {	fld	ry1
			fmul	aux1
			fistp	sy1a
			fld	ry2
			fmul	aux2
			fistp	sy2a
			fld	ry3
			fmul	aux3
			fistp	sy3a }

		if (sy1a > ubya && sy2a > ubya && sy3a > ubya) return;
		if (sy1a <= lbya && sy2a <= lbya && sy3a <= lbya) return;

		trifill (sx1a + icenter_x, sy1a + icenter_y,
			 sx2a + icenter_x, sy2a + icenter_y,
			 sx3a + icenter_x, sy3a + icenter_y);

	// Ok, done.
}

void seteffect (WORD onscreeneffect)
{
	/* Sets the engine to use the given combination of effects,
	   specified by the input WORD (filler code) as explained
	   just before the filling routines. */

	asm	and	onscreeneffect, forbiddenbitsmask
	asm	and	mapeffect, 4
	asm	mov	ax, onscreeneffect
	asm	or	mapeffect, ax
}

void setcolor (double red, double green, double blue)
{
	/* A very important function.
	   Sets the color of an uniformly-filled polygon.
	   But that color is ALSO used by the following effects:

	   PLAIN ------- "setcolor" sets the color of all the pixels
			 forming the polygon (ok, that's clear);
	   GRADIENT ---- "setcolor" sets the gradient that will be merged
			 with the colors in the texture: obviously, if you
			 don't specify a texture, the engine will switch
			 back to plain surface filling;
	   TRANSPARENT - "setcolor" sets which color must be considered
			 transparent (pixels won't be drawn in that case,
			 and given color will be some sort of chroma-key);
	   SHADE ------- "setcolor" sets the color of the light source. */

	/* The parameters represent the three components of the light
	   coming out from a given pixel. Both RED, GREEN and BLUE
	   are specified with doubleing point values ranging from zero
	   to one. Values outside this range are normalized to fit it. */

	/* Note: you may also use this function to build your own textures,
	   by calling "setcolor" to obtain the hardware version of the
	   specified color, in order to fill one or more pixels with it.
	   You just write: "setcolor (r, g, b); texture[ptr] = patword;"...
	   However, it's not recommended to do that in real time, because
	   this function's not that fast. In general, you should never
	   rebuild textures WHILE in your rendering loop. Always build
	   all of them BEFORE entering the main loop in your program. */

	int temp;

	const double redrange = 31;
	const double grnrange = 63;
	const double blurange = 31;

	if (red   < 0) red   = 0;
	if (green < 0) green = 0;
	if (blue  < 0) blue  = 0;

	if (red   > 1) red   = 1;
	if (green > 1) green = 1;
	if (blue  > 1) blue  = 1;

	asm {	fld	red
        	fmul	redrange
		fistp	temp
		mov	ax, temp
		shl	ax, 11
		fld	green
		fmul	grnrange
		fistp	temp
		mov	bx, temp
		shl	bx, 5
		fld	blue
		fmul	blurange
		fistp	temp
		mov	cx, temp
		or	cx, ax
		or	cx, bx
		mov	patword, cx }
}

void attachtexture (double reference_x1, double reference_y1, double reference_z1,
		    double reference_x2, double reference_y2, double reference_z2,
		    double reference_x3, double reference_y3, double reference_z3,
		    unsigned int huge *texturemappointer)
{
	/* Helps "triangle" in tracing a texture-mapped polygon.
	   It has to be called before "triangle" whenever a texture is needed.

	   Reference vectors are the ones merged with a cross product
	   to form the basis for the texture-mapping algorithm. They
	   are usually loaded with three coordinates representing the
	   3D-triangle: those coordinates will fix the texturing plane.
	   I must say they are separated from the real polygon coordinates
	   because by doing so we're able to texture-map more than a triangle
	   without repeating the calculations. For example, say you need a
	   tetragon (a four-sided polygon): all you have to do is splitting
	   the polygon in two triangles, attach the texture to one of them,
	   and trace the other one without calling this function again.
	   Also, even tracing only one textured triangle, keeping separate
	   vectors allows easy anti-aliasing and texture positioning.

	   For standard texture mapping, call this functions with
	   the parameter "onscreeneffect" assigned to "TEXTURE_FILL". */

	double xx, yy, zz, aux;	/* Auxiliary variables. 		*/
	double midx, midy, midz; /* Polygon's midpoint coordinates. 	*/

	double rx1, ry1, rz1;	/* Adjusted coordinates for vertex #1. 	*/
	double rx2, ry2, rz2;    /* Adjusted coordinates for vertex #2. 	*/
	double rx3, ry3, rz3;    /* Adjusted coordinates for vertex #3. 	*/

	double tx1, ty1, tz1;   /* Reference vectors (texture mapping).	*/
	double tx2, ty2, tz2;   /* Reference vectors (texture mapping).	*/
	double tx3, ty3, tz3;   /* Reference vectors (texture mapping).	*/

	double mx, my, mz;	/* First reference vector for texture.	*/
	double nx, ny, nz;	/* Second reference vector for texture.	*/

	/* Adjusting coordinates to viewpoint given by cam_x;cam_y;cam_z
	   at angles given by alpha;beta;gamma - inizializing rx#/ry#/rz#. */

		asm {	fld 	reference_z1
			fsub 	cam_z
			fst 	zz
			fmul 	opt_tsinbeta
			fld 	reference_x1
			fsub 	cam_x
			fst 	xx
			fmul 	opt_tcosbeta
			faddp
			fstp 	rx1
			fld 	zz
			fmul 	opt_tcosbeta
			fld 	xx
			fmul 	opt_tsinbeta
			fsubp
			fst 	aux
			fmul 	opt_tcosalpha
			fld 	reference_y1
			fsub 	cam_y
			fst 	yy
			fmul 	opt_tsinalpha
			faddp
			fstp 	rz1
			fld 	yy
			fmul 	opt_tcosalpha
			fld 	aux
			fmul 	opt_tsinalpha
			fsubp
			fst 	aux
			fmul 	opt_tcosgamma
			fld 	rx1
			fmul 	opt_tsingamma
			fsubp
			fstp 	ry1
			fld 	aux
			fmul 	opt_tsingamma
			fld 	rx1
			fmul 	opt_tcosgamma
			faddp
			fstp 	rx1
			fld 	reference_z2
			fsub 	cam_z
			fst 	zz
			fmul 	opt_tsinbeta
			fld 	reference_x2
			fsub 	cam_x
			fst 	xx
			fmul 	opt_tcosbeta
			faddp
			fstp 	rx2
			fld 	zz
			fmul 	opt_tcosbeta
			fld 	xx
			fmul 	opt_tsinbeta
			fsubp
			fst 	aux
			fmul 	opt_tcosalpha
			fld 	reference_y2
			fsub 	cam_y
			fst 	yy
			fmul 	opt_tsinalpha
			faddp
			fstp 	rz2
			fld 	yy
			fmul 	opt_tcosalpha
			fld 	aux
			fmul 	opt_tsinalpha
			fsubp
			fst 	aux
			fmul 	opt_tcosgamma
			fld 	rx2
			fmul 	opt_tsingamma
			fsubp
			fstp 	ry2
			fld 	aux
			fmul 	opt_tsingamma
			fld 	rx2
			fmul 	opt_tcosgamma
			faddp
			fstp 	rx2
			fld 	reference_z3
			fsub 	cam_z
			fst 	zz
			fmul 	opt_tsinbeta
			fld 	reference_x3
			fsub 	cam_x
			fst 	xx
			fmul 	opt_tcosbeta
			faddp
			fstp 	rx3
			fld 	zz
			fmul 	opt_tcosbeta
			fld 	xx
			fmul 	opt_tsinbeta
			fsubp
			fst 	aux
			fmul 	opt_tcosalpha
			fld 	reference_y3
			fsub 	cam_y
			fst 	yy
			fmul 	opt_tsinalpha
			faddp
			fstp 	rz3
			fld 	yy
			fmul 	opt_tcosalpha
			fld 	aux
			fmul 	opt_tsinalpha
			fsubp
			fst 	aux
			fmul 	opt_tcosgamma
			fld 	rx3
			fmul 	opt_tsingamma
			fsubp
			fstp 	ry3
			fld 	aux
			fmul 	opt_tsingamma
			fld 	rx3
			fmul 	opt_tcosgamma
			faddp
			fstp 	rx3 }

	/* Calculating vectors to texture map. */

		midx = (rx1 + rx2 + rx3) * 0.33333333333;
		midy = (ry1 + ry2 + ry3) * 0.33333333333;
		midz = (rz1 + rz2 + rz3) * 0.33333333333;
		tx1  = (rx1 - midx) * x_antialias + midx;
		ty1  = (ry1 - midy) * y_antialias + midy;
		tz1  = (rz1 - midz) * z_antialias + midz;
		tx2  = (rx2 - midx) * x_antialias + midx;
		ty2  = (ry2 - midy) * y_antialias + midy;
		tz2  = (rz2 - midz) * z_antialias + midz;
		tx3  = (rx3 - midx) * x_antialias + midx;
		ty3  = (ry3 - midy) * y_antialias + midy;
		tz3  = (rz3 - midz) * z_antialias + midz;
		mx   = tx3 - tx1;
		my   = ty3 - ty1;
		mz   = tz3 - tz1;
		nx   = tx1 - tx2;
		ny   = ty1 - ty2;
		nz   = tz1 - tz2;
		hx   = (tz1 * my - ty1 * mz) * XCOEFF;
		hy   = (tz1 * ny - ty1 * nz) * XCOEFF;
		hz   =  (nz * my - ny * mz) * inv_dpp;
		vx   = (tx1 * mz - tz1 * mx) * YCOEFF;
		vy   = (tx1 * nz - tz1 * nx) * YCOEFF;
		vz   =  (nx * mz - nz * mx) * inv_dpp;
		ox   = (ty1 * mx - tx1 * my) * EMU_K;
		oy   = (ty1 * nx - tx1 * ny) * EMU_K;
		oz   =  (ny * mx - nx * my);

	/* Setting rest of the global parameters. */

		asm	and	mapeffect, forbiddenbitsmask

		if (hz >= 0) {	// Forward filling.

			fx   = hx * spanlength;
			fy   = hy * spanlength;
			fz   = hz * spanlength;

			txm  = texturemappointer;

		}
		else {	// Backward filling.

			hx   = -hx;
			hy   = -hy;
			hz   = -hz;

			fx   = hx * spanlength;
			fy   = hy * spanlength;
			fz   = hz * spanlength;

			txm        = texturemappointer;
			mapeffect += BACKWARD;

		}
}

/// Utilities of common interest. ////////////////////////////////////////////

char facing (double x1, double y1, double z1,
	     double x2, double y2, double z2,
	     double x3, double y3, double z3)
{

	/* This should be of vital importance in basic hidden surfaces
	   removal. Assuming vertexs are always given in clockwise order,
	   relatively to the visible side of the polygon to be traced,
	   the function returns 1 if the triangle whose vertexs
	   are (x1;y1;z1),(x2;y2;z2),(x3;y3;z3) is currently
	   facing the viewpoint (cam_x;cam_y;cam_z).
	   Otherwise, the function returns 0.

	   Hidden surfaces removal could then be easily accomplished like so:

	   if (facing (x1, y1, z1, x2, y2, z2, x3, y3, z3))
		triangle (x1, y1, z1, x2, y2, z2, x3, y2, z3, color);
	   else
		// er, do nothing...

	   thus, being a piece of cake. */

	double _x1, _y1, _z1, _x2, _y2, _z2, xr, yr, zr;

		asm {	fld   	x2
			fsub  	x3
			fstp  	_x1
			fld   	y2
			fsub  	y3
			fstp  	_y1
			fld   	z2
			fsub  	z3
			fstp  	_z1
			fld   	x1
			fsub  	x3
			fstp  	_x2
			fld   	y1
			fsub  	y3
			fstp  	_y2
			fld   	z1
			fsub  	z3
			fst   	_z2
			fmul  	_y1
			fld   	_y2
			fmul  	_z1
			fsubp
			fstp  	xr
			fld   	_z1
			fmul  	_x2
			fld   	_z2
			fmul  	_x1
			fsubp
			fstp  	yr
			fld   	_x1
			fmul  	_y2
			fld   	_x2
			fmul  	_y1
			fsubp
			fstp  	zr
			fld   	cam_x
			fsub  	x3
			fmul  	xr
			fld   	cam_y
			fsub  	y3
			fmul  	yr
			faddp
			fld   	cam_z
			fsub  	z3
			fmul  	zr
			faddp
			ftst
			ffree 	st(0)
			fstsw 	ax
			xor 	dl, dl
			sahf
			jb 	_zero
			not 	dl }

	 _zero:	return (_DL);

}

double pnx, pny, pnz, pnm;    /* Values returned by the function below:
				they describe the normal vector to the
				surface of a triangle. */

void pnorm (double x1, double y1, double z1,
	    double x2, double y2, double z2,
	    double x3, double y3, double z3)
{
	/* Calculates the normal vector of a 3D triangle,
	   providing its vertexs are given in clockwise order
	   (following the so-called "rule of the right hand").
	   It's not been optimized that much, but should be useful
	   as an example for any simplified shading procedure:
	   say for example plain shading, Gouraud, or Phong
	   (interpolation of normals, that's much harder).

	   Since the vector is normalized (-1 <= pnx, pny, pnz <= 1),
	   you may need the modulus (or "lenght") of the said vector
	   separately: this is returned in "pnm".
	   The vector calculated by this function may be useful
	   for many other purposes. */

	double _x1, _y1, _z1;
	double _x2, _y2, _z2;
	double  xr,  yr,  zr;

	double ln;

	_x1 = x2 - x3;
	_y1 = y2 - y3;
	_z1 = z2 - z3;
	_x2 = x1 - x3;
	_y2 = y1 - y3;
	_z2 = z1 - z3;

	xr = _y1 * _z2 - _y2 * _z1;
	yr = _z1 * _x2 - _z2 * _x1;
	zr = _x1 * _y2 - _x2 * _y1;

	pnm = sqrt (xr * xr + yr * yr + zr * zr);
	if (pnm > 0) {
		ln  = 1 / pnm;
		pnx = xr * ln;
		pny = yr * ln;
		pnz = zr * ln;
	}
	else {
		pnx = 0;
		pny = 0;
		pnz = 0;
	}
}

/// End of source. ///////////////////////////////////////////////////////////

#endif
