#include "noctis-d.h"

extern uint16_t QUADWORDS;
extern uint8_t *adapted;
extern int16_t get_key();
extern bool is_key();
extern uint8_t range8088[64 * 3];
extern uint8_t tmppal[768];
extern uint8_t currpal[768];
extern int8_t return_palette[768];
extern int8_t surface_palette[768];
extern void tavola_colori(const uint8_t *nuova_tavolozza,
                          uint16_t colore_di_partenza, uint16_t nr_colori,
                          int8_t filtro_rosso, int8_t filtro_verde,
                          int8_t filtro_blu);
extern int16_t mdltx, mdlty, mouse_x, mouse_y;
extern uint16_t mpul;
extern struct wasdmov key_move_dir;
extern void handle_input();
extern void area_clear(uint8_t *dest, int16_t x, int16_t y, int16_t x2,
                      int16_t y2, int16_t l, int16_t h, uint8_t pattern);
extern void psmooth_grays(uint8_t *target);
extern void pfade(uint8_t *target, uint16_t segshift, uint8_t speed);
extern void psmooth_64(uint8_t *target, uint16_t segshift);
extern void smootharound_64(uint8_t *target, int32_t cx, int32_t cy, int32_t r,
                            int8_t diffuse);
extern void mask_pixels(uint8_t *target, uint8_t mask);

extern int32_t XSIZE, YSIZE;        // calibrazione BMP.
extern float uneg;
extern float cam_x, cam_y, cam_z;
extern float dpp;
extern int32_t H_MATRIXS, V_MATRIXS;
extern float alfa, beta, ngamma;
extern uint16_t ptr;
extern void segment(int32_t xp, int32_t yp, int32_t xa, int32_t ya);
extern int8_t flares;
extern int32_t lbxl;
extern int32_t ubxl;
extern int32_t lbyl;
extern int32_t ubyl;
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

extern void change_angle_of_view();
extern void change_camera_lens();
extern void change_txm_repeating_mode();
extern uint8_t entity;
extern void poly3d(const float *x, const float *y, const float *z, uint16_t nrv,
                   uint8_t colore);
extern void forward(float delta);
extern float pnx, pny, pnz;
extern void pnorm(const float *x, const float *y, const float *z);
extern uint8_t *txtr;
extern float x_antialias, y_antialias, z_antialias;
extern int8_t culling_needed, halfscan_needed;
extern uint8_t escrescenze;
extern void polymap(float *x, float *y, float *z, int8_t nv, uint8_t tinta);
extern int32_t _x_, _y_;
extern int8_t get_coords(float x, float y, float z);
extern bool facing(float *x, float *y, float *z);

extern const char *situation_file;
extern const char *starmap_file;
extern const char *goesoutputfile;
extern const char *surface_file;

extern int8_t nsync;
extern int8_t anti_rad;
extern int8_t pl_search;
extern int8_t field_amplificator;
extern int8_t ilight;
extern int8_t ilightv;
extern int8_t charge;
extern int8_t revcontrols;
extern int8_t ap_targetting;
extern int8_t ap_targetted;
extern int8_t ip_targetting;
extern int8_t ip_targetted;
extern int8_t ip_reaching;
extern int8_t ip_reached;
extern int8_t ap_target_spin;
extern int8_t ap_target_r;
extern int8_t ap_target_g;
extern int8_t ap_target_b;
extern int8_t nearstar_spin;
extern int8_t nearstar_r;
extern int8_t nearstar_g;
extern int8_t nearstar_b;
extern int8_t gburst;
extern int8_t menusalwayson;
extern int8_t depolarize;
extern int16_t sys;
extern int16_t pwr;
extern int16_t dev_page;
extern int16_t ap_target_class;
extern int16_t f_ray_elapsed;
extern int16_t nearstar_class;
extern int16_t nearstar_nop;
extern float pos_x;
extern float pos_y;
extern float pos_z;
extern float user_alfa;
extern float user_beta;
extern float navigation_beta;
extern float ap_target_ray;
extern float nearstar_ray;
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
extern char fcs_status[11];
extern int16_t fcs_status_delay;
extern int16_t psys;
extern double ap_target_initial_d;
extern double requested_vimana_coefficient;
extern double current_vimana_coefficient;
extern double vimana_reaction_time;
extern int8_t lithium_collector;
extern int8_t autoscreenoff;
extern int8_t ap_reached;
extern int16_t lifter;
extern double secs;
extern int8_t data;
extern int8_t surlight;

