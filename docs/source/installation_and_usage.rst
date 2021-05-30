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
to disable this dependency and remove/override logging.

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
definition seen below:

.. code:: shell

    cmake -DMICROLITH_NO_SPDLOG='ON'

**ctti** can be embedded within **microlith** in the event that it cannot be
found with ``find_package`` through a similar fashion:

.. code:: shell

    cmake -DMICROLITH_EMBED_CTTI='ON'

CMake + Conan
^^^^^^^^^^^^^

Conan is targeted primarily as it is currently the standard build system for
**microlith**.

.. note::

    The `official Conan documentation <https://docs.conan.io/>`_ is the primary
    resource for learning about Conan.

**microlith** releases are not currently hosted on the
`Conan-Center <https://conan.io/center/>`_, however that is the ultimate goal
once **microlith** leaves the alpha stage. Conan packages can be created using
the following steps:

1. Clone the repository

.. code:: shell

    git clone ssh://git@github.com:dragozir/microlith-cpp.git

2. Prepare the build directories

.. code:: shell

    cd microlith-cpp
    mkdir build && cd build

3. Build using Conan

.. code:: shell

    conan create ..

4. Add **microlith** as a requirement in your conanfile

.. code-block:: ini
    :caption: conanfile.txt

    [requires]
    microlith/0.0.5

.. code-block:: py
    :caption: conanfile.py

    requires = ("microlith/0.0.5",)
