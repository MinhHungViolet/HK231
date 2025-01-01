#include "main.h"


class customerStatus{
public:
	Restaurant::customer * infor;
	customerStatus* next;
	customerStatus* prev;
	bool onTable;
public:
	customerStatus(string name, int enery, bool onTable, customerStatus* next = nullptr, customerStatus* prev = nullptr)
	:next(next),prev(prev), onTable(onTable) {
		this->infor = new Restaurant::customer(name, enery, nullptr, nullptr);
	COUNTDELETE--;
	}
	~customerStatus(){
		delete infor;
		COUNTDELETE++;
	}
};


class imp_res : public Restaurant
{
private:
	customer * headQueue;
	customer * customerX; 

	int numTable; 
	int numQueue; 

	customerStatus * headStatus; 
	customerStatus * tailStatus; 
	friend class customerStatus;
public:
	imp_res() {
		customerX = headQueue =  nullptr;
		numQueue = numTable = 0;
		headStatus = tailStatus = nullptr;
	};
	void RED(string name, int energy);
	void BLUE(int num);
	void PURPLE();
	void REVERSAL();
	void DOMAIN_EXPANSION();
	void UNLIMITED_VOID();
	void LIGHT(int num);	

	~imp_res(){  
		while(headStatus)
		{
			customerStatus* temp = headStatus;	
			headStatus = headStatus->next;
			delete temp;
		}
	}

	void delteCustomerTimeInDisk(customerStatus* customerTimeDelete)
	{
		//* Bước 1 
		if(numTable == 1) customerX = nullptr;
		//* bước 2 
		else
		{
			customer* customerDelete = customerTimeDelete->infor;
			//TODO cập nhật lại khách hàng x
			if(customerDelete->energy > 0) customerX = customerDelete->next;
			else customerX = customerDelete->prev;

			//TODO cập nhật tại phía trước và phía sau
			customerDelete->next->prev = customerDelete->prev;
			customerDelete->prev->next = customerDelete->next;
		}
		numTable--; //! cập nhật size trong bàn
	}

	void insertCustomerQueueToInDisk()
	{
		
		while(numQueue != 0 && numTable != MAXSIZE)
		{
			//* bước 1
			customer* newCustomer = headQueue;

			//* bước 1.1
			customerStatus* temp = headStatus;
			for(int i = 0; i < numQueue + numTable; i++, temp = temp->next)
			{
				if(temp->infor == newCustomer) break;	
			}
			temp->onTable = true;

			//* Bước 1.2
			if(numQueue == 1) headQueue = nullptr;
			else
			{
				headQueue->prev->next = headQueue->next;
				headQueue->next->prev = headQueue->prev;
				headQueue = headQueue->next;
			}
			numQueue --;

			//* bước 2
			if(numTable == 0) newCustomer->next = newCustomer->prev = newCustomer;
			else
			{
				//* bước 2.1
				if(numTable >= MAXSIZE / 2)
				{
					customer* temp = customerX;
					for(int i = 0; i < numTable; i++)
					{
						if(abs(newCustomer->energy - temp->energy) > abs(newCustomer->energy - customerX->energy))
						{
							customerX = temp;
						}
						temp = temp->next;
					}
				}
				//* bước 2.2 
				if(newCustomer->energy >= customerX->energy)
				{
					newCustomer->next = customerX->next;
					newCustomer->prev = customerX;
					customerX->next = newCustomer->next->prev = newCustomer;
				}
				//* bước 2.2
				else
				{
					newCustomer->next = customerX;
					newCustomer->prev = customerX->prev;
					customerX->prev = newCustomer->prev->next = newCustomer;
				}
			}
			customerX = newCustomer;
			numTable ++;
		}	
	}

	void calenergyBlue(int &sumGhost, int &sumSorcerer)
	{
		customerStatus* temp = tailStatus;
		while (temp != nullptr)
		{
			if (temp->infor->energy > 0) sumSorcerer += temp->infor->energy;
			else sumGhost += temp->infor->energy;
			temp = temp->prev;
		}
		delete temp;
	}

	void printBlue(int sumGhost, int sumSorcerer)
	{
		customerStatus* temp = tailStatus;
		while (temp != nullptr)
		{
			if ((temp->infor->energy > 0 && sumSorcerer < sumGhost) || (temp->infor->energy < 0 && sumSorcerer >= sumGhost))
				temp->infor->print();
			temp = temp->prev;	
		}
		delete temp;
	}

