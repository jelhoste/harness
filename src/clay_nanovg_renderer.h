// Nova — pont de rendu entre Clay (layout) et NanoVG (dessin).
//
// Clay calcule la disposition (position/taille de chaque élément) et
// produit une liste de "commandes de rendu" génériques (rectangle,
// bordure, texte...). Ce fichier traduit ces commandes en appels NanoVG
// réels.

#ifndef NOVA_CLAY_NANOVG_RENDERER_H
#define NOVA_CLAY_NANOVG_RENDERER_H

#include "clay.h"
#include <nanovg.h>

// Dessine l'ensemble des commandes produites par Clay_EndLayout() avec le
// contexte NanoVG donné. À appeler entre nvgBeginFrame() et nvgEndFrame().
void nova_render_clay_commands(NVGcontext* vg, Clay_RenderCommandArray commands);

#endif // NOVA_CLAY_NANOVG_RENDERER_H
