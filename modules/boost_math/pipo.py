import os
import shutil
from os.path import join, getsize
for root, dirs, files in os.walk('./'):
    for name in files :
        print join(root, name)
        n =  join(root, name)
##        shutil.move(n,n+'z')
        shutil.move(n,n[:-1])