	customer* rvsheadSor(customer* head)
	{
		for(int i = 0; i < numTable; i++)
		{
			if(head->energy > 0) break;
			head = head->prev;
		}
		return head;
	}

	customer* rvsheadGhost(customer* head)
	{
		int i = 0;
		while (i < numTable && head->energy >= 0)
		{
			head = head->prev;
			i++;
		}
		return head;
	}

	customer* rvstailSoc(customer* tail)
	{
		int i = 0;
		while (i < numTable && tail->energy <= 0)
		{
			tail = tail->next;
			i++;
		}
		return tail;
	}

	customer* rvstailGhost(customer* tail)
	{
		for(int i = 0; i < numTable; i++)
		{
			if(tail->energy < 0) break;
			tail = tail->next;
		}
		return tail;
	}

	void daoGhost(customer* head, customer* tail)
	{
		while(head != tail)
		{
			this->swap(head, tail);
			customer* temp = head;
			head = tail;
			tail = temp;

			head = this->rvsheadSor(head->prev);
			if(head == tail) break;		
			tail = this->rvstailSoc(tail->next);
		}
	}

	void daoSor(customer* head, customer* tail)
	{
		while(head != tail)
		{
			this->swap(head, tail);
			customer* temp = head;
			head = tail;
			tail = temp;

			head = this->rvsheadGhost(head->prev);
			if(head == tail) break;		
			tail = this->rvstailGhost(tail->next);
		}
	}

	customer* checkCus(customer* x, int index)
	{
		for(int i = 0; i < index; i++) x = x->next;
		return x;
	}

	bool compare(customer* x, customer* y){
		if(abs(x->energy) > abs(y->energy)) return true;
		else if(abs(x->energy) < abs(y->energy)) return false;

		customerStatus* tail = tailStatus;
		while(tail)
		{
			if(tail->infor == x) return false;
			else if(tail->infor == y) return true;
			tail = tail->prev;
		}
		return false;
	}

	// void inssort2(customer* head, int n, int incr, int &removeBLUE) {
	// 	int i = incr;
	// 	while (i < n) {
	// 		int j = i;
	// 		while (j >= incr) {
	// 			customer* b = this->checkCus(head, j - incr);
	// 			customer* a = this->checkCus(b, incr);

	// 			// if((abs(a->energy) > abs(b->energy)) || check(a, b))
	// 			if(compare(a, b))
	// 			{
	// 				// customer* temp = new customer();
	// 				// temp->next = a->next;
	// 				// temp->prev = a->prev;
	// 				// a->next->prev = a->prev->next = temp;

	// 				// a->next = b->next;
	// 				// a->prev = b->prev;
	// 				// b->next->prev = b->prev->next = a;

	// 				// b->next = temp->next;
	// 				// b->prev = temp->prev;
	// 				// temp->next->prev = temp->prev->next = b;
	// 				// delete temp; 
	// 				this->swap(a, b);
	// 				if(b == headQueue) headQueue = a;
	// 				if(head == b) head = a;
	// 				removeBLUE++;
	// 			}
	// 			else break;
	// 			j -= incr;
	// 		}
	// 		i += incr;
	// 	}
	// }

	void inssort2(customer* head, int n, int incr, int &removeBLUE) {
		for(int i = incr; i < n; i += incr)
		{
			for(int j = i; j >= incr; j -= incr)
			{
				customer* b = this->checkCus(head, j - incr);
				customer* a = this->checkCus(b, incr);

				if(compare(a,b))
				{
					this->swap(a, b);
					if(b == headQueue) headQueue = a;
					if(head == b) head = a;
					removeBLUE++;
				}
				else break;
			}
		}
	}

	void swap(customer* head, customer * tail)
	{
		customer* temp = new customer();
		temp->next = head->next;
		temp->prev = head->prev;
		head->next->prev = head->prev->next = temp;

		head->next = tail->next;
		head->prev = tail->prev;
		tail->next->prev = tail->prev->next = head;

		tail->next = temp->next;
		tail->prev = temp->prev;
		temp->next->prev = temp->prev->next = tail;
		delete temp; 
	}	

	void findSubList(int &ans, int &sizeList, customer* &headlist)
	{
		customer* a = customerX;
		for(int i = 0; i < numTable; i++)
		{
			int sum = 0;
			customer* b = a;
			for(int j = 0; j < numTable; j++)
			{
				sum = sum + b->energy;
				if(j >= 3 && ans > sum)
				{
					ans = sum;
					sizeList = j + 1;
					headlist = a;
				}
				if(j >= 3 && ans == sum && sizeList - 1 <= j)
				{
					ans = sum;
					sizeList = j + 1;
					headlist = a;
				}
				b = b->next;
			}
			a = a->next;
		}
	}

