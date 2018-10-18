extern int QUADWORDS;
extern unsigned char far *adaptor;
extern unsigned char far *adapted;
extern void reach_your_dir (void);
extern void _320_200_256 (void);
extern void _80_25_C (void);
extern int attendi_pressione_tasto (void);
extern int tasto_premuto (void);
extern unsigned char range8088[64*3];
extern unsigned char tmppal[768];
extern char return_palette[768];
extern char surface_palette[768];
extern void tavola_colori (unsigned char *nuova_tavolozza,
		    unsigned colore_di_partenza, unsigned nr_colori,
		    char filtro_rosso, char filtro_verde, char filtro_blu);
extern int mdltx, mdlty, mx, my, mpul;
extern void mouse_input (void);
extern char test_and_init_mouse (void);
extern void pcopy (unsigned char far *dest, unsigned char far *sorg);
extern void pclear (unsigned char far *target, unsigned char pattern);
extern void areacopy (unsigned char far *dest, unsigned char far *sorg,
		      int x, int y, int l, int h);
extern void areaclear (unsigned char far *dest, int x, int y,
		       int x2, int y2, int l, int h, unsigned char pattern);
extern void psmooth_grays (unsigned char far *target);
extern void pfade (unsigned char far *target, unsigned segshift, unsigned char speed);
extern void psmooth_64 (unsigned char far *target, unsigned segshift);
extern void smootharound_64 (unsigned char far *target, long cx, long cy, long r, char diffuse);
extern void mask_pixels (unsigned char far *target, unsigned char mask);

const TEXTURE_XSIZE = 256; // Larghezza delle BMP.
const TEXTURE_YSIZE = 256; // Altezza delle BMP.
extern long XSIZE, YSIZE; // calibrazione BMP.
extern float uneg;
extern float alfa, beta, gamma;
extern float cam_x, cam_y, cam_z;
extern float dpp;
extern long H_MATRIXS, V_MATRIXS;
extern unsigned riga[200];
extern void initscanlines (void);
extern unsigned ptr;
extern unsigned long xp, yp, xa, ya;
extern unsigned long global_x, global_y;
extern void Segmento (void);
extern char flares;
extern float x2, y2, z2;
extern float xx, yy, zz;
extern long lbxl;
extern long ubxl;
extern long lbyl;
extern long ubyl;
extern float lbxf;
extern float ubxf;
extern float lbyf;
extern float ubyf;
extern float x_centro_f;
extern float y_centro_f;
extern float opt_pcosbeta;
extern float opt_psinbeta;
extern float opt_tcosbeta;
extern float opt_tsinbeta;
extern float opt_pcosalfa;
extern float opt_psinalfa;
extern float opt_tcosalfa;
extern float opt_tsinalfa;
extern void change_angle_of_view (void);
extern void change_camera_lens (void);
extern void change_txm_repeating_mode (void);
extern unsigned char entity;
extern void poly3d (float *x, float *y, float *z,
	     unsigned nrv, unsigned char colore);
extern void Forward (float delta);
extern float pnx, pny, pnz;
extern void pnorm (float *x, float *y, float *z);
extern unsigned char huge *txtr;
extern unsigned int  huge *wtxtr;
extern float x_antialias, y_antialias, z_antialias;
extern char culling_needed, halfscan_needed;
extern unsigned char escrescenze;
extern void polymap (float *x, float *y, float *z, char nv, unsigned char tinta);
extern long _x_, _y_;
extern char getcoords (float x, float y, float z);
extern char facing (float *x, float *y, float *z);

extern char   *situation_file;
extern char   *starmap_file;
extern char   *goesoutputfile;
extern char   *surface_file;
extern int    sfh;

