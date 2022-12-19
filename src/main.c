#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SVGMAXSTR 255

#define SVGBGCOLOR "#fff"
#define SVGBGFILLOK (1)
#define SVGBGFILLNG (-1)

char svg_rgbtxt[SVGMAXSTR + 1] = "";
char svg_rgbstroke[SVGMAXSTR + 1] = "";
char svg_rgbfill[SVGMAXSTR + 1] = "";

char *svg_sharendopt[5] = {"inherit", "auto", "optimizeSpeed", "crispEdges",
                           "geometricPrecision"};
char *svg_txtrendopt[5] = {"inherit", "auto", "optimizeSpeed",
                           "optimizeLegibility", "geometricPrecision"};
char *svg_colrendopt[4] = {"inherit", "auto", "optimizeSpeed",
                           "optimizeQuality"};

#define SVGRDINHE (0)  // inherit
#define SVGRDAUTO (1)  // auto
#define SVGRDOPSP (2)  // optimizeSpeed
#define SVGRDCRED (3)  // crispEdges
#define SVGRDOPLE (3)  // optimizeLegibility
#define SVGRDOPQU (3)  // optimizeQuality
#define SVGRDGEPR (4)  // geometricPrecision

char *svg_txtanchoropt[3] = {"start", "middle", "end"};

#define SVGTXTLEFT (0)    //"start"
#define SVGTXTCENTER (1)  //"middle"
#define SVGTXTRIGHT (2)   //"end"
#define SVGTXTSTART (0)   //"start"
#define SVGTXTMIDDLE (1)  //"middle"
#define SVGTXTEND (2)     //"end"

#define SVGPTPS (1)   // point with plus sign
#define SVGPTCS (-1)  // point with cross sign

void *svg_ptrcheck(void *ptr, char *name) {
  if (ptr == NULL) {
    fprintf(stderr, "error: %s is NULL\n", name);
    exit(EXIT_FAILURE);
  }
  return ptr;
}

char *svg_strcheck(char *str, char *name) {
  svg_ptrcheck(str, name);
  size_t sl = strlen(str);
  if (sl > SVGMAXSTR) {
    fprintf(stderr, "string error: (strlen(%s)==%zu) > %d. it is too long. \n",
            name, sl, SVGMAXSTR);
    exit(EXIT_FAILURE);
  }
  return str;
}

int svg_open(FILE *fp, unsigned width, unsigned height, int fillflag) {
  svg_ptrcheck(fp, "fp");
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
    fprintf(
        fp,
        "<rect x=\"0\" y=\"0\" width=\"%u\" height=\"%u\" stroke-width=\"1\" "
        "stroke=\"%s\" fill=\"%s\" shape-rendering=\"auto\"/>\n",
        width, height, SVGBGCOLOR, SVGBGCOLOR);
  }
  return EXIT_SUCCESS;
}

int svg_close(FILE *fp) {
  svg_ptrcheck(fp, "fp");
  fprintf(fp, "\n</svg>\n");
  return EXIT_SUCCESS;
}

int svg_line(FILE *fp, int x1px, int y1px, int x2px, int y2px,
             char *strokecolor, int swpx, size_t rendopt) {
  svg_ptrcheck(fp, "fp");
  fprintf(fp,
          " <line x1=\"%d\" y1=\"%d\" x2=\"%d\" y2=\"%d\" "
          "stroke=\"%s\" stroke-width=\"%d\" shape-rendering=\"%s\"/>\n",
          x1px, y1px, x2px, y2px, strokecolor, swpx, svg_sharendopt[rendopt]);
  return EXIT_SUCCESS;
}

int svg_ptmark(FILE *fp, int xpx, int ypx, int size, char *color, int cpflag) {
  svg_ptrcheck(fp, "fp");
  if (cpflag > 0) {  // SVGPTPS plus
    svg_line(fp, xpx - size, ypx, xpx + size, ypx, color, 1, SVGRDAUTO);
    svg_line(fp, xpx, ypx - size, xpx, ypx + size, color, 1, SVGRDAUTO);
  } else {  // SVGPTCS cross
    svg_line(fp, xpx - size, ypx - size, xpx + size, ypx + size, color, 1,
             SVGRDAUTO);
    svg_line(fp, xpx - size, ypx + size, xpx + size, ypx - size, color, 1,
             SVGRDAUTO);
  }
  return EXIT_SUCCESS;
}

