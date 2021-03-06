/*  Kore_template - simple templating engine for embedded Kore.io apps
 *
 *  (c) Copyright 2016 Dyne.org foundation, Amsterdam
 *      written and maintained by Denis Roio <jaromil@dyne.org>
 *      includes libcgi code by Jon Mayo found in the Public Domain
 *
 * This source code is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Public License as published
 * by the Free Software Foundation; either version 3 of the License,
 * or (at your option) any later version.
 *
 * This source code is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * Please refer to the GNU Public License for more details.
 *
 * You should have received a copy of the GNU Public License along with
 * this source code; if not, write to:
 * Free Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 *
 */

#ifndef TEMPLATE_H
#define TEMPLATE_H
#include "attr.h"

struct template {
	const char *cstr; /* constant string */
	struct entry *entry_list;
};

typedef struct template template_t;

typedef struct kore_buf kore_buf_t;

int template_load(const char *str, int len, template_t *tmpl);

void template_apply(template_t *t, attrlist_t al, kore_buf_t *out);

void template_free(template_t *t);

#endif
