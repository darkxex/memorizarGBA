#ifndef BN_SPRITE_ITEMS_CAVEMAN_H
#define BN_SPRITE_ITEMS_CAVEMAN_H

#include "bn_sprite_item.h"

//{{BLOCK(caveman_bn_gfx)

//======================================================================
//
//	caveman_bn_gfx, 64x64@4, 
//	+ palette 16 entries, not compressed
//	+ 64 tiles Metatiled by 8x8 not compressed
//	Total size: 32 + 2048 = 2080
//
//	Exported by Cearn's GBA Image Transmogrifier, v0.9.2
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_CAVEMAN_BN_GFX_H
#define GRIT_CAVEMAN_BN_GFX_H

#define caveman_bn_gfxTilesLen 2048
extern const bn::tile caveman_bn_gfxTiles[64];

#define caveman_bn_gfxPalLen 32
extern const bn::color caveman_bn_gfxPal[16];

#endif // GRIT_CAVEMAN_BN_GFX_H

//}}BLOCK(caveman_bn_gfx)

namespace bn::sprite_items
{
    constexpr inline sprite_item caveman(sprite_shape_size(sprite_shape::SQUARE, sprite_size::HUGE), 
            sprite_tiles_item(span<const tile>(caveman_bn_gfxTiles, 64), bpp_mode::BPP_4, compression_type::NONE, 1), 
            sprite_palette_item(span<const color>(caveman_bn_gfxPal, 16), bpp_mode::BPP_4, compression_type::NONE));
}

#endif

