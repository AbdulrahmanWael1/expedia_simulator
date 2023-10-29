#ifndef HELPERS_
#define HELPERS_

//////////////// HELPER FNs and Properties ///////////////

// useful to Include
#include <iostream>
#include <vector>
#include <assert.h>

// to validate reading an integer
int read_int(const int &num_of_options, std::istream &input = std::cin);
// displays menu layout in the whole application
int display_menu(const std::vector<std::string> &points, std::istream &input = std::cin);

// some properties .. each is an interface with one member function
class Printable
{
public:
	virtual std::ostream &print(std::ostream &output) const = 0;
	virtual ~Printable() {}
};
class Readable
{
public:
	virtual std::istream &read(std::istream &input) = 0;
	virtual ~Readable() {}
};
class Payable
{
public:
	virtual const double get_cost() const = 0;
	virtual ~Payable() {}
};


#endif
