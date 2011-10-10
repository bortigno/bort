#ifndef CUTSANDHISTOS_H
#define CUTSANDHISTOS_H
#include <string>
#include <sstream>
#include <vector>
#include <TROOT.h>
#include <TFile.h>
#include "ntupleReader.h"

enum  VType{ Zmm, Zee, Wmn, Wen, Znn } iType;

class Histos {
public:
   virtual void book(TFile &f, std::string suffix) = 0;
   virtual void fill( ntupleReader &event, float w) = 0;
//   virtual Histos * clone() =0;
};

class Cut {
 public:
  virtual bool pass( ntupleReader &event ) = 0;
   virtual std::string name() = 0;
   virtual bool operator()(ntupleReader &event) {return pass(event); }
};

class NoCut : public Cut {
 public:
  virtual bool pass( ntupleReader &event )  { return true;}
   virtual std::string name() {return "NoCut"; }
};

/// One parameter cut class
class PCut : public Cut
{
 public:
 PCut(float cut) : m_cut(cut) {}
 void setCut(float cut) {m_cut=cut;}

 std::string cutValueString()
  {
     std::stringstream s;
     s << m_cut;
     return s.str();
  } 

 float m_cut;
 
};

class CutSet : public Cut {
 public:
 void add(Cut *c) {cuts.push_back(c);}  
 bool pass(ntupleReader &event) {
  bool result=true;
  for(size_t i=0; i< cuts.size() ; i++) 
    if( ! (cuts.at(i)->pass(event)) ) 
      result=false;
  return result;
 } 
 std::string name() {
   std::stringstream s;
   for(size_t i=0; i< cuts.size() ; i++) {
     s << "_" << cuts.at(i)->name();
   }
 return s.str();
 }

private:
 std::vector<Cut *> cuts;
 
};



///CutSet of PCut, with scanning functions
// to be implemented still
class PCutSet : public Cut {
 public:
 void add(PCut *c) {cuts.push_back(c);}
 bool pass(ntupleReader &event) {
  bool result=true;
  for(size_t i=0; i< cuts.size(); i++)
    if( ! (cuts.at(i)->pass(event)) )
      result=false;
  return result;
 }
 std::string name() {
   std::stringstream s;
   for(size_t i=0; i< cuts.size(); i++) {
     s << "_" << cuts.at(i)->name();
   }
 return s.str();
 }

private:
 std::vector<PCut *> cuts;

};



class CutsAndHistos {
public:
  CutsAndHistos() {}
  CutsAndHistos(Cut * c, std::vector<Histos *> & h):
    cut(c),
    histos(h) {}
  CutsAndHistos(Cut * c, Histos * h):
    cut(c) {
       histos.push_back(h);
   }
  //TODO: implement destructor for all pointers received
  
  void book(TFile &f) {
    std::string suffix=cut->name();
    for(size_t i=0; i< histos.size(); i++) 
      histos.at(i)->book(f,suffix);
  }
  
  void process(ntupleReader &event, float w)
  {
    if(cut->pass(event))
      for(size_t i=0; i< histos.size(); i++) 
	histos.at(i)->fill(event,w);
  }

  
  Cut * cut;
  std::vector<Histos *> histos;
    
}; 

#endif

