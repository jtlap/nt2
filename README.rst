.. title:: Ryppl - Git-based Software Development / Testing / Installation


================================================================
A Git-based Software Development / Testing / Installation System
================================================================

.. contents:: Index

-----------
About Ryppl
-----------

Think of Ryppl as a `Git <http://git-scm.com>`_-based `package
management <http://en.wikipedia.org/wiki/Package_management_system>`_
and testing system designed to accomodate both end-users *and*
developers.  Unlike a traditional package manager, which delivers
binaries and/or a source snapshot, when ryppl downloads a package, it
gives you a clone of a Git repository, with that package's entire
development history.

--------------------
Support This Project
--------------------

Most contributors are giving their time to this project for free.  If
you make a donation to Ryppl, it will be used to pay for the time of
those who can't afford to be quite so generous.  We need their help,
and they need to pay the bills, so please consider `making a donation
<http://pledgie.com/campaigns/9508>`_.  Thanks!

-------------
Documentation
-------------

User Documentation
::::::::::::::::::

For emergent user-level HTML documentation, see http://www.ryppl.org

Developer Documentation
:::::::::::::::::::::::

This rest of this document is a getting-started guide for Ryppl
developers - the people who will be checking out from this repository
and are working on development of the ryppl project.  

...............
Things To Learn
...............

* First, get a handle on `the technologies
  <http://www.ryppl.org/technology.html>`_ we're using.

* Then, take a look at `The Hitchhiker's Guide to Packaging
  <http://guide.python-distribute.org/>`_, which describes some of the
  Python packaging and distribution tools we're exploiting.  You can
  find Git mirrors of the essential codebases `at Github
  <http://github.com/ryppl>`_.

.................
Building The Docs
.................

.. Note:: right now you can't get a complete build of the docs under
   Cygwin_ because there's no GraphViz_ binary in the Cygwin repo, and
   building GraphViz_ under Cygwin hangs at some point.  Cygwin users
   can use a `native Win32 installation
   <http://graphviz.org/Download_windows.php>`_ of GraphViz, but it
   will warn you that it can't generate the image because make will be
   passing it a Cygwin-style path.  That's ok if you just care about
   the HTML parts.  Otherwise, just use the windows-native tools as
   described below.

   A front-end path-converting wrapper might work here if someone is
   really committed to getting a *complete* doc build under Cygwin.

.. _Cygwin: http://cygwin.com
.. _GraphViz: http://graphviz.org

Setting up prerequisites
========================

1. **Get Python 2.x**.  If your OS doesn't have a builtin package
   manager that can install Python for you, get it from `Python.org
   <http://python.org/download/>`_.

2. **Install Sphinx**.  Get it from your OS package manager (usually
   listed as ``python-sphinx`` or ``py-sphinx``) if you can, and skip
   to step 5.  Otherwise, use setuptools as detailed below

3. **Install setuptools** for installing Python packages.  Your
   package manager may have it, or you may be able to get a prebuilt
   package from `PyPi <http://pypi.python.org/pypi/setuptools>`_, but
   the most universal way is to `download ez_setup.py
   <http://peak.telecommunity.com/dist/ez_setup.py>`_ and run it with
   Python::

     % python ez_setup.py

   On windows, ``easy_install``\ ed executables don't go in your ``PATH`` by
   default, so you'll need to add something like ``c:\Python26\Scripts``
   to your path to make the rest of this work.

4. **Use setuptools to get Sphinx**.  The servers were really slow
   last time I checked; expect this to take a while (add ``-v`` if
   you're easily bored).

     % easy_install sphinx

5. **make sure** ``sphinx-build`` is in your path:

     % sphinx-build --help

6. **Install GNU Make**.  If you're on native Windows, to get a compatible
   GNU Make you should install the `MSYS Base System
   <http://sourceforge.net/projects/mingw/files/MSYS%20Base%20System/>`_.
   At the time of this writing, the latest with an executable
   installer is `version 1.0.11
   <http://sourceforge.net/projects/mingw/files/MSYS%20Base%20System/msys-1.0.11/MSYS-1.0.11.exe/download>`_.
   Make sure your PATH includes the path to the `make` executable::

     % make -v

   .. Note:: if you're on native windows (or MSYS) and the output ends with the line::

        This program built for i686-pc-cygwin

     or::

        This program built for i386-pc-mingw32

   Then you've done something wrong.  The platform string should be `i386-pc-msys`.

7. **Install** GraphViz_.  Use your native package manager or get it
   from the GraphViz `download page <http://graphviz.org/Download.php>`_

8. **Install** Git_.  On Windows, this means MSysGit_.

.. _Git: http://git-scm.com
.. _MSysGit: http://code.google.com/p/msysgit/


Running the Build
=================

Now the easy part.  To *finally build* the documentation, enter the
``doc/`` subdirectory and issue the command::

  $ make html

The results will be generated in the ``build/html/`` subdirectory of
this project.  If you don't like building in your source tree, you can
change the parent of the generated ``html/`` directory by setting the
make (or environment) variable ``BUILDDIR``::

  $ make BUILDDIR=/tmp/ryppl-build

.. _Python: http://python.org
.. _Sphinx: http://sphinx.pocoo.org/
.. _GNU Make: http://www.gnu.org/software/make/
.. _GraphViz: http://graphviz.org


................
Additional Notes
................

For more developer notes, please see the `Ryppl Wiki
<http://wiki.github.com/ryppl/ryppl/>`_.