extern char   sync;
extern char   anti_rad;
extern char   pl_search;
extern char   field_amplificator;
extern char   ilight;
extern char   ilightv;
extern char   charge;
extern char   revcontrols;
extern char   ap_targetting;
extern char   ap_targetted;
extern char   ip_targetting;
extern char   ip_targetted;
extern char   ip_reaching;
extern char   ip_reached;
extern char   ap_target_spin;
extern char   ap_target_r;
extern char   ap_target_g;
extern char   ap_target_b;
extern char   nearstar_spin;
extern char   nearstar_r;
extern char   nearstar_g;
extern char   nearstar_b;
extern char   gburst;
extern char   menusalwayson;
extern char   depolarize;
extern int    sys;
extern int    pwr;
extern int    dev_page;
extern int    ap_target_class;
extern int    f_ray_elapsed;
extern int    nearstar_class;
extern int    nearstar_nop;
extern float  pos_x;
extern float  pos_y;
extern float  pos_z;
extern float  user_alfa;
extern float  user_beta;
extern float  navigation_beta;
extern float  ap_target_ray;
extern float  nearstar_ray;
extern double dzat_x;
extern double dzat_y;
extern double dzat_z;
extern double ap_target_x;
extern double ap_target_y;
extern double ap_target_z;
extern double nearstar_x;
extern double nearstar_y;
extern double nearstar_z;
extern double helptime;
extern double ip_target_initial_d;
extern double requested_approach_coefficient;
extern double current_approach_coefficient;
extern double reaction_time;
extern char   fcs_status[11];
extern int    fcs_status_delay;
extern int    psys;
extern double ap_target_initial_d;
extern double requested_vimana_coefficient;
extern double current_vimana_coefficient;
extern double vimana_reaction_time;
extern char   lithium_collector;
extern char   autoscreenoff;
extern char   ap_reached;
extern int    lifter;
extern double secs;
extern char   data;
extern char   surlight;

extern char   land_now;
extern char   landing_point;
extern int    landing_pt_lon;
extern int    landing_pt_lat;
extern int    rotation;
extern char seconds[3], minutes[3], hours[3], day[3], month[3], year[5];
extern int  epoc;
extern unsigned char cyclon[384];
extern char          ctb[512];
extern char	      _delay;
extern char          stspeed;
extern char          bright;
extern char   	     elight;
extern unsigned      gl_start;
extern unsigned      point;
extern unsigned      vptr;
extern int           infoarea;
extern int           s_control;
extern int           s_command;
extern int           isecs, p_isecs;
extern double	     fsecs;
extern int	     gl_fps;
extern int	     fps;
extern float         dlt_alfa;
extern float	     dlt_beta;
extern float	     dlt_nav_beta;
extern float	     step;
extern float	     shift;
extern double        s_m;
extern double	     plx, ply, plz;
extern double        pxx, pyy;
extern double        delta_x, delta_y;
extern double 	     nearstar_identity;
extern int	     nearstar_nob;
extern int	     nearstar_labeled;
extern int 	     npcs;
extern char   	     ontheroof;
extern int	     datasheetscroll;
extern int	     datasheetdelta;

extern char *ord[21];
extern char *star_description[12];
extern char class_rgb[3*star_classes];
extern int class_ray[star_classes];
extern int class_rayvar[star_classes];
extern int class_act[star_classes];
extern char class_planets[star_classes];
extern char   nearstar_p_type       [maxbodies];
extern int    nearstar_p_owner	    [maxbodies];
extern char   nearstar_p_moonid     [maxbodies];
extern char   nearstar_p_mapped     [maxbodies];
extern double nearstar_p_ring       [maxbodies];
extern double nearstar_p_tilt       [maxbodies];
extern double nearstar_p_ray        [maxbodies];
extern double nearstar_p_orb_ray    [maxbodies];
extern double nearstar_p_orb_tilt   [maxbodies];
extern double nearstar_p_orb_orient [maxbodies];
extern double nearstar_p_orb_ecc    [maxbodies];
extern int    nearstar_p_rtperiod   [maxbodies];
extern int    nearstar_p_rotation   [maxbodies];
extern int    nearstar_p_term_start [maxbodies];
extern int    nearstar_p_term_end   [maxbodies];
extern int    nearstar_p_qsortindex [maxbodies];
extern float  nearstar_p_qsortdist  [maxbodies];
extern char *planet_description[10];
extern unsigned char planet_rgb_and_var[40];
extern int planet_possiblemoons[10];
extern float mindiff;
extern unsigned char far  *p_background;
extern unsigned char far  *s_background;
extern unsigned char huge *p_surfacemap;
extern quadrant      far  *objectschart;
extern unsigned char far  *ruinschart; // come objectschart, ma dichiarato in bytes
extern unsigned char far  *pvfile;
extern unsigned char far  *n_offsets_map;
extern char far           *n_globes_map;
extern unsigned	    seg_adapted;
extern char sky_red_filter;
extern char sky_grn_filter;
extern char sky_blu_filter;
extern char gnd_red_filter;
extern char gnd_grn_filter;
extern char gnd_blu_filter;
extern float planet_grav;
extern float rainy;
extern int albedo;
extern unsigned char sky_brightness;
extern unsigned char horiz_brt;
extern unsigned m200[200];
extern unsigned wtl;
extern float	rwp;
extern float    iwp;
extern float    wp;
extern float    wdir;
extern float    wdirsin;
extern float    wdircos;
extern char landed;
extern long atl_x, atl_z, atl_x2, atl_z2;
extern double qid;
extern int fn;
extern unsigned char far *fnv, *fcolor;
extern float far *fx, *inv_fx, *fy, *fz;
extern int vhn;
extern float far *vhx, *vhy, *vhz;
extern float far *vhxm, *vhym, *vhzm, *vh_mdq;
extern unsigned char far *vhnv, *vhcolor, *vhindex;
extern int in;
extern float far *ix, *iy, *iz;
extern unsigned char far *inv, *icolor;
extern int alpha_n;
extern unsigned char far *alpha_nv;
extern float far *alpha_x, *alpha_y, *alpha_z;
extern long flat_rnd_seed;
extern void fast_srand (long seed);
extern long fast_random (long mask);
extern int ranged_fast_random (int range);
extern int sa_open (long offset_of_virtual_file);
extern void shade (unsigned char far *palette_buffer,
		   int first_color, int number_of_colors,
		   float start_r,  float start_g,  float start_b,
		   float finish_r, float finish_g, float finish_b);
