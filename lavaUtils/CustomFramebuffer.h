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

#ifndef __LAVA_UTILS_CUSTOMFRAMEBUFFER__
#define __LAVA_UTILS_CUSTOMFRAMEBUFFER__

#include <lava/lava.h>
#include "api.h" // #include <lavaUtils/api.h>

namespace lava
{
	namespace utility
	{
		struct FramebufferAttachment
		{
			std::shared_ptr<Image> image;
			std::shared_ptr<ImageView> imageView;
			vk::ImageLayout finalLayout;
			vk::ImageSubresourceRange subresourceRange;
			vk::AttachmentDescription description;
			vk::Format format;
			
			LAVAUTILS_API
			bool hasDepth( void )
			{
			static std::vector<vk::Format> formats =
			{
				vk::Format::eD16Unorm,
				vk::Format::eX8D24UnormPack32,
				vk::Format::eD32Sfloat,
				vk::Format::eD16UnormS8Uint,
				vk::Format::eD24UnormS8Uint,
				vk::Format::eD32SfloatS8Uint
			};
			return std::find(
				formats.begin( ), formats.end( ), format
				) != std::end( formats );
			}
			LAVAUTILS_API
			bool hasStencil( void )
			{
				static std::vector<vk::Format> formats =
				{
					vk::Format::eS8Uint,
					vk::Format::eD16UnormS8Uint,
					vk::Format::eD24UnormS8Uint,
					vk::Format::eD32SfloatS8Uint
				};
				return std::find(
					formats.begin( ), formats.end( ), format
				) != std::end( formats );
			}
			LAVAUTILS_API
			bool isDepthStencil( void )
			{
				return( hasDepth( ) || hasStencil( ) );
			}
		};

		/*struct AttachmentInfo
		{
			uint32_t width, height;
			vk::Format format;
			vk::ImageUsageFlagBits usage;
		};*/
		class CustomFramebuffer : public VulkanResource
		{
		protected:
		public:
			std::vector< FramebufferAttachment > attachments;
			std::shared_ptr< Sampler> _sampler;
			std::shared_ptr< RenderPass > _renderPass;
			std::shared_ptr< Framebuffer > _framebuffer;
			uint32_t _width, _height;
			std::shared_ptr<Semaphore> semaphore;
		public:
			LAVAUTILS_API
			CustomFramebuffer( std::shared_ptr< Device > device, uint32_t w, uint32_t h );

			LAVAUTILS_API
			virtual ~CustomFramebuffer( void );

			LAVAUTILS_API
			uint32_t addAttachment( uint32_t width_, uint32_t height_, 
				vk::Format format_, vk::ImageUsageFlags usage_, uint32_t numLayers = 1 );
			LAVAUTILS_API
			void createSampler( vk::Filter magFilter, vk::Filter minFilter, 
				vk::SamplerAddressMode addressMode );

			LAVAUTILS_API
			void createRenderPass( void );
		};
	}
}

#endif /* __LAVA_UTILS_CUSTOMFRAMEBUFFER__ */