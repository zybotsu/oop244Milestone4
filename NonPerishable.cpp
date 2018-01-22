#define _CRT_SECURE_NO_WARNINGS
#include "ErrorMessage.h"
#include "NonPerishable.h"

using namespace std;
namespace sict
{
	void NonPerishable::name(const char *prodName) {
	
		
		if (prodName != nullptr) //if does have an address
		{
			delete[]m_productName;
			m_productName = new char[strlen(prodName) + 1]; //create space in dynamic memory
			strcpy(m_productName, prodName);
		}
		else
			prodName = nullptr;

	}

	const char *NonPerishable::name() const
	{
		if (m_productName == nullptr)
			return nullptr;
		else return m_productName;
	}


		void NonPerishable::message(const char *message)
	{
			e.message(message);
		//e = message;
	}


	bool NonPerishable::isClear()const {
		if (e.isClear())

			return true;
		else
			return false;
	}
	NonPerishable::NonPerishable(char type)
	{
		//safe empty state
		m_productType = '\0';
		m_productSku[0] = '\0';
		m_productName = nullptr;
		m_productUnit[0] = '\0';
		m_currentQuantity = 0;
		m_quantityNeeded = 0;
		m_price = 0;
		m_taxable = true;
	}

	NonPerishable::NonPerishable(const char* productSku, const char*productName, const char*productUnit, int qty, bool taxable, double pricePreTax, int qtyNeeded)
	{
		//assign
		m_productType = '\0';
		m_productSku[0] = '\0';
		m_productName = nullptr;
		m_productUnit[0] = '\0';
		m_currentQuantity = 0;
		m_quantityNeeded = 0;
		m_price = 0.0;

		strcpy(m_productSku, productSku);
		m_productName = new char[strlen(productName) + 1];
		strcpy(m_productName, productName);
		strcpy(m_productUnit, productUnit);
		m_taxable = taxable;
		m_currentQuantity = qty;
		m_quantityNeeded = qtyNeeded;
		m_price = pricePreTax;
	}

	NonPerishable::NonPerishable(const NonPerishable& other)
	{
		m_productName = nullptr;
		*this = other;

}
	NonPerishable & NonPerishable::operator=(const NonPerishable & other)
	{

		if (this != &other) {
			strcpy(m_productSku, other.m_productSku);
			name(other.m_productName);
			strcpy(m_productUnit, other.m_productUnit);
			m_currentQuantity = other.m_currentQuantity;
			m_quantityNeeded = other.m_quantityNeeded;
			m_taxable = other.m_taxable;
			m_price = other.m_price;

			return *this;
			//if (m_productName_ != nullptr) {
			//delete[] m_productName_;
		}
		else
		m_productSku[0] = '\0';
		m_productName = nullptr;
		m_productUnit[0] = '\0';
		m_currentQuantity = 0;
		m_quantityNeeded = 0;
		m_taxable = false;

		return *this;
	}

	
		NonPerishable::~NonPerishable()
		{
		delete [] m_productName;
		}

		fstream & NonPerishable::store(fstream& file, bool newLine) const
		{
			
			file << m_productType << ',' << m_productSku << ',' << m_productName << ',' << m_price << ',' << m_taxable << ',' << m_currentQuantity 
			   	<< ',' << m_productUnit << ',' << m_quantityNeeded;
			if (newLine) {
				file << endl;
				//return file;
			}
			return file;
		}

		fstream& NonPerishable::load(fstream& file)
		{
			char sku[100];   
			char pName[100]; 
			char unit[100];
			double price;   
			bool taxed;
			int quantity;    

			file.getline(sku, 100, ',');
			file.getline(pName, 100, ',');
			file.getline(unit, 100, ',');
			file >> price;
			file.ignore();
			file >> taxed;
			file.ignore();
			file >> quantity;
			file.ignore();

			strcpy(m_productSku, sku);
			strcpy(m_productName, pName);
			strcpy(m_productUnit, unit);
			m_price = price;
			m_taxable = taxed;
			m_quantityNeeded = quantity;
		

			return file;
		}

		std::ostream &NonPerishable::write(std::ostream & os, bool linear) const
		{

		
				if (linear) {
					os.width(max_sku_length);
					os << left << m_productSku;
					os << '|';
					os.width(20);
					os << left << m_productName;
					os << '|';
					os.width(7);
					os.precision(2);
					os << right << fixed << m_price;
					os << '|';
					os.width(7);
					os.precision(2);
					os << right << fixed << m_productUnit;
					os << '|';
					os.width(7);
					os.precision(2);
					os << right << fixed << m_quantityNeeded;


			return os;
				}
				else
				{
					
					os << "Sku: " << m_productSku << endl;
					os << "Name: " << m_productName << endl;
					os << "Price:" << m_price << endl;
				
					if (taxed())
					{
						os << "Price after tax:" << cost() << endl;		
						}
					else {
						os << "N/A" << endl;
					}
				}
					return os;
		}