extern int8_t land_now;
extern int8_t landing_point;
extern int16_t landing_pt_lon;
extern int16_t landing_pt_lat;
extern int16_t rotation;
extern int16_t epoc;
extern char ctb[512];
extern int8_t _delay;
extern int8_t stspeed;
extern int8_t elight;
extern uint16_t gl_start;
extern uint16_t point;
extern uint16_t vptr;
extern int16_t infoarea;
extern int16_t s_control;
extern int16_t s_command;
extern int16_t isecs, p_isecs;
extern double fsecs;
extern int16_t gl_fps;
extern int16_t fps;
extern float dlt_alfa;
extern float dlt_beta;
extern float dlt_nav_beta;
extern float step;
extern float shift;
extern double s_m;
extern double plx, ply, plz;
extern double pxx, pyy;
extern double delta_x, delta_y;
extern double nearstar_identity;
extern int16_t nearstar_nob;
extern int16_t nearstar_labeled;
extern int16_t npcs;
extern int8_t ontheroof;
extern int16_t datasheetscroll;
extern int16_t datasheetdelta;

extern int8_t *ord[21];
extern int8_t *star_description[12];
extern int8_t class_rgb[3 * star_classes];
extern int16_t class_ray[star_classes];
extern int16_t class_rayvar[star_classes];
extern int8_t class_planets[star_classes];
extern int8_t nearstar_p_type[maxbodies];
extern int16_t nearstar_p_owner[maxbodies];
extern int8_t nearstar_p_moonid[maxbodies];
extern double nearstar_p_ring[maxbodies];
extern double nearstar_p_tilt[maxbodies];
extern double nearstar_p_ray[maxbodies];
extern double nearstar_p_orb_ray[maxbodies];
extern double nearstar_p_orb_tilt[maxbodies];
extern double nearstar_p_orb_orient[maxbodies];
extern double nearstar_p_orb_ecc[maxbodies];
extern int16_t nearstar_p_rtperiod[maxbodies];
extern int16_t nearstar_p_rotation[maxbodies];
extern int16_t nearstar_p_term_start[maxbodies];
extern int16_t nearstar_p_term_end[maxbodies];
extern int16_t nearstar_p_qsortindex[maxbodies];
extern float nearstar_p_qsortdist[maxbodies];
extern int8_t *planet_description[10];
extern uint8_t planet_rgb_and_var[40];
extern int16_t planet_possiblemoons[10];
extern float mindiff;
extern uint8_t *p_background;
extern uint8_t *s_background;
extern uint8_t *p_surfacemap;
extern struct quadrant *objectschart;
extern uint8_t *ruinschart; // come objectschart, ma dichiarato in bytes
extern uint8_t *pvfile;
extern uint8_t *n_offsets_map;
extern int8_t *n_globes_map;
extern int8_t sky_red_filter;
extern int8_t sky_grn_filter;
extern int8_t sky_blu_filter;
extern int8_t gnd_red_filter;
extern int8_t gnd_grn_filter;
extern int8_t gnd_blu_filter;
extern float planet_grav;
extern float rainy;
extern int16_t albedo;
extern uint8_t sky_brightness;
extern uint16_t m200[200];
extern float rwp;
extern float iwp;
extern float wp;
extern float wdir;
extern float wdirsin;
extern float wdircos;
extern int8_t landed;
extern int32_t atl_x, atl_z, atl_x2, atl_z2;
extern double qid;
extern int16_t in;
extern int32_t flat_rnd_seed;
extern void fast_srand(int32_t seed);
extern int32_t fast_random(int32_t mask);
extern int16_t ranged_fast_random(int16_t range);
extern FILE *sa_open(int32_t offset_of_virtual_file);
extern void shade(uint8_t *palette_buffer, int16_t first_color,
                  int16_t number_of_colors, float start_r, float start_g,
                  float start_b, float finish_r, float finish_g,
                  float finish_b);
extern int8_t snapfilename[24];
extern void snapshot(int16_t forcenumber, int8_t showdata);
extern void from_vehicle();
extern void from_user();
extern void watch(double cam_x, double cam_y, double cam_z, double see_x,
                  double see_y, double see_z);
extern int8_t xy(double cam_x, double cam_y, double cam_z, double point_x,
                 double point_y, double point_z);
extern void p_forward(float delta);
extern void setfx(int8_t fx);
extern void chgfx(int8_t fx);
extern void resetfx();
extern void stick(uint32_t xp, uint32_t yp, uint32_t xa, uint32_t ya);
extern int32_t fpx;
extern int32_t fpy;
extern float p_rx, p_ry, p_rz;
extern float stick_uneg;
extern void stick3d(float p_x, float p_y, float p_z, float x, float y, float z);
extern void fline(int32_t fx, int32_t fy, int32_t lx, int32_t ly);
//--------------------------------------------------------------------------//
extern uint8_t map_color_a;
extern uint8_t map_color_b;
extern uint8_t map_color_c;
extern uint8_t map_color_d;
extern void randomic_mapper(float x0, float y0, float z0, float x1, float y1,
                            float z1, float x2, float y2, float z2,
                            int8_t divisions);
extern void unloadpv(int16_t handle);
extern void unloadallpv();
extern int8_t loadpv(int16_t handle, int32_t virtual_file_position,
                     float xscale, float yscale, float zscale, float xmove,
                     float ymove, float zmove, uint8_t base_color,
                     int8_t depth_sort);
