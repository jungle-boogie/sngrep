/**************************************************************************
 **
 ** sngrep - SIP Messages flow viewer
 **
 ** Copyright (C) 2013-2015 Ivan Alonso (Kaian)
 ** Copyright (C) 2013-2015 Irontec SL. All rights reserved.
 **
 ** This program is free software: you can redistribute it and/or modify
 ** it under the terms of the GNU General Public License as published by
 ** the Free Software Foundation, either version 3 of the License, or
 ** (at your option) any later version.
 **
 ** This program is distributed in the hope that it will be useful,
 ** but WITHOUT ANY WARRANTY; without even the implied warranty of
 ** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 ** GNU General Public License for more details.
 **
 ** You should have received a copy of the GNU General Public License
 ** along with this program.  If not, see <http://www.gnu.org/licenses/>.
 **
 ****************************************************************************/
/**
 * @file media.h
 * @author Ivan Alonso [aka Kaian] <kaian@irontec.com>
 *
 * @brief Functions to manage call media
 *
 */

#ifndef __SNGREP_MEDIA_H_
#define __SNGREP_MEDIA_H_

#include "config.h"
#include <sys/types.h>
#include "capture.h"

//! Shorter declaration of sdp_media structure
typedef struct sdp_media sdp_media_t;
//! Shorter declaration of sdp_media_fmt structure
typedef struct sdp_media_fmt sdp_media_fmt_t;

struct sip_msg;
struct sip_call;

struct sdp_media_fmt {
    u_int id;
    char format[50];
};


struct sdp_media {
    //! SDP Addresses information
    char address[ADDRESSLEN];
    u_short port;
    char type[10];
    u_int fmtcode;
    //! List of described formats in this media
    vector_t *formats;
    //! Message with this SDP content
    struct sip_msg *msg;
};

sdp_media_t *
media_create(struct sip_msg *msg);

void
media_destroyer(void *item);

void
media_set_port(sdp_media_t *media, u_short port);

void
media_set_type(sdp_media_t *media, const char *type);

void
media_set_address(sdp_media_t *media, const char *address);

void
media_set_prefered_format(sdp_media_t *media, u_int code);

void
media_add_format(sdp_media_t *media, u_int code, const char *format);

const char *
media_get_address(sdp_media_t *media);

u_short
media_get_port(sdp_media_t *media);

const char *
media_get_type(sdp_media_t *media);

const char *
media_get_format(sdp_media_t *media, u_int code);

const char *
media_get_prefered_format(sdp_media_t *media);

int
media_get_format_code(sdp_media_t *media);

#endif /* __SNGREP_MEDIA_H_ */
