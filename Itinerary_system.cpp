#include "Itinerary_system.h"

// Reservation_option //////////////////
const double Reservation_option ::get_price() const
{
	return price;
}
const std::string Reservation_option ::get_from_date() const
{
	return from_date;
}
const std::string Reservation_option ::get_to_date() const
{
	return to_date;
}
void Reservation_option ::set_price(double price)
{
	this->price = price;
}
void Reservation_option ::set_to_date(std::string to_date)
{
	this->to_date = to_date;
}
void Reservation_option ::set_from_date(std::string from_date)
{
	this->from_date = from_date;
}


// flight_option ////////////////////
ostream &Flight_option::print(ostream &output) const
{
	output << "Airline: " << get_type() << ", Cost: " << get_price() << ", Departure Date " << get_from_date() << " , Arrival date " << get_to_date() << "\n";
	return output;
}


// AirCanadaFlight_handler //////////////////
	AirCanadaFlight_handler::AirCanadaFlight_handler(const AirCanadaFlight &flight_info)
	{
		AirCanadaCustomerInfo customer_info;
		set(flight_info, customer_info);
	}
	AirCanadaFlight_handler::AirCanadaFlight_handler() = default;

void AirCanadaFlight_handler::set(const AirCanadaFlight &flight_info, const AirCanadaCustomerInfo &customer_info)
{
	set_price(flight_info.price);
	set_from_date(flight_info.date_time_from);
	set_to_date(flight_info.date_time_to);
}
const std::string AirCanadaFlight_handler::get_type() const
{
	return "AirCanada Airlines";
}


// TurkishFlight_handler ////////////////
	TurkishFlight_handler::TurkishFlight_handler() = default;
	TurkishFlight_handler::TurkishFlight_handler(const TurkishFlight &flight_info)
	{
		TurkishCustomerInfo customer_info;
		set(flight_info, customer_info);
	}

void TurkishFlight_handler::set(const TurkishFlight &flight_info, const TurkishCustomerInfo &customer_info)
{
	set_price(flight_info.cost);
	set_from_date(flight_info.datetime_from);
	set_to_date(flight_info.datetime_to);
}
const std::string TurkishFlight_handler::get_type() const
{
	return "Turkish Airlines";
}


// Hotel_option ////////////////////////
void Hotel_option::set_room_type(std::string room_type)
{
	this->room_type = room_type;
}
void Hotel_option::set_availability(int available)
{
	this->available = available;
}
ostream &Hotel_option::print(ostream &output) const
{
	output << "Hotel: " << get_type() << ", Room type: " << get_room_type() << "(" << get_available() << "), Price per night: " << get_price() << ", From date: " << get_from_date() << " to " << get_to_date() << "\n";
	return output;
}
const int Hotel_option::get_available() const
{
	return available;
}
const std::string Hotel_option::get_room_type() const
{
	return room_type;
}


// HiltonRoom_handler /////////////////////
	HiltonRoom_handler::HiltonRoom_handler() = default;
	HiltonRoom_handler::HiltonRoom_handler(const HiltonRoom &room)
	{
		set(room);
	}

void HiltonRoom_handler::set(const HiltonRoom &room)
{
	set_room_type(room.room_type);
	set_availability(room.available);
	set_price(room.price_per_night);
	set_from_date(room.date_from);
	set_to_date(room.date_to);
}
const std::string HiltonRoom_handler::get_type() const
{
	return "Hilton Hotel";
}


// MarriottFoundRoom_handler /////////////////////
	MarriottFoundRoom_handler::MarriottFoundRoom_handler() = default;
	MarriottFoundRoom_handler::MarriottFoundRoom_handler(const MarriottFoundRoom &room)
	{
		set(room);
	}

void MarriottFoundRoom_handler::set(const MarriottFoundRoom &room)
{
	set_room_type(room.room_type);
	set_availability(room.available);
	set_price(room.price_per_night);
	set_from_date(room.date_from);
	set_to_date(room.date_to);
}
const std::string MarriottFoundRoom_handler::get_type() const
{
	return "Marriott Hotel";
}

ostream &operator<<(ostream &output, Reservation_option *reservation_option)
{
	return reservation_option->print(output);
}


// Reservation ////////////////////////////
int cost = 0;

