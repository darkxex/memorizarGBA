#ifndef BN_SPRITE_ITEMS_GREEN_SPRITE_H
#define BN_SPRITE_ITEMS_GREEN_SPRITE_H

#include "bn_sprite_item.h"

//{{BLOCK(green_sprite_bn_gfx)

//======================================================================
//
//	green_sprite_bn_gfx, 64x64@4, 
//	+ palette 16 entries, not compressed
//	+ 64 tiles Metatiled by 8x8 not compressed
//	Total size: 32 + 2048 = 2080
//
//	Exported by Cearn's GBA Image Transmogrifier, v0.9.2
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_GREEN_SPRITE_BN_GFX_H
#define GRIT_GREEN_SPRITE_BN_GFX_H

#define green_sprite_bn_gfxTilesLen 2048
extern const bn::tile green_sprite_bn_gfxTiles[64];

#define green_sprite_bn_gfxPalLen 32
extern const bn::color green_sprite_bn_gfxPal[16];

#endif // GRIT_GREEN_SPRITE_BN_GFX_H

//}}BLOCK(green_sprite_bn_gfx)

namespace bn::sprite_items
{
    constexpr inline sprite_item green_sprite(sprite_shape_size(sprite_shape::SQUARE, sprite_size::HUGE), 
            sprite_tiles_item(span<const tile>(green_sprite_bn_gfxTiles, 64), bpp_mode::BPP_4, compression_type::NONE, 1), 
            sprite_palette_item(span<const color>(green_sprite_bn_gfxPal, 16), bpp_mode::BPP_4, compression_type::NONE));
}

#endif

