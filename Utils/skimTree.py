#!/usr/bin/python2.6

import os
import ROOT
from sys import argv, exit
from optparse import OptionParser


if __name__=="__main__":
    usage = """usage : %prog --fin inputFileName --cut cutString"""

    parser = OptionParser( usage = usage, version="%prog 1.0")
    parser.add_option("--fin", action="store", dest="inputFileName",default="", help="Input file name")
    parser.add_option("--treein", action="store", dest="inputTreeName",default="", help="Input tree name")
    parser.add_option("--fout", action="store", dest="outputFileName",default="", help="Output file name")
    parser.add_option("--cut", action="store", dest="tcut",default="", help="Selection to be applyed")
    parser.add_option("--treeName", action="store", dest="treeName",default="", help="Name for the new Tree")
    parser.add_option("--treeTitle", action="store", dest="treeTitle",default="", help="Title for the new Tree")
    parser.add_option("--clone", action="store_true", dest="clone",default=True, help="Clone all the rest")
#to come
#    parser.add_option("--dir", action="store", dest="path",default="", help="If you want to pass a dir instead of a file.")
    (moptions, args) = parser.parse_args()

#    if len(args)<1:
#        print usage
#        exit(-1)    


#def GetKeyNames(self, dir = ""):
#    self.cd(dir)
#    return [ key.GetName() for key in ROOT.gDirectory.GetListOfKeys()]
#ROOT.TFile.GetKeyNames = GetKeyNames
#            keyList = infile.GetKeyNames("./")
#            print "\nKeys in file:", keyList

def skimTree(args, moptions):
    global options
    options=moptions
    
    print options.inputFileName

    if options.tcut == "":
        print "No cuts selected. Quit"
        exit(-1)

    if options.inputFileName == "" or options.inputTreeName=="":
        print "Missing input file or tree name. Quit"
        exit(-1)
    else:
#        inputFileName=args[0] # here just for reference
        inputFileName=""
        inputFileName=str(options.inputFileName)
        if options.outputFileName == "":
            print 'Missing explicit output file name. Using Skimmed_'+str(inputFileName)+' instead.'
            outputFileName="Skimmed_"+str(inputFileName)
        else:
            outputFileName=options.outputFileName

        infile = ROOT.TFile(inputFileName,"READ")
        tree = ROOT.TTree()
        tree = infile.Get(options.inputTreeName)

        if options.treeName == "":
            print "No name given for the skimmed tree. Using old one."
            treeName=tree.GetName()
        else:
            treeName=options.treeName

        if options.treeTitle == "":
            print "No new title given for the skimmed tree. Using old one."
            treeTitle=tree.GetTitle()
        else:
            treeTitle=options.treeTitle

        outfile = ROOT.TFile(outputFileName,"RECREATE")

        if options.clone==True:
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
                

#            nextKey = ROOT.TIter(infile.GetListOfKeys())
#            newkey = ROOT.TKey
#            newkey = nextKey()
#            while (newkey != nextKey()):
#                infile.cd()
#                obj = newkey.ReadObj()
#                print obj.GetName()
#                outfile.cd()
#                print newkey.GetName()
#                obj.Write(newkey.GetName())
#                newkey = nextKey()

        outfile.cd()
        treeSkimmed = ROOT.TTree
#        treeSkimmed = tree.CopyTree("Vtype==1")
        treeSkimmed = tree.CopyTree(options.tcut)
        treeSkimmed.SetName(treeName)
        treeSkimmed.SetTitle(treeTitle)
        treeSkimmed.Write()
        treeSkimmed.AutoSave()
        outfile.Write()
        outfile.Close()

if __name__ == "__main__":
    skimTree(args, moptions)
