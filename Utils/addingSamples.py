#!/afs/cern.ch/cms/slc5_amd64_gcc434/cms/cmssw/CMSSW_4_2_8/external/slc5_amd64_gcc434/bin/python2.6

import ROOT
from array import array


def getTree( infile ):
    infile.cd()
    for key in ROOT.gDirectory.GetListOfKeys():
        obj = key.ReadObj()
        print obj.GetName()
        if obj.GetName() == 'tree':
            return obj;

def getEventsArray( tree, lheBin ):
    N={}
    for bin in lheBin:
        print bin
        #        N[bin] = tree.Draw('>>'+bin,bin,'goff')
        N[bin] = 1.*tree.GetEntries(bin)
    return N

fileList = ['DYJets.root',
            'DYJetsPt70To100.root']


lheBin = ['lheV_pt < 50',
          'lheV_pt > 50 & lheV_pt < 70',
          'lheV_pt > 70 & lheV_pt < 100',
          'lheV_pt > 100']

eventList = {}
num = {}
for file in fileList:
    print file
    infile = ROOT.TFile(file,"READ")
    tree = getTree(infile)
    num[file] = getEventsArray( tree, lheBin )
    print num[file]

print num
#print num[fileList[1]]

#total -> total numer of events in each lheBin
print 'Calculating total'
total = {}
weight= {}
for file in fileList:
    for bin in lheBin:
        total[bin] = 0.
        for file in fileList:
            total[bin] = total[bin] + num[file][bin]
        #print total[bin]
        print bin
        if total[bin] > 0.:
            weight[bin] = num[fileList[0]][bin]/total[bin]
            print weight[bin]
        else:
            weight[bin] = 1.
    #print num[file][bin]
    
#now add the branch with the weight normalized to the inclusive
for file in fileList:
    infile = ROOT.TFile(file,"READ")
    outfile = ROOT.TFile('out'+file,'RECREATE')
    infile.cd()
#     obj = ROOT.TObject
#     for key in ROOT.gDirectory.GetListOfKeys():
#         infile.cd()
#         obj = key.ReadObj()
#         print obj.GetName()
#         if obj.GetName() == 'tree' or file != fileList[0]: #Count is saved only for the inclusive sample
#             continue
#         outfile.cd()
#         print key.GetName()
#         obj.Write(key.GetName())            

    infile.cd()
    tree = infile.Get('tree')
    outfile.cd()
    newtree = tree.CloneTree(0)
    lheWeight = array('f',[0])
    newtree.Branch('lheWeight',lheWeight,'lheWeight/F')
#     for ev in tree:
#         if ev.lheV_pt < 50:
#             lheWeight[0] = weight[lheBin[0]]
#         elif ev.lheV_pt > 50 and ev.lheV_pt < 70:
#             lheWeight[0] = weight[lheBin[1]]
#         elif ev.lheV_pt > 70 and ev.lheV_pt < 100:
#             lheWeight[0] = weight[lheBin[2]]
#         elif ev.lheV_pt > 100:
#             lheWeight[0] = weight[lheBin[3]]
#         else:
#             lheWeight[0] = 1.
    nEntries = tree.GetEntries()
    for entry in range(0,nEntries):
        tree.GetEntry(entry)
        if tree.lheV_pt < 50:
            lheWeight[0] = weight[lheBin[0]]
        elif tree.lheV_pt > 50 and tree.lheV_pt < 70:
            lheWeight[0] = weight[lheBin[1]]
        elif tree.lheV_pt > 70 and tree.lheV_pt < 100:
            lheWeight[0] = weight[lheBin[2]]
        elif tree.lheV_pt > 100:
            lheWeight[0] = weight[lheBin[3]]
        else:
            lheWeight[0] = 1.

            
        newtree.Fill()
                   
    newtree.AutoSave()
    outfile.Write()
    outfile.Close()

