#include <modui/core/image/image.hpp>
#include <modui/core/image/rasterimage.hpp>
#include <modui/core/image/vectorimage.hpp>

#define STB_IMAGE_IMPLEMENTATION
#define GL_CLAMP_TO_EDGE 0x812F

#include <stb/stb_image.h>
#ifdef _WIN32
	#include <GL/gl.h>
#else // assume Android
	#include <GLES3/gl3.h>
#endif // _WIN32
#include <imgui/imgui_impl_opengl3.h>

#include <cstdio>
#include <cstring>

namespace modui::image
{
	ImageID Image::load_image(const std::string& file_path)
	{
		FILE* file = fopen(file_path.c_str(), "rb");

		fseek(file, 0, SEEK_END);
		size_t file_size = ftell(file);

		char* buffer = (char*)malloc(file_size);
		if (!buffer)
		{
			fclose(file);
			return nullptr;
		}

		fseek(file, 0, SEEK_SET);
		file_size = fread((void*)buffer, sizeof(char), file_size, file);
		fclose(file);

		auto ret = Image::load_image_from_memory(buffer, file_size);
		free(buffer);
		return ret;
	}

	ImageID Image::load_image_from_memory(void* buffer, unsigned buffer_size)
	{
		if (buffer_size == -1) buffer_size = strlen((char*)buffer);

		int image_width = 0;
		int image_height = 0;
		stbi_uc* image_data = stbi_load_from_memory((stbi_uc*)buffer, buffer_size, &image_width, &image_height, NULL, 4);
		if (image_data == NULL)
			return nullptr;

		// Create a OpenGL texture identifier
		GLuint image_texture;
		glGenTextures(1, &image_texture);
		glBindTexture(GL_TEXTURE_2D, image_texture);

		// Setup filtering parameters for display
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); // This is required on WebGL for non power-of-two textures
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); // Same

		// Upload pixels into texture
	#if defined(GL_UNPACK_ROW_LENGTH) && !defined(__EMSCRIPTEN__)
		glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
	#endif
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image_width, image_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_data);
		stbi_image_free(image_data);

		#pragma GCC diagnostic push
		#pragma GCC diagnostic ignored "-Wint-to-pointer-cast"
		return new RasterImage((ImTextureID)image_texture, image_width, image_height);
		#pragma GCC diagnostic pop
	}

	void Image::unload(ImageID image)
	{
		delete image;
	}

	ImageID Image::load_svg(const std::string& file_path)
	{
		NSVGimage* image = nsvgParseFromFile(file_path.c_str(), "px", 96 /* seems like this parameter is ignored */);
		return new VectorImage(image);
	}

	ImageID Image::load_svg_from_memory(char* buffer)
	{
		NSVGimage* image = nsvgParse(buffer, "px", 96);
		return new VectorImage(image);
	}
}