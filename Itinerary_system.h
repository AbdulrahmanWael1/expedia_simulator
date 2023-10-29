/////////////// Itinerary system ////////////

#ifndef ITINERARY_SYSTEM
#define ITINERARY_SYSTEM

// // useful
// #include "helperFNs_and_properties.h"

// it's also dependent on
#include "Payment_system.h"

// local APIs
#include "expedia_flights_api.h"
#include "expedia_hotels_api.h"



/*
this part of the system named "Itinerary system" contains five things:
1. the "Itinerary manager" makes operations on Itineraries by the following:
2. gets the information to do so from "Sources" ..
3. those sources provides the manager with "options"
4. so that the user can choose from them to make a "reservation"
5. one "Itinerary" is a combination of reservations ..
*/

class Reservation_option : public Printable
{
private:
	double price = 0;
	std::string from_date;
	std::string to_date;

protected:
	void set_price(double price);
	void set_to_date(std::string to_date);
	void set_from_date(std::string from_date);

public:
	virtual const std::string get_type() const = 0;

	const double get_price() const;
	const std::string get_from_date() const;
	const std::string get_to_date() const;
};
// first variation of reservation_option
class Flight_option : public Reservation_option
{
public:
	virtual ostream &print(ostream &output) const override;
};
class AirCanadaFlight_handler : public Flight_option
{
public:
	AirCanadaFlight_handler(const AirCanadaFlight &flight_info);
	AirCanadaFlight_handler();

	void set(const AirCanadaFlight &flight_info, const AirCanadaCustomerInfo &customer_info);
	virtual const std::string get_type() const override;
};
class TurkishFlight_handler : public Flight_option
{
public:
	TurkishFlight_handler();
	TurkishFlight_handler(const TurkishFlight &flight_info);

	void set(const TurkishFlight &flight_info, const TurkishCustomerInfo &customer_info);
	virtual const std::string get_type() const override;
};
// second variation of reservation_option
class Hotel_option : public Reservation_option
{
private:
	std::string room_type;
	int available = 0;

protected:
	void set_room_type(std::string room_type);
	void set_availability(int available);

public:
	virtual ostream &print(ostream &output) const override;
	const int get_available() const;
	const std::string get_room_type() const;
};
class HiltonRoom_handler : public Hotel_option
{
public:
	HiltonRoom_handler();
	HiltonRoom_handler(const HiltonRoom &room);

	void set(const HiltonRoom &room);
	virtual const std::string get_type() const override;
};
class MarriottFoundRoom_handler : public Hotel_option
{
public:
	MarriottFoundRoom_handler();
	MarriottFoundRoom_handler(const MarriottFoundRoom &room);

	void set(const MarriottFoundRoom &room);
	virtual const std::string get_type() const override;
};

class Reservation : public Payable, public Readable, public Printable
{
private:
	std::string from_date;
	std::string to_date;
	std::string specific_type;
	double cost = 0;

protected:
	void set_specific_type(std::string specific_type);
	const std::string get_specific_type() const;
	void set_from_date(std::string from_date);
	void set_to_date(std::string to_date);
	void set_cost(double cost);

public:
	std::string get_from_date() const;
	std::string get_to_date() const;

	virtual const double get_cost() const override;
	virtual void update_with_chosen_option(Reservation_option *option) = 0;
	virtual ~Reservation();
};
class Flight : public Reservation
{
private:
	std::string from; // from what country ?
	std::string to;
	int num_of_adults = 0;
	int num_of_children = 0;
	int num_of_infants = 0;

public:
	virtual istream &read(istream &input) override;
	virtual ostream &print(ostream &output) const override;
	virtual void update_with_chosen_option(Reservation_option *option) override;

	const std::string get_from_destination() const;
	const std::string get_to_destination() const;
	const int get_num_of_adults() const;
	const int get_num_of_children() const;
	const int get_num_of_infants() const;

	void dummy_reader(std::string from_date, std::string from, std::string to_date, std::string to, double cost, int adults, int children, int infants, std::string specific_type);

	virtual ~Flight();
};
class Hotel : public Reservation
{
private:
	std::string country;
	std::string city;
	int num_of_adults = 0;
	int num_of_children = 0;
	int available_rooms = 0;
	std::string room_type;

	void set_available_rooms(int num_of_rooms);
	void set_room_type(std::string room_type);

public:
	virtual istream &read(istream &input) override;
	virtual ostream &print(ostream &output) const override;
	virtual void update_with_chosen_option(Reservation_option *option) override;
	const std::string get_country() const;
	const std::string get_city() const;
	const int get_num_of_adults() const;
	const int get_num_of_children() const;
	const int get_needed_rooms() const;

	void dummy_reader(std::string from_date, std::string country, std::string to_date, std::string city, double cost, std::string room_type, int available_rooms, int adults, int children, std::string specific_type);

	virtual ~Hotel();
};
// taking the reservation type as std::string input, we can generate this type as a class
class Reservation_factory
{
public:
	static Reservation *get_reservation(std::string type);
};
// input and output reservations
ostream &operator<<(ostream &output, Reservation *reservation);
istream &operator>>(istream &input, Reservation *reservation);