void Reservation::set_specific_type(std::string specific_type)
{
	this->specific_type = specific_type;
}
const std::string Reservation::get_specific_type() const
{
	return specific_type;
}

std::string Reservation::get_from_date() const
{
	return from_date;
}
std::string Reservation::get_to_date() const
{
	return to_date;
}
void Reservation::set_from_date(std::string from_date)
{
	this->from_date = from_date;
}
void Reservation::set_to_date(std::string to_date)
{
	this->to_date = to_date;
}
const double Reservation::get_cost() const
{
	return cost;
}
void Reservation::set_cost(double cost)
{
	this->cost = cost;
}
	Reservation:: ~Reservation() {}


// Flight ////////////////////////////////////

istream &Flight::read(istream &input)
{
	std::string str;
	std::cout << "Enter From: ";
	input >> from;
	std::cout << "Enter From Date (dd-mm-yy): ";
	input >> str;
	set_from_date(str);
	std::cout << "Enter To: ";
	input >> to;
	std::cout << "Enter To Date (dd-mm-yy): ";
	input >> str;
	set_to_date(str);
	std::cout << "Enter # of adults children (5-16) and Infants: ";
	input >> num_of_adults >> num_of_children >> num_of_infants;

	return input;
}
ostream &Flight::print(ostream &output) const
{
	output << "Airline reservation with details: " << get_specific_type() << ", From " << from << " on " << get_from_date() << "\n";
	output << "\tTo " << to << " on " << get_to_date() << "\n";
	output << "\tAdults: " << num_of_adults << ", Children: " << num_of_children << ", infants: " << num_of_infants << "\n";
	output << "\tTotal cost: " << get_cost() << "\n";

	return output;
}
void Flight::update_with_chosen_option(Reservation_option *option)
{
	Flight_option *flight_option = dynamic_cast<Flight_option *>(option);
	set_specific_type(flight_option->get_type());
	set_cost(flight_option->get_price());
	set_from_date(flight_option->get_from_date());
	set_to_date(flight_option->get_to_date());
}

const std::string Flight::get_from_destination() const
{
	return from;
}
const std::string Flight::get_to_destination() const
{
	return to;
}
const int Flight::get_num_of_adults() const
{
	return num_of_adults;
}
const int Flight::get_num_of_children() const
{
	return num_of_children;
}
const int Flight::get_num_of_infants() const
{
	return num_of_infants;
}

void Flight::dummy_reader(std::string from_date, std::string from, std::string to_date, std::string to, double cost, int adults, int children, int infants, std::string specific_type)
{
	set_from_date(from_date);
	this->from = from;
	set_to_date(to_date);
	this->to = to;
	set_cost(cost);
	this->num_of_adults = adults;
	this->num_of_children = children;
	this->num_of_infants = infants;
	set_specific_type(specific_type);
}

	Flight:: ~Flight() {}


// Hotel //////////////////////////////////////
void Hotel::set_available_rooms(int num_of_rooms)
{
	available_rooms = num_of_rooms;
}
void Hotel::set_room_type(std::string room_type)
{
	this->room_type = room_type;
}

istream &Hotel::read(istream &input)
{
	std::string str;
	std::cout << "Enter From Date (dd-mm-yy): ";
	input >> str;
	set_from_date(str);
	std::cout << "Enter To Date (dd-mm-yy): ";
	input >> str;
	set_to_date(str);
	std::cout << "Enter country: ";
	input >> country;
	std::cout << "Enter city: ";
	input >> city;
	std::cout << "Enter # of adults and children: ";
	input >> num_of_adults >> num_of_children;

	return input;
}
ostream &Hotel::print(ostream &output) const
{
	output << "Hotel reservation: " << get_specific_type() << ": " << city << " @ " << country << "\n";
	output << "\t" << get_from_date() << " to " << get_to_date() << " : " << available_rooms << "\n";
	output << "\tAdults: " << num_of_adults << ", Children: " << num_of_children << "\n";
	output << "\tTotal cost: " << get_cost() << "\n";

	return output;
}
void Hotel::update_with_chosen_option(Reservation_option *option)
{
	Hotel_option *hotel_option = dynamic_cast<Hotel_option *>(option);
	set_specific_type(hotel_option->get_type());
	set_room_type(hotel_option->get_room_type());
	set_available_rooms(hotel_option->get_available());
	set_cost(hotel_option->get_price());
	set_from_date(hotel_option->get_from_date());
	set_to_date(hotel_option->get_to_date());
}
const std::string Hotel::get_country() const
{
	return country;
}
const std::string Hotel::get_city() const
{
	return city;
}
const int Hotel::get_num_of_adults() const
{
	return num_of_adults;
}
const int Hotel::get_num_of_children() const
{
	return num_of_children;
}
const int Hotel::get_needed_rooms() const
{
	return num_of_adults + num_of_children / 3;
}

