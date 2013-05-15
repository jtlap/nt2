#!/usr/bin/python

import subprocess
import os

srcpath, srcfile = os.path.split(os.path.abspath(__file__))

with open('Testing/TAG', 'r') as f:
  lastBuild = f.readline()
  tag = "Testing/%s/Test.xml" % lastBuild[:-1]
  subprocess.call(["python", srcpath + "/bench.py", tag])
