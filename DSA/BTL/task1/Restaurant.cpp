#include "main.h"

class imp_res : public Restaurant
{
	class customerTime;
private:
	customer * customerQueue; //! lưu vị trí đầu tiên của khách hàng trong queue
	customer * customerX; //! lưu vị trí của khách hàng vừa cập nhật trong bàn ăn
	//^ ví dụ cho customerX là chỗ lên món đầu tiên

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
	void BLUE(int num){}
	void PURPLE(){}
	void REVERSAL(){}
	void DOMAIN_EXPANSION(){}
	void UNLIMITED_VOID(){}
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
		~customerTime(){
			//delete data; //! đuổi nó thôi
		}
	};

};

void imp_res::RED(string name, int energy)
{
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
			if (temp->data->name == name){
				return;
			}
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
			newCustomer->prev = newCustomer;
			newCustomer->next = newCustomer;
		}
		//* task4 chèn cuối danh sách liên kết đôi vòng
		//& thì ra hàng chờ đang đồng cho mày xuống cuối hàng đứng hộ tao
		else{
			//TODO thêm vào sau khách hàng đầu tiên (thêm vào cuối) dùng next
			newCustomer->next = customerQueue;
			newCustomer->prev = customerQueue->prev; 
			customerQueue->prev = newCustomer; 
			newCustomer->prev->next = newCustomer; 
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
		//TODO cập nhật thằng mới vô này là danh sách liên kết vòng đôi trong bàn ăn cần cập nhật prev và next
		customerX = new customer (name, energy, nullptr, nullptr);  
		customerX->next = customerX;
		customerX->prev = customerX;
		sizeCustomerInDesk ++;
		//^ biến quản lý thời gian khách hàng nào đến trước giống như 1 sổ kí lưu vị trí khách hàng
		//& ghi nó vào danh sách để còn tính tiền nó trốn nữa
		CustomerTimeTail = CustomerTimeHead = new customerTime (customerX, true);  
		return;
	}


	//* Bước 6 nếu TH mà sizeCustomerInDesk >= MAXSIZE / 2.0 ta phải tìm vị trí mới của customerX
	//* tìm vị trí mới đễ dễ dàng insert customer mới
	//
	if(sizeCustomerInDesk >= MAXSIZE / 2.0)
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
		customerX->next = newCustomer;
		newCustomer->next->prev = newCustomer;
	}
	//* Bước 7 trương hợp chèn ngược chiều kim đồng hồ
	else
	{
		//& thôi thấy nó mạnh hơn kia thêm nó vào sau thằng X đi
		//& cập nhật cho 2 anh kế bên chứ 2 ảnh đấm nó nữa
		//TODO thêm vào sau khách hàng dùng next
		newCustomer->next = customerX;
		newCustomer->prev = customerX->prev;
		customerX->prev = newCustomer;
		newCustomer->prev->next = newCustomer;
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
	return;
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
	else if (num > 0)
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