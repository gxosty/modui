import sys
import json


def get_value(theme, name):
	return theme[name][1:]


def convert_to_cpp(theme):
	output = ""

	output += f"new_theme().primary                   = MODUI_COLOR_HEX(0xFF'{get_value(theme, 'primary')});\n"
	output += f"new_theme().on_primary                = MODUI_COLOR_HEX(0xFF'{get_value(theme, 'onPrimary')});\n"
	output += f"new_theme().primary_container         = MODUI_COLOR_HEX(0xFF'{get_value(theme, 'primaryContainer')});\n"
	output += f"new_theme().on_primary_container      = MODUI_COLOR_HEX(0xFF'{get_value(theme, 'onPrimaryContainer')});\n\n"

	output += f"new_theme().secondary                 = MODUI_COLOR_HEX(0xFF'{get_value(theme, 'secondary')});\n"
	output += f"new_theme().on_secondary              = MODUI_COLOR_HEX(0xFF'{get_value(theme, 'onSecondary')});\n"
	output += f"new_theme().secondary_container       = MODUI_COLOR_HEX(0xFF'{get_value(theme, 'secondaryContainer')});\n"
	output += f"new_theme().on_secondary_container    = MODUI_COLOR_HEX(0xFF'{get_value(theme, 'onSecondaryContainer')});\n\n"

	output += f"new_theme().tertiary                  = MODUI_COLOR_HEX(0xFF'{get_value(theme, 'tertiary')});\n"
	output += f"new_theme().on_tertiary               = MODUI_COLOR_HEX(0xFF'{get_value(theme, 'onTertiary')});\n"
	output += f"new_theme().tertiary_container        = MODUI_COLOR_HEX(0xFF'{get_value(theme, 'tertiaryContainer')});\n"
	output += f"new_theme().on_tertiary_container     = MODUI_COLOR_HEX(0xFF'{get_value(theme, 'onTertiaryContainer')});\n\n"

	output += f"new_theme().error                     = MODUI_COLOR_HEX(0xFF'{get_value(theme, 'error')});\n"
	output += f"new_theme().on_error                  = MODUI_COLOR_HEX(0xFF'{get_value(theme, 'onError')});\n"
	output += f"new_theme().error_container           = MODUI_COLOR_HEX(0xFF'{get_value(theme, 'errorContainer')});\n"
	output += f"new_theme().on_error_container        = MODUI_COLOR_HEX(0xFF'{get_value(theme, 'onErrorContainer')});\n\n"

	output += f"new_theme().surface                   = MODUI_COLOR_HEX(0xFF'{get_value(theme, 'surface')});\n"
	output += f"new_theme().on_surface                = MODUI_COLOR_HEX(0xFF'{get_value(theme, 'onSurface')});\n"
	output += f"new_theme().surface_variant           = MODUI_COLOR_HEX(0xFF'{get_value(theme, 'surfaceVariant')});\n"
	output += f"new_theme().on_surface_variant        = MODUI_COLOR_HEX(0xFF'{get_value(theme, 'onSurfaceVariant')});\n"
	output += f"new_theme().surface_container_highest = MODUI_COLOR_HEX(0xFF'{get_value(theme, 'surfaceContainerHighest')});\n"
	output += f"new_theme().surface_container_high    = MODUI_COLOR_HEX(0xFF'{get_value(theme, 'surfaceContainerHigh')});\n"
	output += f"new_theme().surface_container         = MODUI_COLOR_HEX(0xFF'{get_value(theme, 'surfaceContainer')});\n"
	output += f"new_theme().surface_container_low     = MODUI_COLOR_HEX(0xFF'{get_value(theme, 'surfaceContainerLow')});\n"
	output += f"new_theme().surface_container_lowest  = MODUI_COLOR_HEX(0xFF'{get_value(theme, 'surfaceContainerLowest')});\n"
	output += f"new_theme().inverse_surface           = MODUI_COLOR_HEX(0xFF'{get_value(theme, 'inverseSurface')});\n"
	output += f"new_theme().inverse_on_surface        = MODUI_COLOR_HEX(0xFF'{get_value(theme, 'inverseOnSurface')});\n"
	output += f"new_theme().surface_tint              = MODUI_COLOR_HEX(0xFF'{get_value(theme, 'surfaceTint')});\n\n"
	
	output += f"new_theme().outline                   = MODUI_COLOR_HEX(0xFF'{get_value(theme, 'outline')});\n"
	output += f"new_theme().outline_variant           = MODUI_COLOR_HEX(0xFF'{get_value(theme, 'outlineVariant')});\n"

	print(output)


def main():
	if len(sys.argv) < 3:
		raise ValueError("Expected [file_name] [theme_name]")

	filename = sys.argv[1]
	themename = sys.argv[2]

	with open(filename, "r") as file:
		theme = json.load(file)

	convert_to_cpp(theme["schemes"][themename])


if __name__ == '__main__':
	main()