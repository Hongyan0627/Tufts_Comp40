#ifndef YBR_PIXEL_INCLUDED
#define YBR_PIXEL_INCLUDED

/* structure for component video color pixel. three members are all float 
 * numbers. */
typedef struct Pnm_ybr {
    float y;
    float pb;
    float pr;
} *Pnm_ybr;

#endif