void Hotel::dummy_reader(std::string from_date, std::string country, std::string to_date, std::string city, double cost, std::string room_type, int available_rooms, int adults, int children, std::string specific_type)
{
	set_from_date(from_date);
	this->country = country;
	set_to_date(to_date);
	this->city = city;
	set_cost(cost);
	this->room_type = room_type;
	this->available_rooms = available_rooms;
	this->num_of_adults = adults;
	this->num_of_children = children;
	set_specific_type(specific_type);
}

	Hotel:: ~Hotel() {}


// Reservation_factory ///////////////////////////////
/* static */ Reservation *Reservation_factory::get_reservation(std::string type)
{
	if (type == "Flight")
		return new Flight();
	else if (type == "Hotel")
		return new Hotel();
	else
		return nullptr;
}

ostream &operator<<(ostream &output, Reservation *reservation)
{
	return reservation->print(output);
}
istream &operator>>(istream &input, Reservation *reservation)
{
	return reservation->read(input);
}


// Itinerary ////////////////////////////////////
int Itinerary::id_generator = 500;

Itinerary::Itinerary()
{
	id = std::to_string(++id_generator);
}

ostream &Itinerary::print(ostream &output) const
{
	output << "***************************************************\n";
	output << "Itinerary of " << (int)reservations.size() << " sub-reservations\n";
	for (const auto &reservation : reservations)
		output << reservation << "\n";
	output << "Total Itinerary cost: " << get_cost() << "\n";
	output << "***************************************************\n";
	return output;
}
const double Itinerary::get_cost() const
{
	double total_cost = 0;
	for (const auto &reservation : reservations)
	{
		total_cost += reservation->get_cost();
	}
	return total_cost;
}

void Itinerary::update_reservations(Reservation *reservation)
{
	reservations.push_back(reservation);
}
const std::string &Itinerary::get_id()
{
	return id;
}

Itinerary::~Itinerary()
{
	for (auto *&reservation : reservations)
	{
		if (reservation != nullptr)
		{
			delete reservation;
			reservation = nullptr;
		}
	}
	reservations.clear();
}

ostream &operator<<(ostream &output, Itinerary *itinerary)
{
	return itinerary->print(output);
}


// Reservation_data_source ///////////////////////////////
Reservation_data_source::Reservation_data_source() = default;
void Reservation_data_source::reset_options()
{
	for (auto *&option : options)
	{
		if (option != nullptr)
		{
			delete option;
			option = nullptr;
		}
	}
	options.clear();
}
Reservation_data_source::~Reservation_data_source()
{
	reset_options();
}


// AirCanadaFlightAPI_handler ////////////////////////////
AirCanadaFlightAPI_handler::AirCanadaFlightAPI_handler()
{
	aircanada = new AirCanadaOnlineAPI();
}

const std::string AirCanadaFlightAPI_handler::get_type()
{
	return "Flight";
}
std::vector<Reservation_option *> AirCanadaFlightAPI_handler::view_options(Reservation *reservation, std::string type)
{
	reset_options();
	assert(this->get_type() == type);
	Flight *flight = dynamic_cast<Flight *>(reservation);
	const std::vector<AirCanadaFlight> &flight_options = aircanada->GetFlights(flight->get_from_destination(),
																			   flight->get_from_date(),
																			   flight->get_to_destination(),
																			   flight->get_to_date(),
																			   flight->get_num_of_adults(),
																			   flight->get_num_of_children());

	for (const AirCanadaFlight &flight_option : flight_options)
	{
		options.push_back(new AirCanadaFlight_handler(flight_option));
	}
	return options;
}
bool AirCanadaFlightAPI_handler::reserve(Reservation_option *option)
{
	AirCanadaFlight flight_info;
	flight_info.price = option->get_price();
	flight_info.date_time_to = option->get_to_date();
	flight_info.date_time_from = option->get_from_date();

	AirCanadaCustomerInfo customer_info;

	return aircanada->ReserveFlight(flight_info, customer_info);
}
bool AirCanadaFlightAPI_handler::cancel_reservation(Reservation_option *option)
{
	// this is the code that is supposed to run ... but the API is incomplete

	// AirCanadaFlight flight_info;
	// flight_info.price = option->get_price();
	// flight_info.date_time_to = option->get_to_date();
	// flight_info.date_time_from = option->get_from_date();

	// AirCanadaCustomerInfo customer_info;

	// return aircanada.CancelReserveFlight(flight_info,customer_info);

	return true;
}
AirCanadaFlightAPI_handler::~AirCanadaFlightAPI_handler()
{
	if (aircanada != nullptr)
		delete aircanada;
	aircanada = nullptr;
	Reservation_data_source ::~Reservation_data_source();
}


