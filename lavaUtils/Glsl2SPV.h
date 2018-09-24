/**
 * Copyright (c) 2017 - 2018, Lava
 * All rights reserved.
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 **/

#ifndef __LAVA_UTILS_GLSL2SPV__
#define __LAVA_UTILS_GLSL2SPV__

#include <lava/lava.h>
#include "api.h" // #include <lavaUtils/api.h>
#include <vector>

#include <thirdparty/glslang/SPIRV/GlslangToSpv.h>

namespace lava
{
	namespace utility
	{
    class GLSLToSPIRVCompiler
    {
    public:
      GLSLToSPIRVCompiler( void );
      ~GLSLToSPIRVCompiler( void );

      std::vector<uint32_t> compile( vk::ShaderStageFlagBits stage,
        const std::string& source ) const;

    private:
      TBuiltInResource  _resource;
    };
  	std::vector< uint32_t > compileGLSLToSPIRV( 
  		vk::ShaderStageFlagBits stage, const std::string& source );
	}
}

#endif /* __LAVA_UTILS_GLSL2SPV__ */