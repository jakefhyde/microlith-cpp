/*!
 * MIT License
 *
 * Copyright (c) 2021 Dragozir
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 * \file detail/log.h
 *
 */

#ifndef INCLUDE_MICROLITH_DETAIL_LOG_H_
#define INCLUDE_MICROLITH_DETAIL_LOG_H_

#ifndef MICROLITH_NO_SPDLOG
#include <spdlog/spdlog.h>
#define MICROLITH_TRACE(...) SPDLOG_TRACE(__VA_ARGS__)
#define MICROLITH_DEBUG(...) SPDLOG_DEBUG(__VA_ARGS__)
#define MICROLITH_INFO(...) SPDLOG_INFO(__VA_ARGS__)
#define MICROLITH_WARN(...) SPDLOG_WARN(__VA_ARGS__)
#define MICROLITH_ERROR(...) SPDLOG_ERROR(__VA_ARGS__)
#define MICROLITH_CRITICAL(...) SPDLOG_CRITICAL(__VA_ARGS__)
#define MICROLITH_OFF(...) SPDLOG_OFF(__VA_ARGS__)
#else
#define MICROLITH_TRACE(...)
#define MICROLITH_DEBUG(...)
#define MICROLITH_INFO(...)
#define MICROLITH_WARN(...)
#define MICROLITH_ERROR(...)
#define MICROLITH_CRITICAL(...)
#define MICROLITH_OFF(...)
#endif

#endif  // INCLUDE_MICROLITH_DETAIL_LOG_H_
