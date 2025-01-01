#include "main.h"


class customerTime{
public:
	Restaurant::customer * data;
	customerTime* next;
//^ thêm task4 biến customerTime thành danh sách đôi để dễ xử lí sort
	customerTime* prev;
	bool inDisk; //! xem thử khách hàng có trong bàn hay không
public:
	customerTime(string name, int enery, bool inDisk, customerTime* next = nullptr, customerTime* prev = nullptr)
	:next(next),prev(prev), inDisk(inDisk) {
		this->data = new Restaurant::customer(name, enery, nullptr, nullptr);
		COUNTDELETE--;
	}
	~customerTime(){
		delete data;
		COUNTDELETE++;
	}
};


class imp_res : public Restaurant
{
private:
	customer * customerQueue;
	customer * customerX; 

	int sizeCustomerInDesk; 
	int sizeCustomerQueue; 

	customerTime * CustomerTimeHead; 
	customerTime * CustomerTimeTail; 
	friend class customerTime;
public:
	imp_res() {
		customerX = customerQueue =  nullptr;
		sizeCustomerQueue = sizeCustomerInDesk = 0;
		CustomerTimeHead = CustomerTimeTail = nullptr;
	};
	void RED(string name, int energy);
	void BLUE(int num);
	void PURPLE();
	void REVERSAL();
	void DOMAIN_EXPANSION();
	void UNLIMITED_VOID();
	void LIGHT(int num);	

	~imp_res(){  

	}

	void delteCustomerTimeInDisk(customerTime* customerTimeDelete)
	{
		//* Bước 1 
		if(sizeCustomerInDesk == 1) customerX = nullptr;
		//* bước 2 
		else
		{
			customer* customerDelete = customerTimeDelete->data;
			//TODO cập nhật lại khách hàng x
			if(customerDelete->energy > 0) customerX = customerDelete->next;
			else customerX = customerDelete->prev;

			//TODO cập nhật tại phía trước và phía sau
			customerDelete->next->prev = customerDelete->prev;
			customerDelete->prev->next = customerDelete->next;
		}
		sizeCustomerInDesk--; //! cập nhật size trong bàn
	}

	void delteCustomerTimeInQueue(customerTime* customerTimeDelete)
	{
		//* Bước 1
		if(sizeCustomerQueue == 1) customerQueue = nullptr;
		//* bước 2
		else
		{
			customer* customerDelete = customerTimeDelete->data;
			//* cập nhật xóa
			customerDelete->next->prev = customerDelete->prev;
			customerDelete->prev->next = customerDelete->next;

			//* cập nhật customerQueue
			if(customerDelete == customerQueue) customerQueue = customerQueue->next;
		}
		sizeCustomerQueue--;
	}	

