//////////////// Users system ///////////


#ifndef USERS_SYSTEM
#define USERS_SYSTEM

// useful
#include "helperFNs_and_properties.h"


class User : public Printable
{
private:
	std::string username;
	std::string password;
	std::string name;
	std::string email;
	std::string address;
protected:
	void set(std::string username, std::string password, std::string email, std::string name, std::string address);

public:
	User(std::string username, std::string password, std::string email, std::string name, std::string address);
	virtual std::string get_type() const = 0;
	const std::string get_name() const;
	const std::string get_username() const;
	const std::string get_password() const;
	const std::string get_email() const;
};
class Customer : public User
{
private:
	// those are just ids for the actual cards and itineraries
	std::vector<std::string> cards;
	std::vector<std::string> itineraries;

public:
	Customer(std::string username, std::string password, std::string email, std::string name, std::string address);
	virtual std::string get_type() const override;
	virtual std::ostream &print(std::ostream &output) const override;

	void update_itineraries(std::string itinerary);
	void update_cards(std::string card);
	const int get_num_of_cards() const;
	const std::vector<std::string> get_itinerary_ids() const;
	const std::vector<std::string> get_card_ids() const;
};
// this application focuses on the customer side of the website Expedia .. so this Admin class is not actually used ..
// the system is capable of being upgraded to fit to different user types
class Admin : public User
{
public:
	using User ::User;
	virtual std::string get_type() const override;
	virtual std::ostream &print(std::ostream &output) const override;
};

// the "print" member function coming from the "Printable" interface is used with this operator for a nicer looking code ..
std::ostream &operator<<(std::ostream &output, User *user);

class Users_manager
{
private:
	User *active_user;
	std::vector<User *> users;

	void update_data(User *user);
	void reset_data();

	void login();
	// the only type of user allowed to sign-up is the "customer" .. other just login directly if they exist
	void sign_up();
	void hello();

public:
	void load_users();

	Users_manager(const Users_manager &users_manager) = delete;
	Users_manager &operator=(const Users_manager &users_manager) = delete;
	Users_manager() = default;

	void access_menu();

	void view_profile();

	User *get_current_user();

	~Users_manager();
};

#endif