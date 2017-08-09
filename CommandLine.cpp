#include "base.h"
#include "CommandLine.h"
namespace Basic
{

CommandLine::CommandLine(int narg, const char** args)
{
    for (int i = 1; i < narg; ++i) {
        uString element = args[i];
        size_t pos = element.find("=");
        if (pos != uString::npos) {
            uString key = element.substr(0, pos);
            uString value = element.substr(pos + 1);
            mArgs.Insert(key, value);
        }
    }
}

CommandLine::~CommandLine()
{
}

size_t CommandLine::arg_count()
{
    return mArgs.size();
}
}