	void insertCustomerQueueToInDisk()
	{
		
		while(sizeCustomerQueue != 0 && sizeCustomerInDesk != MAXSIZE)
		{
			//* bước 1
			customer* newCustomer = customerQueue;

			//* bước 1.1
			customerTime* temp = CustomerTimeHead;
			for(int i = 0; i < sizeCustomerQueue + sizeCustomerInDesk; i++, temp = temp->next)
			{
				if(temp->data == customerQueue) break;	
			}
			temp->inDisk = true;

			//* Bước 1.2
			if(sizeCustomerQueue == 1) customerQueue = nullptr;
			else
			{
				customerQueue->prev->next = customerQueue->next;
				customerQueue->next->prev = customerQueue->prev;
				customerQueue = customerQueue->next;
			}
			sizeCustomerQueue --;

			//* bước 2
			if(sizeCustomerInDesk == 0) newCustomer->next = newCustomer->prev = newCustomer;
			else
			{
				//* bước 2.1
				if(sizeCustomerInDesk >= MAXSIZE / 2)
				{
					customer* temp = customerX;
					for(int i = 0; i < sizeCustomerInDesk; i++, temp = temp->next)
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
			sizeCustomerInDesk ++;
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

		customerTime* tail = CustomerTimeTail;
		while(tail)
		{
			if(tail->data == x) return false;
			else if(tail->data == y) return true;
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
					if(b == customerQueue) customerQueue = a;
					if(head == b) head = a;
					removeBLUE++;
				}
				else break;
			}
		}
	}

	customer* REVERSALhead(customer* head, int energy)
	{
		for(int i = 0; i < sizeCustomerInDesk; i++)
		{
			if(head->energy * energy > 0) break;
			head = head->prev;
		}
		return head;
	}

	customer* REVERSALtail(customer* tail, int energy)
	{
		for(int i = 0; i < sizeCustomerInDesk; i++)
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

void imp_res::RED(string name, int energy)
{
	//* Bước 1 - 2
	if(energy == 0 || sizeCustomerInDesk + sizeCustomerQueue >= MAXSIZE * 2) return;
	//* Bước 3
	else
	{
		//TODO : xem thử khác hàng dùng bữa có chung tên không
		customerTime* temp = CustomerTimeHead;
		int i = 0;
		while(i != sizeCustomerInDesk + sizeCustomerQueue)
		{
			if(temp->data->name == name) return;
			temp = temp->next;
			i ++;
		}		
	}

	customerTime* newCustomerTime = new customerTime (name, energy, true);
	COUNTDELETE--; //! check rác

	//* bước 5
	if(sizeCustomerInDesk == 0)
	{
		//* cập nhật danh sách khách hàng bàn ăn
		customerX = newCustomerTime->data;  
		customerX->next = customerX->prev = customerX;
		sizeCustomerInDesk ++;
		//* cập nhật danh sách liên kết đôi
		CustomerTimeTail = CustomerTimeHead = newCustomerTime;  
		return;

	}


	//* Bước 4 đưa vào hàng chờ 
	if(sizeCustomerInDesk == MAXSIZE)
	{
		newCustomerTime->inDisk = false;
		if(sizeCustomerQueue == 0)
		{
			customerQueue = newCustomerTime->data;
			customerQueue->next = customerQueue->prev = customerQueue;
		}
		//* thêm vào khách hàng phái sau khách hàng queue
		else{
			newCustomerTime->data->next = customerQueue;
			newCustomerTime->data->prev = customerQueue->prev;
			customerQueue->prev = newCustomerTime->data;
			newCustomerTime->data->prev->next = newCustomerTime->data;
		}
		sizeCustomerQueue ++;
	}
	else
	{
		//* Bước 6
		if(sizeCustomerInDesk >= MAXSIZE / 2)
		{
			customer* temp = customerX;
			for(int i = 0; i < sizeCustomerInDesk; i++, temp = temp->next)
			{
				if(abs(energy - temp->energy) > abs(energy - customerX->energy)) customerX = temp;
			}
		
		}

		//* Bước 7 trường hợp chèn theo chiều kim đồng hồ
		if(energy >= customerX->energy)
		{
			newCustomerTime->data->next = customerX->next;
			newCustomerTime->data->prev = customerX;
			customerX->next = newCustomerTime->data->next->prev = newCustomerTime->data;
			customerX = newCustomerTime->data;
			sizeCustomerInDesk ++;
		}
		//* Bước 7 trương hợp chèn ngược chiều kim đồng hồ
		else
		{
			newCustomerTime->data->next = customerX;
			newCustomerTime->data->prev = customerX->prev;
			customerX->prev = newCustomerTime->data->prev->next = newCustomerTime->data;
			customerX = newCustomerTime->data;
			sizeCustomerInDesk ++;
		}
	}

	
	CustomerTimeTail->next = newCustomerTime;
	newCustomerTime->prev = CustomerTimeTail;
	CustomerTimeTail = CustomerTimeTail->next;
	return;
}

void imp_res::BLUE(int num)
{
	//* Không có khách lấy gì xóa :<
		if(sizeCustomerInDesk == 0) return;

	//* Bước 1
		for(int i = 0; i < num && sizeCustomerInDesk != 0; i++)
		{
			//* Bước 1.1 Tìm khách chuẩn bị đuổi và xóa khỏi danh sách Time
			customerTime* customerTimeDelete = CustomerTimeHead;
			for(int i = 0; 
			i < sizeCustomerQueue + sizeCustomerInDesk && !customerTimeDelete->inDisk; 
			i++, customerTimeDelete = customerTimeDelete->next);
			//^ Xóa khỏi danh sách hàng customerTime
			if(sizeCustomerQueue + sizeCustomerInDesk == 1)
			{
				CustomerTimeHead = CustomerTimeTail = nullptr;
			}
			else if(customerTimeDelete == CustomerTimeHead)
			{
				CustomerTimeHead->next->prev = nullptr;
				CustomerTimeHead = CustomerTimeHead->next;
			}
			else if(customerTimeDelete == CustomerTimeTail)
			{
				CustomerTimeTail->prev->next = nullptr;
				CustomerTimeTail = CustomerTimeTail->prev;
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
	if(sizeCustomerQueue <= 1) return;
	

	//* bước 1
	customerTime* temp = CustomerTimeHead;
	customerTime* max = nullptr;
	for(int i = 0; i < sizeCustomerQueue + sizeCustomerInDesk; i++, temp = temp->next)
	{
		if(!temp->inDisk && (max == nullptr || abs(temp->data->energy) >= abs(max->data->energy))) max = temp;
	}

	int n = 1; //! kích thước danh sách cần sort
	customer* t = customerQueue;
	while(t != max->data)
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
			customer* head = this->getCustomerAt(customerQueue, j);
			inssort2(head, n - j, i, removeBLUE);
		}
	}
	inssort2(customerQueue, n, 1, removeBLUE);
	//* bước 3
	this->BLUE(removeBLUE % MAXSIZE);
}

void imp_res::DOMAIN_EXPANSION()
{
	//* Không có khách để đuổi
		if(sizeCustomerInDesk == 0) return;

	//* Bước 1
		int total_Wizard = 0, total_Spirit = 0;
		customerTime* temp = CustomerTimeHead;
		for(int i = 0; i < sizeCustomerInDesk + sizeCustomerQueue; i++, temp = temp->next)
		{
			if(temp->data->energy > 0 ) total_Wizard += temp->data->energy;
			else total_Spirit += temp->data->energy;
		}
		total_Spirit += total_Wizard;
		total_Spirit = abs(total_Spirit);

	//^ kết quả bước này sẽ có kết quả total_Wizard và total_Spirit

	temp = CustomerTimeTail;
	while(temp != nullptr){
		if(abs(total_Spirit) <= total_Wizard && temp->data->energy < 0 //! TH 1
		|| abs(total_Spirit) > total_Wizard && temp->data->energy > 0 //! TH 2
		)
			temp->data->print();
		temp = temp->prev;
	}

	//* Bước 2 đuổi
	temp = CustomerTimeHead;
	while(temp != nullptr)
	{	
		customerTime *customerTimeDelete = temp;
		temp = temp->next;
		if(customerTimeDelete->data->energy < 0 && total_Spirit <= total_Wizard
		|| customerTimeDelete->data->energy > 0 && total_Spirit > total_Wizard)
		{
			
			//^ Xóa khỏi danh sách hàng customerTime
			if(sizeCustomerQueue + sizeCustomerInDesk == 1)
			{
				CustomerTimeHead = CustomerTimeTail = nullptr;
			}
			else if(customerTimeDelete == CustomerTimeHead)
			{
				CustomerTimeHead->next->prev = nullptr;
				CustomerTimeHead = CustomerTimeHead->next;
			}
			else if(customerTimeDelete == CustomerTimeTail)
			{
				CustomerTimeTail->prev->next = nullptr;
				CustomerTimeTail = CustomerTimeTail->prev;
			}
			else
			{
				customerTimeDelete->next->prev = customerTimeDelete->prev;
				customerTimeDelete->prev->next = customerTimeDelete->next;
			}				

			if(customerTimeDelete->inDisk) this->delteCustomerTimeInDisk(customerTimeDelete);
			else this->delteCustomerTimeInQueue(customerTimeDelete);
			delete customerTimeDelete;
		}
	}
	
//* Bước 3
	this->insertCustomerQueueToInDisk();
}

void imp_res::REVERSAL()
{

	if(sizeCustomerInDesk <= 1) return;			
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
	if(sizeCustomerInDesk <= 3) return;

	int MIN_TOTAL = INT_MAX; //! đáp án
	customer* head = nullptr;
	int sizeMAX = 0; //^ thêm
	//* ý tưởng cho i j chạy theo hình tròn tìm min nhỏ nhất và xa khách hàng x nhất
	customer* tempi = customerX; //! khách hàng i
	for(int i = 0; i < sizeCustomerInDesk; i++)
	{
		int TOTAL = 0;  //! tổng từ chạy i -> i + sizeCustomerInDesk
		customer* tempj = tempi; //! khách hàng j
		for(int j = 0; j < sizeCustomerInDesk; j++)
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
	if(num > 0) this->printNext(customerX, sizeCustomerInDesk);
	else if(num == 0) this->printNext(customerQueue, sizeCustomerQueue);
	else this->printPrev(customerX, sizeCustomerInDesk);
}



