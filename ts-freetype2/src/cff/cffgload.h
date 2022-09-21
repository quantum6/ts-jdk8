/****************************************************************************
 *
 * cffgload.h
 *
 *   OpenType Glyph Loader (specification).
 *
 * Copyright (C) 1996-2022 by
 * David Turner, Robert Wilhelm, and Werner Lemberg.
 *
 * This file is part of the FreeType project, and may only be used,
 * modified, and distributed under the terms of the FreeType project
 * license, LICENSE.TXT.  By continuing to use, modify, or distribute
 * this file you indicate that you have read the license and
 * understand and accept it fully.
 *
 */


#ifndef CFFGLOAD_H_
#define CFFGLOAD_H_


#include <freetype/freetype.h>
#include <freetype/internal/cffotypes.h>


FT_TS_BEGIN_HEADER

  FT_TS_LOCAL( FT_TS_Error )
  cff_get_glyph_data( TT_Face    face,
                      FT_TS_UInt    glyph_index,
                      FT_TS_Byte**  pointer,
                      FT_TS_ULong*  length );
  FT_TS_LOCAL( void )
  cff_free_glyph_data( TT_Face    face,
                       FT_TS_Byte**  pointer,
                       FT_TS_ULong   length );


#if 0  /* unused until we support pure CFF fonts */

  /* Compute the maximum advance width of a font through quick parsing */
  FT_TS_LOCAL( FT_TS_Error )
  cff_compute_max_advance( TT_Face  face,
                           FT_TS_Int*  max_advance );

#endif /* 0 */


  FT_TS_LOCAL( FT_TS_Error )
  cff_slot_load( CFF_GlyphSlot  glyph,
                 CFF_Size       size,
                 FT_TS_UInt        glyph_index,
                 FT_TS_Int32       load_flags );


FT_TS_END_HEADER

#endif /* CFFGLOAD_H_ */


/* END */