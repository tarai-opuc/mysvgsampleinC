#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "libmysvg.h"

#define MAXSTR 255

int main() {
  //  char filename[MAXSTR] = "samplesvg";
  srand(0);
  svg_open(stdout, 640, 480, SVGBGFILLOK);
  svg_line(stdout, 0, 10, 640, 10, "black", 1);
  svg_line(stdout, 10, 0, 10, 480, "black", 1);
  svg_line(stdout, 0, 20, 640, 20, "red", 2);
  svg_line(stdout, 20, 0, 20, 480, "red", 2);
  svg_line(stdout, 0, 30, 640, 30, "blue", 2);
  svg_line(stdout, 30, 0, 30, 480, "blue", 2);
  svg_pxlinex(stdout, 0, 40, 640, "green", 1);
  svg_pxliney(stdout, 40, 0, 480, "green", 1);
  svg_pxlinex(stdout, 0, 60, 640, "cyan", 2);
  svg_pxliney(stdout, 60, 0, 480, "cyan", 2);
  svg_pxlinex(stdout, 0, 80, 640, "yellow", 3);
  svg_pxliney(stdout, 80, 0, 640, "yellow", 3);

  svg_line(stdout, 128, 0, 128, 128, svg_rgbtostr(0, 0, 0, svg_rgbtxt), 1);
  svg_rect(stdout, 128, 128, 128, 128, svg_rgbtostr(0, 255, 0, svg_rgbstroke),
           1);
  svg_rectfill(stdout, 128, 256, 128, 128, svg_rgbtostr(0, 0, 0, svg_rgbstroke),
               1, svg_rgbtostr(255, 0, 255, svg_rgbfill));
  svg_pxfill(stdout, 256, 128, 128, 128,
             svg_rgbtostr(0, 255, 128, svg_rgbfill));

  svg_circle(stdout, 300, 300, 16, "red", 1);
  svg_circle(stdout, 340, 300, 16, "yellow", 1);
  svg_circle(stdout, 380, 300, 16, "blue", 1);
  svg_circlefill(stdout, 300, 340, 16, "black", 0,
                 svg_rgbtostr(255, 0, 0, svg_rgbfill));
  svg_circlefill(stdout, 340, 340, 16, "black", 0,
                 svg_rgbtostr(255, 255, 0, svg_rgbfill));
  svg_circlefill(stdout, 380, 340, 16, "black", 0,
                 svg_rgbtostr(0, 0, 255, svg_rgbfill));

  svg_cross(stdout, 400, 300, 2, "orange", SVGPTP);
  svg_cross(stdout, 400, 340, 2, "orange", SVGPTP);
  svg_cross(stdout, 400, 380, 2, "orange", SVGPTP);
  svg_cross(stdout, 600, 300, 2, "orange", SVGPTX);
  svg_cross(stdout, 600, 340, 2, "orange", SVGPTX);
  svg_cross(stdout, 600, 380, 2, "orange", SVGPTX);
  svg_pxlinex(stdout, 400, 300, 200, "gray", 1);
  svg_pxlinex(stdout, 400, 340, 200, "gray", 1);
  svg_pxlinex(stdout, 400, 380, 200, "gray", 1);
  svg_pxplus(stdout, 400, 300, 2, "black");
  svg_pxplus(stdout, 500, 340, 2, "black");
  svg_pxplus(stdout, 600, 380, 2, "black");
  svg_text(stdout, "Sample SVG", 400, 300, "Helvetica", 24,
           svg_rgbtostr(0, 0, 0, svg_rgbtxt), SVGTXTLEFT);
  svg_text(stdout, "0123456789", 500, 340, "Helvetica", 24,
           svg_rgbtostr(0, 0, 0, svg_rgbtxt), SVGTXTCENTER);
  svg_text(stdout, "iIlLoOqQ", 600, 380, "Helvetica", 24,
           svg_rgbtostr(0, 0, 0, svg_rgbtxt), SVGTXTRIGHT);

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
