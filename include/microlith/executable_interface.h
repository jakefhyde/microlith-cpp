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
 * \file executable_interface.h
 *
 * This file is part of the microlith library.
 * microlith is free software, licensed under the MIT License. A copy of the
 * license is provided with the library in the LICENSE file.
 *
 */

#ifndef INCLUDE_MICROLITH_EXECUTABLE_INTERFACE_H_
#define INCLUDE_MICROLITH_EXECUTABLE_INTERFACE_H_

#include <unordered_set>

#include "microlith/services.h"

namespace microlith {

template <std::size_t apiVersion>
class executable_interface;

template <>
class executable_interface<0>
    : public service_interface<executable_interface<0>> {
 public:
  virtual void start();
  virtual void stop();
};  // class executable_interface

}  // namespace microlith

#endif  // INCLUDE_MICROLITH_EXECUTABLE_INTERFACE_H_