int svg_circle(FILE *fp, int xpx, int ypx, int rpx, char *strokecolor, int swpx,
               size_t rendopt) {
  svg_ptrcheck(fp, "fp");
  fprintf(fp,
          " <circle cx=\"%d\" cy=\"%d\" r=\"%d\" "
          "stroke=\"%s\" stroke-width=\"%d\" fill=\"none\" "
          "shape-rendering=\"%s\"/>\n",
          xpx, ypx, rpx, strokecolor, swpx, svg_sharendopt[rendopt]);
  return EXIT_SUCCESS;
}

int svg_circlefill(FILE *fp, int xpx, int ypx, int rpx, char *strokecolor,
                   int swpx, char *fillcolor, size_t rendopt) {
  svg_ptrcheck(fp, "fp");
  fprintf(fp,
          " <circle cx=\"%d\" cy=\"%d\" r=\"%d\" "
          "stroke=\"%s\" stroke-width=\"%d\" fill=\"%s\" "
          "shape-rendering=\"%s\"/>\n",
          xpx, ypx, rpx, strokecolor, swpx, fillcolor, svg_sharendopt[rendopt]);
  return EXIT_SUCCESS;
}

int svg_rect(FILE *fp, int xpx, int ypx, int wpx, int hpx, char *strokecolor,
             int swpx, size_t rendopt) {
  svg_ptrcheck(fp, "fp");
  fprintf(fp,
          " <rect x=\"%d\" y=\"%d\" width=\"%d\" height=\"%d\" stroke=\"%s\" "
          "stroke-width=\"%d\" fill=\"none\" shape-rendering=\"%s\"/>\n",
          xpx, ypx, wpx, hpx, strokecolor, swpx, svg_sharendopt[rendopt]);
  return EXIT_SUCCESS;
}

int svg_rectfill(FILE *fp, int xpx, int ypx, int wpx, int hpx,
                 char *strokecolor, int swpx, char *fillcolor, size_t rendopt) {
  svg_ptrcheck(fp, "fp");
  fprintf(fp,
          " <rect x=\"%d\" y=\"%d\" width=\"%d\" height=\"%d\" stroke=\"%s\" "
          "stroke-width=\"%d\" fill=\"%s\" shape-rendering=\"%s\"/>\n",
          xpx, ypx, wpx, hpx, strokecolor, swpx, fillcolor,
          svg_sharendopt[rendopt]);
  return EXIT_SUCCESS;
}

int svg_pxfill(FILE *fp, int xpx, int ypx, int wpx, int hpx, char *fillcolor) {
  svg_ptrcheck(fp, "fp");
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
             int fspx, char *fontcolor, size_t textanchor, size_t rendopt) {
  svg_ptrcheck(fp, "fp");
  svg_strcheck(string, "string");
  fprintf(fp,
          "<text font-family=\"%s\" x=\"%d\" y=\"%d\" font-size=\"%d\" "
          "fill=\"%s\" text-anchor=\"%s\" text-rendering=\"%s\">\n",
          fontfamily, xpx, ypx, fspx, fontcolor, svg_txtanchoropt[textanchor],
          svg_txtrendopt[rendopt]);
  fprintf(fp, "%s\n</text>\n", string);
  return EXIT_SUCCESS;
}

char *svg_rgbtostr(int r, int g, int b, char outstr[]) {
  sprintf(outstr, "rgb(%d,%d,%d)", r, g, b);
  return outstr;
}

#define MAXSTR 255