// TurkishAirlinesAPI_handler /////////////////////////////
TurkishAirlinesAPI_handler::TurkishAirlinesAPI_handler()
{
	turkish = new TurkishAirlinesOnlineAPI();
}

const std::string TurkishAirlinesAPI_handler::get_type()
{
	return "Flight";
}
std::vector<Reservation_option *> TurkishAirlinesAPI_handler::view_options(Reservation *reservation, std::string type)
{
	reset_options();
	assert(this->get_type() == type);
	Flight *flight = dynamic_cast<Flight *>(reservation);
	turkish->SetFromToInfo(flight->get_from_date(),
						   flight->get_from_destination(),
						   flight->get_to_date(),
						   flight->get_to_destination());
	turkish->SetPassengersInfo(flight->get_num_of_infants(),
							   flight->get_num_of_children(),
							   flight->get_num_of_adults());

	const std::vector<TurkishFlight> &flight_options = turkish->GetAvailableFlights();
	for (const TurkishFlight &flight_option : flight_options)
	{
		options.push_back(new TurkishFlight_handler(flight_option));
	}
	return options;
}

// this will always return false as the API returns false
bool TurkishAirlinesAPI_handler::reserve(Reservation_option *option)
{
	TurkishFlight flight_info;
	flight_info.cost = option->get_price();
	flight_info.datetime_from = option->get_from_date();
	flight_info.datetime_to = option->get_to_date();

	TurkishCustomerInfo customer_info;

	return turkish->ReserveFlight(customer_info, flight_info);
}
bool TurkishAirlinesAPI_handler::cancel_reservation(Reservation_option *option)
{
	// no implementation for this in the API - but it's logical to have it

	return true; // true means done successfully
}
TurkishAirlinesAPI_handler::~TurkishAirlinesAPI_handler()
{
	if (turkish != nullptr)
		delete turkish;
	turkish = nullptr;
	Reservation_data_source ::~Reservation_data_source();
}


// HiltonHotelAPI_handler ///////////////////////////////////
HiltonHotelAPI_handler::HiltonHotelAPI_handler()
{
	hilton = new HiltonHotelAPI();
}

const std::string HiltonHotelAPI_handler::get_type()
{
	return "Hotel";
}
std::vector<Reservation_option *> HiltonHotelAPI_handler::view_options(Reservation *reservation, std::string type)
{
	reset_options();
	assert(this->get_type() == type);
	Hotel *hotel = dynamic_cast<Hotel *>(reservation);
	const std::vector<HiltonRoom> &room_options = hilton->SearchRooms(hotel->get_country(),
																	  hotel->get_city(),
																	  hotel->get_from_date(),
																	  hotel->get_to_date(),
																	  hotel->get_num_of_adults(),
																	  hotel->get_num_of_children(),
																	  hotel->get_needed_rooms());

	for (const auto &room_option : room_options)
	{
		options.push_back(new HiltonRoom_handler(room_option));
	}
	return options;
}
bool HiltonHotelAPI_handler::reserve(Reservation_option *option)
{
	// this has no implementation in the provided API but it's logical to have it
	return true;
}
bool HiltonHotelAPI_handler::cancel_reservation(Reservation_option *option)
{
	// this has no implementation in the provided API but it's logical to have it
	return true;
}

HiltonHotelAPI_handler::~HiltonHotelAPI_handler()
{
	if (hilton != nullptr)
		delete hilton;
	hilton = nullptr;
	Reservation_data_source ::~Reservation_data_source();
}


