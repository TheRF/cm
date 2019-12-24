#ifndef PARAMS_H
#define PARAMS_H

#include <string>
#include <vector>
#include <filesystem>

const std::string CONFFILE = "cm";

//config file key words
const char CONF_DELIM = ';';


//input parameters
struct ParamPath {
  std::string sParam;
  std::string sPath;
  std::string sBakAltPath;

  ParamPath(std::string, std::string, std::string);
};

namespace fs = std::filesystem;

struct Params {
  fs::path sOrig, sBackup;//base root directories
  std::vector<ParamPath> vRegisteredPaths;

  Params(std::string);//note: paths are assumed to end on a delimiter
  fs::path getOrigPathFromFlag(std::string);
  fs::path getBakPathFromFlag(std::string);

  bool IsFlag(std::string);
};

//we want to sort files depending on the associated parameter flag
//that way we can have multiple flags in one go
struct ParamInput {
  std::string sParam;
  std::vector<std::string> vFiles;
};

struct FileDistributer {
  std::vector<ParamInput> vInputCollection;
public:
  void addAssociation(std::string, std::string);
  bool distribute(Params&);
};

#endif
