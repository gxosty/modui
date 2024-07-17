#pragma once

#include "../common.hpp"

#include <string>

namespace modui::image
{
	class Image
	{
	public:
		static ImageID load_image(const std::string& file_path);
		static ImageID load_image_from_memory(void* buffer, unsigned buffer_size = -1);
		
		static ImageID load_svg(const std::string& file_path);
		static ImageID load_svg_from_memory(char* buffer /* null terminated */);

		static void unload(ImageID image);

		virtual void draw(Vec2 pos, Vec2 size, Col32 color) = 0;

	};
}