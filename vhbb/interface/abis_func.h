#ifndef  ABIS_FUNC_INC
#define  ABIS_FUNC_INC
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


#include <string>
#include <map>
#include "TTree.h"
#include <vector>

namespace abis{

    //create branch with var in all trees in map
    //various oveloaded functions
    void make_branch(std::map<std::string, TTree*>& map_, std::string name, unsigned short& var);
    void make_branch(std::map<std::string, TTree*>& map_, std::string name, bool& var);
    void make_branch(std::map<std::string, TTree*>& map_, std::string name, double& var);
    void make_branch(std::map<std::string, TTree*>& map_, std::string name, int& var);
    void make_branch(std::map<std::string, TTree*>& map_, std::string name, float& var);
/*     void make_branch(std::map<std::string, TTree*>& map_, std::string name, std::vector<double>& var); */

    void make_branch(std::map<std::string, TTree*>& map_, std::string name, unsigned short* var_array);
    void make_branch(std::map<std::string, TTree*>& map_, std::string name, bool* var_array);
    void make_branch(std::map<std::string, TTree*>& map_, std::string name, double* var_array);
    void make_branch(std::map<std::string, TTree*>& map_, std::string name, int* var_array);
    void make_branch(std::map<std::string, TTree*>& map_, std::string name, float* var_array);

}



#endif // ----- #ifndef ABIS_FUNC_INC  -----
