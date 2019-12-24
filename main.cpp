#include <iostream>
#include <string>
#include <cstdlib>

#include "params.h"

int main(int argc, char* argv[]) {
  if (argc < 3) {
    std::cerr << "Usage: " << argv[0] << "<parameter> [files]" << '\n';
    std::cerr << "Defined parameters can be found in: " << CONFFILE << '\n';
    return 1;
  }

  //default location of the config file is in $HOME
  std::string sPath = std::getenv("HOME");
  if (sPath.length()==0) {
    std::cerr << "HOME not set!" << '\n';
    return 1;
  }

  sPath.append("/.config/");

  //figure out which paths are available
  Params appParams(sPath.append(CONFFILE));

  //make sure we know where to put the files
  //filenames can have wildcards so we expand them (TODO)
  //assumption: files only in current directory
  std::vector<std::string> vFiles;
  FileDistributer fd;
  std::string sCur;
  for (int i = 1; i < argc; i++) {
    std::string sTmp = std::string(argv[i]);

    if (appParams.IsFlag(sTmp)) {
      sCur = sTmp;
    }
    else {
      //assumption: is actual existing file and not flag
      //also flag already specified (sCur not empty)
      fd.addAssociation(sCur, sTmp);
    }
  }

  //backup every file and then move them to their final location
  if(!fd.distribute(appParams)){
    return 1;
  }

  return 0;
}