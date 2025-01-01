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

	void delteCustomerTimeInQueue(customerStatus* customerTimeDelete)
	{
		//* Bước 1
		if(numQueue == 1) headQueue = nullptr;
		//* bước 2
		else
		{
			customer* customerDelete = customerTimeDelete->infor;
			//* cập nhật xóa
			customerDelete->next->prev = customerDelete->prev;
			customerDelete->prev->next = customerDelete->next;

			//* cập nhật headQueue
			if(customerDelete == headQueue) headQueue = headQueue->next;
		}
		numQueue--;
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
				if(temp->infor == headQueue) break;	
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
					for(int i = 0; i < numTable; i++, temp = temp->next)
					{
						if(abs(newCustomer->energy - temp->energy) > abs(newCustomer->energy - customerX->energy))
						{
							customerX = temp;
						}
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

	customer* getCustomerAt(customer* x, int index)
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

	void inssort2(customer* head, int n, int incr, int &removeBLUE) {
		for(int i = incr; i < n; i += incr)
		{
			for(int j = i; j >= incr; j -= incr)
			{
				customer* b = this->getCustomerAt(head, j - incr);
				customer* a = this->getCustomerAt(b, incr);

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

	customer* REVERSALhead(customer* head, int energy)
	{
		for(int i = 0; i < numTable; i++)
		{
			if(head->energy * energy > 0) break;
			head = head->prev;
		}
		return head;
	}

	customer* REVERSALtail(customer* tail, int energy)
	{
		for(int i = 0; i < numTable; i++)
		{
			if(tail->energy * energy > 0) break;
			tail = tail->next;
		}
		return tail;
	}

	void swap(customer* head, customer * tail)
	{
		customer* temp = new customer();
		//* thế temp vào head
		temp->next = head->next;
		temp->prev = head->prev;
		head->next->prev = head->prev->next = temp;

		//* đổi head với tail
		head->next = tail->next;
		head->prev = tail->prev;
		tail->next->prev = tail->prev->next = head;

		//* đổi tail với temp
		tail->next = temp->next;
		tail->prev = temp->prev;
		temp->next->prev = temp->prev->next = tail;
		delete temp; 
	}	

	void printNext(customer* head, int size)
	{
		if(size == 0) return;
		head->print();
		printNext(head->next, size - 1);
	}

	void printPrev(customer* head, int size)
	{
		if(size == 0) return;
		head->print();
		printPrev(head->prev, size - 1);
	}

};

// void imp_res::RED(string name, int energy)
// {
// 	//* Bước 1 - 2
// 	if(energy == 0 || numTable + numQueue >= MAXSIZE * 2) return;
// 	//* Bước 3
// 	else
// 	{
// 		//TODO : xem thử khác hàng dùng bữa có chung tên không
// 		customerStatus* temp = headStatus;
// 		int i = 0;
// 		while(i != numTable + numQueue)
// 		{
// 			if(temp->infor->name == name) return;
// 			temp = temp->next;
// 			i ++;
// 		}		
// 	}

// 	customerStatus* newCustomerTime = new customerStatus (name, energy, true);
// 	COUNTDELETE--; //! check rác

// 	//* bước 5
// 	if(numTable == 0)
// 	{
// 		//* cập nhật danh sách khách hàng bàn ăn
// 		customerX = newCustomerTime->infor;  
// 		customerX->next = customerX->prev = customerX;
// 		numTable ++;
// 		//* cập nhật danh sách liên kết đôi
// 		tailStatus = headStatus = newCustomerTime;  
// 		return;

// 	}


// 	//* Bước 4 đưa vào hàng chờ 
// 	if(numTable == MAXSIZE)
// 	{
// 		newCustomerTime->onTable = false;
// 		if(numQueue == 0)
// 		{
// 			headQueue = newCustomerTime->infor;
// 			headQueue->next = headQueue->prev = headQueue;
// 		}
// 		//* thêm vào khách hàng phái sau khách hàng queue
// 		else{
// 			newCustomerTime->infor->next = headQueue;
// 			newCustomerTime->infor->prev = headQueue->prev;
// 			headQueue->prev = newCustomerTime->infor;
// 			newCustomerTime->infor->prev->next = newCustomerTime->infor;
// 		}
// 		numQueue ++;
// 	}
// 	else
// 	{
// 		//* Bước 6
// 		if(numTable >= MAXSIZE / 2)
// 		{
// 			customer* temp = customerX;
// 			for(int i = 0; i < numTable; i++, temp = temp->next)
// 			{
// 				if(abs(energy - temp->energy) > abs(energy - customerX->energy)) customerX = temp;
// 			}
		
// 		}

// 		//* Bước 7 trường hợp chèn theo chiều kim đồng hồ
// 		if(energy >= customerX->energy)
// 		{
// 			newCustomerTime->infor->next = customerX->next;
// 			newCustomerTime->infor->prev = customerX;
// 			customerX->next = newCustomerTime->infor->next->prev = newCustomerTime->infor;
// 			customerX = newCustomerTime->infor;
// 			numTable ++;
// 		}
// 		//* Bước 7 trương hợp chèn ngược chiều kim đồng hồ
// 		else
// 		{
// 			newCustomerTime->infor->next = customerX;
// 			newCustomerTime->infor->prev = customerX->prev;
// 			customerX->prev = newCustomerTime->infor->prev->next = newCustomerTime->infor;
// 			customerX = newCustomerTime->infor;
// 			numTable ++;
// 		}
// 	}

	
// 	tailStatus->next = newCustomerTime;
// 	newCustomerTime->prev = tailStatus;
// 	tailStatus = tailStatus->next;
// 	return;
// }

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
	//* Không có khách lấy gì xóa :<
		if(numTable == 0) return;

	//* Bước 1
		for(int i = 0; i < num && numTable > 0; i++)
		{
			//* Bước 1.1 Tìm khách chuẩn bị đuổi và xóa khỏi danh sách Time
			customerStatus* customerTimeDelete = headStatus;
			for(int i = 0; 
			i < numQueue + numTable && !customerTimeDelete->onTable; 
			i++, customerTimeDelete = customerTimeDelete->next);
			//^ Xóa khỏi danh sách hàng customerTime
			if(numQueue + numTable == 1)
			{
				headStatus = tailStatus = nullptr;
			}
			else if(customerTimeDelete == headStatus)
			{
				headStatus->next->prev = nullptr;
				headStatus = headStatus->next;
			}
			else if(customerTimeDelete == tailStatus)
			{
				tailStatus->prev->next = nullptr;
				tailStatus = tailStatus->prev;
			}
			else
			{
				customerTimeDelete->next->prev = customerTimeDelete->prev;
				customerTimeDelete->prev->next = customerTimeDelete->next;
			}

			//* Bước 1.2
			this->delteCustomerTimeInDisk(customerTimeDelete);
			delete customerTimeDelete;
		}

	//* Bước 2
		this->insertCustomerQueueToInDisk();
}

void imp_res::PURPLE()
{
	if(numQueue <= 1) return;
	

	//* bước 1
	customerStatus* temp = headStatus;
	customerStatus* max = nullptr;
	for(int i = 0; i < numQueue + numTable; i++, temp = temp->next)
	{
		if(!temp->onTable && (max == nullptr || abs(temp->infor->energy) >= abs(max->infor->energy))) max = temp;
	}

	int n = 1; //! kích thước danh sách cần sort
	customer* t = headQueue;
	while(t != max->infor)
	{
		n++;
		t = t->next;
	}

	//* bước 2
	int removeBLUE = 0;
	for(int i = n / 2; i > 2; i /= 2)
	{
		for(int j = 0; j < i; j++)
		{
			customer* head = this->getCustomerAt(headQueue, j);
			inssort2(head, n - j, i, removeBLUE);
		}
	}
	inssort2(headQueue, n, 1, removeBLUE);
	//* bước 3
	this->BLUE(removeBLUE % MAXSIZE);
}

void imp_res::DOMAIN_EXPANSION()
{
	//* Không có khách để đuổi
		if(numTable == 0) return;

	//* Bước 1
		int total_Wizard = 0, total_Spirit = 0;
		customerStatus* temp = headStatus;
		for(int i = 0; i < numTable + numQueue; i++, temp = temp->next)
		{
			if(temp->infor->energy > 0 ) total_Wizard += temp->infor->energy;
			else total_Spirit += temp->infor->energy;
		}
		total_Spirit += total_Wizard;
		total_Spirit = abs(total_Spirit);

	//^ kết quả bước này sẽ có kết quả total_Wizard và total_Spirit

	temp = tailStatus;
	while(temp != nullptr){
		if(abs(total_Spirit) <= total_Wizard && temp->infor->energy < 0 //! TH 1
		|| abs(total_Spirit) > total_Wizard && temp->infor->energy > 0 //! TH 2
		)
			temp->infor->print();
		temp = temp->prev;
	}

	//* Bước 2 đuổi
	temp = headStatus;
	while(temp != nullptr)
	{	
		customerStatus *customerTimeDelete = temp;
		temp = temp->next;
		if(customerTimeDelete->infor->energy < 0 && total_Spirit <= total_Wizard
		|| customerTimeDelete->infor->energy > 0 && total_Spirit > total_Wizard)
		{
			
			//^ Xóa khỏi danh sách hàng customerTime
			if(numQueue + numTable == 1)
			{
				headStatus = tailStatus = nullptr;
			}
			else if(customerTimeDelete == headStatus)
			{
				headStatus->next->prev = nullptr;
				headStatus = headStatus->next;
			}
			else if(customerTimeDelete == tailStatus)
			{
				tailStatus->prev->next = nullptr;
				tailStatus = tailStatus->prev;
			}
			else
			{
				customerTimeDelete->next->prev = customerTimeDelete->prev;
				customerTimeDelete->prev->next = customerTimeDelete->next;
			}				

			if(customerTimeDelete->onTable) this->delteCustomerTimeInDisk(customerTimeDelete);
			else this->delteCustomerTimeInQueue(customerTimeDelete);
			delete customerTimeDelete;
		}
	}
	
//* Bước 3
	this->insertCustomerQueueToInDisk();
}

void imp_res::REVERSAL()
{

	if(numTable <= 1) return;			
	customer* head = nullptr;
	customer* tail = nullptr;

	customer*headWrid = this->REVERSALhead(customerX, 1); //
	customer*tailWrid = this->REVERSALtail(customerX->next, 1); 

	//* Bước 1 tìm head và tai  oán linh enery âm,  enery = -1
	head = this->REVERSALhead(customerX, -1); //
	tail = this->REVERSALtail(customerX->next, -1); 
	if(head->energy < 0){
		while(head != tail)
		{
			this->swap(head, tail);
			customer* temp = head;
			head = tail;
			tail = temp;

			head = this->REVERSALhead(head->prev, - 1);
			if(head == tail) break;		
			tail = this->REVERSALtail(tail->next, - 1);
		}
	}

	//* Bước 1 tìm head và tai  oán linh enery âm,  enery = 1
	
	if(headWrid->energy > 0){
		while(headWrid != tailWrid)
		{
			
			this->swap(headWrid, tailWrid);
			customer* temp = headWrid;
			headWrid = tailWrid;
			tailWrid = temp;

			headWrid = this->REVERSALhead(headWrid->prev, 1);
			if(headWrid == tailWrid) break;		
			tailWrid = this->REVERSALtail(tailWrid->next, 1);
		}
	}
}

void imp_res::UNLIMITED_VOID()
{
	if(numTable <= 3) return;

	int MIN_TOTAL = INT_MAX; //! đáp án
	customer* head = nullptr;
	int sizeMAX = 0; //^ thêm
	//* ý tưởng cho i j chạy theo hình tròn tìm min nhỏ nhất và xa khách hàng x nhất
	customer* tempi = customerX; //! khách hàng i
	for(int i = 0; i < numTable; i++)
	{
		int TOTAL = 0;  //! tổng từ chạy i -> i + sizeCustomerInDesk
		customer* tempj = tempi; //! khách hàng j
		for(int j = 0; j < numTable; j++)
		{
			//TODO: tính tổng TOTAL, cập nhật head và tail khi số khách > 4 và TOTAL nhỏ bằng
			TOTAL +=  tempj->energy;
			if(j >= 3 && (MIN_TOTAL > TOTAL || MIN_TOTAL == TOTAL  && j + 1 >= sizeMAX))
			{
				head = tempi;
				sizeMAX = j + 1;
				MIN_TOTAL = TOTAL;
			}

			tempj = tempj->next;
		}
		tempi = tempi->next;
	}			
	//TODO: print ra khách hàng từ head -> tail
	//^ chú ý nếu khách hàng đều là oán linh tail->Next = head

	customer* min = head;
	customer* temp = head; //! vì duyệt qua next nên sizeHeadToTail = 1
	int sizeHeadToMin = 1;
	//TODO: tìm min energy đầu tiên, tính sizeHeadToMin và sizeHeadToTail
	for(int i = 0; i < sizeMAX; i++)
	{
		if(min->energy > temp->energy)
		{
			min = temp;
			sizeHeadToMin = i + 1;
		}
		temp = temp->next;
	}
	//TODO: print từ min -> tail 
	this->printNext(min, sizeMAX - sizeHeadToMin + 1);
	
	//TODO: print từ head -> min
	this->printNext(head, sizeHeadToMin - 1);
	
}

void imp_res::LIGHT(int num)
{
	if(num > 0) this->printNext(customerX, numTable);
	else if(num == 0) this->printNext(headQueue, numQueue);
	else this->printPrev(customerX, numTable);
}



