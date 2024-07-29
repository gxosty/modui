import sys
import os


DECLARATION_FILE = "icons.hpp"
IMPLEMENTATION_FILE = "icons.cxx"

IMPLEMENTATION_EXCLUDES = ["close"]


class IconData:
	icon_name: str
	icon_path: str

	_declaration: str
	_implementation: str

	def __init__(self, icon_path):
		self.icon_path = icon_path
		self.icon_name = self._make_icon_name_from_path(icon_path)

		self._declaration = None
		self._implementation = None

	def _make_icon_name_from_path(self, icon_path):
		icon_name = os.path.splitext(os.path.basename(icon_path))[0]
		icon_name = icon_name.replace("-", "_")

		if icon_name[0].isdigit():
			icon_name = "_" + icon_name;

		return icon_name

	def __repr__(self):
		return self.__str__()

	def __str__(self):
		return "<{}: {}>".format(IconData.__name__, self.icon_name)

	def get_declaration(self):
		if self._declaration is not None:
			return self._declaration

		self._declaration = f"extern ImageID {self.icon_name};"

		return self._declaration

	def get_implementation(self):
		if self._implementation is not None:
			return self._implementation

		with open(self.icon_path, "r") as file:
			icon_content = file.read()

		self._implementation = f"char {self.icon_name}_bfr[] = R\"=({icon_content})=\"\"\\x00\";"
		self._implementation += f"\n\tImageID {self.icon_name} = modui::image::Image::load_from_memory({self.icon_name}_bfr, -1, modui::image::ImageType::ICON);"

		return self._implementation


def create_files(icons, output_dir):
	declaration = \
"""#pragma once

#include "core/image/image.hpp"

namespace modui::icons
{{
#ifdef MODUI_EMBED_ICONS
	{}
#endif // MODUI_EMBED_ICONS
}}
""".format(
		"\n\t".join(icon.get_declaration() for icon in icons)
	)

	implementation = \
"""#include "{}"

namespace modui::icons
{{
#ifdef MODUI_EMBED_ICONS
	{}
#endif // MODUI_EMBED_ICONS
}}
""".format(
		DECLARATION_FILE,
		"\n\n\t".join(icon.get_implementation() for icon in icons if icon.icon_name not in IMPLEMENTATION_EXCLUDES)
	)

	with open(os.path.join(output_dir, DECLARATION_FILE), "w") as file:
		file.write(declaration)

	with open(os.path.join(output_dir, IMPLEMENTATION_FILE), "w") as file:
		file.write(implementation)


def icons_to_hpp(icons_dir, output_dir):
	icons = []

	for root, dirs, files in os.walk(icons_dir):
		for filename in files:
			if filename.endswith(".svg"):
				icons.append(IconData(os.path.join(root, filename)))

	if not os.path.isdir(output_dir):
		os.makedirs(output_dir)

	create_files(icons, output_dir)

	print(os.path.join(output_dir, IMPLEMENTATION_FILE).replace("\\", "/"))


def main():
	if len(sys.argv) < 3:
		raise ValueError(
			"Expected [icons_directory] and [output_directory]"
		)

	icons_dir = sys.argv[1].replace("\\", "/")
	output_dir = sys.argv[2].replace("\\", "/")

	icons_to_hpp(icons_dir, output_dir)

	exit(0)


if __name__ == '__main__':
	main()