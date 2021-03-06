/**************************************************************************
 **
 ** sngrep - SIP Messages flow viewer
 **
 ** Copyright (C) 2013,2014 Ivan Alonso (Kaian)
 ** Copyright (C) 2013,2014 Irontec SL. All rights reserved.
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
 * @file sip_attr.c
 * @author Ivan Alonso [aka Kaian] <kaian@irontec.com>
 *
 * @brief Source of functions defined in sip_attr.h
 *
 */
#include "config.h"
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include "option.h"
#include "sip_attr.h"
#include "util.h"

static sip_attr_hdr_t attrs[SIP_ATTR_COUNT] = {
    { SIP_ATTR_CALLINDEX,   "index",       "Idx",  "Call Index",    4 },
    { SIP_ATTR_SIPFROM,     "sipfrom",     NULL,   "SIP From",      25 },
    { SIP_ATTR_SIPFROMUSER, "sipfromuser", NULL,   "SIP From User", 20 },
    { SIP_ATTR_SIPTO,       "sipto",       NULL,   "SIP To",        25 },
    { SIP_ATTR_SIPTOUSER,   "siptouser",   NULL,   "SIP To User",   20 },
    { SIP_ATTR_SRC,         "src",         NULL,   "Source",        22 },
    { SIP_ATTR_DST,         "dst",         NULL,   "Destination",   22 },
    { SIP_ATTR_CALLID,      "callid",      NULL,   "Call-ID",       50 },
    { SIP_ATTR_XCALLID,     "xcallid",     NULL,   "X-Call-ID",     50 },
    { SIP_ATTR_DATE,        "date",        NULL,   "Date",          10 },
    { SIP_ATTR_TIME,        "time",        NULL,   "Time",          8 },
    { SIP_ATTR_METHOD,      "method",      NULL,   "Method",        15 },
    { SIP_ATTR_SDP_ADDRESS, "sdpaddress",  NULL,   "SDP Address",   22 },
    { SIP_ATTR_SDP_PORT,    "sdpport",     NULL,   "SDP Port",      5 },
    { SIP_ATTR_TRANSPORT,   "transport",   "Trans", "Transport",    3 },
    { SIP_ATTR_MSGCNT,      "msgcnt",      "Msgs", "Message Count", 5 },
    { SIP_ATTR_CALLSTATE,   "state",       NULL,   "Call State",    10 },
    { SIP_ATTR_CONVDUR,     "convdur",     "ConvDur", "Conversation Duration", 7 },
    { SIP_ATTR_TOTALDUR,    "totaldur",    "TotalDur", "Total Duration", 8 }
};

sip_attr_hdr_t *
sip_attr_get_header(enum sip_attr_id id)
{
    return &attrs[id];
}

const char *
sip_attr_get_description(enum sip_attr_id id)
{
    sip_attr_hdr_t *header;
    if ((header = sip_attr_get_header(id))) {
        return header->desc;
    }
    return NULL;
}

const char *
sip_attr_get_title(enum sip_attr_id id)
{
    sip_attr_hdr_t *header;
    if ((header = sip_attr_get_header(id))) {
        if (header->title)
            return header->title;
        return header->desc;
    }
    return NULL;
}

const char *
sip_attr_get_name(enum sip_attr_id id)
{
    sip_attr_hdr_t *header;
    if ((header = sip_attr_get_header(id))) {
        return header->name;
    }
    return NULL;
}

int
sip_attr_get_width(enum sip_attr_id id)
{
    sip_attr_hdr_t *header;
    if ((header = sip_attr_get_header(id))) {
        return header->dwidth;
    }
    return 0;
}

enum sip_attr_id
sip_attr_from_name(const char *name)
{
    int i;
    for (i = 0; i < SIP_ATTR_COUNT; i++) {
        if (!strcasecmp(name, attrs[i].name)) {
            return attrs[i].id;
        }
    }
    return -1;
}

sip_attr_t *
sip_attr_create(enum sip_attr_id id, const char *value)
{
    sip_attr_t *attr;
    // Create a new attribute struct and store it
    if (!(attr = sng_malloc(sizeof(sip_attr_t))))
        return NULL;
    attr->id = id;
    attr->value = strdup(value);
    return attr;
}

void
sip_attr_destroy(sip_attr_t *attr)
{
    sng_free(attr->value);
    sng_free(attr);
}

void
sip_attr_destroyer(void *attr)
{
    sip_attr_destroy((sip_attr_t*) attr);
}

void
sip_attr_set(vector_t *attrs, enum sip_attr_id id, const char *value)
{
    sip_attr_t *attr;
    // Remove previous value if any
    if ((attr = sip_attr_get(attrs, id)))
        vector_remove(attrs, attr);
    // Create a new attribute struct and store it
    vector_append(attrs, sip_attr_create(id, value));
}

sip_attr_t *
sip_attr_get(vector_t *attrs, enum sip_attr_id id)
{
    sip_attr_t *attr;
    vector_iter_t it = vector_iterator(attrs);
    while ((attr = vector_iterator_next(&it))) {
        if (attr->id == id)
            return attr;
    }
    return NULL;
}

const char *
sip_attr_get_value(vector_t *attrs, enum sip_attr_id id)
{
    sip_attr_t *attr = sip_attr_get(attrs, id);
    return (attr) ? attr->value : NULL;
}

