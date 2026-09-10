#include "clay_nanovg_renderer.h"

static NVGcolor nova_clay_to_nvg_color(Clay_Color c)
{
    return nvgRGBA(
        (unsigned char)c.r,
        (unsigned char)c.g,
        (unsigned char)c.b,
        (unsigned char)c.a
    );
}

void nova_render_clay_commands(NVGcontext* vg, Clay_RenderCommandArray commands)
{
    for (int32_t i = 0; i < commands.length; i++)
    {
        Clay_RenderCommand* cmd = Clay_RenderCommandArray_Get(&commands, i);
        Clay_BoundingBox box = cmd->boundingBox;

        switch (cmd->commandType)
        {
            case CLAY_RENDER_COMMAND_TYPE_RECTANGLE:
            {
                Clay_RectangleRenderData* data = &cmd->renderData.rectangle;
                float radius = data->cornerRadius.topLeft; // même rayon sur les 4 coins pour l'instant

                nvgBeginPath(vg);
                if (radius > 0.0f)
                    nvgRoundedRect(vg, box.x, box.y, box.width, box.height, radius);
                else
                    nvgRect(vg, box.x, box.y, box.width, box.height);
                nvgFillColor(vg, nova_clay_to_nvg_color(data->backgroundColor));
                nvgFill(vg);
                break;
            }

            case CLAY_RENDER_COMMAND_TYPE_BORDER:
            {
                Clay_BorderRenderData* data = &cmd->renderData.border;
                float radius = data->cornerRadius.topLeft;
                float w = (float)data->width.left; // épaisseur uniforme pour l'instant

                nvgBeginPath(vg);
                if (radius > 0.0f)
                    nvgRoundedRect(vg, box.x + w * 0.5f, box.y + w * 0.5f, box.width - w, box.height - w, radius);
                else
                    nvgRect(vg, box.x + w * 0.5f, box.y + w * 0.5f, box.width - w, box.height - w);
                nvgStrokeColor(vg, nova_clay_to_nvg_color(data->color));
                nvgStrokeWidth(vg, w);
                nvgStroke(vg);
                break;
            }

            case CLAY_RENDER_COMMAND_TYPE_SCISSOR_START:
            {
                nvgSave(vg);
                nvgScissor(vg, box.x, box.y, box.width, box.height);
                break;
            }

            case CLAY_RENDER_COMMAND_TYPE_SCISSOR_END:
            {
                nvgRestore(vg);
                break;
            }

            // Texte et images : pas encore branchés à cette étape (il nous
            // faudra une police chargée dans NanoVG). On les ignore pour
            // l'instant plutôt que de planter.
            case CLAY_RENDER_COMMAND_TYPE_TEXT:
            case CLAY_RENDER_COMMAND_TYPE_IMAGE:
            case CLAY_RENDER_COMMAND_TYPE_CUSTOM:
            case CLAY_RENDER_COMMAND_TYPE_NONE:
            default:
                break;
        }
    }
}
