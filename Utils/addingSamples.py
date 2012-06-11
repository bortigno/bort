#!/usr/bin/python2.6

##!/afs/cern.ch/cms/slc5_amd64_gcc434/cms/cmssw/CMSSW_4_2_8/external/slc5_amd64_gcc434/bin/python2.6

import ROOT
from array import array


def getObj( infile, name ):
    infile.cd()
    for key in ROOT.gDirectory.GetListOfKeys():
        obj = key.ReadObj()
        print obj.GetName()
        if obj.GetName() == name:
            return obj;
    
def getTotal( bin, fileList ):
    total = 0.
    for i in range(0,len(fileList)):
        total = total + fileList[i][2][bin]
    return total
    
inc = []
pt70To100 = []
fileList = [ ['ZllH.May23.DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola.root' , 2950., inc ] ,
             ['ZllH.May23.DYJetsToLL_PtZ-100_TuneZ2_7TeV-madgraph-tauola.root' , 52.31, pt70To100 ] ]

#look here https://www.evernote.com/shard/s186/sh/8ffc289c-ede2-4e09-83ba-1e1981f13617/4d5aac2f42a9fd480dc66f9303c1c217

lheBin = ['lheV_pt < 50',
          'lheV_pt > 50 & lheV_pt < 70',
          'lheV_pt > 70 & lheV_pt < 100',
          'lheV_pt > 100']

eventList = {}
num = []
for file in fileList:
    print file[0]
    infile = ROOT.TFile(file[0],"READ")
    tree = getObj(infile, 'tree')
    for bin in lheBin:
        print bin
        file[2].append( 1.*tree.GetEntries(bin) )
    count = getObj( infile, 'CountWithPU' )
    file.append( count.GetBinContent(1) )
    print fileList

CountIncl = fileList[0][3]
print fileList


#TH1 with axis name as the branch
h_outfile = ROOT.TFile('lheWeightHisto.root','RECREATE')
binning  = array('f',[0]*(len(lheBin)))
binning[0] = 0.
binning[1] = 50.
binning[2] = 70.
binning[3] = 100.
print binning
h_lheWeight = ROOT.TH1F("h_lheWeight","h_lheWeihgt",len(lheBin), 0,len(lheBin));
h_lheWeight.GetXaxis().SetTitle("lheV_pt")
for bin in range(0,h_lheWeight.GetNbinsX()):
    print h_lheWeight.GetBinLowEdge(bin+1)
    print h_lheWeight.GetBinWidth(bin+1)
    print h_lheWeight.GetBinCenter(bin+1)

#total -> total numer of events in each lheBin
print 'Calculating total'
total = []
weight= []
for bin in range(0, len(lheBin) ):
    total.append(getTotal(bin, fileList))
    print bin
    #to better stich we need the highest stat
    fileList.sort( key=lambda file: file[2][bin], reverse=True )
    print 'After sorting'
    print fileList
    if total[bin] > 0.:
        #the first is always the one with the highest N in the bin: 
        weight.append( (fileList[0][1]/fileList[0][3]) * (CountIncl/2950.) * fileList[0][2][bin]/total[bin] )
        h_lheWeight.SetBinContent( bin+1,  weight[bin] )
        print weight[bin]
    else:
        weight.append(1.)
        h_lheWeight.SetBinContent( bin+1,  weight[bin] )
print weight

h_outfile.Write()
h_outfile.Close()

# hadd all the files. Non-sense file but need for stitching
#sys.os('hadd -f notToUse_haddTTree_DYJets.root DYJets*root') 
#sys.os('addHistos -i DYJets_inclusive.root -t notToUse_haddTTree_DYJets.root -o notToUse_haddFile_DYJets.root') #-> this is the file you can plug in the Philipp-Niklas framework

#----------------------------------------------------------------------------------


#now add the branch with the weight normalized to the inclusive 
for file in fileList: # file[0] = 'notToUse_haddFiles_DYJets.root'
    infile = ROOT.TFile(file[0],"READ")
    outfile = ROOT.TFile('lheWeight.'+file[0],'RECREATE')

    infile.cd()
    tree = infile.Get('tree')
    outfile.cd()
    newtree = tree.CloneTree(0)
    lheWeight = array('f',[0])
    newtree.Branch('lheWeight',lheWeight,'lheWeight/F')

    nEntries = tree.GetEntries()
    for entry in range(0,nEntries):
        tree.GetEntry(entry)
        if tree.lheV_pt < 50:
            lheWeight[0] = weight[0] #h_lheWeight.GetBinContent(1)
        elif tree.lheV_pt > 50 and tree.lheV_pt < 70:
            lheWeight[0] = weight[1] #h_lheWeight.GetBinContent(2)
        elif tree.lheV_pt > 70 and tree.lheV_pt < 100:
            lheWeight[0] = weight[2] #h_lheWeight.GetBinContent(3)
        elif tree.lheV_pt > 100:
            lheWeight[0] = weight[3] #h_lheWeight.GetBinContent(4)
        else:
            lheWeight[0] = 1.

            
        newtree.Fill()
                   
    newtree.AutoSave()
    outfile.Write()
    outfile.Close()