// MarriottHotelAPI_handler /////////////////////////////////
MarriottHotelAPI_handler::MarriottHotelAPI_handler()
{
	marriott = new MarriottHotelAPI();
}
const std::string MarriottHotelAPI_handler::get_type()
{
	return "Hotel";
}
std::vector<Reservation_option *> MarriottHotelAPI_handler::view_options(Reservation *reservation, std::string type)
{
	reset_options();
	assert(this->get_type() == type);
	Hotel *hotel = dynamic_cast<Hotel *>(reservation);
	const std::vector<MarriottFoundRoom> &room_options = marriott->FindRooms(hotel->get_from_date(),
																			 hotel->get_to_date(),
																			 hotel->get_country(),
																			 hotel->get_city(),
																			 hotel->get_needed_rooms(),
																			 hotel->get_num_of_adults(),
																			 hotel->get_num_of_children());

	for (const auto &room_option : room_options)
	{
		options.push_back(new MarriottFoundRoom_handler(room_option));
	}
	return options;
}
bool MarriottHotelAPI_handler::reserve(Reservation_option *option)
{
	// this has no implementation in the provided API but it's logical to have it
	return true;
}
bool MarriottHotelAPI_handler::cancel_reservation(Reservation_option *option)
{
	// this has no implementation in the provided API but it's logical to have it
	return true;
}
MarriottHotelAPI_handler::~MarriottHotelAPI_handler()
{
	if (marriott != nullptr)
		delete marriott;
	marriott = nullptr;
	Reservation_data_source ::~Reservation_data_source();
}


// Reservation_data_source_factory //////////////////////////////////
/* static */ std::vector<Reservation_data_source *> Reservation_data_source_factory::all_sources()
{
	std::vector<Reservation_data_source *> all;
	all.push_back(new AirCanadaFlightAPI_handler());
	all.push_back(new TurkishAirlinesAPI_handler());
	all.push_back(new HiltonHotelAPI_handler());
	all.push_back(new MarriottHotelAPI_handler());

	return all;
}


