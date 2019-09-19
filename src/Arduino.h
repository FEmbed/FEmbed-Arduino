/*
 Arduino.h - Main include file for the Arduino SDK
 Copyright (c) 2005-2013 Arduino Team.  All right reserved.

 This library is free software; you can redistribute it and/or
 modify it under the terms of the GNU Lesser General Public
 License as published by the Free Software Foundation; either
 version 2.1 of the License, or (at your option) any later version.

 This library is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 Lesser General Public License for more details.

 You should have received a copy of the GNU Lesser General Public
 License along with this library; if not, write to the Free Software
 Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */

#ifndef Arduino_h
#define Arduino_h

#include <stdarg.h>
#include <stdint.h>

#if USE_FEMBED
#include <FEmbed.h>

#define millis fe_get_ticks
#endif

#if USE_ESPRESSIF8266
extern uint32_t sys_now(void);

#ifndef elog_i
#define elog_v ESP_LOGV
#define elog_d ESP_LOGD
#define elog_i ESP_LOGI
#define elog_w ESP_LOGW
#define elog_e ESP_LOGE
#define elog_a ESP_LOGA
#endif

#define log_a(...)       elog_a(LOG_TAG, __VA_ARGS__)
#define log_e(...)       elog_e(LOG_TAG, __VA_ARGS__)
#define log_w(...)       elog_w(LOG_TAG, __VA_ARGS__)
#define log_i(...)       elog_i(LOG_TAG, __VA_ARGS__)
#define log_d(...)       elog_d(LOG_TAG, __VA_ARGS__)
#define log_v(...)       elog_v(LOG_TAG, __VA_ARGS__)

#define millis sys_now
#endif

#define yeild portYIELD

#ifdef __cplusplus
extern "C" {
#endif

typedef bool boolean;

#ifdef __cplusplus
} // extern "C"
#endif

#endif //Arduino_h