extern char snapfilename[24];
extern void snapshot (int forcenumber, char showdata);
extern char helpfile_hlp[13];
extern char *helpfile_img[13];
extern void readline (int tfh);
extern void from_vehicle (void);
extern void from_user (void);
extern void watch (double cam_x, double cam_y, double cam_z,
	    double see_x, double see_y, double see_z);
extern char xy (double cam_x, double cam_y, double cam_z,
	 double point_x, double point_y, double point_z);
extern void p_Forward (float delta);
extern void copia (unsigned char far *dest, unsigned char far *sorg, unsigned x, unsigned y, int l, int a);
extern void setfx (char fx);
extern void chgfx (char fx);
extern void resetfx (void);
extern void Stick (unsigned long xp, unsigned long yp,
	    unsigned long xa, unsigned long ya);
extern long fpx;
extern long fpy;
extern float p_rx, p_ry, p_rz;
extern float stick_uneg;
extern void stick3d (float p_x, float p_y, float p_z,
	      float x, float y, float z);
extern void link3d (float x, float y, float z);
extern void fline (long fx, long fy,
	    long lx, long ly);
//--------------------------------------------------------------------------//
extern unsigned char map_color_a;
extern unsigned char map_color_b;
extern unsigned char map_color_c;
extern unsigned char map_color_d;
extern void randomic_mapper (float x0,
		      float y0,
		      float z0,
		      float x1,
		      float y1,
		      float z1,
		      float x2,
		      float y2,
		      float z2,
		      char divisions);
extern void unloadpv (int handle);
extern void unloadallpv (void);
extern char loadpv (int   handle, long virtual_file_position,
		    float xscale, float yscale, float zscale,
		    float xmove,  float ymove,  float zmove,
		    unsigned char base_color,   char depth_sort);
extern void QuickSort (int far *index, float far *mdist, int start, int end);
extern void drawpv (int handle, int mode, int rm_iterations,
		    float center_x, float center_y, float center_z,
		    char use_depth_sort);
extern void copypv (int dest_handle, int src_handle);
extern void modpv (int handle, int polygon_id, int vertex_id,
		   float x_scale, float y_scale, float z_scale,
		   float x_angle, float y_angle, float z_angle,
		   pvlist *vertexs_to_affect);
//--------------------------------------------------------------------------//
extern char *alphavalue (double value);
extern void background (unsigned start,
		 unsigned char far *target,
		 unsigned char far *background,
		 unsigned char far *offsetsmap,
		 unsigned total_map_bytes,
		 unsigned screenshift);
extern void sky (unsigned limits);
extern double laststar_x, laststar_y, laststar_z;
extern char isthere (double star_id);
extern char glass_bubble;
extern void globe (unsigned start,
	    unsigned char far *target,
	    unsigned char far *tapestry,
	    unsigned char far *offsetsmap,
	    unsigned total_map_bytes,
	    double x, double y, double z,
	    float mag_factor, char colormask,
	    char globe_saturation);
extern void glowinglobe (int start,
	    unsigned char far *target,
	    unsigned char far *offsetsmap,
	    unsigned total_map_bytes,
	    double x, double y, double z, float mag_factor,
	    int terminator_start, int terminator_end, unsigned char color);
