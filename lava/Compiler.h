#pragma once

#include "api.h" // #include <lavaUtils/api.h>

#include <vector>
#include <string>

#include <vulkan/vulkan.hpp>

namespace lava
{
  namespace utility
  {
    LAVA_API
    std::vector<uint32_t> compileGLSLToSPIRV(vk::ShaderStageFlagBits stage, 
      std::string const & source);
  }
}