int main() {
  //  char filename[MAXSTR] = "samplesvg";
  srand(0);
  svg_open(stdout, 640, 480, SVGBGFILLOK);
  svg_line(stdout, 0, 10, 640, 10, "black", 1, SVGRDAUTO);
  svg_line(stdout, 10, 0, 10, 480, "black", 1, SVGRDAUTO);
  svg_line(stdout, 0, 20, 640, 20, "red", 2, SVGRDAUTO);
  svg_line(stdout, 20, 0, 20, 480, "red", 2, SVGRDAUTO);
  svg_line(stdout, 0, 30, 640, 30, "blue", 2, SVGRDAUTO);
  svg_line(stdout, 30, 0, 30, 480, "blue", 2, SVGRDAUTO);
  svg_pxlinex(stdout, 0, 40, 640, "green", 1);
  svg_pxliney(stdout, 40, 0, 480, "green", 1);
  svg_pxlinex(stdout, 0, 60, 640, "cyan", 2);
  svg_pxliney(stdout, 60, 0, 480, "cyan", 2);
  svg_pxlinex(stdout, 0, 80, 640, "yellow", 3);
  svg_pxliney(stdout, 80, 0, 640, "yellow", 3);

  svg_line(stdout, 128, 0, 128, 128, svg_rgbtostr(0, 0, 0, svg_rgbtxt), 1,
           SVGRDAUTO);
  svg_rect(stdout, 128, 128, 128, 128, svg_rgbtostr(0, 255, 0, svg_rgbstroke),
           1, SVGRDAUTO);
  svg_rectfill(stdout, 128, 256, 128, 128, svg_rgbtostr(0, 0, 0, svg_rgbstroke),
               1, svg_rgbtostr(255, 0, 255, svg_rgbfill), SVGRDAUTO);
  svg_pxfill(stdout, 256, 128, 128, 128,
             svg_rgbtostr(0, 255, 128, svg_rgbfill));

  svg_circle(stdout, 300, 300, 16, "red", 1, SVGRDAUTO);
  svg_circle(stdout, 340, 300, 16, "yellow", 1, SVGRDAUTO);
  svg_circle(stdout, 380, 300, 16, "blue", 1, SVGRDAUTO);
  svg_circlefill(stdout, 300, 340, 16, "black", 0,
                 svg_rgbtostr(255, 0, 0, svg_rgbfill), SVGRDAUTO);
  svg_circlefill(stdout, 340, 340, 16, "black", 0,
                 svg_rgbtostr(255, 255, 0, svg_rgbfill), SVGRDAUTO);
  svg_circlefill(stdout, 380, 340, 16, "black", 0,
                 svg_rgbtostr(0, 0, 255, svg_rgbfill), SVGRDAUTO);

  svg_ptmark(stdout, 400, 300, 2, "orange", SVGPTPS);
  svg_ptmark(stdout, 400, 340, 2, "orange", SVGPTPS);
  svg_ptmark(stdout, 400, 380, 2, "orange", SVGPTPS);
  svg_ptmark(stdout, 600, 300, 2, "orange", SVGPTCS);
  svg_ptmark(stdout, 600, 340, 2, "orange", SVGPTCS);
  svg_ptmark(stdout, 600, 380, 2, "orange", SVGPTCS);
  svg_pxlinex(stdout, 400, 300, 200, "gray", 1);
  svg_pxlinex(stdout, 400, 340, 200, "gray", 1);
  svg_pxlinex(stdout, 400, 380, 200, "gray", 1);
  svg_pxplus(stdout, 400, 300, 2, "black");
  svg_pxplus(stdout, 500, 340, 2, "black");
  svg_pxplus(stdout, 600, 380, 2, "black");
  svg_text(stdout, "Sample SVG", 400, 300, "Helvetica", 24,
           svg_rgbtostr(0, 0, 0, svg_rgbtxt), SVGTXTLEFT, SVGRDINHE);
  svg_text(stdout, "0123456789", 500, 340, "Helvetica", 24,
           svg_rgbtostr(0, 0, 0, svg_rgbtxt), SVGTXTCENTER, SVGRDINHE);
  svg_text(stdout, "iIlLoOqQ", 600, 380, "Helvetica", 24,
           svg_rgbtostr(0, 0, 0, svg_rgbtxt), SVGTXTRIGHT, SVGRDINHE);

  for (int ix = 0; ix < 128; ix += 2) {
    for (int iy = 0; iy < 128; iy += 2) {
      svg_pxdot(stdout, ix, iy, 2,
                svg_rgbtostr((rand() % 256), (rand() % 256), (rand() % 256),
                             svg_rgbtxt));
    }
  }

  svg_close(stdout);

  return EXIT_SUCCESS;
}
