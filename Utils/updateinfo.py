#!/usr/bin/env python
from samplesinfo import sample
import pickle
import sys

path=sys.argv[1]
#path='/scratch/nov10_inclusive/Z'
type=sys.argv[2]
#type='BKG'
attribute=sys.argv[3]
#attribute='split'
newvalue=sys.argv[4]
#newvalue=0.5


infofile = open(path+'/samples.info','r')
info = pickle.load(infofile)
infofile.close()

for job in info:
    if job.type == type:
        print '\t - %s' %(job.name)
        setattr(job,attribute,newvalue)

infofile = open(path+'/samples.info','w')
pickle.dump(info,infofile)
infofile.close()
