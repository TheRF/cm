#include <fstream>
#include <sstream>

#include "params.h"

ParamPath::ParamPath(std::string sFlag, std::string sOrig, std::string sBak) {
  sParam = sFlag;
  sPath = sOrig;
  sBakAltPath = sBak;
}

Params::Params(std::string sFile) {
  std::ifstream is(sFile, std::fstream::in);
  if (is) {
    std::string s;
    std::getline(is, s);//orig
    sOrig = s;

    std::getline(is, s);//bak
    sBackup = s;

    //flags
    while (std::getline(is, s)) {
      std::istringstream ts(s);
      std::string sToken;
      std::vector<std::string> vTokens;
      while (std::getline(ts, sToken, CONF_DELIM)) {
        vTokens.push_back(sToken);
      }

      ParamPath pp(vTokens[0], vTokens[1], vTokens[2]);

      vRegisteredPaths.push_back(pp);
    }
  }
}

fs::path Params::getOrigPathFromFlag(std::string sFlag) {
  for (ParamPath pp : vRegisteredPaths) {
    if (pp.sParam.compare(sFlag) == 0)
      return pp.sPath;
  }

  return "";
}

fs::path Params::getBakPathFromFlag(std::string sFlag) {
  for (ParamPath pp : vRegisteredPaths) {
    if (pp.sParam.compare(sFlag) == 0)
      return pp.sBakAltPath;
  }

  return "";
}

bool Params::IsFlag(std::string sFlag) {
  for (ParamPath pp : vRegisteredPaths) {
    if (pp.sParam.compare(sFlag) == 0)
      return true;
  }

  return false;
}

void FileDistributer::addAssociation(std::string sFlag, std::string sFile) {
  for(auto itColFlags : vInputCollection){
    if(itColFlags.sParam.compare(sFlag)==0){
      itColFlags.vFiles.push_back(sFile);
      return;
    }
  }

  ParamInput pi;
  pi.sParam = sFlag;
  pi.vFiles.push_back(sFile);
  vInputCollection.push_back(pi);
}

bool FileDistributer::distribute(Params& p) {
  for (auto itColFlags : vInputCollection) {
    fs::path pOrig = fs::path( p.sOrig) /= p.getOrigPathFromFlag(itColFlags.sParam);
    fs::path pBak = fs::path(p.sBackup) /= p.getBakPathFromFlag(itColFlags.sParam);

    for (auto itColFiles : itColFlags.vFiles) {
      fs::path _pBak(pBak);
      _pBak /= fs::path(itColFiles);

      fs::copy_file(itColFiles, _pBak);

      fs::path _pOrig(pOrig);
      _pOrig /= fs::path(itColFiles);

      fs::rename(itColFiles, _pOrig);
    }
  }

  return true;
}