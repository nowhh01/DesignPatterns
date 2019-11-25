#include <iostream>
#include <memory>
#include <string>
#include <vector>

class IShape
{
public:
	// pure virtual function
	virtual void Display() = 0;
};

class CompositeShape : public IShape
{
public:
	void Add(std::unique_ptr<IShape> shape)
	{
		mShapes.push_back(std::move(shape));
	}
	void Display() override
	{
		for(const auto& s : mShapes)
		{
			s->Display();
		}
	}

private:
	std::vector<std::unique_ptr<IShape>> mShapes{};

};

class Circle : public IShape
{
public:
	Circle(std::string name) : mName{ name } {};

	void Display() override
	{
		std::cout << "Circle: " << mName << std::endl;
	}

private:
	std::string mName;

};

int main()
{
	std::unique_ptr<IShape> c1 = std::make_unique<Circle>("c1");
	std::unique_ptr<IShape> c2 = std::make_unique<Circle>("c2");
	std::unique_ptr<IShape> c3 = std::make_unique<Circle>("c3");
	
	CompositeShape shapes{};
	shapes.Add(std::move(c1));
	shapes.Add(std::move(c2));
	shapes.Add(std::move(c3));
	shapes.Display();

	return 0;
}
