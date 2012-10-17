#!/afs/cern.ch/cms/slc5_amd64_gcc434/cms/cmssw/CMSSW_4_2_8/external/slc5_amd64_gcc434/bin/python2.6

import os
import ROOT
from sys import argv, exit
from optparse import OptionParser

parser = OptionParser()
parser.add_option("-i", "--histo", dest="h_in",
                                    help="file from which get the histos", metavar="FILE")
parser.add_option("-t", "--tree", dest="t_in",
                                    help="file from which get the trees", metavar="FILE")

(moptions, args) = parser.parse_args()


def addHistos(args, moptions):
    global option
    option=moptions

    print len(argv)
    print argv
    print len(args)
    print args

    if len(args) > 0:
        h_in = args[0]
        t_in = args[1]
    else:
        h_in = option.h_in
        t_in = option.t_in

    if ( not h_in ) or ( not t_in ) :
        print 'No input files given'
        exit(-1)

    print h_in
    print t_in

    infile = ROOT.TFile(h_in,"READ")
    infile_tree = ROOT.TFile(t_in,"READ")
#    p1 = h_in.find(".")
#    p2 = h_in.find(".",p1+1)
#    outfile = h_in.replace(h_in[p1+1:p2],h_in[p1+1:p2]+'Likelihood')
#    outfile = outfile.split('/')
    outfile = 'withHistos.'+t_in
    outfile = ROOT.TFile(outfile,"RECREATE")

    treeName = 'tree'
    tree = infile_tree.Get(treeName)

    infile.cd()
    obj = ROOT.TObject
    for key in ROOT.gDirectory.GetListOfKeys():
        infile.cd()
        obj = key.ReadObj()
        print obj.GetName()
        if obj.GetName() == treeName:
            continue
        outfile.cd()
        print key.GetName()
        obj.Write(key.GetName())
        
        
    outfile.cd()
    treeCopy = ROOT.TTree
    treeCopy = tree.CloneTree()
    treeCopy.Write()
    treeCopy.AutoSave()
    outfile.Write()
    outfile.Close()
        
if __name__ == "__main__":
    addHistos(args, moptions)
