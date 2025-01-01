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
	void PURPLE();
	void REVERSAL();
	void DOMAIN_EXPANSION();
	void UNLIMITED_VOID();
	void LIGHT(int num);

	~imp_res(){
		while(CustomerTimeHead)
		{
			customerTime* temp = CustomerTimeHead;	
			CustomerTimeHead = CustomerTimeHead->next;
			delete temp;
			COUNTDELETE++;
		}
	}
private:
	class customerTime{
	public:
		customer * data; //! vị trí của thằng này trong nhà hàng
		customerTime* next; //! thằng phái trước nó
		customerTime* prev; //! thằng phái sau nó
		bool inDisk; //! xem thử nó có trong bàn hay không
	public:
		//! Contructor
		customerTime(customer * data, bool inDisk, customerTime* next = nullptr, customerTime* prev = nullptr)
		:data(data),next(next),prev(prev), inDisk(inDisk) {}
		//! Destructor
		~customerTime(){delete data;}
	};

	//! Tới chỗ nó đuổi thẳng cổ
	void delteCustomerInDisk(customerTime*);
	void delteCustomerInQueue(customerTime*);
	//! Tới nắm đầu đứa từ hàng chờ vào ngồi bàn ăn.
	void insertCustomerQueueToInDisk();

	//! REVERSAL
	customer* REVERSAL_Wizardhead(customer* x);
	customer* REVERSAL_Wizardtail(customer* x);
	customer* REVERSAL_Spirithead(customer* x);
	customer* REVERSAL_Spirittail(customer* x);
	void REVERSAL_Wizard(customer* x);
	void REVERSAL_Spirit(customer* x);
	void swapAdress(customer* head, customer * tail);

	//! PURPLE
	customer* getCustomerAt(customer* x, int index);
	bool checkCustomer(customer* x, customer* y);
	int inssort2(customer* head, int n, int incr);
};

