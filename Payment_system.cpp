#include "Payment_system.h"

// Payment_card /////////////////////////////
	void Payment_card::set_owner(const string &owner)
	{
		this->owner = owner;
	}
	void Payment_card::set_address(const string &address)
	{
		this->address = address;
	}
	void Payment_card::set_id(const string &id)
	{
		this->id = id;
	}
	void Payment_card::set_ccv(const int &ccv)
	{
		this->ccv = ccv;
	}
	void Payment_card::set_expiry_date(const string &expiry_date)
	{
		this->expiry_date = expiry_date;
	}
	void Payment_card::set_type(const string &type)
	{
		this->type = type;
	}
	const string &Payment_card::get_owner() const
	{
		return owner;
	}
	const string &Payment_card::get_address() const
	{
		return address;
	}
	const string &Payment_card::get_id() const
	{
		return id;
	}
	const string &Payment_card::get_expiry_date() const
	{
		return expiry_date;
	}
	const string &Payment_card::get_type() const
	{
		return type;
	}
	const int &Payment_card::get_ccv() const
	{
		return ccv;
	}

	void Payment_card::dummy_reader(string owner, string address, string id, int ccv, string expiry_date, string type)
	{
		set_owner(owner);
		set_address(address);
		set_id(id);
		set_ccv(ccv);
		set_expiry_date(expiry_date);
		set_type(type);
	}

	std::istream &Payment_card::read(std::istream &input) 
	{
		cout << "Enter use info. (name , address)\n";
		input >> owner >> address;
		cout << "Enter card info. (type, id, ccv, expiry_date)";
		input >> type >> id >> ccv >> expiry_date;

		return input;
	}

	ostream &Payment_card::print(std::ostream &output) const 
	{
		output << "[" << type << "]: Owner: " << owner << " Card number: " << id << "\n";
		return output;
	}

istream &operator>>(std::istream &input, Payment_card *payment_card)
{
	return payment_card->read(input);
}
ostream &operator<<(std::ostream &output, Payment_card *payment_card)
{
	return payment_card->print(output);
}

// Payment_provider /////////////////////
Payment_provider::~Payment_provider() {}

// PayPal_API ///////////////////////////
	PayPal_API::PayPal_API()
	{
		card = new PayPalCreditCard();
		paypal = new PayPalOnlinePaymentAPI();
	}
	void PayPal_API::set_info(const Payment_card &info) 
	{
		card->name = info.get_owner();
		card->address = info.get_address();
		card->id = info.get_id();
		card->ccv = info.get_ccv();
		card->expiry_date = info.get_expiry_date();

		paypal->SetCardInfo(card);
	}
	bool PayPal_API::make_payment(const double &money) 
	{
		return paypal->MakePayment(money);
	}
	PayPal_API::~PayPal_API()
	{
		if (card != nullptr)
		{
			delete card;
			card = nullptr;
		}
		if (paypal != nullptr)
		{
			delete paypal;
			paypal = nullptr;
		}
	}


// Stripe_API ///////////////////////////
	Stripe_API::Stripe_API()
	{
		card_info = new StripeCardInfo();
		user_info = new StripeUserInfo();
		stripe = new StripePaymentAPI();
	}

	void Stripe_API::set_info(const Payment_card &info) 
	{
		user_info->name = info.get_owner();
		user_info->address = info.get_address();
		card_info->expiry_date = info.get_expiry_date();
		card_info->id = info.get_id();
	}

	bool Stripe_API::make_payment(const double &money) 
	{
		return stripe->WithDrawMoney(*user_info, *card_info, money);
	}
	Stripe_API::~Stripe_API()
	{
		if (card_info != nullptr)
		{
			delete card_info;
			card_info = nullptr;
		}
		if (user_info != nullptr)
		{
			delete user_info;
			user_info = nullptr;
		}
		if (stripe != nullptr)
		{
			delete stripe;
			stripe = nullptr;
		}
	}


// Payment_provider_factory ///////////////////////////
	/* static */ Payment_provider *Payment_provider_factory::our_chosen_payment_provider()
	{
		return new PayPal_API();
	}


// Payment_manager //////////////////////////////////
	const int Payment_manager::view_cards(const vector<string> &user_card_ids) const
	{
		int counter = 0;
		if (user_card_ids.size() == 0)
			return counter;

		// because cards and card_ids (related to user) are recorded at the same order .. we can do this
		for (const auto &card : cards)
		{
			if (counter >= user_card_ids.size())
				break;
			if (card->get_id() == user_card_ids.at(counter))
			{
				cout << ++counter << ": " << card;
			}
		}
		cout << "\n";
		return counter;
	}

	void Payment_manager::load_cards()
	{
		// this uses dummy data
		Payment_card *card1 = new Payment_card();
		Payment_card *card2 = new Payment_card();
		Payment_card *card3 = new Payment_card();

		// those are actual names of our users and their addresses
		card1->dummy_reader("ahmed hamed", "Talkha city", "11-22-33", 123, "25-2025", "Debit Card");
		card2->dummy_reader("mohamed elbaz", "Mansoura city", "33-22-11", 321, "26-2026", "Debit Card");
		card3->dummy_reader("mohamed elbaz", "Mansoura city", "44-33-22", 432, "27-2027", "Credit Card");

		cards.push_back(card1);
		cards.push_back(card2);
		cards.push_back(card3);
	};


	Payment_manager::Payment_manager()
	{
		payment_provider = Payment_provider_factory ::our_chosen_payment_provider();
	}

	void Payment_manager::add_card(Customer *customer)
	{
		Payment_card *card = new Payment_card();
		cin >> card;
		cards.push_back(card);
		customer->update_cards(card->get_id());
	}

	bool Payment_manager::payment_screen(const int &money, Customer *customer)
	{
		cout << "Select a payment choice: \n";
		int total = view_cards(customer->get_card_ids());

		// no cards recorded for this user ?
		if (total == 0)
		{
			cout << "no cards recorded for this user .. please enter any num to add card data or -1 to return to the reservation menu: \n";
			int choice;
			cin >> choice;
			if (choice == -1)
			{
				return false;
			}
			add_card(customer);
			return payment_screen(money, customer);
		}

		// now the user chooses the card he wants to use ..
		int choice = read_int(total);

		// now the payment_provider will make its operations ..
		const Payment_card *chosen_card = cards.at(choice);
		payment_provider->set_info((*chosen_card));
		return (payment_provider->make_payment(money));
	}
