Installation and Usage
======================

.. note::
    This library is developed with ``gcc-10.2`` and requires C++17. Other
    compiler/standard combinations are liable to work in the alpha stage,
    however they are not currently supported. This will likely be resolved
    with upcoming CI integration.

Dependencies
------------

Currently **microlith** requires **ctti** in order to extract service names
from types, however this requirement is tentative and subject to change in a
future release. **microlith** also requires **spdlog**, but can be configured
to disable this dependency and remove/override logging. See
`Configuration <configuration.html>`_ for more info.

Installation
------------

**microlith** supports a variety of installation methods, the following are
just a few examples:

Copy
^^^^

While **microlith** is not header only, it self-packages it's **ctti**
dependency and can be configured not to use **spdlog** using the
``MICROLITH_NO_SPDLOG`` cmake definition. At this point, **microlith** can be
added as a submodule into a project as long as a **cmake/3.16.3** or greater is
installed.

CMake
^^^^^

While **microlith** is primarily developed (and consumed) using Conan, it's
CMakeLists.txt files have been carefully crafted to allow alternatives build
systems and environments.

**spdlog** can be disabled by using the ``MICROLITH_NO_SPDLOG`` cmake
definition seen below

.. code:: cmake

    cmake -DMICROLITH_NO_SPDLOG=1
