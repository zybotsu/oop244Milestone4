#ifndef SICT_NONPERISHABLE_H
#define SICT_NONPERISHABLE_H
#include "Product.h"
#include "ErrorMessage.h"
#include  <cstring>

namespace sict

{
	const int max_sku_length = 7;
	const int max_unit_length = 10;
	const int max_name_length = 75;
	const double taxRate = .13;

	class NonPerishable : public Product
	{
		
	private:
		char  m_productType;
		char m_productSku[max_sku_length];
		char* m_productName;
		char m_productUnit[max_unit_length];
		int m_currentQuantity;
		int m_quantityNeeded;
		double m_price;//price before tax
		bool m_taxable;
		ErrorMessage e;

	protected:
		void name(const char* other);
		const char* name() const;
		double cost() const;
		void message(const char*);
		bool isClear() const;

	public:
		NonPerishable(char type = '\0');
		NonPerishable(const char* productSku,const char*productName, const char*productUnit, int qty = 0, bool taxable =true,  double pricePreTax = 0, int qtyneeded = 0);
		NonPerishable(const NonPerishable& obj);
		NonPerishable& operator=(const NonPerishable&);
		~NonPerishable();
		std::fstream& store(std::fstream& file, bool newLine = true) const;
		std::fstream& load(std::fstream& file);
		std::ostream& write(std::ostream& os, bool linear) const;
		std::istream& read(std::istream& is);
		bool operator==(const char*) const;
		double total_cost() const;
		void quantity(int);
		bool isEmpty() const;
		int qtyNeeded() const;
		int quantity() const;
		bool taxed() const;

		//setter functions
		void setQuantity(int);
		void setQtyNeeded(int);
		void setProductName(char*);
		void setPrice(double);



		bool operator>(const char*) const;
		int operator+=(int);
		bool operator>(const Product&) const;
		void setTaxable(bool b);
	};
	//helper functions
	std::ostream& operator<<(std::ostream&, const Product&);
	std::istream& operator>>(std::istream&, Product&);
	double operator+=(double&, const Product&);
	Product* CreateProduct();












}














#endif
