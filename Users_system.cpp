#include "Users_system.h"

// User ////////////////////////////////////////
User::User(std::string username, std::string password, std::string email, std::string name, std::string address)
{
    set(username, password, email, name, address);
}
void User::set(std::string username, std::string password, std::string email, std::string name, std::string address)
{
    this->username = username;
    this->password = password;
    this->email = email;
    this->name = name;
    this->address = address;
}
const std::string User::get_name() const
{
    return name;
}
const std::string User::get_username() const
{
    return username;
}
const std::string User::get_password() const
{
    return password;
}
const std::string User::get_email() const
{
    return email;
}


// Customer ////////////////////////////////
Customer::Customer(std::string username, std::string password, std::string email, std::string name, std::string address) : User(username, password, email, name, address) {}
std::string Customer::get_type() const
{
    return "Customer";
}
std::ostream &Customer::print(std::ostream &output) const
{
    output << "\nName: " << get_name();
    output << "\nEmail: " << get_email();
    output << "\nUsername: " << get_password() << "\n";

    return output;
}

void Customer::update_itineraries(std::string itinerary)
{
    itineraries.push_back(itinerary);
}
void Customer::update_cards(std::string card)
{
    cards.push_back(card);
}
const int Customer::get_num_of_cards() const
{
    return cards.size();
}
const std::vector<std::string> Customer::get_itinerary_ids() const
{
    return itineraries;
}
const std::vector<std::string> Customer::get_card_ids() const
{
    return cards;
}


// Admin //////////////////////////////////
std::string Admin::get_type() const
{
    return "Customer";
}
std::ostream &Admin::print(std::ostream &output) const
{
    output << "\nName: " << get_name();
    output << "\nEmail: " << get_email();
    output << "\nUsername: " << get_password() << "\n";

    return output;
}

std::ostream &operator<<(std::ostream &output, User *user)
{
    return user->print(output);
}


// Users_manager ////////////////////////////////////
void Users_manager::update_data(User *user)
{
    // we can update more data here later .. like a permanent storage (file, etc) or something else
    users.push_back(user);
}
void Users_manager::reset_data()
{
    for (auto *&user : users)
    {
        if (user != nullptr)
        {
            delete user;
            user = nullptr;
        }
    }
    users.clear();

    if (active_user != nullptr)
        delete active_user;
    active_user = nullptr;
}

void Users_manager::login()
{
    bool found = 0;
    std::string username, password;
    std::cout << "Enter user's user_name and password: ";
    std::cin >> username >> password;
    for (auto *&user : users)
    {
        if (user->get_username() == username && user->get_password() == password)
        {
            found = true;
            active_user = user;
            break;
        }
    }
    if (!found)
    {
        std::cout << "ERROR: user not found! .. Try again to login or sign-up instead?\n";
        return access_menu();
    }

    // it's actually better to put this here .. not in access_menu .. because ?
    // when you get username and password wrong multiple times it will be done multiple times after you get both (username, password) right
    hello();
}
void Users_manager::sign_up()
{
    while (true)
    {
        bool found = false;

        std::string username, email, password, name, address;
        std::cout << "Enter user name. (NO SPACES): ";
        std::cin >> username;

        std::cout << "Enter email: ";
        std::cin >> email;

        for (const auto &user : users)
        {
            if (user->get_username() == username && user->get_email() == email)
            {
                found = true;
                break;
            }
        }
        if (found)
        {
            std::cout << "ERROR: username or password is already used .. Try again!\n";
            continue;
        }

        std::cout << "Enter password: ";
        std::cin >> password;
        std::cout << "Enter name: ";
        getline(std::cin, name);
        getline(std::cin, name);

        std::cout << "Enter address: ";
        getline(std::cin, address);

        active_user = new Customer(username, email, password, name, address);
        update_data(active_user);
        break;
    }

    hello();
}
void Users_manager::hello()
{
    std::cout << "\n\nHello " << active_user->get_name() << " | ";
    if (active_user->get_type() == "Customer")
        std::cout << "User View\n\n";
    else
        std::cout << "Admin View\n\n";
}

void Users_manager::load_users()
{
    reset_data();
    // let's use dummy data for now

    Customer *customer1 = new Customer("ahmed", "pass1", "ahmed@gmail.com", "ahmed hamed", "Talkha city");
    Customer *customer2 = new Customer("mohamed", "pass2", "mohamed@gmail.com", "mohamed elbaz", "Mansoura city");

    // each user has it's card_ids and itinerary_ids attached with it
    customer1->update_itineraries("501");
    customer2->update_itineraries("502");
    customer2->update_itineraries("503");
    customer1->update_cards("11-22-33");
    customer2->update_cards("33-22-11");
    customer2->update_cards("44-33-22");

    users.push_back(customer1);
    users.push_back(customer2);
}

void Users_manager::access_menu()
{

    int choice = display_menu({"Login", "Sign up"});
    if (choice == 1)
        login();
    else if (choice == 2)
        sign_up();
    else
        assert(false);
}

void Users_manager::view_profile()
{
    std::cout << active_user;
}

User *Users_manager::get_current_user()
{
    return active_user;
}

Users_manager::~Users_manager()
{
    reset_data();
}
