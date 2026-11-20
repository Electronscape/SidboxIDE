/* COMPILE ONLY: this probes raw gfx EBI code generation.
 * DO NOT call raw_graphics_probe or draw outside an exclusive display lease.
 * Current SBAPI05 clibs.library DOES NOT expose an exclusive lease.
 * main() only returns 0, so running does not exercise the gfx paths.
 */
#include "apis.h"
static uint8_t pixels[256];
static int palette[256];

static void raw_graphics_probe(void)
{
    API.gfx->primatives->setcolour(12);
    API.gfx->primatives->cls();
    API.gfx->primatives->rectf(3, 3, 100, 50);
    API.gfx->primatives->drawline(0, 0, 120, 90);
    API.gfx->primatives->circle(80, 50, 12);
    API.gfx->primatives->circlef(80, 50, 5);
    API.gfx->primatives->plot(17, 27);
    API.gfx->primatives->drawtext(8, 10, "Raw gfx symbols compiled");
    API.gfx->primatives->drawtextf(10, 25, "Scale", 1, 1);
    API.gfx->primatives->blit(pixels, 4, 4, 16, 16);
    API.gfx->primatives->blitw(pixels, 5, 5, 16, 16, 16);
    API.gfx->hgfx->usepalettef(palette);
    API.gfx->hgfx->displaynow();
    API.gfx->hgfx->lcdwait();
}
int main(void)
{
    return 0;
}