	void findMin(customer* &min, int &headToMin, customer* headlist, int sizeList)
	{
		customer* temp = headlist;
		int i = 0;
		while(i < sizeList)
		{
			if(min->energy > temp->energy)
			{
				min = temp;
				headToMin = i + 1;
			}
			temp = temp->next;
			i++;
		}
	}
};

void imp_res::RED(string name, int energy)
{
	if(energy == 0 || numTable + numQueue >= MAXSIZE * 2) return;
	else
	{
		customerStatus* temp1 = headStatus;
		customerStatus* temp2 = tailStatus;
		for(int i = 0; i < numTable; i++)
		{		
			if (temp1->infor->name == name){
				return;
			}
			temp1 = temp1->next;
		}
		int i = 0;
		while(i < numQueue)
		{
			if (temp2->infor->name == name){
				return;
			}
			temp2 = temp2->prev;
			i++;
		}	
	}

	customerStatus* newCusStatus = new customerStatus (name, energy, true);
	COUNTDELETE--;
	if(numTable == 0)
	{
		customerX = newCusStatus->infor; 
		customerX->next = customerX;
		customerX->prev = customerX;
		numTable++;
		tailStatus = headStatus = newCusStatus;
		return;
	}

	if(numTable == MAXSIZE)
	{
		newCusStatus->onTable = false;
		if(numQueue == 0)
		{
			headQueue = newCusStatus->infor;
			headQueue->prev = headQueue;
			headQueue->next = headQueue;
		}
		else{
			newCusStatus->infor->next = headQueue;
			newCusStatus->infor->prev = headQueue->prev; 
			headQueue->prev = newCusStatus->infor; 
			newCusStatus->infor->prev->next = newCusStatus->infor; 
		}
		numQueue++;
	}
	else
	{
		if(numTable >= MAXSIZE / 2)
		{
			customer* temp = customerX;
			int i = 0;
			while(i < numTable)
			{
				int tempEnergy = temp->energy;
				int energyX = customerX->energy;
				if(abs(energy - tempEnergy) > abs(energy - energyX))
				{
					customerX = temp;
				}
				temp = temp->next;
				i++;
			}
		
		}
		
		if(energy < customerX->energy)
		{
			newCusStatus->infor->next = customerX;
			newCusStatus->infor->prev = customerX->prev;
			customerX->prev = newCusStatus->infor;
			newCusStatus->infor->prev->next = newCusStatus->infor;
			customerX = newCusStatus->infor;
			numTable++;
		}
		else
		{
			newCusStatus->infor->next = customerX->next;
			newCusStatus->infor->prev = customerX;
			customerX->next = newCusStatus->infor;
			newCusStatus->infor->next->prev = newCusStatus->infor;
			customerX = newCusStatus->infor;
			numTable++;
		}

	}
	
	newCusStatus->prev = tailStatus;
	tailStatus->next = newCusStatus;
	tailStatus = tailStatus->next;
	return;
}

