#! /usr/bin/env python
# -*- coding: iso-8859-15  -*-
"""This package provide tools for creating nt2 toolboxes templates

   Provides:
     archi.py:
           provides classes Sse and Vmx
     nt2_env.py:
           provides function nt2_dir
     files_utils.py
           provides functions mkdir, write, read and exist
     banner.py:
           provides class Banner
     headerguards.py:
           class Guard 
     nt2_base.py:
           class Nt2
     headerfiles.py
           provides class Headers that inherit from Banner and Guard
     toolbox.py
           provides class Toolbox that inherit from Nt2
     functors.py
           provides class Functor that inherit from Toolbox

   """

import nt2
from nt2 import nt2_logs

NT2_LOGS = nt2_logs.Nt2_logs()
