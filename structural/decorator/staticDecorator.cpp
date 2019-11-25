#include <iostream>
#include <memory>
#include <string>

class ICoffee
{
	// pure virtual functions
	virtual float GetCost() const = 0;
	virtual std::string GetIngredients() const = 0;
	virtual void SetCost(float) = 0;
	virtual void SetIngredients(const std::string&) = 0;
	virtual void Display() = 0;
};

class BaseCoffee : public ICoffee
{
public:
	BaseCoffee() : mCost{ 1.f }, mIngredients{ "Coffee" } {}

	float GetCost() const override
	{
		return mCost;
	}
	std::string GetIngredients() const
	{
		return mIngredients;
	}

	void SetCost(float cost) override
	{
		mCost = cost;
	}
	void SetIngredients(const std::string& ingredients) override
	{
		mIngredients = ingredients;
	}
	void Display() override
	{
		std::cout << "Cost: " << GetCost()
			<< "; Ingredients: " << GetIngredients() << std::endl;
	}

private:
	float mCost;
	std::string mIngredients;
};

template<typename T>
class DecoratedCoffee : public T
{
public:
	DecoratedCoffee(const std::string& decorator) : mDecorator{ decorator } {}

	void Display()
	{
		std::cout << "Cost: " << T::GetCost()
			<< "; Ingredients: " << T::GetIngredients() << " with " << mDecorator << std::endl;
	}
private:
	std::string mDecorator;
};

int main()
{
	DecoratedCoffee<BaseCoffee> icedCoffee("ice");
	icedCoffee.Display();

	DecoratedCoffee<BaseCoffee> milkCoffee("milk");
	milkCoffee.SetCost(1.5f);
	milkCoffee.SetIngredients("arabica coffee");
	milkCoffee.Display();
	
	DecoratedCoffee<BaseCoffee> creamCoffee("cream");
	creamCoffee.SetCost(1.8f);
	creamCoffee.SetIngredients("robusta coffee");
	creamCoffee.Display();
}