void imp_res::RED(string name, int energy){
	//* Bước 1 đuổi về không phải Thuật sư hay oán linh
	//& thằng này loại nào đây thôi cho nó cút
	if(energy == 0) return;
	//* Bước 2  hàng chờ đã đầy đuổi về
	//& nhà hàng tao đông rồi cút về hộ tao chạy bàn mệt
	else if(sizeCustomerInDesk + sizeCustomerQueue >= MAXSIZE * 2) return;
	//* Bước 3 "thiên thượng thiên hạ, duy ngã độc tôn" : chung tên đuổi về
	//& ghét mấy thằng chung tên lắm nha khó tìm kiếm mày nữa thôi méo nhận nó
	else
	{
		customerTime* temp = CustomerTimeHead;
		//* xem thử khác hàng có chung tên không với khách nào hay không
		for(int i = 0; i < sizeCustomerInDesk + sizeCustomerQueue; i++)
		{	
			//TODO tìm thử trung tên không
			if(temp->data->name == name) return;
			temp = temp->next;
		}	
	}

	//* Bước 4 đưa vào hàng chờ 
	//& nhà hàng hết bàn ăn rồi tụ bay đứng đó xếp hàng cho t
	//^ chú ý này đang quản lí trong hàng chờ sử dụng customerQueue
	if(sizeCustomerInDesk == MAXSIZE)
	{
		//& đọc tên để ghi mày vô danh sách biết còn kêu mày vô ăn
		customer* newCustomer = new customer(name, energy, nullptr, nullptr);
		//& thì ra trong hàng chờ không có nào đứng nên mày đứng 1 mình đi 
		if(sizeCustomerQueue == 0)
		{
			//TODO cập nhật thằng mới vô này là danh sách liên kết vòng đôi trong hàng chờ cần cập nhật prev và next
			customerQueue = newCustomer;
			customerQueue->next = customerQueue->prev = newCustomer;
		}
		//* task4 chèn cuối danh sách liên kết đôi vòng
		//& thì ra hàng chờ đang đồng cho mày xuống cuối hàng đứng hộ tao
		else{
			//TODO thêm vào sau khách hàng đầu tiên (thêm vào cuối) dùng next
			newCustomer->next = customerQueue; //! cập nhật thằng mới vô
			newCustomer->prev = customerQueue->prev; //! cập nhật thằng mới vô
			customerQueue->prev = newCustomer->prev->next = newCustomer;		
		}
		//& cập nhật số lượng khách nhà hàng
		sizeCustomerQueue ++;


		//^biến quản lý thời gian khách hàng nào đến trước giống như 1 sổ kí lưu vị trí khách hàng
		//& ghi nó vào danh sách để còn tính tiền nó trốn nữa
		customerTime* newCustomerTime = new customerTime (newCustomer, false);  
		//TODO thêm khách hàng mới vô vào danh sách CustomerTime này đang dùng danh sách liên kết đôi
		CustomerTimeTail->next = newCustomerTime;
		newCustomerTime->prev = CustomerTimeTail;
		CustomerTimeTail = newCustomerTime;
		return;
	}
	
	//* Bước 5 khách hàng đầu tiên vào nhà hàng này là danh sách liên kết đôi vòng
	//* giá trị next = prev = chính nó và cập nhật sizeCustomerInDesk
	//& thì ra khách hàng mở bát đầu tiên nhà hàng
	//^ chú ý này đang quản lí trong hàng chờ sử dụng customerX
	else if(sizeCustomerInDesk == 0)
	{
		//& đưa đại ka tới một chỗ bất kì ngồi
		customerX = new customer (name, energy, nullptr, nullptr);  
		
		//TODO cập nhật thằng mới vô này là danh sách liên kết vòng đôi trong bàn ăn cần cập nhật prev và next
		customerX->next = customerX->prev = customerX;

		sizeCustomerInDesk ++;
		//^ biến quản lý thời gian khách hàng nào đến trước giống như 1 sổ kí lưu vị trí khách hàng
		//& ghi nó vào danh sách để còn tính tiền nó trốn nữa
		CustomerTimeTail = CustomerTimeHead = new customerTime (customerX, true);  
		return;
	}


	//* Bước 6 nếu TH mà sizeCustomerInDesk >= MAXSIZE / 2 ta phải tìm vị trí mới của customerX
	//* tìm vị trí mới đễ dễ dàng insert customer mới
	//
	if(sizeCustomerInDesk >= MAXSIZE / 2)
	{
		//* tìm kiếm khách hàng customerX dùng for để tìm giá trị lớn nhất dựa trên sizeCustomerInDesk
		//* customerX sẽ lưu vị trí lớn nhất
		//& nhà hàng đông quá mất tích thằng lên món đầu tiên rồi thôi tìm thằng có trị tuyệt đối hiện năng lượng lớn nhất
		//& tìm được nó mới thêm thằng nhót nảy hàng chờ chứ thêm nó vô đại mấy anh kia đấm nữa
		customer* temp = customerX;
		for(int i = 0; i < sizeCustomerInDesk; i++)
		{
			//& thằng này đang có trị tuyệt đối enery lớn hơn nè mà duyệt đến cuối xem nào lớn hơn nữa không
			//TODO tìm thằng có năng có độ chênh lệch sức mạng so với thằng mới vô
			if(abs(energy - temp->energy) > abs(energy - customerX->energy))
			{
				customerX = temp;
			}			
			temp = temp->next; 
			//& Tìm được thằng lên món đầu tiên thôi (customerX) tìm hơi mệt nha
		}
	
	}
	customer* newCustomer = new customer (name, energy, nullptr, nullptr); 
	
	//* Bước 7 trường hợp chèn theo chiều kim đồng hồ
	//& h có thằng khách hàng lên món đàu tiên rồi h thêm thằng 
	//& thêm thằng nhót nảy hàng chờ vào trước hay sau thằng X đây
	if(energy >= customerX->energy)
	{
		//& thôi thấy nó mạnh hơn kia thêm nó vào trước thằng X đi
		//& cập nhật cho 2 anh kế bên chứ 2 ảnh đấm nó nữa
		//TODO thêm vào trước khách hàng dùng prev
		newCustomer->next = customerX->next;
		newCustomer->prev = customerX;
		customerX->next = newCustomer->next->prev = newCustomer;
	}
	//* Bước 7 trương hợp chèn ngược chiều kim đồng hồ
	else
	{
		//& thôi thấy nó mạnh hơn kia thêm nó vào sau thằng X đi
		//& cập nhật cho 2 anh kế bên chứ 2 ảnh đấm nó nữa
		//TODO thêm vào sau khách hàng dùng next
		newCustomer->next = customerX;
		newCustomer->prev = customerX->prev;
		customerX->prev = newCustomer->prev->next = newCustomer;
	}

	//& lên món cho anh mới vô nào đưa ảnh thành khách hàng X
	customerX = newCustomer;
	//& cập nhật số lượng khách trong bàn bàn
	sizeCustomerInDesk ++;

	//^biến quản lý thời gian khách hàng nào đến trước giống như 1 sổ kí lưu vị trí khách hàng
	//& ghi nó vào danh sách để còn tính tiền nó trốn nữa
	customerTime* newCustomerTime = new customerTime (customerX, true);
	//TODO thêm khách hàng mới vô vào danh sách CustomerTime này đang dùng danh sách liên kết đôi
	CustomerTimeTail->next = newCustomerTime;
	newCustomerTime->prev = CustomerTimeTail;
	CustomerTimeTail = newCustomerTime;
}

