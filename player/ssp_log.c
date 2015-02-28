// Copyright © 2011-2015 Yanick Castonguay
//
// This file is part of Sessions, a music player for musicians.
//
// Sessions is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// Sessions is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with Sessions. If not, see <http://www.gnu.org/licenses/>.

#include <stdlib.h>
#include <stdarg.h>
#include "ssp_log.h"

static player_log_cb log_cb = NULL;
static void* log_cb_user = NULL;

void log_setCallback(player_log_cb cb, void* user) {
    log_cb = cb;
    log_cb_user = user;
}

void log_removeCallback() {
    log_cb = NULL;
    log_cb_user = NULL;
}

void log_text(const char* str) {
    if(log_cb != NULL) {
        log_cb(log_cb_user, str);
    }
}

void log_textf(const char* format, ...) {
    va_list ap;
    va_start(ap, format);
    char result[1024];
    vsnprintf(result, 1024, format, ap);

    if(log_cb != NULL) {
        log_cb(log_cb_user, result);
    }

    va_end(ap);
}