#ifndef BN_SPRITE_ITEMS_IMA_H
#define BN_SPRITE_ITEMS_IMA_H

#include "bn_sprite_item.h"

//{{BLOCK(ima_bn_gfx)

//======================================================================
//
//	ima_bn_gfx, 32x32@4, 
//	+ palette 16 entries, not compressed
//	+ 16 tiles Metatiled by 4x4 not compressed
//	Total size: 32 + 512 = 544
//
//	Exported by Cearn's GBA Image Transmogrifier, v0.9.2
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_IMA_BN_GFX_H
#define GRIT_IMA_BN_GFX_H

#define ima_bn_gfxTilesLen 512
extern const bn::tile ima_bn_gfxTiles[16];

#define ima_bn_gfxPalLen 32
extern const bn::color ima_bn_gfxPal[16];

#endif // GRIT_IMA_BN_GFX_H

//}}BLOCK(ima_bn_gfx)

namespace bn::sprite_items
{
    constexpr inline sprite_item ima(sprite_shape_size(sprite_shape::SQUARE, sprite_size::BIG), 
            sprite_tiles_item(span<const tile>(ima_bn_gfxTiles, 16), bpp_mode::BPP_4, compression_type::NONE, 1), 
            sprite_palette_item(span<const color>(ima_bn_gfxPal, 16), bpp_mode::BPP_4, compression_type::NONE));
}

#endif

