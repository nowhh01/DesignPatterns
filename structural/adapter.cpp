#include <iostream>
#include <memory>
#include <string>

class LightningPhone
{
public:
	virtual void Recharge() = 0;
	virtual void UseLightning() = 0;
	virtual void Display() = 0;
};

class MicroUsbPhone
{
public:
	virtual void Recharge() = 0;
	virtual void UseMicroUsb() = 0;
	virtual void Display() = 0;
};

class Iphone : public LightningPhone
{
public:
	void Recharge() override
	{
		if(mHasConnector)
		{
			std::cout << "Recharge started" << std::endl;
			std::cout << "Recharge finished" << std::endl;
		}
		else
		{
			std::cout << "Connect Lightning first" << std::endl;
		}
	}

	void UseLightning() override
	{
		mHasConnector = true;
		std::cout << "Lightning connected" << std::endl;
	}

	void Display() override
	{
		UseLightning();
		Recharge();
	}

private:
	bool mHasConnector;
};

class Android : public MicroUsbPhone
{
public:
	void Recharge() override
	{
		if(mHasConnector)
		{
			std::cout << "Recharge started" << std::endl;
			std::cout << "Recharge finished" << std::endl;
		}
		else
		{
			std::cout << "Connect MicroUsb first" << std::endl;
		}
	}

	void UseMicroUsb() override
	{
		mHasConnector = true;
		std::cout << "MicroUsb connected" << std::endl;
	}

	void Display() override
	{
		UseMicroUsb();
		Recharge();
	}

private:
	bool mHasConnector;
};

class LightningToMicroUsbAdapter : public MicroUsbPhone
{
public:
	LightningToMicroUsbAdapter(std::unique_ptr<LightningPhone> lightningPhone) : mLightningPhone{ std::move(lightningPhone) }
	{
	}

	void Recharge() override
	{
		mLightningPhone->Recharge();
	}

	void UseMicroUsb() override
	{
		std::cout << "MicroUsb connected" << std::endl;
		mLightningPhone->UseLightning();
	}

	void Display() override
	{
		UseMicroUsb();
		Recharge();
	}

private:
	std::unique_ptr<LightningPhone> mLightningPhone;
};

int main()
{
	std::unique_ptr<Android> android = std::make_unique<Android>();
	std::unique_ptr<Iphone> iPhone = std::make_unique<Iphone>();

	std::cout << "Recharging android with MicroUsb" << std::endl;
	android->Display();
	std::cout << '\n';

	std::cout << "Recharging iPhone with Lightning" << std::endl;
	android->Display();
	std::cout << '\n';
	
	std::unique_ptr<LightningToMicroUsbAdapter> adapter = std::make_unique<LightningToMicroUsbAdapter>(std::move(iPhone));

	std::cout << "Recharging iPhone with MicroUsb" << std::endl;
	adapter->Display();
}
