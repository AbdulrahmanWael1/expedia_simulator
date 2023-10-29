/*
what is this?
a console application that simulates "Expedia.com" .. a popular booking website

How it's structured?
it consists of 3 back-end subsystems (Itineraries system, Payment system, and Users system), 1 front-end system (Expedia), and some global helper functions and properties.

Program features:
1. polymorphism is the main target .. extensibility is to be achieved
2. heavy use of pointers and dynamic allocation
3. API handling .. however, they are local
4. using properties as interfaces
5. factory design pattern is prominent
6. operator overloading for nicer code
7. the project is separated into abstract .h files and implementation details in .cpp files

unfortunately:
8. it uses dummy data instead of permanent storage for simplicity
9. the system is vulnerable to wrong user input .. like string instead of int and so
10. some classes are non-copyable indicating that it's enough to have one copy of them
11. the application focuses on only the customer view

side note:
any member function named "dummy reader" has the purpose to quickly initialize objects with dummy data .. for easy usage
*/

// NEXT STEPS : 1- try to move print, read operator overloading to .cpp .... 2. solve the issue of cyclic dependency .... 3. separate from implementation

// all of those are included in the uncommented library included below
// #include "helperFNs_and_properties.h"
// #include "Users_system.h"
// #include "Payment_system.h"
#include "Itinerary_system.h"

// for each class that must be initialized with dummy data .. we will use a function : void dummy_reader(.. some variables)

////////////// front-end system //////////
class Expedia
{
private:
	Users_manager *users_manager;
	Itinerary_manager *itinerary_manager;
	User *user;
	Payment_manager *payment_manager;

	void load_data()
	{
		users_manager->load_users();
		itinerary_manager->load_itineraries();
		itinerary_manager->load_data_sources();
		payment_manager->load_cards();
	}

	void customer_view()
	{
		auto *customer = dynamic_cast<Customer *>(user);
		while (true)
		{
			int choice = display_menu({"View Profile", "Make itinerary", "List my itineraries", "Logout"});
			if (choice == 1)
				users_manager->view_profile();
			else if (choice == 2)
				itinerary_manager->make_itinerary(payment_manager, customer);
			else if (choice == 3)
				itinerary_manager->list_itineraries(customer);
			else
				break;
		}
	}
	// and each type of user we add later will have a separate view connected to the application
	void admin_view()
	{
		std::cout << "\n\nWorking on it :)\n\n";
	}

public:
	Expedia(const Expedia &expedia) = delete;
	Expedia &operator=(const Expedia &expedia) = delete;
	Expedia()
	{
		itinerary_manager = new Itinerary_manager();
		users_manager = new Users_manager();
		payment_manager = new Payment_manager();
	}
	void run()
	{
		// load all the data once at the begging of the program to save some type
		load_data();
		while (true)
		{
			users_manager->access_menu();
			user = users_manager->get_current_user();
			if (user->get_type() == "Customer")
				customer_view();
			else
				admin_view();
		}
	}

	~Expedia()
	{
		if (users_manager != nullptr)
		{
			delete users_manager;
			users_manager = nullptr;
		}
		if (itinerary_manager != nullptr)
		{
			delete itinerary_manager;
			itinerary_manager = nullptr;
		}
		if (user != nullptr)
		{
			delete user;
			user = nullptr;
		}
		if (payment_manager != nullptr)
		{
			delete payment_manager;
			nullptr;
		}
	}
};

int main()
{
	Expedia *site = new Expedia();
	site->run();
	delete site;
	return 0;
}