extern void whiteglobe (unsigned char far *target,
	    double x, double y, double z,
	    float mag_factor, float fgm_factor);
extern double xsun_onscreen;
extern void whitesun (unsigned char far *target,
	    double x, double y, double z,
	    float mag_factor, float fgm_factor);
extern float far lft_sin[361];
extern float far lft_cos[361];
extern char lens_flares_init (void);
extern void lens_flares_for (double cam_x, double cam_y, double cam_z,
		      double xlight, double ylight, double zlight,
		      double step, int added, char on_hud, char condition,
		      int xshift, int yshift);
extern void single_pixel_at_ptr (unsigned ptr, unsigned char pixel_color);
extern char far_pixel_at (double xlight, double ylight, double zlight, double radii, unsigned char unconditioned_color);
extern unsigned long far *digimap2;
extern void cupola (float y_or, float brk);
extern void polycupola (float y_or, char textured);
//extern void alogena (void);
//extern void qsel (float *x, float *y, float *z, unsigned n, unsigned char c);
//extern void reflexes (void);
//extern void squaredot (float x, float y, float size, unsigned char color);
//extern void digit_at (char digit, float x, float y, float size, unsigned char color);
//extern void screen (void);
//extern void frame (float x, float y, float l, float h, float borderwidth, unsigned char color);
//extern void pointer_cross_for (double xlight, double ylight, double zlight);
//extern void cline (int line, char *text);
//extern void other (char *text);
//extern void control (int line, char *text);
//extern void command (int nr, char *text);
//extern void clear_onboard_screen (void);
//--------------------------------------------------------------------------//
//extern unsigned char reset_signal;
//extern char active_screen;
//extern void build_osscreen (void);
//extern void mslocate (int screen_id, int cursor_x, int cursor_y);
//extern void mswrite (int screen_id, char* text);
//--------------------------------------------------------------------------//
//extern void show_planetary_map ();
//extern int goesk_a;
//extern int goesk_e;
//extern void vehicle (float opencapcount);
//extern void other_vehicle_at (double ovhx, double ovhy, double ovhz);
extern void getsecs (void);
extern void extract_ap_target_infos (void);
extern float zrandom (int range);
extern int starnop (double star_x, double star_y, double star_z);
extern void prepare_nearstar (void);
extern void ssmooth (unsigned char far *target);
extern void lssmooth (unsigned char far *target);
extern int      c, gr, r, g, b, cr, cx, cy;
extern char     lave, crays;
extern float    kfract;
extern unsigned px, py;
extern float    a;
extern void spot (void);
extern void permanent_storm (void);
extern void crater (void);
extern void band (void);
extern void wave (void);
extern void fracture (unsigned char far *target, float max_latitude);
extern void volcano (void);
extern void contrast (float kt, float kq, float thrshld);
extern void randoface (int range, int upon);
extern void negate (void);
extern void crater_juice (void);
extern void cirrus (void);
extern void atm_cyclon (void);
extern void storm (void);
extern void planet_xyz (int n);
extern float rtp (int n);
extern int planet_viewpoint (double obs_x, double obs_z);
extern void surface (int logical_id, int type, double seedval, unsigned char colorbase);
extern int nightzone, crepzone, sun_x_factor;
extern void planets (void);
extern void ring (void);
extern void init_FP_segments (void);
extern int smh;
extern double idscale;
extern double laststar_x, laststar_y, laststar_z;
extern char isthere (double star_id);
extern long search_id_code (double id_code, char type);
extern long tgt_collect_lastpos;
extern int targets;
extern int topmost_target;
extern int target_line;
extern char update_targets;
extern char collecting_targets;
extern double targets_table_id[50];
extern double targets_table_px[50];
extern double targets_table_py[50];
extern double targets_table_pz[50];
extern void collect_targets (void);
extern void status (char *status_description, int message_delay);

extern float flandom ();
extern float fast_flandom ();

extern clock_t gtime;
extern void sync_start ();
extern void sync_stop ();

extern long   global_surface_seed;
extern float  ppos_x, ppos_y, ppos_z;
extern double dsd;

extern void load_starface ();
extern void load_QVRmaps ();
extern void load_digimap2 ();

extern char outhudbuffer[81];
extern void wrouthud (unsigned x, unsigned y, unsigned l, char *text);
extern void surrounding (char compass_on, int openhudcount);

extern float	pp_gravity;
extern float	pp_temp;
extern float	pp_pressure;
extern float    pp_pulse;

extern void additional_consumes (void);