// Itinerary_manager //////////////////////////////////
	void Itinerary_manager::itinerary_done(Payment_manager *payment_manager, Customer *customer)
	{
		if (payment_manager->payment_screen(active_itinerary->get_cost(), customer))
		{
			std::cout << "Money is withdrawn successfully\n";
			std::cout << "Reservation confirmed\n";
			std::cout << "Itinerary reserved\n";
		}
	}
	void Itinerary_manager::itinerary_canceled()
	{
		// we can make changes to this in the future .. but for now it only displays a message to the console
		std::cout << "Reservation canceled\n";
		std::cout << "Itinerary deprecated\n";
	}
	void Itinerary_manager::update_itineraries(Customer *customer)
	{
		customer->update_itineraries(active_itinerary->get_id());
		itineraries.push_back(active_itinerary);
		cout << "Itinerary reserved\n";
	}
	void Itinerary_manager::add_reservation(const std::string type)
	{
		// the following (reservation) will be deleted in the itinerary obj itself .. not here in the manager
		Reservation *reservation = Reservation_factory ::get_reservation(type);
		assert(reservation != nullptr);

		// this will read the data of the reservation
		std::cin >> reservation;

		// this will display the options, prompt the user to choose one, and then update the data of reservation with the chosen option
		search_options(reservation, type);

		// update our vector of reservations with the current reservation
		active_itinerary->update_reservations(reservation);
	}
	// view options .. choose one .. update your reservation info
	void Itinerary_manager::search_options(Reservation *reservation, const std::string type)
	{
		// load all our possible data sources (APIs) + reset options to restart correctly every time
		reset_all_options();

		// display all options coming from those data sources (APIs)
		for (auto *&source : sources)
		{
			if (source->get_type() == type)
			{
				std::vector<Reservation_option *> options = source->view_options(reservation, type);
				for (Reservation_option *&option : options)
				{
					all_options.push_back(option);
					std::cout << option;
				}
			}
		}

		// here we will read the user's choice
		int choice;
		while (true)
		{
			std::cout << "Enter -1 to cancel or number in range 1 - " << all_options.size() << ": ";
			std::cin >> choice;
			if (choice == -1)
				return;
			else
			{
				if (choice >= 1 && choice <= all_options.size())
				{
					break;
				}
			}

			// if you ended up here then the user chose a wrong number
			std::cout << "ERROR: wrong choice .. try again!\n";
		}

		// now updating the our reservation info with the option the user have chosen
		Reservation_option *chosen_option = all_options.at(choice - 1);
		reservation->update_with_chosen_option(chosen_option);
	}

	void Itinerary_manager::reset_data_sources()
	{
		for (auto *&source : sources)
		{
			if (source != nullptr)
			{
				delete source;
				source = nullptr;
			}
		}
		sources.clear();
	}
	void Itinerary_manager::reset_all_options()
	{
		////// the only class allowed to delete dynamically allocated memory is the one that created it .. so the next commented code will corrupt the application if not commented
		// for (auto *&option : all_options)
		// {
		// 	if (option != nullptr)
		// 	{
		// 		delete option;
		// 		option = nullptr;
		// 	}
		// }
		all_options.clear();
	}
	void Itinerary_manager::reset_and_initialize_active_itinerary()
	{
		if (active_itinerary != nullptr)
			delete active_itinerary;
		active_itinerary = nullptr;
		active_itinerary = new Itinerary();
	}

	void Itinerary_manager::load_data_sources()
	{
		reset_data_sources();
		sources = Reservation_data_source_factory ::all_sources();
	}
	void Itinerary_manager::load_itineraries()
	{
		// loading with dummy data
		Flight *flight1 = new Flight();
		Hotel *hotel1 = new Hotel();
		Flight *flight2 = new Flight();
		Hotel *hotel2 = new Hotel();

		flight1->dummy_reader("12-12-2012", "Canada", "13-12-2012", "Australia", 200.5, 2, 5, 1, "AirCanada Airlines");
		hotel1->dummy_reader("13-12-2012", "Australia", "20-12-2012", "Sidney", 50, "Deluxe View", 6, 2, 5, "Marriott Hotel");
		flight2->dummy_reader("24-12-2012", "Egypt", "25-12-2012", "USA", 500.12345, 5, 2, 1, "Turkish Airlines");
		hotel2->dummy_reader("25-12-2012", "USA", "30-12-2012", "Washington", 100, "Interior View", 6, 5, 2, "Hilton Hotel");

		Itinerary *itinerary1 = new Itinerary();
		Itinerary *itinerary2 = new Itinerary();
		Itinerary *itinerary3 = new Itinerary();

		itinerary1->update_reservations(flight1);
		itinerary1->update_reservations(hotel1);
		itinerary2->update_reservations(flight2);
		itinerary3->update_reservations(hotel2);

		itineraries.push_back(itinerary1);
		itineraries.push_back(itinerary2);
		itineraries.push_back(itinerary3);
	}

	Itinerary_manager::Itinerary_manager() = default;

	// the main two functions of the system as a whole
	void Itinerary_manager::make_itinerary(Payment_manager *payment_manager, Customer *customer)
	{
		reset_and_initialize_active_itinerary();
		while (true)
		{
			int choice = display_menu({"Add Flight", "Add Hotel", "Done", "cancel"});
			if (choice == 1)
				add_reservation("Flight");
			else if (choice == 2)
				add_reservation("Hotel");
			else if (choice == 3)
			{
				itinerary_done(payment_manager, customer);
				update_itineraries(customer);
				break;
			}
			else
			{
				itinerary_canceled();
				break;
			}
		}
	}
	void Itinerary_manager::list_itineraries(Customer *customer)
	{
		if (customer->get_itinerary_ids().size() == 0)
		{
			std::cout << "\n\nNo itineraries yet .. book one to show it here :)\n\n";
			return;
		}

		// all itineraries are in the same order as itineraries specific to the user.. so we can do this
		int counter = 0;
		for (const auto &itinerary : itineraries)
		{
			if (counter < customer->get_itinerary_ids().size())
			{
				if (itinerary->get_id() == customer->get_itinerary_ids().at(counter))
				{
					std::cout << itinerary;
					counter++;
				}
			}
		}
	}

	Itinerary_manager::~Itinerary_manager()
	{
		if (active_itinerary != nullptr)
			delete active_itinerary;
		active_itinerary = nullptr;

		for (auto *&itinerary : itineraries)
		{
			if (itinerary != nullptr)
			{
				delete itinerary;
				itinerary = nullptr;
			}
		}
		itineraries.clear();

		reset_data_sources();
	}