//! Tới chỗ nó đuổi thẳng cổ
void imp_res::delteCustomerInDisk(customerTime* customerTimeDelete)
{

	//* Bước 1 đuổi khách hàng trong bàn ăn khi chỉ có 1 khách hàng
	//& thì ra trong bàn không còn nào chỉ còn mình nó ăn kéo đầu nó ra khỏi quán
	if(sizeCustomerInDesk == 1) customerX = nullptr;

	//* bước 2 đuổi khách hàng
	//& thì ra thằng này đang ăn với 1 mớ thằng nên cho nó cút sớm 
	else
	{
		//& tới chỗ nó lôi nó ra
		customer* customerDelete = customerTimeDelete->data;

		//* cập nhật tại khách hàng phía trước và khách hàng phía sau
		//& cập nhật cho 2 anh hai bên của nó không mấy ảnh giận về nữa
		//TODO cập nhật khách hàng phái trước và sau
		customerDelete->next->prev = customerDelete->prev;
		customerDelete->prev->next = customerDelete->next;

		//* cập nhật lại khách hàng x thầy mô tả trong thread khi đang xóa khách hàng trong bàn
		//& đuổi nó đi rồi h phải lấy lòng 2 anh 2 bên để xem anh nào được ưu tiên lên món đầu tiên
		//TODO cập nhật khách hàng X
		if(customerDelete->energy > 0) customerX = customerDelete->next;
		else customerX = customerDelete->prev;
	}

	//* Bước 3 cập nhật size
	//& cập nhật số lượng khách trong bàn bàn
	sizeCustomerInDesk--;
}

