#include "main.h"

class imp_res : public Restaurant
{
	class customerTime;
private:
	customer * customerQueue; //! lưu vị trí đầu tiên của khách hàng trong queue
	customer * customerX; //! lưu vị trí của khách hàng vừa cập nhật trong bàn ăn

	int sizeCustomerInDesk; //! số lượng khách hàng trong bàn ăn
	int sizeCustomerQueue; //! số lượng khách hàng trong hàng chờ

	customerTime * CustomerTimeHead; //! khách hàng đầu tiên tới nhà hàng
	customerTime * CustomerTimeTail; //! khách hàng cuối cùng tới nhà hàng

private:

public:	
	imp_res() {
		customerX = customerQueue =  nullptr;
		sizeCustomerQueue = sizeCustomerInDesk = 0;
		CustomerTimeHead = CustomerTimeTail = nullptr;
	};
	void RED(string name, int energy);
	void BLUE(int num);
	void PURPLE(){};
	void REVERSAL(){};
	void DOMAIN_EXPANSION(){};
	void UNLIMITED_VOID(){};
	void LIGHT(int num);

	~imp_res(){}
private:
	class customerTime{
	public:
		customer * data; //! vị trí của thằng này trong nhà hàng
		customerTime* next; //! thằng phái trước nó
		customerTime* prev; //! thằng phái sau nó
		bool inDisk; //! xem thử nó có trong bàn hay không
	public:
		customerTime(customer * data, bool inDisk, customerTime* next = nullptr, customerTime* prev = nullptr)
		:data(data),next(next),prev(prev), inDisk(inDisk) {}
		~customerTime(){delete data;}
	};

};

void imp_res::RED(string name, int energy)
{
	if(energy == 0) return;
	else if(sizeCustomerInDesk + sizeCustomerQueue >= MAXSIZE * 2) return;
	else
	{
		customerTime* temp = CustomerTimeHead;
		for(int i = 0; i < sizeCustomerInDesk + sizeCustomerQueue; i++)
		{		
			if (temp->data->name == name){
				return;
			}
			temp = temp->next;
		}	
	}

	if(sizeCustomerInDesk == MAXSIZE)
	{
		customer* newCustomer = new customer(name, energy, nullptr, nullptr);
		if(sizeCustomerQueue == 0)
		{
			customerQueue = newCustomer;
			newCustomer->prev = newCustomer;
			newCustomer->next = newCustomer;
		}
		else{
			newCustomer->next = customerQueue;
			newCustomer->prev = customerQueue->prev; 
			customerQueue->prev = newCustomer; 
			newCustomer->prev->next = newCustomer; 
		}
		sizeCustomerQueue ++;


		customerTime* newCustomerTime = new customerTime (newCustomer, false);  
		CustomerTimeTail->next = newCustomerTime;
		newCustomerTime->prev = CustomerTimeTail;
		CustomerTimeTail = newCustomerTime;
		return;
	}
	
	else if(sizeCustomerInDesk == 0)
	{
		customerX = new customer (name, energy, nullptr, nullptr);  
		customerX->next = customerX;
		customerX->prev = customerX;
		sizeCustomerInDesk ++;
		CustomerTimeTail = CustomerTimeHead = new customerTime (customerX, true);  
		return;
	}

	if(sizeCustomerInDesk >= MAXSIZE / 2.0)
	{
		customer* temp = customerX;
		for(int i = 0; i < sizeCustomerInDesk; i++)
		{
			if(abs(energy - temp->energy) > abs(energy - customerX->energy))
			{
				customerX = temp;
			}
			temp = temp->next; 
		}
	
	}
	customer* newCustomer = new customer (name, energy, nullptr, nullptr); 
	
	if(energy >= customerX->energy)
	{
		newCustomer->next = customerX->next;
		newCustomer->prev = customerX;
		customerX->next = newCustomer;
		newCustomer->next->prev = newCustomer;
	}
	else
	{
		newCustomer->next = customerX;
		newCustomer->prev = customerX->prev;
		customerX->prev = newCustomer;
		newCustomer->prev->next = newCustomer;
	}

	customerX = newCustomer;
	sizeCustomerInDesk ++;

	customerTime* newCustomerTime = new customerTime (customerX, true);
	CustomerTimeTail->next = newCustomerTime;
	newCustomerTime->prev = CustomerTimeTail;
	CustomerTimeTail = newCustomerTime;
	return;
}