class Itinerary : public Payable, public Printable
{
private:
	std::vector<Reservation *> reservations;
	static int id_generator;
	std::string id;

public:
	Itinerary();
	Itinerary(const Itinerary &copy) = delete;
	Itinerary &operator=(const Itinerary &copy) = delete;

	virtual ostream &print(ostream &output) const override;
	virtual const double get_cost() const override;

	void update_reservations(Reservation *reservation);
	const std::string &get_id();

	virtual ~Itinerary();
};
ostream &operator<<(ostream &output, Itinerary *itinerary);

class Reservation_data_source
{

protected:
	std::vector<Reservation_option *> options;
	void reset_options();

public:
	Reservation_data_source();
	Reservation_data_source(const Reservation_data_source &reservation_manager) = delete;
	Reservation_data_source &operator=(const Reservation_data_source &reservation_manager) = delete;
	virtual const std::string get_type() = 0;
	virtual std::vector<Reservation_option *> view_options(Reservation *reservation, std::string type) = 0;
	virtual bool reserve(Reservation_option *option) = 0;
	virtual bool cancel_reservation(Reservation_option *option) = 0;
	virtual ~Reservation_data_source();
};
// the following API_handlers are wrapping the actual APIs functions so that we can use them in our system polymorphically
class AirCanadaFlightAPI_handler : public Reservation_data_source
{
private:
	AirCanadaOnlineAPI *aircanada;

public:
	AirCanadaFlightAPI_handler();
	AirCanadaFlightAPI_handler(const AirCanadaFlightAPI_handler &copy) = delete;
	AirCanadaFlightAPI_handler &operator=(const AirCanadaFlightAPI_handler &copy) = delete;

	virtual const std::string get_type() override;
	virtual std::vector<Reservation_option *> view_options(Reservation *reservation, std::string type) override;
	virtual bool reserve(Reservation_option *option) override;
	virtual bool cancel_reservation(Reservation_option *option) override;
	virtual ~AirCanadaFlightAPI_handler();
};
class TurkishAirlinesAPI_handler : public Reservation_data_source
{
private:
	TurkishAirlinesOnlineAPI *turkish;

public:
	TurkishAirlinesAPI_handler();
	TurkishAirlinesAPI_handler(const TurkishAirlinesAPI_handler &copy) = delete;
	TurkishAirlinesAPI_handler &operator=(const TurkishAirlinesAPI_handler &copy) = delete;

	virtual const std::string get_type() override;
	virtual std::vector<Reservation_option *> view_options(Reservation *reservation, std::string type) override;

	// this will always return false as the API returns false
	virtual bool reserve(Reservation_option *option) override;
	virtual bool cancel_reservation(Reservation_option *option) override;
	~TurkishAirlinesAPI_handler();
};
class HiltonHotelAPI_handler : public Reservation_data_source
{
private:
	HiltonHotelAPI *hilton;

public:
	HiltonHotelAPI_handler();
	HiltonHotelAPI_handler(const HiltonHotelAPI_handler &copy) = delete;
	HiltonHotelAPI_handler &operator=(const HiltonHotelAPI_handler &copy) = delete;

	virtual const std::string get_type() override;
	virtual std::vector<Reservation_option *> view_options(Reservation *reservation, std::string type) override;
	virtual bool reserve(Reservation_option *option) override;
	virtual bool cancel_reservation(Reservation_option *option);

	~HiltonHotelAPI_handler();
};
class MarriottHotelAPI_handler : public Reservation_data_source
{
private:
	MarriottHotelAPI *marriott;

public:
	MarriottHotelAPI_handler();
	MarriottHotelAPI_handler(const MarriottHotelAPI_handler &copy) = delete;
	MarriottHotelAPI_handler &operator=(const MarriottHotelAPI_handler &copy) = delete;
	virtual const std::string get_type() override;
	virtual std::vector<Reservation_option *> view_options(Reservation *reservation, std::string type) override;
	virtual bool reserve(Reservation_option *option) override;
	virtual bool cancel_reservation(Reservation_option *option) override;
	~MarriottHotelAPI_handler();
};
// returns all types of sources that we currently are using in our system
class Reservation_data_source_factory
{
public:
	static std::vector<Reservation_data_source *> all_sources();
};

class Itinerary_manager
{
private:
	Itinerary *active_itinerary = nullptr;
	std::vector<Itinerary *> itineraries;
	std::vector<Reservation_data_source *> sources;
	std::vector<Reservation_option *> all_options;

	// when itinerary is done, it's time to pay :)
	void itinerary_done(Payment_manager *payment_manager, Customer *customer);
	void itinerary_canceled();
	void update_itineraries(Customer *customer);
	void add_reservation(const std::string type);
	// view options .. choose one .. update your reservation info
	void search_options(Reservation *reservation, const std::string type);

	void reset_data_sources();
	void reset_all_options();
	void reset_and_initialize_active_itinerary();

public:
	void load_data_sources();
	void load_itineraries();

	Itinerary_manager();
	Itinerary_manager(const Itinerary_manager &Itinerary_manager) = delete;
	Itinerary_manager &operator=(const Itinerary_manager &Itinerary_manager) = delete;

	// the main two functions of the system as a whole
	void make_itinerary(Payment_manager *payment_manager, Customer *customer);
	void list_itineraries(Customer *customer);

	~Itinerary_manager();
};

#endif