//! Tới nắm đầu đứa từ hàng chờ vào ngồi bàn ăn.
void imp_res::insertCustomerQueueToInDisk()
{
	//& Thì ra hàm chờ vẫn còn khách mà trong bàn ăn vẫn trống nên vẫn nắm đầu đứa từ hàng chờ vào ngồi bàn ăn.
	while(sizeCustomerQueue != 0 && sizeCustomerInDesk != MAXSIZE)
	{
		//* bước 1 đưa khách hàng đầu ra khỏi hàng chờ
		//& thằng này được ưu tiên vào bàn ăn nè sắp được ăn rồi em mừng đi
		customer* newCustomer = customerQueue;

		//* bước 1.1 tìm khách hàng trong danh sách Time và cập nhật inDisk
		//& thằng nảy được ưu tiên phải tìm nó trong số Time của mình đánh dấu nó đã vô bàn ăn đã
		customerTime* temp = CustomerTimeHead; //! vị trí của khách hàng trong Time
		for(int i = 0; i < sizeCustomerQueue + sizeCustomerInDesk; i++)
		{
			//& thấy được mày rồi cập nó trong bàn ăn chứ nó không tính tiền nữa
			//TODO cập nhật indisk vì đã đưa khách hàng customerQueue->Name và bàn
			if(temp->data == newCustomer)
			{
				temp->inDisk = true;
				break;
			}
			temp = temp->next;
		}
		//* Bước 1.2 xóa khách hàng trong hàng chờ 
		//& thì ra nó là thằng duy nhất trong hàng chờ, nhìn nó tôi nên kéo đầu nó vô bàn ăn
		if(sizeCustomerQueue == 1) customerQueue = nullptr;
		//& thì ra phía sau nó còn 1 đồng thằng, đưa thằng tiếp theo lên làm đàn anh đầu hàng hàng
		else
		{
			//TODO lấy ra khách hàng đầu tiên trong queue và cập nhật lại customerQueue
			customerQueue->next->prev = customerQueue->prev;
			customerQueue->prev->next = customerQueue->next;
			customerQueue = customerQueue->next;
		}
		//& cập nhật số lượng khách trong bàn bàn
		sizeCustomerQueue --;

		//* bước 2 thêm khách hàng vào bàn ăn, cập nhật size
		//& thì ra bàn ăn lũ này bị đuổi hết rồi thôi đưa anh nảy mới nắm đầu từ hàng chờ vào
		if(sizeCustomerInDesk == 0)
		{
			customerX = newCustomer;
			newCustomer->next = newCustomer->prev = newCustomer;
		}
		//& thì ra bàn ăn vẫn còn nhiều anh kiếm chỗ cho anh nảy mới nắm đầu từ hàng chờ vào thôi
		else
		{
			//* giống hàm RED
			
			//* Bước 6 nếu TH mà sizeCustomerInDesk >= MAXSIZE / 2 ta phải tìm vị trí mới của customerX
			//* tìm vị trí mới đễ dễ dàng insert customer mới
			//
			if(sizeCustomerInDesk >= MAXSIZE / 2)
			{
				//* tìm kiếm khách hàng customerX dùng for để tìm giá trị lớn nhất dựa trên sizeCustomerInDesk
				//* customerX sẽ lưu vị trí lớn nhất
				//& nhà hàng đông quá mất tích thằng lên món đầu tiên rồi thôi tìm thằng có trị tuyệt đối hiện năng lượng lớn nhất
				//& tìm được nó mới thêm thằng nhót nảy hàng chờ chứ thêm nó vô đại mấy anh kia đấm nữa
				customer* temp = customerX;
				for(int i = 0; i < sizeCustomerInDesk; i++)
				{
					//& thằng này đang có trị tuyệt đối enery lớn hơn nè mà duyệt đến cuối xem nào lớn hơn nữa không
					//TODO tìm thằng có năng có độ chênh lệch sức mạng so với thằng mới vô
					if(abs(newCustomer->energy - temp->energy) > abs(newCustomer->energy - customerX->energy))
					{
						customerX = temp;
					}			
					temp = temp->next; 
					//& Tìm được thằng lên món đầu tiên thôi (customerX) tìm hơi mệt nha
				}
			
			}
			
			//* Bước 7 trường hợp chèn theo chiều kim đồng hồ
			//& h có thằng khách hàng lên món đàu tiên rồi h thêm thằng 
			//& thêm thằng nhót nảy hàng chờ vào trước hay sau thằng X đây
			if(newCustomer->energy >= customerX->energy)
			{
				//& thôi thấy nó mạnh hơn kia thêm nó vào trước thằng X đi
				//& cập nhật cho 2 anh kế bên chứ 2 ảnh đấm nó nữa
				//TODO thêm vào trước khách hàng dùng prev
				newCustomer->next = customerX->next;
				newCustomer->prev = customerX;
				customerX->next = newCustomer->next->prev = newCustomer;
			}
			//* Bước 7 trương hợp chèn ngược chiều kim đồng hồ
			else
			{
				//& thôi thấy nó mạnh hơn kia thêm nó vào sau thằng X đi
				//& cập nhật cho 2 anh kế bên chứ 2 ảnh đấm nó nữa
				//TODO thêm vào sau khách hàng dùng next
				newCustomer->next = customerX;
				newCustomer->prev = customerX->prev;
				customerX->prev = newCustomer->prev->next = newCustomer;
			}
		}	
		customerX = newCustomer;
		//& cập nhật số lượng khách trong bàn bàn
		sizeCustomerInDesk++;
	}
}

