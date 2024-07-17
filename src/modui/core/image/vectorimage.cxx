#include <cstdio>
#include <cstring>
#include <cmath>
#define NANOSVG_IMPLEMENTATION
#define NANOSVGRAST_IMPLEMENTATION
#include <modui/core/image/vectorimage.hpp>
#include <modui/thirdparty/nanosvg/nanosvgrast.h>

#define GL_CLAMP_TO_EDGE 0x812F

#ifdef _WIN32
	#include <GL/gl.h>
#else // assume Android
	#include <GLES3/gl3.h>
#endif // _WIN32

namespace modui::image
{
	VectorImage::VectorImage(NSVGimage* image)
		: _image{image}, _texture{0}, _last_min_size(-1) {}

	void VectorImage::draw(Vec2 pos, Vec2 size, Col32 color)
	{
		if (this->_image == nullptr) return;

		float min_size = fmin(size.x, size.y);

		if (min_size != this->_last_min_size)
				this->_rasterize_image(size);

		ImDrawList* draw_list = ImGui::GetWindowDrawList();
		draw_list->AddImage(this->_texture, pos, pos + size, Vec2(0.0f, 0.0f), Vec2(1.0f, 1.0f), color);
	}

	void VectorImage::_rasterize_image(const Vec2& size)
	{
		static constexpr float s_scale = 1.5f;

		if (this->_texture != 0)
		{
			glDeleteTextures(1, (const GLuint*)&this->_texture);
			this->_texture = 0;
		}

		float image_scale = ((size.x - this->_image->width) < (size.y - this->_image->height) ?
			size.x / this->_image->width :
			size.y / this->_image->height
		);

		this->_last_min_size = fmin(size.x, size.y);
		unsigned image_width = _last_min_size;
		unsigned image_height = _last_min_size;

		size_t image_data_size = size.x * size.y * 4;
		unsigned char image_data[image_data_size * size_t(s_scale * 2)];

		NSVGrasterizer* rasterizer = nsvgCreateRasterizer();

		if (rasterizer == nullptr)
		{
			memset((void*)image_data, 0, image_data_size);
			return;
		}

		nsvgRasterize(rasterizer, this->_image, 0.0f, 0.0f, image_scale * s_scale, image_data, image_width * s_scale, image_height * s_scale, image_width * s_scale * 4);
		nsvgDeleteRasterizer(rasterizer);

		GLuint image_texture;
		glGenTextures(1, &image_texture);
		glBindTexture(GL_TEXTURE_2D, image_texture);

		#pragma GCC diagnostic push
		#pragma GCC diagnostic ignored "-Wint-to-pointer-cast"
		this->_texture = (ImTextureID)image_texture;
		#pragma GCC diagnostic pop

		// Setup filtering parameters for display
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); // This is required on WebGL for non power-of-two textures
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); // Same

		// Upload pixels into texture
	#if defined(GL_UNPACK_ROW_LENGTH) && !defined(__EMSCRIPTEN__)
		glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
	#endif
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image_width * s_scale, image_height * s_scale, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_data);
	}
}