/****************************************************************************
 *
 * ftpfr.c
 *
 *   FreeType API for accessing PFR-specific data (body).
 *
 * Copyright (C) 2002-2022 by
 * David Turner, Robert Wilhelm, and Werner Lemberg.
 *
 * This file is part of the FreeType project, and may only be used,
 * modified, and distributed under the terms of the FreeType project
 * license, LICENSE.TXT.  By continuing to use, modify, or distribute
 * this file you indicate that you have read the license and
 * understand and accept it fully.
 *
 */

#include <freetype/internal/ftdebug.h>

#include <freetype/internal/ftobjs.h>
#include <freetype/internal/services/svpfr.h>


  /* check the format */
  static FT_TS_Service_PfrMetrics
  ft_pfr_check( FT_TS_Face  face )
  {
    FT_TS_Service_PfrMetrics  service = NULL;


    if ( face )
      FT_TS_FACE_LOOKUP_SERVICE( face, service, PFR_METRICS );

    return service;
  }


  /* documentation is in ftpfr.h */

  FT_TS_EXPORT_DEF( FT_TS_Error )
  FT_TS_Get_PFR_Metrics( FT_TS_Face    face,
                      FT_TS_UInt   *aoutline_resolution,
                      FT_TS_UInt   *ametrics_resolution,
                      FT_TS_Fixed  *ametrics_x_scale,
                      FT_TS_Fixed  *ametrics_y_scale )
  {
    FT_TS_Error               error = FT_TS_Err_Ok;
    FT_TS_Service_PfrMetrics  service;


    if ( !face )
      return FT_TS_THROW( Invalid_Face_Handle );

    service = ft_pfr_check( face );
    if ( service )
    {
      error = service->get_metrics( face,
                                    aoutline_resolution,
                                    ametrics_resolution,
                                    ametrics_x_scale,
                                    ametrics_y_scale );
    }
    else
    {
      FT_TS_Fixed  x_scale, y_scale;


      /* this is not a PFR font */
      if ( aoutline_resolution )
        *aoutline_resolution = face->units_per_EM;

      if ( ametrics_resolution )
        *ametrics_resolution = face->units_per_EM;

      x_scale = y_scale = 0x10000L;
      if ( face->size )
      {
        x_scale = face->size->metrics.x_scale;
        y_scale = face->size->metrics.y_scale;
      }

      if ( ametrics_x_scale )
        *ametrics_x_scale = x_scale;

      if ( ametrics_y_scale )
        *ametrics_y_scale = y_scale;

      error = FT_TS_THROW( Unknown_File_Format );
    }

    return error;
  }


  /* documentation is in ftpfr.h */

  FT_TS_EXPORT_DEF( FT_TS_Error )
  FT_TS_Get_PFR_Kerning( FT_TS_Face     face,
                      FT_TS_UInt     left,
                      FT_TS_UInt     right,
                      FT_TS_Vector  *avector )
  {
    FT_TS_Error               error;
    FT_TS_Service_PfrMetrics  service;


    if ( !face )
      return FT_TS_THROW( Invalid_Face_Handle );

    if ( !avector )
      return FT_TS_THROW( Invalid_Argument );

    service = ft_pfr_check( face );
    if ( service )
      error = service->get_kerning( face, left, right, avector );
    else
      error = FT_TS_Get_Kerning( face, left, right,
                              FT_TS_KERNING_UNSCALED, avector );

    return error;
  }


  /* documentation is in ftpfr.h */

  FT_TS_EXPORT_DEF( FT_TS_Error )
  FT_TS_Get_PFR_Advance( FT_TS_Face   face,
                      FT_TS_UInt   gindex,
                      FT_TS_Pos   *aadvance )
  {
    FT_TS_Error               error;
    FT_TS_Service_PfrMetrics  service;


    if ( !face )
      return FT_TS_THROW( Invalid_Face_Handle );

    if ( !aadvance )
      return FT_TS_THROW( Invalid_Argument );

    service = ft_pfr_check( face );
    if ( service )
      error = service->get_advance( face, gindex, aadvance );
    else
      /* XXX: TODO: PROVIDE ADVANCE-LOADING METHOD TO ALL FONT DRIVERS */
      error = FT_TS_THROW( Invalid_Argument );

    return error;
  }


/* END */