void imp_res::BLUE(int num)
{
	//* Không có khách lấy gì xóa :<
		//& nhà hàng méo còn khách mà ông chủ bắt đuổi
		if(sizeCustomerInDesk == 0) return;

	//* Bước 1 số lượng khách hàng bị đuổi
		//& chạy KPI số khách đuổi để nộp lên sếp nào không ổng trừ lương nữa
		for(int i = 0; i < num && sizeCustomerInDesk != 0; i++)
		{
		//* Bước 1.1 Tìm khách chuẩn bị đuổi và xóa khỏi danh sách Time
			//& thằng này là thằng ngồi ăn lì tại nhà hàng tao à mày chết rồi
			//* tìm khách hàng đang ăn mà lâu nhất đuổi cổ nó ra
			customerTime* customerTimeDelete = CustomerTimeHead;
			for(int i = 0; i < sizeCustomerQueue + sizeCustomerInDesk; i++)
			{
				//TODO tìm thấy khách hàng ăn lâu nhất
				if(customerTimeDelete->inDisk) break;
				customerTimeDelete = customerTimeDelete->next;
			}

			//* xóa nó ra khỏi danh sách Time đuổi nó thì tống cổ nó đi thôi
			//& thì ra chỉ còn thằng cuối cùng trong nhà hàng cho cút luôn
			if(sizeCustomerQueue + sizeCustomerInDesk == 1)
			{
				CustomerTimeHead = CustomerTimeTail = nullptr;
			}
			//& thì ra thằng mới vô đầu tiên cho nó cút rồi cập nhật khác làm đầu tiền
			else if(customerTimeDelete == CustomerTimeHead) 
			{
				//TODO xóa node đầu danh sách liên kết đôi
				customerTimeDelete->next->prev = nullptr;
				CustomerTimeHead = CustomerTimeHead->next;
			}
			//& thì ra thằng này mới vô thôi thấy hơi tội cũng có nó cút luôn
			else if(customerTimeDelete == CustomerTimeTail)
			{
				//TODO xóa node cuối danh sách liên kết đôi
				customerTimeDelete->prev->next = nullptr;
				CustomerTimeTail = CustomerTimeTail->prev;
			}
			//& thì ra thằng này không phải đầu tiên hay cuối cùng nhưng cũng cho nó cút
			else
			{
				//TODO xóa node bất kì danh sách liên kết đôi
				customerTimeDelete->next->prev = customerTimeDelete->prev;
				customerTimeDelete->prev->next = customerTimeDelete->next;
			}



		//* Bước 1.2 đuổi khách trong bàn
			//& tới chỗ nó kéo đầu ra dần 1 trận rồi đuổi này thì không tip
			this->delteCustomerInDisk(customerTimeDelete);
			delete customerTimeDelete;
		}

	//* Bước 2 xử lý đưa khách hàng từ hàng chờ vào bàn ăn
		//& đuổi xong rồi đưa mấy em từ hàng chờ vào ăn kiếm siền thôi
		this->insertCustomerQueueToInDisk();
}

//! Tới chỗ nó đuổi thẳng cổ
void  imp_res::delteCustomerInQueue(customerTime* customerTimeDelete){
	//* Bước 1 đuổi khách hàng trong hàng chờ khi chỉ có 1 khách hàng
	//& thì ra trong bàn không còn nào chỉ còn mình nó ăn kéo đầu nó ra khỏi quán
	if(sizeCustomerQueue == 1) customerQueue = nullptr;

	//* bước 2 đuổi khách hàng
	//& thì ra thằng này đang ăn với 1 mớ thằng nên cho nó cút sớm 
	else
	{
		//& tới chỗ nó lôi nó ra
		customer* customerDelete = customerTimeDelete->data;

		//* cập nhật tại khách hàng phía trước và khách hàng phía sau
		//& cập nhật cho 2 anh hai bên của nó không mấy ảnh giận về nữa
		//TODO cập nhật khách hàng phái trước và sau
		customerDelete->next->prev = customerDelete->prev;
		customerDelete->prev->next = customerDelete->next;

		//* cập nhật lại khách hàng đầu hàng chờ
		if(customerDelete == customerQueue) customerQueue = customerQueue->next;	
	}

	//* Bước 3 cập nhật size
	//& cập nhật số lượng khách trong bàn bàn
	sizeCustomerQueue--;
}

