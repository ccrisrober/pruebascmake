#pragma once

#include <lava/lava.h>
#include "api.h" // #include <lavaUtils/api.h>

namespace lava
{
  namespace utility
  {
    LAVAUTILS_API
    std::vector<uint32_t> compileGLSLToSPIRV(vk::ShaderStageFlagBits stage, 
      std::string const & source);
  }
}