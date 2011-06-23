Getting Started
===============
The following section will guide you through the downloading, building, installing and testing |nt2|.

Requirements
^^^^^^^^^^^^
Installing and using |nt2| requires additional software dependencies. We will take for
granted that regular tools like an archive manager, text editor and such other softwares
are readily available to the user.

Supported Compiler and Operating System
---------------------------------------
|nt2| currently supports the following operating systems:

* Linux
* Mac OS X
* Microsoft Windows

On these systems, the following compilers are supported:

  +--------------------+------------------------------+
  | Operating Systems  | Supported Compilers          |
  +====================+==============================+
  | Linux              | ``g++`` 4.3 or above,        |
  |                    | ``icc`` 11.0 or above        |
  +--------------------+------------------------------+
  | Microsoft Windows  | ``g++`` 4.3 or above,        |
  |                    | ``icc`` 11.0 or above,       |
  |                    | ``Visual Studio`` 9 or above |
  +--------------------+------------------------------+
  | Mac OS X           | ``g++`` 4.? or above         |
  +--------------------+------------------------------+

Build System
------------
|nt2| depends on ``CMake`` for its build system. ``CMake`` `can be downloaded
from Kitware webpage <http://www.cmake.org/cmake/resources/software.html>`_ and
`easily installed <http://www.cmake.org/cmake/help/install.html>`_.
Unix or Linux users can also grab the proper version of ``CMake`` for their system through
their usual package manager.

For optimal use, |nt2| recommends ``CMake`` **version 2.6 or superior**.

Other library
-------------
|nt2| depends heavily on the `Boost library <http://www.boost.org>`_ which can be
`downloaded here <http://sourceforge.net/projects/boost/files/boost/>`_ and
`installed following these directives <http://www.boost.org/doc/libs/1_44_0/more/getting_started/index.html>`_.
On some system, you can install the latest ``Boost`` library using your usual package manager
or by `downloading a binary installer <http://www.boostpro.com/download/>`_.

Current required **version is 1.44 or superior**. If you want to contribute to |nt2|
as a developer, you may want to use the ``Boost`` SVN trunk version.

Download
^^^^^^^^^
You can choose to either use a stable release of |nt2| or to use the current development
snapshot hosted on `GitHub <http://github.com>`_ .

Getting the latest stable release
---------------------------------
Latest release tar ball can be fetched `from our GitHub download page <https://github.com/MetaScale/nt2/downloads>`_
Once downloaded, uncompress the file using your archive manager of choice.

Getting the latest develoment snapshot
--------------------------------------
If you like to live on the edge, you can clone the main |nt2|
repository from `GitHub <http://github.com>`_ via the following command:

.. code-block:: bash

  git clone git@github.com:MetaScale/nt2.git

or by `creating a Fork in your GitHub account <http://help.github.com/forking/>`_.
You can play it safe by staying in the ``master`` branch. Other branch may contain
experimental code or work for which we can't garantee the state of completeness.

Build and Install
^^^^^^^^^^^^^^^^^
At this point, we consider that the user has a valid OS/compiler version, installed ``CMake``
and ``Boost``. After downloading or cloning the |nt2| source files, you should end up with a folder
named ''nt2'' in which the following file structure can be found:

.. code-block:: bash

  . nt2
    |-- benchmark
    |-- cmake
    |-- CMakeLists.txt
    |-- doc
    |-- examples
    |-- include
    |   `-- nt2
    |-- LICENSE
    |-- README.rst
    |-- script
    |-- src
    `-- unit

From now on, we'll consider you're located into the ``nt2/`` folder.

Preparing the build system
--------------------------
|nt2| uses a ``CMake`` based build system. The first step is then to generate the build
scripts from the ``CMakeList.txt`` file. To do so, you can:

* Use your platform default generator:

  .. code-block:: bash

    cmake .

  This command will generate scripts for you system native build system.

* Specify a custom generator:

  .. code-block:: bash

    cmake -G "your generator"

  where ``your generator`` has to be replaced by the ``cmake`` identifier of your
  preferred build system. For example, building a Makefile on a Linux machine is done via:

  .. code-block:: bash

    cmake -G "Unix Makefiles"

  Additional informations about generator are `available on the KitWare wiki <http://www.cmake.org/Wiki/CMake_Generator_Specific_Information>`_.

* Use the CMake GUI Wizard of your system to configure and generate the build system.
  For Windows users, this is usually easier than to play with the command line ``cmake``.

The invocation of ``cmake`` will try to detect various aspect of your system and generate a proper
configuration script for |nt2|. At the end of the process, a message indicating the success of the
build system generation is displayed along with build instructions.

Building the library
--------------------
Once the ``cmake`` completed its task, you should find a proper build system in the current
folder. Depending on your choice, you may have to:

* call ``make install`` to build the library and install it to its default location.
* Open the IDE-specific project and build the ``install`` target.

Testing the library
^^^^^^^^^^^^^^^^^^^