void imp_res::DOMAIN_EXPANSION()
{
//* Không có khách để đuổi
	if(sizeCustomerInDesk == 0) return;

//* Bước 1 tính tổng của thuật sư và oán linh
	int total_Wizard = 0; //! Tổng năng lượng thuật sư
	int total_Spirit = 0; //! Tổng năng lượng oán linh

	customerTime* temp = CustomerTimeHead;
	for(int i = 0; i < sizeCustomerInDesk + sizeCustomerQueue; i++)
	{
		//TODO tính tổng năng lượng thuật sư, năng lượng oán linh	
	 	if(temp->data->energy > 0) total_Wizard += temp->data->energy;
		else total_Spirit += temp->data->energy;
		temp = temp->next;
	}


//* Bước 2 đuổi khách xem thử đuổi bên nào và print ra luôn đuổi trong hàng bàng
	
	temp = CustomerTimeTail;
	while(temp != nullptr){
		if(abs(total_Spirit) <= total_Wizard && temp->data->energy < 0 //! TH 1
		|| abs(total_Spirit) > total_Wizard && temp->data->energy > 0 //! TH 2
		)
			temp->data->print();
		temp = temp->prev;
	}

	temp = CustomerTimeHead;
	while(temp != nullptr)
	{
		//* xóa xảy ra 2 
		//* trường hợp xóa 1 khách hàng temp là thuật sư và tổng năng lượng thuật sư thua
		//* trường hợp xóa 2 khách hàng temp là oán linh và tổng năng lượng oán linh thua
		if(abs(total_Spirit) <= total_Wizard && temp->data->energy < 0 //! TH 1
		|| abs(total_Spirit) > total_Wizard && temp->data->energy > 0 //! TH 2
		)
		{
		//* Bước 2.1 Tìm khách chuẩn bị đuổi và xóa khỏi danh sách Time
			//& thằng này là thằng ngồi ăn lì tại nhà hàng tao à mày chết rồi
			//* tìm khách hàng đang ăn mà lâu nhất đuổi cổ nó ra
			customerTime* customerTimeDelete = temp; //! lấy khách hàng đó xử lí thôi
			temp = temp->next; //! di chuyển em nó lên khách hàng tiếp theo phái sau

			//* xóa nó ra khỏi danh sách Time đuổi nó thì tống cổ nó đi thôi
			//& thì ra chỉ còn thằng cuối cùng trong nhà hàng cho cút luôn
			if(sizeCustomerQueue + sizeCustomerInDesk == 1)
			{
				CustomerTimeHead = CustomerTimeTail = nullptr;
			}
			//& thì ra thằng mới vô đầu tiên cho nó cút rồi cập nhật khác làm đầu tiền
			else if(customerTimeDelete == CustomerTimeHead) 
			{
				//TODO xóa node đầu danh sách liên kết đôi
				customerTimeDelete->next->prev = nullptr;
				CustomerTimeHead = CustomerTimeHead->next;
			}
			//& thì ra thằng này mới vô thôi thấy hơi tội cũng có nó cút luôn
			else if(customerTimeDelete == CustomerTimeTail)
			{
				//TODO xóa node cuối danh sách liên kết đôi
				customerTimeDelete->prev->next = nullptr;
				CustomerTimeTail = CustomerTimeTail->prev;
			}
			//& thì ra thằng này không phải đầu tiên hay cuối cùng nhưng cũng cho nó cút
			else
			{
				//TODO xóa node bất kì danh sách liên kết đôi
				customerTimeDelete->next->prev = customerTimeDelete->prev;
				customerTimeDelete->prev->next = customerTimeDelete->next;
			}


		
		//* Bước 2.2 đuổi khách trong bàn
			//& tới chỗ nó kéo đầu ra dần 1 trận rồi đuổi này thì không tip
			if(customerTimeDelete->inDisk) this->delteCustomerInDisk(customerTimeDelete);
			else this->delteCustomerInQueue(customerTimeDelete);
			delete customerTimeDelete;
		}
		else temp = temp->next;
	}

		
//* Bước 3 xử lý đưa khách hàng từ hàng chờ vào bàn ăn
	this->insertCustomerQueueToInDisk();
}