		std::istream & NonPerishable::read(std::istream & is){
	    char m_sku[max_sku_length + 1];
		string m_name;
		double m_price;
		char m_taxed;
		this->e.clear();

		while (!is.fail()) {
			cout << "Item Entry:" << endl;
			cout << "Sku: ";
			is >> m_sku;
			cout << "Name:" << endl;
			is.ignore();
			getline(is, m_name, '\n');
			cout << "Unit: " << endl;
			is >> m_productUnit;

			cout << "Taxed: ";
			is >> m_taxed;
			if (is.fail() || (m_taxed != 'y' && m_taxed != 'n')) {
				e.message("Invalid Taxed Entry, (y)es or (n)o");
				is.setstate(ios::failbit);
				break;
			}
			if (m_taxed == 'y') {
				setTaxable(true);
			}
			else {
				setTaxable(false);
			}

			cout << "Price: ";
			is >> m_price;
			if (is.fail()) {
				e.message ("Invalid Price Entry");
				break;
			}
			
			cout << "Quantity on hand: ";
			is >> m_currentQuantity;
			if (is.fail()) {
				this->e.message("Invalid Quantity Entry");
				break;
			}

			cout << "Quantity Needed: ";
			is >> m_quantityNeeded;
			if (is.fail()) {
				this->e.message("Invalid Quantity Entry");
				break;
			}

			this->setPrice(m_price);
			this->setQuantity(m_currentQuantity);
			this->setQtyNeeded(m_quantityNeeded);
			this->setProductName(m_productName);
		
//			this->quantity(m_quantity);

			break;
		}
		return is;
		}


		
	
		bool NonPerishable::operator==(const char*fooSku) const
		{
			if (strcmp(m_productSku, fooSku) == 0)
				return true;
			else
				return false;

		}
		
		double NonPerishable::total_cost() const {
		 
		
			double totalcost = 0.0;

			totalcost = m_currentQuantity * cost();


			return totalcost;

		}


		void NonPerishable::quantity(int b)
		{
			m_currentQuantity = b;
		}
		int NonPerishable::quantity() const {

			return  m_currentQuantity;
		}

		int NonPerishable::qtyNeeded() const {
			return m_quantityNeeded;
		}

		double NonPerishable::cost() const {
			double price = m_price;

			if (taxed()) {
				price *= 1 + taxRate;
			}
			return price;
		}

		bool NonPerishable::isEmpty() const {
			if ( m_productName == nullptr) 
				return true;
			else
				return false;
			}



				int NonPerishable::operator+=(int add) {
					if (add > 0)
					{
						m_currentQuantity += add;
						return m_currentQuantity;
					}
					else
						return m_currentQuantity;
				}




				bool NonPerishable::operator>(const char* item) const {
					int a = strcmp(m_productSku, item);
					if (a > 0)
						return true;
					else
						return false;
				}

				bool NonPerishable::operator>(const Product& name) const
				{
					int a = strcmp(m_productSku, name.name());
					if (a > 0)
						return true;
					else
						return false;
				}



				std::ostream& operator<<(std::ostream&os, const Product& I)
				{
					
					return I.write(os, true);
					//return os;
				}



				std::istream& operator >> (std::istream& is, Product& I) {
					return I.read(is);
					
				}


				double operator+=(double& l, const Product& item) {
					// * item.quantity());
					return l += item.total_cost();
					
				
				}


				void NonPerishable::setTaxable(bool b) {

					m_taxable = b;
				}


				void NonPerishable::setQuantity(int qty) {

					m_currentQuantity = qty;
				}





				void NonPerishable::setQtyNeeded(int qtyNeeded) {

					m_quantityNeeded = qtyNeeded;
				}


				void NonPerishable::setProductName(char* name) {

					m_productName = name;
				}


				void NonPerishable::setPrice(double price)
				{
					m_price = price;
				}




				bool NonPerishable::taxed() const {
					return m_taxable;
				}

				Product * CreateProduct()
				{
					//NonPerishable *obj;

					//return obj;
					NonPerishable *p = new NonPerishable;
					return p;

				}

}
