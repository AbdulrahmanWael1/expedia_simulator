/////////////// Payment system ////////////


#ifndef PAYMENT_SYSTEM_
#define PAYMENT_SYSTEM_

// // useful
// #include "helperFNs_and_properties.h"

// it's also dependent on
#include "Users_system.h"

// local API
#include "expedia_payments_api.h"



class Payment_card : public Printable, public Readable
{
private:
	string owner;
	string address;
	string id;
	int ccv;
	string expiry_date;
	string type;

	// setters
	void set_owner(const string &owner);
	void set_address(const string &address);
	void set_id(const string &id);
	void set_ccv(const int &ccv);
	void set_expiry_date(const string &expiry_date);
	void set_type(const string &type);
public:
	// getters
	const string &get_owner() const;
	const string &get_address() const;
	const string &get_id() const;
	const string &get_expiry_date() const;
	const string &get_type() const;
	const int &get_ccv() const;

	void dummy_reader(string owner, string address, string id, int ccv, string expiry_date, string type);

	virtual std::istream &read(std::istream &input) override;

	virtual ostream &print(std::ostream &output) const override;
};

// the "read" member function which comes from "Readable" interface (property) is used with operator >> ..
istream &operator>>(std::istream &input, Payment_card *payment_card);
ostream &operator<<(std::ostream &output, Payment_card *payment_card);

class Payment_provider
{
public:
	virtual void set_info(const Payment_card &info) = 0;
	virtual bool make_payment(const double &money) = 0;
	virtual ~Payment_provider();
};
// some concrete classes for handling the APIs
class PayPal_API : public Payment_provider
{
private:
	PayPalCreditCard *card;
	PayPalOnlinePaymentAPI *paypal;

public:
	PayPal_API();
	PayPal_API(const PayPal_API &copy) = delete;
	PayPal_API &operator=(const PayPal_API &copy) = delete;
	virtual void set_info(const Payment_card &info) override;
	virtual bool make_payment(const double &money) override;
	~PayPal_API();
};
class Stripe_API : public Payment_provider
{
private:
	StripeCardInfo *card_info;
	StripeUserInfo *user_info;
	StripePaymentAPI *stripe;

public:
	Stripe_API();
	Stripe_API(const Stripe_API &copy) = delete;
	Stripe_API &operator=(const Stripe_API &copy) = delete;
	virtual void set_info(const Payment_card &info) override;

	virtual bool make_payment(const double &money) override;
	~Stripe_API();
};
// this class will provide us with chosen payment provider (API) .. we can specify which API we will use here ..
// the system only uses one provider
class Payment_provider_factory
{
public:
	static Payment_provider *our_chosen_payment_provider();
};

class Payment_manager
{
private:
	vector<Payment_card *> cards;
	Payment_provider *payment_provider;

// this will view the cards of specific user .. by only knowing their IDs (related to that user)
	const int view_cards(const vector<string> &user_card_ids) const;

public:
	void load_cards();

	// this class is intended to only have one copy in the entire life time of the system
	Payment_manager(const Payment_manager *copy) = delete;
	Payment_manager &operator=(const Payment_manager *copy) = delete;
	Payment_manager();

// we need a customer pointer so that we can add the card id to the customer info
	void add_card(Customer *customer);

// all the actual magic happens here
	bool payment_screen(const int &money, Customer *customer);
};

#endif