void imp_res::BLUE(int num)
{
		if (numTable == 0) return;
		for (int i = 0; i < num && numTable > 0; i++)
		{
			customerStatus* cusDelStatus = headStatus;
			// customerStatus* temp = headStatus;
			// while(temp != nullptr && temp->onTable == false)
			// {
			// 	temp = temp->next;
			// }
			// cusDelStatus = temp;
			for(int i = 0; i < numQueue + numTable && !cusDelStatus->onTable; 
			i++, cusDelStatus = cusDelStatus->next);
			if (numTable == 1 && numQueue == 0)
			{
				headStatus = nullptr;
				tailStatus = nullptr;
			} else if (cusDelStatus == headStatus)
			{
				headStatus->next->prev = nullptr;
				headStatus = headStatus->next;
			}
			else if (cusDelStatus = tailStatus)
			{
				tailStatus->prev->next = nullptr;
				tailStatus = tailStatus->prev;
			}
			else
			{
				cusDelStatus->prev->next = cusDelStatus->next;
				cusDelStatus->next->prev = cusDelStatus->prev;
			}
			// /// duoi khoi ban an
			// if (numTable == 1) customerX = nullptr;
			// else 
			// {
			// 	customer* cusDel = cusDelStatus->infor;
			// 	if (cusDel->energy > 0) customerX = cusDel->next;
			// 		else customerX = cusDel->prev;
			// 	cusDel->prev->next = cusDel->next;
			// 	cusDel->next->prev = cusDel->prev;
			// }
			// numTable--;
			this->delteCustomerTimeInDisk(cusDelStatus);
			delete cusDelStatus;
		}

		// while (numQueue > 0 && numTable < MAXSIZE)
		// {
		// 	customer* newCus = headQueue;

		// 	customerStatus* temp = tailStatus;
		// 	int i = 0;
		// 	while (i < numQueue + numTable)
		// 	{
		// 		if (temp->infor == newCus)
		// 		{
		// 			break;
		// 		}
		// 		temp = temp->prev;
		// 		i++;
		// 	}
		// 	temp->onTable = true;
		// 	// delete temp;

		// 	if(numQueue == 1) headQueue = nullptr;
		// 	else
		// 	{
		// 		headQueue->prev->next = headQueue->next;
		// 		headQueue->next->prev = headQueue->prev;
		// 		headQueue = headQueue->next;
		// 	}
		// 	numQueue --;

		// 	if(numTable == 0) newCus->next = newCus->prev = newCus;
		// 	else
		// 	{
		// 		if(numTable >= MAXSIZE / 2)
		// 		{
		// 			customer* temp = customerX;
		// 			for(int i = 0; i < numTable; i++)
		// 			{
		// 				if(abs(newCus->energy - temp->energy) > abs(newCus->energy - customerX->energy))
		// 				{
		// 					customerX = temp;
		// 				}
		// 				temp = temp->next; 
		// 			}
		// 			// delete temp;
		// 		}
		// 		if(newCus->energy >= customerX->energy)
		// 		{
		// 			newCus->next = customerX->next;
		// 			newCus->prev = customerX;
		// 			customerX->next = newCus;
		// 			newCus->next->prev = newCus;
		// 		}
		// 		else
		// 		{
		// 			newCus->next = customerX;
		// 			newCus->prev = customerX->prev;
		// 			customerX->prev = newCus;
		// 			newCus->prev->next = newCus;
		// 		}
		// 	}
		// 	customerX = newCus;
		// 	numTable ++;
		// 	// delete temp;
		// 	// delete newCus;
		// }	
		this->insertCustomerQueueToInDisk();
}

void imp_res::DOMAIN_EXPANSION()
{
	if (numTable == 0) return;
	int sumSorcerer = 0;
	int sumGhost = 0;
	int sumabs = 0;

	this->calenergyBlue(sumGhost, sumSorcerer);
	//sumabs = abs(sumGhost) + sumSorcerer;
	sumGhost = abs(sumGhost);
	this->printBlue(sumGhost, sumSorcerer);

	// duoi khach
	customerStatus* temp = headStatus;
	while(temp != nullptr)
	{	
		customerStatus *cusDelStatus = temp;
		temp = temp->next;
		if(cusDelStatus->infor->energy < 0 && sumGhost <= sumSorcerer || cusDelStatus->infor->energy > 0 && sumGhost > sumSorcerer)
		{
			
			if(numQueue + numTable == 1)
			{
				headStatus = tailStatus = nullptr;
			}
			else if(cusDelStatus == headStatus)
			{
				headStatus->next->prev = nullptr;
				headStatus = headStatus->next;
			}
			else if(cusDelStatus == tailStatus)
			{
				tailStatus->prev->next = nullptr;
				tailStatus = tailStatus->prev;
			}
			else
			{
				cusDelStatus->next->prev = cusDelStatus->prev;
				cusDelStatus->prev->next = cusDelStatus->next;
			}				

			if(cusDelStatus->onTable == true)
			{
				if (numTable == 1) customerX = nullptr;
				else 
				{
					customer* cusDel = cusDelStatus->infor;
					cusDel->prev->next = cusDel->next;
					cusDel->next->prev = cusDel->prev;
					if (cusDel->energy > 0) customerX = cusDel->next;
						else customerX = cusDel->prev;
				}
				numTable--;
			}
			else 
			{
				if(numQueue == 1) headQueue = nullptr;
				else
				{
					customer* cusDel = cusDelStatus->infor;
					cusDel->next->prev = cusDel->prev;
					cusDel->prev->next = cusDel->next;

					if(cusDel == headQueue) headQueue = headQueue->next;
				}
				numQueue--;
			}
			delete cusDelStatus;
		}
	}
	
	while (numQueue > 0 && numTable < MAXSIZE)
	{
		customer* newCus = headQueue;

		customerStatus* temp = tailStatus;
		while (temp != nullptr)
		{
			if (temp->infor == newCus)
			{
				temp->onTable = true;
				break;
			}
			temp = temp->prev;
		}

		if(numQueue == 1) headQueue = nullptr;
		else
		{
			headQueue->prev->next = headQueue->next;
			headQueue->next->prev = headQueue->prev;
			headQueue = headQueue->next;
		}
		numQueue --;

		if(numTable == 0) newCus->next = newCus->prev = newCus;
		else
		{
			if(numTable >= MAXSIZE / 2)
			{
				customer* temp = customerX;
				for(int i = 0; i < numTable; i++)
				{
					if(abs(newCus->energy - temp->energy) > abs(newCus->energy - customerX->energy))
					{
						customerX = temp;
					}
					temp = temp->next; 
				}
			}
			if(newCus->energy < customerX->energy)
			{
				newCus->next = customerX;
				newCus->prev = customerX->prev;
				customerX->prev = newCus;
				newCus->prev->next = newCus;
			}
			if(newCus->energy >= customerX->energy)
			{
				newCus->next = customerX->next;
				newCus->prev = customerX;
				customerX->next = newCus;
				newCus->next->prev = newCus;
			}
		}
		customerX = newCus;
		numTable ++;
	}	
}

