#include "helperFNs_and_properties.h"

int read_int(const int &num_of_options, std::istream &input)
{
	int result;
	bool correct_choice = false;

	while (!correct_choice)
	{
		const int MIN_CHOICE = 1;
		const int MAX_CHOICE = num_of_options;
		std::cout << "Enter number in range " << MIN_CHOICE << " - " << MAX_CHOICE << ": ";
		input >> result;

		if (MIN_CHOICE > result || result > MAX_CHOICE)
		{
			std::cout << "Invalid choice ... Try again\n";
			continue;
		}
		correct_choice = true;
	}
	return result;
}
int display_menu(const std::vector<std::string> &points, std::istream &input)
{
	std::cout << "#####################################\n";
	std::cout << "Menu: \n";

	int i = 1;
	for (const std::string &point : points)
	{
		std::cout << "\t" << i++ << ": " << point << "\n";
	}
	std::cout << "\n";
	const int OPTIONS = points.size();
	return read_int(OPTIONS, input);
}
