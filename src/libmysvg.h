#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SVGMAXSTR 255
#define SVGBGFILLOK (1)
#define SVGBGFILLNG (-1)
#define SVGBGCOLOR "#fff"
//#define SVGSHAREN "crispEdges"
#define SVGSHAREN "geometricPrecision"
#define SVGTXTREN "geometricPrecision"
#define SVGTXTLEFT "start"
#define SVGTXTCENTER "middle"
#define SVGTXTRIGHT "end"
#define SVGPTP (1)
#define SVGPTX (-1)

extern char svg_rgbtxt[SVGMAXSTR + 1];
extern char svg_rgbstroke[SVGMAXSTR + 1];
extern char svg_rgbfill[SVGMAXSTR + 1];

#define MAXSTR 255

int svg_open(FILE *fp, unsigned width, unsigned height, int fillflag);
int svg_close(FILE *fp);

int svg_line(FILE *fp, int x1px, int y1px, int x2px, int y2px,
             char *strokecolor, int swpx);
int svg_cross(FILE *fp, int xpx, int ypx, int size, char *color, int cpflag);
int svg_circle(FILE *fp, int xpx, int ypx, int rpx, char *strokecolor,
               int swpx);
int svg_circlefill(FILE *fp, int xpx, int ypx, int rpx, char *strokecolor,
                   int swpx, char *fillcolor);
int svg_rect(FILE *fp, int xpx, int ypx, int wpx, int hpx, char *strokecolor,
             int swpx);
int svg_rectfill(FILE *fp, int xpx, int ypx, int wpx, int hpx,
                 char *strokecolor, int swpx, char *fillcolor);
int svg_pxfill(FILE *fp, int xpx, int ypx, int wpx, int hpx, char *fillcolor);
int svg_pxdot(FILE *fp, int xpx, int ypx, int size, char *color);
int svg_pxlinex(FILE *fp, int xpx, int ypx, int width, char *color,
                int strokesize);
int svg_pxliney(FILE *fp, int xpx, int ypx, int height, char *color,
                int strokesize);
int svg_pxplus(FILE *fp, int xpx, int ypx, int size, char *color);
int svg_text(FILE *fp, char *string, int xpx, int ypx, char *fontfamily,
             int fspx, char *fontcolor, char *textanchor);
char *svg_rgbtostr(int r, int g, int b, char *outstr);
