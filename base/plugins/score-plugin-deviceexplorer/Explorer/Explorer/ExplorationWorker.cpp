// This is an open source non-commercial project. Dear PVS-Studio, please check
// it. PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "ExplorationWorker.hpp"

namespace Explorer
{
ExplorationWorker::ExplorationWorker(Device::DeviceInterface& theDev)
    : dev{theDev}
{
}
}
