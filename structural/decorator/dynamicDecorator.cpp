#include <iomanip>
#include <iostream>
#include <memory>
#include <string>

class ICoffee  // interface
{
public:
	// pure virtual functions
	virtual float GetCost() const = 0;
	virtual std::string GetIngredients() const = 0;
	virtual void Display() = 0;
};

class BaseCoffee : public ICoffee
{
public:
	float GetCost() const override
	{
		return 1.f;
	}
	std::string GetIngredients() const override
	{
		return "Coffee";
	}
	void Display() override
	{
		std::cout << "Cost: " << GetCost()
			<< "; Ingredients: " << GetIngredients() << std::endl;
	}
};

class CoffeeDecorator : public ICoffee
{
public:
	CoffeeDecorator(std::unique_ptr<ICoffee> c) : mDecoratedCoffee{ std::move(c) } {}

	float GetCost() const override
	{
		return mDecoratedCoffee->GetCost();
	}
	std::string GetIngredients() const override
	{
		return mDecoratedCoffee->GetIngredients();
	}
	void Display() override
	{
		std::cout << "Cost: " << GetCost()
			<< "; Ingredients: " << GetIngredients() << std::endl;
	}

private:
	std::unique_ptr<ICoffee> mDecoratedCoffee;
};

class WithMilk : public CoffeeDecorator
{
public:
	WithMilk(std::unique_ptr<ICoffee> c) : CoffeeDecorator(std::move(c)) {}

	float GetCost() const override
	{
		return CoffeeDecorator::GetCost() + 0.2f;
	}
	std::string GetIngredients() const override
	{
		return CoffeeDecorator::GetIngredients() + ", Milk";
	}
};

class WithSugar : public CoffeeDecorator
{
public:
	WithSugar(std::unique_ptr<ICoffee> c) : CoffeeDecorator(std::move(c)) {}

	float GetCost() const override
	{
		return CoffeeDecorator::GetCost() + 0.1f;
	}
	std::string GetIngredients() const override
	{
		return CoffeeDecorator::GetIngredients() + ", Sugar";
	}
};

int main()
{
	std::unique_ptr<ICoffee> c = std::make_unique<BaseCoffee>();
	c->Display();

	c = std::make_unique<WithMilk>(std::move(c));
	c->Display();
	
	c = std::make_unique<WithSugar>(std::move(c));
	c->Display();

	return 0;
}
