#include "nova_interaction.h"

NovaInteractionState nova_get_interaction_state(Clay_ElementId elementId, bool isDown, bool isDisabled)
{
    if (isDisabled)
        return NOVA_STATE_DISABLED;

    if (isDown && Clay_PointerOver(elementId))
        return NOVA_STATE_PRESSED;

    return NOVA_STATE_NORMAL;
}

Clay_Color nova_state_color(NovaInteractionState state, Clay_Color normalColor, Clay_Color pressedColor, Clay_Color disabledColor)
{
    switch (state)
    {
        case NOVA_STATE_PRESSED:  return pressedColor;
        case NOVA_STATE_DISABLED: return disabledColor;
        case NOVA_STATE_NORMAL:
        default:                  return normalColor;
    }
}
