import sys
import os


def create_file_content(icons):
	pass


def icons_to_hpp(icons_dir, output_path):
	icons = []

	for root, dirs, files in os.walk(icons_dir):
		for filename in files:
			if filename.endswith(".svg"):
				icons.append(os.path.join(root, filename))

	output_directory = os.path.dirname(output_path)

	if not os.path.isdir(output_directory):
		os.makedirs(output_directory)

	data = create_file_content(icons)

	with open(output_path, "w") as file:
		file.write(data)


def main():
	icons_to_hpp(sys.argv[1], sys.argv[2])


if __name__ == '__main__':
	main()