void imp_res::BLUE(int num)
{
	if (sizeCustomerInDesk == 0) return;
	for (int i = 0; i < num && sizeCustomerInDesk > 0; i++)
	{
		customerTime* customerTimeDelete = CustomerTimeHead;
		for(int i = 0; i < sizeCustomerInDesk + sizeCustomerQueue; i++)
		{
			if(customerTimeDelete->inDisk == true) 
				break;
			customerTimeDelete = customerTimeDelete->next;
		}
		if (sizeCustomerInDesk == 1 && sizeCustomerQueue == 0)
		{
			CustomerTimeHead = nullptr;
			CustomerTimeTail = nullptr;
		} else if (customerTimeDelete == CustomerTimeHead)
		{
			customerTimeDelete->next->prev = nullptr;
			CustomerTimeHead = CustomerTimeHead->next;
		}
		else if (customerTimeDelete = CustomerTimeTail)
		{
			customerTimeDelete->prev->next = nullptr;
			CustomerTimeTail = CustomerTimeTail->prev;
		}
		else
		{
			customerTimeDelete->prev->next = customerTimeDelete->next;
			customerTimeDelete->next->prev = customerTimeDelete->prev;
		}
		
		if (sizeCustomerInDesk == 1) customerX = nullptr;
		else 
		{
			customer* customerDelete = customerTimeDelete->data;
			customerDelete->prev->next = customerDelete->next;
			customerDelete->next->prev = customerDelete->prev;
			if (customerDelete->energy > 0) customerX = customerDelete->next;
				else customerX = customerDelete->prev;
		}
		sizeCustomerInDesk--;
		delete customerTimeDelete;
	}
	while (sizeCustomerQueue > 0 && sizeCustomerInDesk < MAXSIZE)
	{
		customer* newCustomer = customerQueue;
		customerTime* temp = CustomerTimeHead;
		for (int i = 0; i < sizeCustomerInDesk; i++)
		{
			if (temp->data == newCustomer)
			{
				temp->inDisk = true;
				break;
			}
			temp = temp->next;
		}
		if (sizeCustomerQueue == 1) customerQueue = nullptr;
		else
		{
			customerQueue->prev->next = customerQueue->next;
			customerQueue->next->prev = customerQueue->prev;
			customerQueue = customerQueue->next;
		}
		sizeCustomerQueue--;
		if (sizeCustomerInDesk == 0)
		{
			newCustomer->next = newCustomer;
			newCustomer->prev = newCustomer;
		}
		else
		{
			if(sizeCustomerInDesk >= MAXSIZE / 2.0)
			{
				customer* temp = customerX;
				for(int i = 0; i < sizeCustomerInDesk; i++)
				{
					if(abs(newCustomer->energy - temp->energy) > abs(newCustomer->energy - customerX->energy))
					{
						customerX = temp;
					}
					temp = temp->next; 
				}
			
			}
			
			if(newCustomer->energy >= customerX->energy)
			{
				newCustomer->next = customerX->next;
				newCustomer->prev = customerX;
				customerX->next = newCustomer;
				newCustomer->next->prev = newCustomer;
			}
			else
			{
				newCustomer->next = customerX;
				newCustomer->prev = customerX->prev;
				customerX->prev = newCustomer;
				newCustomer->prev->next = newCustomer;
			}

			customerX = newCustomer;
			sizeCustomerInDesk ++;
		}
	}
}

void imp_res::LIGHT(int num)
{
	if(num == 0)
	{
		customer* temp = customerQueue;
		for(int i = 0; i < sizeCustomerQueue; i++)
		{
			temp->print();
			temp = temp->next;
		}
	}
	else if (num > 0)
	{	
		customer* temp = customerX;
		for(int i = 0; i < sizeCustomerInDesk; i++)
		{
			temp->print();
			temp = temp->next;
		}
	}
	else
	{
		customer* temp = customerX;
		for(int i = 0; i < sizeCustomerInDesk; i++)
		{
			temp->print();
			temp = temp->prev;
		}
	}
}