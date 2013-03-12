#! /usr/bin/env python2.6

import ROOT, os
import numpy

t = ROOT.TTree('t','t')
t.ReadFile('input.txt','channel/C:value')


c = ROOT.TCanvas("c","c",600,600)

n=5
os_X = ["W+udscg","W+b#bar{b}","Z+udscg","Z+b#bar{b}","t#bar{t}"]

d = numpy.array([0.94, 1.72, 1.10,1.08,1.01])
e = numpy.array([0.02,0.16,0.02,0.04,0.02])
sys_e = numpy.array([0.01,0.10,0.06,0.08,0.06])
p = numpy.array([.5,1.5,2.5,3.5,4.5])
zero = numpy.array([0,0,0,0,0])

h2 = ROOT.TH2F("h2","",1,0.7,2.2,5,0,5)
h2.GetXaxis().SetTitle("Scale factor")

for i in range(n):
    h2.GetYaxis().SetBinLabel(i+1,os_X[i])

g = ROOT.TGraphErrors(n,d,p,e,zero)
g.SetFillColor(0)
g.SetLineColor(2)
g.SetLineWidth(3)
g.SetMarkerStyle(21)

g2 = ROOT.TGraphErrors(n,d,p,sys_e,zero)
g2.SetFillColor(0)
#g2.SetLineColor(2);
g2.SetLineWidth(3);
g2.SetMarkerStyle(21);

h2.Draw(); ROOT.gStyle.SetOptStat(0);
h2.GetXaxis().SetTitleSize(0.04);
h2.GetXaxis().SetLabelSize(0.04);
h2.GetYaxis().SetLabelSize(0.06);
#h2.SetFillStyle(4000)
c.SetFillStyle(4000)

globalFitBand = ROOT.TBox(1.0, 0., 1.5, n);
globalFitBand.SetFillStyle(3013);
globalFitBand.SetFillColor(65);
globalFitBand.SetLineStyle(0);
#globalFitBand.Draw("same");
globalFitLine = ROOT.TLine(1.0, 0., 1.0, 5.);
globalFitLine.SetLineWidth(2);
globalFitLine.SetLineColor(214);#214
globalFitLine.Draw("same");

#l2 = ROOT.TLegend(0.5, 0.82,0.92,0.95)
l2 = ROOT.TLegend(0.55, 0.65,0.80,0.87)
l2.SetLineWidth(2)
l2.SetBorderSize(0)
l2.SetFillColor(0)
l2.SetFillStyle(4000)
l2.SetTextFont(62)
l2.AddEntry(g,"Scale factor","p")
l2.AddEntry(g,"Statistical","l")
l2.AddEntry(g2,"Systematics","l")
l2.SetTextSize(0.035)
#l2.SetNColumns(2)
l2.Draw("same")

g.Draw("P same")
g2.Draw("[] same")
ROOT.gPad.SetLeftMargin(0.2)
ROOT.gPad.Update()
c.Print("histo.pdf")

