#ifndef BN_SPRITE_ITEMS_IMABACK_H
#define BN_SPRITE_ITEMS_IMABACK_H

#include "bn_sprite_item.h"

//{{BLOCK(imaback_bn_gfx)

//======================================================================
//
//	imaback_bn_gfx, 32x32@4, 
//	+ palette 16 entries, not compressed
//	+ 16 tiles Metatiled by 4x4 not compressed
//	Total size: 32 + 512 = 544
//
//	Exported by Cearn's GBA Image Transmogrifier, v0.9.2
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_IMABACK_BN_GFX_H
#define GRIT_IMABACK_BN_GFX_H

#define imaback_bn_gfxTilesLen 512
extern const bn::tile imaback_bn_gfxTiles[16];

#define imaback_bn_gfxPalLen 32
extern const bn::color imaback_bn_gfxPal[16];

#endif // GRIT_IMABACK_BN_GFX_H

//}}BLOCK(imaback_bn_gfx)

namespace bn::sprite_items
{
    constexpr inline sprite_item imaback(sprite_shape_size(sprite_shape::SQUARE, sprite_size::BIG), 
            sprite_tiles_item(span<const tile>(imaback_bn_gfxTiles, 16), bpp_mode::BPP_4, compression_type::NONE, 1), 
            sprite_palette_item(span<const color>(imaback_bn_gfxPal, 16), bpp_mode::BPP_4, compression_type::NONE));
}

#endif

