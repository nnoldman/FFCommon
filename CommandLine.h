#pragma once
#include "uString.h"
#include "Array.h"
#include "Map.h"
namespace Basic {
class CommandLine {
  public:
    CommandLine(int narg, const char** args);
    ~CommandLine();

    template<typename T>
    void get(const char* key, T& v) {
        if (mArgs.findkey(key))
            StringHelper::setValue(mArgs[key].c_str(), &v);
    }
    size_t arg_count();
  private:
    Map<uString, uString> mArgs;
};
}