void imp_res::LIGHT(int num)
{
	//* print hàng chờ customerQueue
	if(num == 0)
	{
		//TODO: dùng vòng lặp for dựa trên sizeCustomerQueue sử dụng hàm print trong class custome
		customer* temp = customerQueue;
		for(int i = 0; i < sizeCustomerQueue; i++)
		{
			temp->print();
			temp = temp->next;
		}
	}
	//* print hàng trong bàn customerX theo chiều kim đồng hồ
	else if(num > 0)
	{	
		//TODO: dùng vòng lặp for dựa trên sizeCustomerInDesk và next sử dụng hàm print trong class custome
		customer* temp = customerX;
		for(int i = 0; i < sizeCustomerInDesk; i++)
		{
			temp->print();
			temp = temp->next;
		}
	}
	//* print hàng trong bàn customerX ngược chiều kim đồng hồ
	else 
	{
		//TODO: dùng vòng lặp for dựa trên sizeCustomerInDesk và prev sử dụng hàm print trong class custome
		customer* temp = customerX;
		for(int i = 0; i < sizeCustomerInDesk; i++)
		{
			temp->print();
			temp = temp->prev;
		}
	}
}

//! swap địa chỉ 2 node
void imp_res::swapAdress(customer* head, customer * tail)
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

//! tìm khách hàng chú thuật sư tiếp theo prev
Restaurant::customer* imp_res::REVERSAL_Wizardhead(customer* x)
{
	for(int i = 0; i < sizeCustomerInDesk; i++)
	{
		if(x->energy > 0) return x;
		x = x->prev;
	}
	return x;
}

//! tìm khách hàng chú thuật sư tiếp theo next
Restaurant::customer* imp_res::REVERSAL_Wizardtail(customer* x)
{
	for(int i = 0; i < sizeCustomerInDesk; i++)
	{
		if(x->energy > 0) return x;
		x = x->next;
	}
	return x;
}
//! tiến hành đảo chú thuật sư
void imp_res::REVERSAL_Wizard(customer* x)
{
	customer* head = this->REVERSAL_Wizardhead(x); //
	customer* tail = this->REVERSAL_Wizardtail(x->next); 
	
	if(head->energy < 0) return;

	while(head != tail)
	{
		
		this->swapAdress(head, tail);
		swap(head, tail);

		head = this->REVERSAL_Wizardhead(head->prev);
		if(head == tail) return;		
		tail = this->REVERSAL_Wizardtail(tail->next); 
	}
}

//! tìm khách hàng oán linh tiếp theo prev
Restaurant::customer* imp_res::REVERSAL_Spirithead(customer* x)
{
	for(int i = 0; i < sizeCustomerInDesk; i++)
	{
		if(x->energy < 0) return x;
		x = x->prev;
	}
	return x;
}

//! tìm khách hàng oán linh tiếp theo next
Restaurant::customer* imp_res::REVERSAL_Spirittail(customer* x)
{
	for(int i = 0; i < sizeCustomerInDesk; i++)
	{
		if(x->energy < 0) return x;
		x = x->next;
	}
	return x;
}
//! tiến hành đảo oán linh
void imp_res::REVERSAL_Spirit(customer* x)
{
	customer* head = this->REVERSAL_Spirithead(x); //
	customer* tail = this->REVERSAL_Spirittail(x->next); 

	if(head->energy > 0) return;

	while(head != tail)
	{
		this->swapAdress(head, tail);
		swap(head, tail);

		head = this->REVERSAL_Spirithead(head->prev);
		if(head == tail) return;		
		tail = this->REVERSAL_Spirittail(tail->next); 
	}
}

void imp_res::REVERSAL()
{

	if(sizeCustomerInDesk > 1)
	{
		//! đảo oán linh trước thuật sư
		if(customerX->energy > 0)
		{	
			REVERSAL_Spirit(customerX);
			REVERSAL_Wizard(customerX);
		}
		//! ngươc lại
		else
		{
			REVERSAL_Wizard(customerX);
			REVERSAL_Spirit(customerX);
		}
	}
}