void imp_res::PURPLE()
{
	if(numQueue == 0 || numQueue == 1) return;
	customerStatus* temp = headStatus;
	customerStatus* max = nullptr;
	int i = 0;
	while(i < numQueue + numTable)
	{
		if(temp->onTable == false && (max == nullptr || abs(temp->infor->energy) >= abs(max->infor->energy))) max = temp;
		// if(temp->onTable == false && max == nullptr) max = temp;
		// if (temp->onTable == false && (abs(temp->infor->energy) == abs(max->infor->energy) || abs(temp->infor->energy) > abs(max->infor->energy))) max = temp;
		temp = temp->next;
		i++;
	}
	
	int n = 1;
	customer* t = headQueue;
	while(t != max->infor)
	{
		n++;
		t = t->next;
	}
	
	int removeBLUE = 0;
	for(int i = n / 2; i > 2; i /= 2)
	{
		for(int j = 0; j < i; j++)
		{
			customer* head = this->checkCus(headQueue, j);
			inssort2(head, n - j, i, removeBLUE);
		}
	}
	inssort2(headQueue, n, 1, removeBLUE);
	this->BLUE(removeBLUE % MAXSIZE);
}

void imp_res::REVERSAL()
{

	if(numTable <= 1) return;			

	customer*headSorList = this->rvsheadSor(customerX); //
	customer*tailSorList = this->rvstailSoc(customerX->next); 

	customer* headGhostList = this->rvsheadGhost(customerX); //
	customer* tailGhostList = this->rvstailGhost(customerX->next); 
	if(headGhostList->energy < 0)
	{
		this->daoSor(headGhostList, tailGhostList);
	}
	
	if(headSorList->energy > 0)
	{
		this->daoGhost(headSorList, tailSorList);
	}
}



void imp_res::UNLIMITED_VOID()
{
	if (numTable <= 3) return;
	customer* headlist = nullptr;
	int ans = INT_MAX;
	int sizeList = 0;
	
	this->findSubList(ans, sizeList, headlist);
	customer* minlist = headlist;
	int headToMin = 1;

	this->findMin(minlist, headToMin, headlist, sizeList);

	customer* tempA = minlist;
	for(int i = 0; i < sizeList - headToMin + 1; i++)
	{
		tempA->print();
		tempA = tempA->next;
	}
	customer* tempB = headlist;
	for(int i = 0; i < headToMin - 1; i++)
	{
		tempB->print();
		tempB = tempB->next;
	}

}

void imp_res::LIGHT(int num)
{
	switch(num)
	{
		case 0:
		{
			customer* temp = headQueue;
			int i = 0;
			while(i < numQueue)
			{
				temp->print();
				temp = temp->next;
				i++;
			}
			break;
		}
		default:
		{
			if (num > 0)
			{
				customer* temp = customerX;
				for(int i = 0; i < numTable; i++)
				{
					temp->print();
					temp = temp->next;
				}
				break;
			}
			else
			{
				customer* temp = customerX;
				int i = 0;
				while(i < numTable)
				{
					temp->print();
					temp = temp->prev;
					i++;
				}
				break;
			}
		}
	}
}
