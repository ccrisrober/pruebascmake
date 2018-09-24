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

#ifndef __LAVAUTILS_MATERIAL__
#define __LAVAUTILS_MATERIAL__

#ifdef LAVA_USE_ASSIMP

#include <assimp/material.h>
#include <glm/glm.hpp>

#include "api.h" // #include <lavaUtils/api.h>

namespace lava
{
  namespace utility
  {
    class Material
    {
    public:
      LAVAUTILS_API
      Material( const aiMaterial* mtl, const std::string& globalPath );
      std::string albedoTexturePath;
      glm::vec3 albedoColor;
      bool useAlbedoTexture;
    };
  }
}

#endif

#endif /* __LAVAUTILS_MATERIAL__  */
