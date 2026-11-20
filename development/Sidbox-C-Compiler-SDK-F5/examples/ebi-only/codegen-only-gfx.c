/* COMPILE-ONLY. Do NOT launch outside a proper SDK-owned display mode! */
#include "apis.h"
int main(void)
{
    API.gfx->hgfx->lcdwait();
    API.gfx->primatives->setcolour(4);
    API.gfx->primatives->rectf(10, 10, 80, 40);
    API.gfx->hgfx->displaynow();
    return 0;
}
