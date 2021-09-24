/*
 * This file is part of Zenroom (https://zenroom.org)
 * 
 * Copyright (C) 2017-2021 Dyne.org foundation
 * designed, written and maintained by Denis Roio <jaromil@dyne.org>
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License v3.0
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 * 
 * Along with this program you should have received a copy of the
 * GNU Affero General Public License v3.0
 * If not, see http://www.gnu.org/licenses/agpl.txt
 * 
 * Last modified by Denis Roio
 * on Wednesday, 22nd September 2021
 */

#ifndef __ZEN_ERROR_H__
#define __ZEN_ERROR_H__

#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <lua.h>

#include <maxvalues.h>

int lerror(lua_State *L, const char *fmt, ...);
// int zenroom_traceback(lua_State *L);

void notice(lua_State *L, const char *format, ...);
void func(void *L, const char *format, ...);
void error(lua_State *L, const char *format, ...);
void act(lua_State *L, const char *format, ...);
void warning(lua_State *L, const char *format, ...);

#define ERROR() error(0, "Error in %s",__func__)
#define SAFE(x) if(!x) lerror(L, "NULL variable in %s",__func__)

// useful for debugging
#if DEBUG == 1
#define HERE() func(0, "-> %s()",__func__)
#define HEREs(s) func(0, "-> %s(%s)",__func__,s)
#define HEREp(p) func(0, "-> %s(%p)",__func__,p)
#define HEREn(n) func(0, "-> %s(%i)",__func__,n)
#define HEREc(c) func(0, "-> %s(%c)",__func__,c)
#define HEREoct(o) \
	func(0, "-> %s - octet %p (%i/%i)",__func__,o->val,o->len,o->max)
#define HEREecdh(e) \
	func(0, "--> %s - ecdh %p\n\tcurve[%s] type[%s]\n\t fieldsize[%i] hash[%i]\n\tpubkey[%p(%i/%i)] publen[%i]\n\tseckey[%p(%i/%i)] seclen[%i]",__func__, e, e->curve, e->type, e->fieldsize, e->hash, e->pubkey, e->pubkey?e->pubkey->len:0x0, e->pubkey?e->pubkey->max:0x0, e->publen, e->seckey, e->seckey?e->seckey->len:0x0, e->seckey?e->seckey->max:0x0, e->seclen)
#else
#define HERE() (void)__func__
#define HEREs(s) (void)__func__
#define HEREp(s) (void)__func__
#define HEREn(s) (void)__func__
#define HEREoct(o) (void)__func__
#define HEREecdh(o) (void)__func__
#endif

#endif