extern void quick_sort(int16_t *index, float *mdist, int16_t start, int16_t end);
extern void drawpv(int16_t handle, int16_t mode, int16_t rm_iterations,
                   float center_x, float center_y, float center_z,
                   int8_t use_depth_sort);
extern void copypv(int16_t dest_handle, int16_t src_handle);
extern void modpv(int16_t handle, int16_t polygon_id, int16_t vertex_id,
                  float x_scale, float y_scale, float z_scale, float x_angle,
                  float y_angle, float z_angle,
                  struct pvlist *vertexs_to_affect);
//--------------------------------------------------------------------------//
extern char *alphavalue(double value);
extern void background(uint16_t start, uint8_t *target, uint8_t *background,
                       uint8_t *offsetsmap, uint16_t total_map_bytes,
                       uint16_t screenshift);
extern void sky(uint16_t limits);
extern double laststar_x, laststar_y, laststar_z;
extern int8_t isthere(double star_id);
extern int8_t glass_bubble;
extern void globe(uint16_t start, uint8_t *target, const uint8_t *tapestry,
                  const uint8_t *offsetsmap, uint16_t total_map_bytes, double x,
                  double y, double z, float mag_factor, int8_t colormask,
                  int8_t globe_saturation);
extern void glowing_globe(int16_t start, uint8_t *target,
                        const uint8_t *offsetsmap, uint16_t total_map_bytes,
                        double x, double y, double z, float mag_factor,
                        int16_t terminator_start, int16_t terminator_arc,
                        uint8_t color);
extern void white_globe(uint8_t *target, double x, double y, double z,
                       float mag_factor, float fgm_factor);
extern double xsun_onscreen;
extern void white_sun(uint8_t *target, double x, double y, double z,
                     float mag_factor, float fgm_factor);
extern float lft_sin[361];
extern float lft_cos[361];
extern int8_t lens_flares_init();
extern void lens_flares_for(double cam_x, double cam_y, double cam_z,
                            double xlight, double ylight, double zlight,
                            double interval, int16_t added, int8_t on_hud,
                            int8_t condition, int16_t xshift, int16_t yshift);
extern void single_pixel_at_ptr(uint16_t offset, uint8_t pixel_color);
extern int8_t far_pixel_at(double xlight, double ylight, double zlight,
                           double radii, uint8_t unconditioned_color);
extern uint32_t *digimap2;
extern void cupola(float y_or, float brk);
extern void polycupola(float y_or, int8_t textured);
extern void getsecs();
extern void extract_ap_target_infos();
extern float zrandom(int16_t range);
extern int16_t starnop(double star_x, double star_y, double star_z);
extern void prepare_nearstar();
extern void ssmooth(uint8_t *target);
extern void lssmooth(uint8_t *target);
extern int16_t gr, r, g, b, cr, cx, cy;
extern int8_t lave, crays;
extern float kfract;
extern uint16_t px, py;
extern float a;
extern void spot();
extern void permanent_storm();
extern void crater();
extern void band();
extern void wave();
extern void fracture(uint8_t *target, float max_latitude);
extern void volcano();
extern void contrast(float kt, float kq, float thrshld);
extern void randoface(int16_t range, int16_t upon);
extern void negate();
extern void crater_juice();
extern void cirrus();
extern void atm_cyclon();
extern void storm();
extern void planet_xyz(int16_t n);
extern float rtp(int16_t n);
extern int16_t planet_viewpoint(double obs_x, double obs_z);
extern void surface(int16_t logical_id, int16_t type, double seedval,
                    uint8_t colorbase);
extern int16_t nightzone, crepzone, sun_x_factor;
extern void planets();
extern void ring(int16_t planet_id, double ox, double oy, double oz,
                 int16_t start, int16_t layers);
extern double idscale;
extern int32_t search_id_code(double id_code, int8_t type);
extern int32_t tgt_collect_lastpos;
extern int16_t targets;
extern int16_t topmost_target;
extern int16_t target_line;
extern int8_t update_targets;
extern int8_t collecting_targets;
extern double targets_table_id[50];
extern double targets_table_px[50];
extern double targets_table_py[50];
extern double targets_table_pz[50];
extern void collect_targets();
extern void status(const char *status_description, int16_t message_delay);

extern float flandom();
extern float fast_flandom();

extern clock_t gtime;
extern void sync_start();
extern void sync_stop();

extern int32_t global_surface_seed;
extern double dsd;

extern void load_starface();
extern void load_QVRmaps();
extern void load_digimap2();

extern int8_t outhudbuffer[81];
extern void wrouthud(uint16_t x, uint16_t y, uint16_t l, const char *text);
extern void surrounding(int8_t compass_on, int16_t openhudcount);

extern float pp_gravity;
extern float pp_temp;
extern float pp_pressure;
extern float pp_pulse;

extern void additional_consumes();