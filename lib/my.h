/*
** EPITECH PROJECT, 2019
** my
** File description:
** Prototype all functions of libmy.a & define macros
*/

#ifndef _my_h_
#define _my_h_

typedef long unsigned int u64;
typedef long int i64;
typedef unsigned int u32;
typedef int i32;

//matrice
float *mat3_init(void);
float *mat3_multiply(float *mat1, float *mat2);
float *mat3_init_x(float a);
float *mat3_init_y(float a);
float *mat3_init_z(float a);
float *mat3_init_scale(float s);
float *init_p(void);
float *mat3_point(float *mat, float *p);
float *mat3_copy(float *mat);

void mat3_rx(float *mat_o, float a);
void mat3_ry(float *mat_o, float a);
void mat3_rz(float *mat_o, float a);
void mat3_tx(float *mat_o, float t);
void mat3_ty(float *mat_o, float t);
void mat3_tz(float *mat_o, float t);

void mat3_ttx(float *mat_o, float t);
void mat3_tty(float *mat_o, float t);
void mat3_ttz(float *mat_o, float t);
void mat3_rrx(float *mat_o, float a);
void mat3_rry(float *mat_o, float a);
void mat3_rrz(float *mat_o, float a);

float *mat3_inv(float *mat);

//linked list (lld)
typedef struct lld
{
    void* data;
    struct lld* next;
    struct lld* prev;
} lld_t;


int lld_db(lld_t *lld);
void lld_free_r(lld_t *lld);
void lld_free(lld_t *lld);
lld_t *lld_init();
void lld_insert_node(lld_t *lld, int poss, lld_t *node);
void lld_insert(lld_t *lld, int pos, void *data);
int lld_len_db(lld_t *lld);
int lld_len(lld_t *lld);
void **lld_lld_to_tab(lld_t *lld);
void *lld_pop_node(lld_t *lld, int pos);
void *lld_pop(lld_t *lld, int pos);
void lld_print_int(lld_t *lld);
void lld_print_str(lld_t *lld);
void *lld_read(lld_t *lld, int poss);
void lld_sort(lld_t *list, int (*cmp)());
void *lld_write(lld_t *lld, int poss, void *data);
lld_t *lld_tab_to_lld(void **tab, int size);

#endif
