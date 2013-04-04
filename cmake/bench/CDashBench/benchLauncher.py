import subprocess

with open('Testing/TAG', 'r') as f:
  lastBuild = f.readline()
  tag = "Testing/%s/Test.xml" % lastBuild[:-1]
  subprocess.call(["python", "CDashBench/bench.py", tag])
