/**
 *  File: gParcer.h
 * Company: CUBY,Ltd
*/

#ifndef GPARCER
#define GPARCER

#ifdef __cplusplus
   extern "C" {
#endif

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <stdbool.h>

#define FLOG


// ------------- vars
extern FILE *flog;


#ifdef SCANNER
extern void b_command (size_t curline, char * param, size_t len);
extern void b_gcomment (size_t curline, char * param, size_t len);
extern void b_g_command (size_t curline, char * param, size_t len);
extern void b_x_coordinate(size_t curline, char * param, size_t len);
extern void b_y_coordinate(size_t curline, char * param, size_t len);
extern void b_z_coordinate(size_t curline, char * param, size_t len);
extern void b_a_parameter(size_t curline, char * param, size_t len);
extern void b_b_parameter(size_t curline, char * param, size_t len);
extern void b_c_parameter(size_t curline, char * param, size_t len);
extern void b_d_parameter(size_t curline, char * param, size_t len);
extern void b_e_parameter(size_t curline, char * param, size_t len);
extern void b_f_parameter(size_t curline, char * param, size_t len);
extern void b_i_parameter(size_t curline, char * param, size_t len);
extern void b_j_parameter(size_t curline, char * param, size_t len);
extern void b_k_parameter(size_t curline, char * param, size_t len);
extern void b_l_parameter(size_t curline, char * param, size_t len);
extern void b_m_parameter(size_t curline, char * param, size_t len);
extern void b_n_parameter(size_t curline, char * param, size_t len);
extern void b_p_parameter(size_t curline, char * param, size_t len);
extern void b_r_parameter(size_t curline, char * param, size_t len);
extern void b_s_parameter(size_t curline, char * param, size_t len);
extern void b_t_parameter(size_t curline, char * param, size_t len);
extern void b_u_parameter(size_t curline, char * param, size_t len);
extern void b_v_parameter(size_t curline, char * param, size_t len);
extern void b_w_parameter(size_t curline, char * param, size_t len);
extern void b_star_parameter(size_t curline, char * param, size_t len);
extern void b_punct(curline, param, len);
#endif


//----------- function

extern void scanner();

extern void execute(char *data, int len);

extern void init();

extern int finish();

#ifdef __cplusplus
   }
#endif

#endif

