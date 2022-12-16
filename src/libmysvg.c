#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "libmysvg_priv.h"

char svg_rgbtxt[SVGMAXSTR + 1] = "";
char svg_rgbstroke[SVGMAXSTR + 1] = "";
char svg_rgbfill[SVGMAXSTR + 1] = "";

void *ptrcheck(void *ptr, char *name) {
  if (ptr == NULL) {
    fprintf(stderr, "error: %s is NULL\n", name);
    exit(EXIT_FAILURE);
  }
  return ptr;
}

char *strcheck(char *str, char *name) {
  ptrcheck(str, name);
  if (strlen(str) > SVGMAXSTR) {
    fprintf(stderr, "string error: %s is too long???\n", name);
    exit(EXIT_FAILURE);
  }
  return str;
}

int svg_open(FILE *fp, unsigned width, unsigned height, int fillflag) {
  ptrcheck(fp, "fp");
  fprintf(fp,
          "<\?xml version=\"1.0\" standalone=\"no\"\?>\n"
          "\t<!DOCTYPE svg PUBLIC \"-//W3C//DTD SVG 1.1//EN\"\n"
          "\t\"http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd\">\n");
  fprintf(fp,
          "<svg width=\"%u\" height=\"%u\" viewBox=\"0, 0, %u, %u\" "
          "version=\"1.1\"\n",
          width, height, width, height);
  fprintf(fp, "\txmlns=\"http://www.w3.org/2000/svg\">\n");
  if (fillflag == SVGBGFILLOK) {
    fprintf(fp,
            "<rect x=\"0\" y=\"0\" width=\"%u\" height=\"%u\" fill=\"%s\" />\n",
            width, height, SVGBGCOLOR);
  }
  return EXIT_SUCCESS;
}

int svg_close(FILE *fp) {
  ptrcheck(fp, "fp");
  fprintf(fp, "\n</svg>\n");
  return EXIT_SUCCESS;
}

int svg_line(FILE *fp, int x1px, int y1px, int x2px, int y2px,
             char *strokecolor, int swpx) {
  ptrcheck(fp, "fp");
  fprintf(fp,
          " <line x1=\"%d\" y1=\"%d\" x2=\"%d\" y2=\"%d\" "
          "stroke=\"%s\" stroke-width=\"%d\" shape-rendering=\"%s\"/>\n",
          x1px, y1px, x2px, y2px, strokecolor, swpx, SVGSHAREN);
  return EXIT_SUCCESS;
}

int svg_cross(FILE *fp, int xpx, int ypx, int size, char *color, int cpflag) {
  ptrcheck(fp, "fp");
  if (cpflag > 0) {  // SVGPTP
    svg_line(fp, xpx - size, ypx, xpx + size, ypx, color, 1);
    svg_line(fp, xpx, ypx - size, xpx, ypx + size, color, 1);
  } else {  // SVGPTX
    svg_line(fp, xpx - size, ypx - size, xpx + size, ypx + size, color, 1);
    svg_line(fp, xpx - size, ypx + size, xpx + size, ypx - size, color, 1);
  }
  return EXIT_SUCCESS;
}

int svg_circle(FILE *fp, int xpx, int ypx, int rpx, char *strokecolor,
               int swpx) {
  ptrcheck(fp, "fp");
  fprintf(fp,
          " <circle cx=\"%d\" cy=\"%d\" r=\"%d\" "
          "stroke=\"%s\" stroke-width=\"%d\" fill=\"none\" "
          "shape-rendering=\"%s\"/>\n",
          xpx, ypx, rpx, strokecolor, swpx, SVGSHAREN);
  return EXIT_SUCCESS;
}

int svg_circlefill(FILE *fp, int xpx, int ypx, int rpx, char *strokecolor,
                   int swpx, char *fillcolor) {
  ptrcheck(fp, "fp");
  fprintf(fp,
          " <circle cx=\"%d\" cy=\"%d\" r=\"%d\" "
          "stroke=\"%s\" stroke-width=\"%d\" fill=\"%s\" "
          "shape-rendering=\"%s\"/>\n",
          xpx, ypx, rpx, strokecolor, swpx, fillcolor, SVGSHAREN);
  return EXIT_SUCCESS;
}

int svg_rect(FILE *fp, int xpx, int ypx, int wpx, int hpx, char *strokecolor,
             int swpx) {
  ptrcheck(fp, "fp");
  fprintf(fp,
          " <rect x=\"%d\" y=\"%d\" width=\"%d\" height=\"%d\" stroke=\"%s\" "
          "stroke-width=\"%d\" fill=\"none\" shape-rendering=\"%s\"/>\n",
          xpx, ypx, wpx, hpx, strokecolor, swpx, SVGSHAREN);
  return EXIT_SUCCESS;
}

int svg_rectfill(FILE *fp, int xpx, int ypx, int wpx, int hpx,
                 char *strokecolor, int swpx, char *fillcolor) {
  ptrcheck(fp, "fp");
  fprintf(fp,
          " <rect x=\"%d\" y=\"%d\" width=\"%d\" height=\"%d\" stroke=\"%s\" "
          "stroke-width=\"%d\" fill=\"%s\" shape-rendering=\"%s\"/>\n",
          xpx, ypx, wpx, hpx, strokecolor, swpx, fillcolor, SVGSHAREN);
  return EXIT_SUCCESS;
}

int svg_pxfill(FILE *fp, int xpx, int ypx, int wpx, int hpx, char *fillcolor) {
  ptrcheck(fp, "fp");
  fprintf(fp,
          " <rect x=\"%d\" y=\"%d\" width=\"%d\" height=\"%d\" fill=\"%s\" "
          "shape-rendering=\"%s\"/>\n",
          xpx, ypx, wpx, hpx, fillcolor, "crispEdges");
  return EXIT_SUCCESS;
}

int svg_pxdot(FILE *fp, int xpx, int ypx, int size, char *color) {
  int rv = 0;
  rv = svg_pxfill(fp, xpx, ypx, size, size, color);
  return rv;
}

int svg_pxlinex(FILE *fp, int xpx, int ypx, int width, char *color,
                int strokesize) {
  int rv = 0;
  rv = svg_pxfill(fp, xpx, ypx, width, strokesize, color);
  return rv;
}

int svg_pxliney(FILE *fp, int xpx, int ypx, int height, char *color,
                int strokesize) {
  int rv = 0;
  rv = svg_pxfill(fp, xpx, ypx, strokesize, height, color);
  return rv;
}

int svg_pxplus(FILE *fp, int xpx, int ypx, int size, char *color) {
  int rv = 0;
  rv = svg_pxlinex(fp, xpx - size, ypx, 2 * size + 1, color, 1);
  rv = svg_pxliney(fp, xpx, ypx - size, 2 * size + 1, color, 1);
  return rv;
}

int svg_text(FILE *fp, char *string, int xpx, int ypx, char *fontfamily,
             int fspx, char *fontcolor, char *textanchor) {
  ptrcheck(fp, "fp");
  strcheck(string, "string");
  fprintf(fp,
          "<text font-family=\"%s\" x=\"%d\" y=\"%d\" font-size=\"%d\" "
          "fill=\"%s\" text-anchor=\"%s\" text-rendering=\"%s\">\n",
          fontfamily, xpx, ypx, fspx, fontcolor, textanchor, SVGTXTREN);
  fprintf(fp, "%s\n</text>\n", string);
  return EXIT_SUCCESS;
}

char *svg_rgbtostr(int r, int g, int b, char outstr[]) {
  sprintf(outstr, "rgb(%d,%d,%d)", r, g, b);
  return outstr;
}
