#ifndef  ABIS_INC
#define  ABIS_INC
// =====================================================================================
// 
//       Filename:  abis_func.h
// 
//    Description:  My functions for easier data analysis
// 
//        Version:  1.0
//        Created:  09/23/2009 10:37:09 PM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  Matteo Abis (), webmaster@latinblog.org
//        Company:  
// 
// =====================================================================================

#include "GammaJets/iCode/interface/abis_func.h"

//implementations
void abis::make_branch(std::map<std::string, TTree*>& map_, std::string name, unsigned short& var){
    for(std::map<std::string, TTree*>::iterator it = map_.begin(); it != map_.end(); it++) 
        it->second->Branch(name.c_str(), &var, (name + "/s").c_str());
}
void abis::make_branch(std::map<std::string, TTree*>& map_, std::string name, bool& var){
    for(std::map<std::string, TTree*>::iterator it = map_.begin(); it != map_.end(); it++) 
        it->second->Branch(name.c_str(), &var, (name + "/O").c_str());
}
void abis::make_branch(std::map<std::string, TTree*>& map_, std::string name, double& var){
    for(std::map<std::string, TTree*>::iterator it = map_.begin(); it != map_.end(); it++) 
        it->second->Branch(name.c_str(), &var, (name + "/D").c_str());
}
void abis::make_branch(std::map<std::string, TTree*>& map_, std::string name, std::vector<double>& var){
    for(std::map<std::string, TTree*>::iterator it = map_.begin(); it != map_.end(); it++) 
        it->second->Branch(name.c_str(), &var, (name).c_str());
}
void abis::make_branch(std::map<std::string, TTree*>& map_, std::string name, int& var){
    for(std::map<std::string, TTree*>::iterator it = map_.begin(); it != map_.end(); it++) 
        it->second->Branch(name.c_str(), &var, (name + "/I").c_str());
}
void abis::make_branch(std::map<std::string, TTree*>& map_, std::string name, float& var){
    for(std::map<std::string, TTree*>::iterator it = map_.begin(); it != map_.end(); it++) 
        it->second->Branch(name.c_str(), &var, (name + "/F").c_str());
}



void abis::make_branch(std::map<std::string, TTree*>& map_, std::string name, unsigned short* var_array){
    for(std::map<std::string, TTree*>::iterator it = map_.begin(); it != map_.end(); it++) 
        it->second->Branch(name.c_str(), var_array, (name + "[2]/s").c_str());
}
void abis::make_branch(std::map<std::string, TTree*>& map_, std::string name, bool* var_array){
    for(std::map<std::string, TTree*>::iterator it = map_.begin(); it != map_.end(); it++) 
        it->second->Branch(name.c_str(), var_array, (name + "[2]/O").c_str());
}
void abis::make_branch(std::map<std::string, TTree*>& map_, std::string name, double* var_array){
    for(std::map<std::string, TTree*>::iterator it = map_.begin(); it != map_.end(); it++) 
        it->second->Branch(name.c_str(), var_array, (name + "[2]/D").c_str());
}
void abis::make_branch(std::map<std::string, TTree*>& map_, std::string name, int* var_array){
    for(std::map<std::string, TTree*>::iterator it = map_.begin(); it != map_.end(); it++) 
        it->second->Branch(name.c_str(), var_array, (name + "[2]/I").c_str());
}
void abis::make_branch(std::map<std::string, TTree*>& map_, std::string name, float* var_array){
    for(std::map<std::string, TTree*>::iterator it = map_.begin(); it != map_.end(); it++) 
        it->second->Branch(name.c_str(), var_array, (name + "[2]/F").c_str());
}


#endif // ----- #ifndef ABIS_FUNC_INC  -----
