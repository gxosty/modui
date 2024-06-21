#include <modui/theme.hpp>

namespace modui
{
	Theme::Theme(const std::string& theme_name) : 
		_theme_name{theme_name},
		_theme_vars{
			0xFFA45067, // primary;
			0xFFFFFFFF, // on_primary;
			0xFFFFDDEA, // primary_container;
			0xFF5D0021, // on_primary_container;

			0xFF715B62, // secondary;
			0xFFFFFFFF, // on_secondary;
			0xFFF8DEE8, // secondary_container;
			0xFF2B191D, // on_secondary_container;

			0xFF60527D, // tertiary;
			0xFFFFFFFF, // on_tertiary;
			0xFFE4D8FF, // tertiary_container;
			0xFF1D1131, // on_tertiary_container;

			0xFF1E26B3, // error;
			0xFFFFFFFF, // on_error;
			0xFFDCDEF9, // error_container;
			0xFF0B0E41, // on_error_container;

			0xFFFFF7FE, // surface;
			0xFF201B1D, // on_surface;
			0xFF7EE0E7, // surface_variant;
			0xFF4F4549, // on_surface_variant;
			0xFF6EE0E6, // surface_container_highest;
			0xFFCEE6EC, // surface_container_high;
			0xFF3EEDF3, // surface_container;
			0xFF7FF2F7, // surface_container_low;
			0xFFFFFFFF, // surface_container_lowest;
			0xFF222F32, // inverse_surface;
			0xFFF7EFF5, // inverse_on_surface;
			0xFFA45067  // surface_tint;
		} {};

	const std::string& Theme::get_name() const
	{
		return this->_theme_name;
	}

	ThemeVars& Theme::operator()()
	{
		return this->_theme_vars;
	}

	void ThemeManager::add(const Theme& theme)
	{
		if (this->_themes.contains(theme.get_name()))
		{
			this->remove(theme.get_name());
		}

		this->_themes.insert({theme.get_name(), theme});
	}

	Theme& ThemeManager::get(const std::string& theme_name)
	{
		if (!this->_themes.contains(theme_name))
		{
			throw new exceptions::ThemeNotFoundException(theme_name);
		}

		return this->_themes.at(theme_name);
	}

	void ThemeManager::remove(const std::string& theme_name)
	{
		if (this->_themes.contains(theme_name))
		{
			this->_themes.erase(theme_name);
		}
	}
}