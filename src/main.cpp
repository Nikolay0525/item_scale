// item_scale: Kyubu port of SirLefti's Cube-World-Item-Scale-Mod (see its LICENSE).
//
// Every UI surface that draws an item goes through DrawItemModel (0x4758C0), a __thiscall with six stack arguments:
//     (renderer = ECX, screen_x, screen_y, ctx, scale, item, z_offset)
// The scale is multiplied by SCALE * REF_HEIGHT / window height, so items keep a constant size relative to the UI on
// any resolution. The original replayed the prologue by hand in a naked stub; here it is an ordinary function hook.
// The scale (0.87 by default) is an option: kyubu\config\item_scale.toml.
#include "../../common.hpp"

namespace {
using DrawFn = void(__fastcall*)(void* renderer, void* edx, float x, float y, void* ctx, float scale, void* item, float z);
DrawFn g_next = nullptr;
volatile float g_scale = 0.87f;
const float kRefHeight = 1080.0f;     // the render height at which g_scale applies as is
const uint32_t kHeightOffset = 0x120; // the render height inside the renderer

void __fastcall draw_item_model(void* renderer, void* edx, float x, float y, void* ctx, float scale, void* item, float z) {
    const int height = *reinterpret_cast<const int*>(static_cast<const uint8_t*>(renderer) + kHeightOffset);
    scale *= (height <= 0) ? g_scale : g_scale * kRefHeight / static_cast<float>(height);
    g_next(renderer, edx, x, y, ctx, scale, item, z);
}
}  // namespace

struct ItemScale {
    explicit ItemScale(kyubu::Mod& m) : mod(m) {
        g_scale = static_cast<float>(m.config_float("scale", 0.87));
        const uintptr_t site = classic::at(m, 0x758C0);
        static const uint8_t want[] = {0x55, 0x8B, 0xEC, 0x81, 0xEC, 0xA8, 0x01, 0x00, 0x00};
        if (!classic::expect(m, site, want, sizeof want, "item_scale")) return;
        KyubuId id = 0;
        const KyubuResult r = m.api()->hook_function(m.handle(), site, reinterpret_cast<void*>(&draw_item_model), 0,
                                                     reinterpret_cast<void**>(&g_next), &id);
        if (r != KY_OK) { m.error("item_scale: could not hook DrawItemModel (result %d)", static_cast<int>(r)); return; }
        m.info("item_scale: item models drawn at %.2f x (relative to a 1080p screen)", static_cast<double>(g_scale));
        m.on("config.changed", [this](KyubuEvent& ev) {
            auto* c = kyubu::Mod::data<KyubuConfigChangedData>(ev);
            if (c && c->mod && c->key && std::strcmp(c->mod, "item_scale") == 0 && std::strcmp(c->key, "scale") == 0)
                g_scale = static_cast<float>(mod.config_float("scale", 0.87));
        });
    }
    kyubu::Mod& mod;
};

KYUBU_MOD("item_scale", KY_SIDE_CLIENT, ItemScale)
