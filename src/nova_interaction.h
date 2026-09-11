// Nova — états d'interaction unifiés souris/tactile.
//
// Volontairement, il n'existe que 3 états : Normal, Pressed, Disabled.
// Pas de "Hover" : un doigt sur un écran tactile n'a pas d'équivalent à
// un survol de souris, donc aucune information indispensable à l'usage
// ne doit jamais dépendre du survol. La seule différence entre souris et
// tactile ici, c'est la provenance de la position/de l'état "enfoncé" —
// une fois combinés en (position, isDown), le reste du code ne fait plus
// la distinction.

#ifndef NOVA_INTERACTION_H
#define NOVA_INTERACTION_H

#include "clay.h"
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    NOVA_STATE_NORMAL,
    NOVA_STATE_PRESSED,
    NOVA_STATE_DISABLED
} NovaInteractionState;

// Détermine l'état d'un élément pour la frame courante.
// - elementId : le même identifiant que celui utilisé dans CLAY_ID() pour
//   l'élément concerné (le hash est déterministe, donc on peut le
//   recalculer ici sans risque de désynchronisation).
// - isDown : vrai si le bouton de la souris (ou le doigt) est actuellement
//   enfoncé, indépendamment de sa provenance.
// - isDisabled : prioritaire sur tout le reste, y compris un appui en cours.
NovaInteractionState nova_get_interaction_state(Clay_ElementId elementId, bool isDown, bool isDisabled);

// Petit utilitaire pour choisir une couleur selon l'état — évite de
// répéter le même switch partout où on construit une Clay_ElementDeclaration.
Clay_Color nova_state_color(NovaInteractionState state, Clay_Color normalColor, Clay_Color pressedColor, Clay_Color disabledColor);

#ifdef __cplusplus
}
#endif

#endif // NOVA_INTERACTION_H