void imp_res::UNLIMITED_VOID()
{
	if(sizeCustomerInDesk <= 3) return;

	int MIN_TOTAL = INT_MAX; //! đáp án
	customer* head = nullptr, * tail = nullptr; //! node đầu cuối dãy nhỏ nhất
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
				tail = tempj;
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
	customer* temp = head->next; //! vì duyệt qua next nên sizeHeadToTail = 1
	int sizeHeadToMin = 1, sizeHeadToTail = 1;
	//TODO: tìm min energy đầu tiên, tính sizeHeadToMin và sizeHeadToTail
	while(temp != tail->next)
	{
		sizeHeadToTail ++;
		if(min->energy > temp->energy)
		{
			min = temp;
			sizeHeadToMin = sizeHeadToTail;
		}
		temp = temp->next;
	}
	//TODO: print từ min -> tail 
	for(int i = 0; i <= sizeHeadToTail - sizeHeadToMin; i++)
	{
		min->print();
		min = min->next;
	}
	
	//TODO: print từ head -> min
	for(int i = 0; i < sizeHeadToMin - 1; i++)
	{
		head->print();
		head = head->next;
	}
}



//* hàm tìm tại vị trí
//& h đang đứng chỗ thằng X h muốn tìm thằng x đống tiền tip phải đếm cách x, index lần
imp_res::customer* imp_res::getCustomerAt(customer* x, int index)
{
	for(int i = 0; i < index; i++) x = x->next;
	return x;
}

bool imp_res::checkCustomer(customer* x, customer* y)
{
	customerTime* temp = CustomerTimeHead;
	while(temp != NULL)
	{
		if(temp->data == x) return false;
		else if (temp->data == y) return true;
		temp = temp->next;
	}
	return true;
}

//* Insertion sort với A[0], A[incr], A[incr*2], ...
//& sort thằng nào mạnh nhất (enery max) lên đầu thằng nào yếu nhất cho nó cút xuống dưới  
int imp_res::inssort2(customer* head, int n, int incr) {
	int COUNT = 0; //! sô lượng swap 
	for(int i = incr; i < n; i += incr)
	{
		for(int j = i; j >= incr; j -= incr)
		{
			//* lấy phần tử so sánh
			//& Thấy 2 thằng này rồi a và b
			customer* a = this->getCustomerAt(head, j);
			customer* b = this->getCustomerAt(head, j - incr);

			//TODO tìm điệu kiện dừng
			//& thôi thằng sau yếu quá thôi cho nó ngồi lại
			if(abs(a->energy) < abs(b->energy) 
				|| (abs(a->energy) == abs(b->energy) && checkCustomer(a,b))) break;

			//& đưa thằng mạnh lên thằng yếu xuống dưới
			swapAdress(a, b);
			COUNT++;

			//TODO xét trường hợp b = customerQueue or head thì án lại bằng a
			//& đưa thằng mạnh lên trúng ngay thằng đầu hàng phải cập lại thằng đầu hàng thành thằng mạnh
			if(b == customerQueue) customerQueue = a;
			//& đưa thằng mạnh lên lại trúng chỗ thằng head đầu dãy thôi để cập nhật lại
			if(head == b) head = a;
		}
	}
	return COUNT;
}

void imp_res::PURPLE()
{
	if(this->sizeCustomerQueue <= 1) return;
	int removeBLUE = 0;

	//* bước 1 tìm vị trí của min abs(energy)
	customerTime* temp = CustomerTimeTail;
	customerTime* max = nullptr;
	for(int i = 0; i < sizeCustomerQueue + sizeCustomerInDesk; i++)
	{
		if(temp->inDisk == 0 && max == nullptr)
		{
			max = temp;
		}
		else if(temp->inDisk == 0 && abs(temp->data->energy) > abs(max->data->energy))
		{
			//* cập nhật max
			max = temp;
		}
		temp = temp->prev;
	}

	int n = 1; //! kích thước danh sách cần sort
	customer* t = customerQueue;
	while(t != max->data)
	{
		n++;
		t = t->next;
	}
	


	//* bước 2 sort
	for(int i = n / 2; i > 2; i /= 2)
	{
		//* phần tử bắt đầu của sort từ 0 -> i 	
		for(int j = 0; j < i; j++)
		{
			//* tiến hành sort với index bắt đầu customerQueue[j]
			//* mỗi bước nhảy là i -> nghĩa là so sánh Q[j], Q[j+i], ...
			//* n - j là kích thước của mảng hiện tại
			removeBLUE += inssort2(this->getCustomerAt(customerQueue, j), n - j, i);
		}
	}
	removeBLUE += inssort2(customerQueue, n, 1);
	
	//* BƯỚC 3 XÓA
	this->BLUE(removeBLUE % MAXSIZE);
}