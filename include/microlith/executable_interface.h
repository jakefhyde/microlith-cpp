/*!
 * \file executable_interface.h
 * 
 * This file is part of the microlith library.
 * microlith is free software, licensed under the MIT License. A copy of the
 * license is provided with the library in the LICENSE file.
 * 
 */

#ifndef MICROLITH_EXECUTABLE_INTERFACE_H
#define MICROLITH_EXECUTABLE_INTERFACE_H

#include "microlith/services.h"
#include <unordered_set>

namespace microlith
{

class executable_interface
    : public service_interface<executable_interface>
{
public:
    virtual void start();
    virtual void stop();

}; // class executable_interface

} // namespace microlith

#endif // MICROLITH_EXECUTABLE_INTERFACE_H
