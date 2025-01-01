/*
! Võ Tiến ..............
* Võ Tiến ..............
~ Võ Tiến ..............
& Võ Tiến ..............
TODO Võ Tiến ..............
*/

#include "main.h"


int MAXSIZE = 0;

class JJK_RESTAURANT_OPERATIONS;
class RESTAURANT_Gojo;
class RESTAURANT_Sukuna;
class HuffTree_AVL;


//* nhà hàng của sư phụ GOJO
//* nhà hàng của sư phụ GOJO
class RESTAURANT_Sukuna{
	class Node;
private:
	vector<Node* > areaTable;  //! nơi lưu trữ các khu vực
	list<Node* > LRU; 		  //!  Least Recently Used này là cơ chế khu vực nào có khác vào nhà hàng lâu nhất
private:

	//* hàm gợi ý của anh thôi dùng hay không thì tùy các bạn nha -> nên suy nghĩ khác
	// bool Compere(int index1, int index2)
	// {

	// }
	void ReHeap_down(int index)
	{
		//TODO: với giá trị xét là areaTable[index].size()
		//TODO: này là min heap nên areaTable[index].size() nào bé hơn thì ở trên
		//TODO: nếu 2 thằng bằng nhau thì chọn ra khu nào có khác vào gần nhất dùng list<Node* > LRU;
		//TODO: ví dụ khu A và khu B có số khách bằng nhau nếu khu A mới có khách vào thì so sánh min heap thì khu B đang nhỏ hơn khu A nên ở trên khu A
		int leftChild = 2 * index + 1;
		int rightChild = 2 * index + 2;
		int smallest = index;

		if (leftChild < areaTable.size() && 
			(areaTable[leftChild]->size() < areaTable[smallest]->size() ||
			(areaTable[leftChild]->size() == areaTable[smallest]->size() && 
			std::distance(LRU.begin(), std::find(LRU.begin(), LRU.end(), areaTable[leftChild])) >
			std::distance(LRU.begin(), std::find(LRU.begin(), LRU.end(), areaTable[smallest]))))){
			smallest = leftChild;
		}

		if (rightChild < areaTable.size() && 
        	(areaTable[rightChild]->size() < areaTable[smallest]->size() ||
        	(areaTable[rightChild]->size() == areaTable[smallest]->size() && 
        	std::distance(LRU.begin(), std::find(LRU.begin(), LRU.end(), areaTable[rightChild])) > 
        	std::distance(LRU.begin(), std::find(LRU.begin(), LRU.end(), areaTable[smallest]))))) {
        	smallest = rightChild;
    	}

		if (smallest != index) {
        // Swap the smallest node with the root
        std::swap(areaTable[index], areaTable[smallest]);

        // Recursively heapify the affected sub-tree
        ReHeap_down(smallest);
    	}
	}
	void ReHeap_up(int index)
	{
		//TODO: với giá trị xét là areaTable[index].size()
		//TODO: này là min heap nên areaTable[index].size() nào bé hơn thì ở trên
		//TODO: nếu 2 thằng bằng nhau thì chọn ra khu nào có khác vào gần nhất
		//TODO: này xử lí tương tự reheap_down
		if (index <= 0) return;
		int parentIndex = (index - 1) / 2;

		if (areaTable[index]->size() < areaTable[parentIndex]->size() ||
			(areaTable[index]->size() == areaTable[parentIndex]->size() &&
			std::distance(LRU.begin(), std::find(LRU.begin(), LRU.end(), areaTable[index])) >
			std::distance(LRU.begin(), std::find(LRU.begin(), LRU.end(), areaTable[parentIndex])))) {
			std::swap(areaTable[index], areaTable[parentIndex]);
			ReHeap_up(parentIndex);
		}
	}

	//* nếu node chưa tồn tại trong LRU thì thêm vô nếu tồn tại thì dịch nó lên đầu danh sách
	void moveTop(Node* node)
	{	
		//TODO: BƯỚC 1 Tìm vị trí của node trong danh sách
		// Node* temp = nullptr;
		// Node* prev = nullptr;
		// for (Node* i : LRU) {
		// 	if (i == node) {
		// 		temp = i;
		// 		break;
		// 	}
		// 	prev = i;
		// }
		// //TODO: BƯỚC 2 nếu nó tồn tại thì dịch nó lên đầu danh sách, nếu không thì insert ở đầu danh sách
		// if (temp != nullptr) {
		// 	LRU.remove(prev);
		// 	LRU.push_front(temp);
		// }
		// else {
		// 	LRU.push_front(node);
		// }
		auto it = find(LRU.begin(), LRU.end(), node);
		//TODO: BƯỚC 2 nếu nó tồn tại thì dịch nó lên đầu danh sách, nếu không thì insert ở đầu danh sách
		if(it != LRU.end()) {
			LRU.splice(LRU.begin(), LRU, it);
		} else {
			LRU.push_front(node);
		}
	}

	//* xóa một node ra khỏi danh sách liên kết không gần gọi delete nha vì đã dùng bên dưới hàm xóa
    void removeNode(Node* node)
	{
		//TODO: 
		// if (LRU.size() == 0) return;
		// if (LRU.back() == node){
		// 	LRU.pop_back();
		// } else {
		// 	LRU.remove(node);
		// }
		LRU.remove(node);
	}
public:
	RESTAURANT_Sukuna(){}

	void insertAreaTable(int result)
	{
		int ID = result % MAXSIZE + 1;
		//*bước 1: kiểm tra xem heap có đang quản lí khu ID hay không nếu chưa quản lí thì phải thêm ở bước sau
		int index = -1;
		//TODO TODO TODO TODO TODO bước 1
		for(int i = 0; i < areaTable.size(); i++) {
			if(areaTable[i]->ID == ID) {
				index = i;
				break;
			}
		}

		//*bước 2: xem thử có khu này trong heap chưa để thêm vô 
		if(index == -1){
			areaTable.push_back(new Node(ID));
			index = areaTable.size() - 1;
			areaTable[index]->insert(result);
			this->moveTop(areaTable[index]);
			this->ReHeap_up(index);
		}
		//*bước 3: thêm khách hàng mới vào khu khách hàng muốn thêm vào và tiến hàn reheap down bàn này xuống vì có số khách đông hơn
		else 
		{
			areaTable[index]->insert(result);
			this->moveTop(areaTable[index]);
			this->ReHeap_down(index);
		}
	}

	void remove_KEITEIKEN(int number)
	{
		if(areaTable.size() <= 0) return;

		//* đuổi num khách hàng tại num khu vực
		int numberRemove = number;
		while(areaTable.size() != 0 && number != 0){
			//* lấy ra khu đang ở đầu đầu heap xóa number khách hàng đầu linklist
			solution << "remove customers in the area ID = " << areaTable[0]->ID << ": ";
			areaTable[0]->remove(numberRemove);
			solution << "\n";

			//* trường hợp xóa hết thì xóa nó trong heap sau đó reheap down khu xuống vì đang ở đầu hàng
			if(areaTable[0]->size() == 0)
			{
				swap(areaTable[0], areaTable[areaTable.size() - 1]);
				//! xóa nó khỏi danh sách liên kết
				this->removeNode(areaTable[areaTable.size() - 1]);
				delete areaTable[areaTable.size() - 1];

				//! xóa trong heap nữa
				areaTable.pop_back();
			}
			this->ReHeap_down(0);
			number --;
		}
 	}
//^hàm in ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	void print_pre_order(int index, int number)
	{	
		if(index >= this->areaTable.size()) return;

		this->areaTable[index]->print(number);
		print_pre_order(index * 2 + 1, number);
		print_pre_order(index * 2 + 2, number);
	}
	void print_CLEAVE(int number)
	{
		if(number <= 0) return;

		solution << "Heap : ";
		for(auto it : this->areaTable)
		{
			int order = 0;
			for (auto ix : LRU) {
				if (ix == it) break;
				++order;
			}
			solution << it->ID << "(len="<< it->size() <<",index=" << order <<")" << " ";
		}
		solution << "\n";

		solution << "Heap : ";
		for(auto it : this->areaTable) solution << it->ID  << " ";
		solution << "\n";

		solution << "list LRU : ";
		for(auto it : LRU) solution << it->ID << " ";
		solution << "\n";


		print_pre_order(0, number);
	}
//^ ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
private:
	class Node{
	private:
		int ID;					//! ID của bàn đó
		list<int> head; 		//! lưu danh sách các result của khách hàng
		friend class RESTAURANT_Sukuna;
	public:
		Node(int ID) : ID(ID) {}
		int size() const { return head.size(); }
		//* thêm vô đầu danh sách
		void insert(int result){head.push_front(result);}
		//* xóa ở cuối với số lượng là number cơ chế FIFO vô sớm thì cút sớm
		void remove(int number)
		{
			//TODO: xóa number khác hàng ở cuối danh sách tương ứng với vô sớm nhất 
			//^ gợi ý dùng hàm của linklist có sẵn
			//* thêm solution << head.back() << " "; để in ra
			for(int i = 0; i < number; i++) {
				if(head.size() > 0) {
					solution << head.back() << " ";
					head.pop_back();
				}
			}
		}
		//* print ra number khách hàng mới đến gần nhất theo cơ chế LIFO các khách hàng gần nhất
		void print(int number)
		{
			solution << "customers in the area ID = " << ID << ": ";
			for(list<int>::iterator it = head.begin(); number > 0 && it != head.end(); ++it, --number)
			{
				solution << *it << " ";
			}
			solution << "\n";
		}

	};

};


//* nhà hàng của sư phụ GOJO
class RESTAURANT_Gojo{
	//TODO: code đâu nén vô
	class Tree_BST;
private:
	//* cứ hiểu mỗi phần tử areaTable là các khu ăn trong đó sẽ có 1 nhân viên quản lí thêm vào và xóa ra chủ không cần quản lí mấy này
	vector<Tree_BST> areaTable;
public:
	RESTAURANT_Gojo():areaTable(MAXSIZE + 1){}
	void insertAreaTable(int result)
	{
		//* khách mới vô thích chọn khu có ID = result % MAXSIZE + 1 dắt nó tới chỗ đó rồi nén vô cho nhân viên khu đó xử lí
		int ID = result % MAXSIZE + 1;
		areaTable[ID].insert(result); 
	}

	void remove_KOKUSEN()
	{
		//* tới từng khu ăn kêu nhân viên tìm thằng nào gián điệp đấm nó rồi đuổi cổ nó đi
		for(int i = 1; i < MAXSIZE + 1; i++) areaTable[i].remove();
 	}

	void print_LIMITLESS(int number)
	{
		//* tới khu number kêu nhân viên liệt kê tất cả khách hàng ra 
		if(number <= 0 || number > MAXSIZE) return; //! quá kí tự
		areaTable[number].print();
	}
private:
	//* Tree_BST giống như các nhân viên
	class Tree_BST{
		class Node;
	private:
		Node* root;	//! cây của khách hàng vị trí khách hàng
		queue<int> queueTime; //! thời gian khách hàng đến có thể hiểu như là sổ ghi thông tin khách hàng
	public:
		Tree_BST():root(nullptr){}
		int size(){
			return queueTime.size();
		}

	//^hàm thêm ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		//* nhân viên được chủ giao cho bố trí khách hàng có result
		Node* insert_recursive(Node* node, int result)
		{
			//TODO TODO TODO  TODO TODO TODO  
			if(node == nullptr) {
				queueTime.push(result);
				return new Node(result);
			}
			if(result < node->result) {
				node->left = insert_recursive(node->left, result);
			} else {
				node->right = insert_recursive(node->right, result);
			}
			return node;
		}
		void insert(int result){
			root = insert_recursive(root, result);
		}
	//^ ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	//^hàm xóa ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		//* nhân viên sẽ tới tận nơi đuổi cổ khách hàng gián điệp ra khỏi nhà hàng với result là khách hàng gián điệp
		Node* remove_recursive(Node* node,int result)
		{	
			//TODO TODO TODO  TODO TODO TODO  
			if (node == nullptr) return nullptr;
			if (result < node->result){
				node->left = remove_recursive(node->left, result);
			}
			else if (result > node->result){
				node->right = remove_recursive(node->right, result);
			}
			else {
				if (node->left == nullptr){
					Node* temp = node->right;
					delete node;
					return temp;
				} else if (node->right == nullptr){
					Node* temp = node->left;
					delete node;
					return temp;
				}
				Node* current = node->right;
				while (current && current->left != nullptr){
					current = current->left;
				}
				Node* temp = current;
				node->result = temp->result;
				node->right = remove_recursive(node->right, temp->result);
			}
			return node;
		}
		int CountNode(Node* node)
		{
			return node == NULL ? 0 : 1 + CountNode(node->left) + CountNode(node->right);
		}
		unsigned long long permutationFormula(int x, int n)
		{
			//!TODO TÍNH C(n,x)= x!(n-x)!/n! công thức chỉnh hợp
			if(x == 0 || x == n) return 1;
			vector<vector<unsigned long long>> C(n + 1, vector<unsigned long long>(x + 1, 0));
			for(unsigned long long i = 0; i <= n; i++) {
				for(unsigned long long j = 0; j <= i && j <= x; j++) {
					if(j == 0 || j == i) C[i][j] = 1;
					else C[i][j] = C[i-1][j-1] + C[i-1][j];
				}
			}
			return C[n][x];
		}
		unsigned long long DFS(Node* node)
		{
			if(node == NULL) return 1;
			//TODO TODO TODO  TODO TODO TODO  đệ quy
			unsigned long long countLeft = CountNode(node->left);
			unsigned long long countRight = CountNode(node->right);
			return permutationFormula(countLeft, countLeft + countRight) * DFS(node->left) * DFS(node->right);

		}
		//* nhân viên sẽ liệt kê ra các khách hàng gián điệp để dễ dàng đuổi
		void remove(){
			if(this->size() == 0) return; //! trường hợp rỗng bỏ qua
			//* bước 1: đếm số lượng node cần xóa
			//^ tìm hiểu : https://leetcode.com/problems/number-of-ways-to-reorder-array-to-get-same-bst/
			//TODO: tính số lượng number
			unsigned long long number = DFS(root);
			//*: trường hợp mà postoder cũng tạo ra một cây giống đó thì chỉ có 1 node -> nên không tính
			if(this->size() == 1) return;

			//* bước 2: xóa node trong cây với số lượng đã tính trên
			//* kiểm tra xem đã xóa đủ số lượng chưa hay cây đã hết node để xóa
			while(number != 0 && !queueTime.empty())
			{
				int temp = queueTime.front();			//! tìm khách hàng đầu tiên được lưu trong sổ và lấy được vị trí nó rồi
				queueTime.pop(); 						//! xóa nó khỏi sổ
				root = remove_recursive(root ,temp);	//! tới chỗ nó cho nó cút khỏi nhà hàng
				number --;
			}
		}
	//^ ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	//^hàm in ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		//* hàm này theo trung thứ tự (in-order) thôi không gì khó hết
		string print_recursive(Node* node)
		{
			if(node == nullptr) return "NULL"; //! trường hợp dừng print

			string left = print_recursive(node->left);
			solution << node->result << " ";
			string right = print_recursive(node->right);
			

			if(node->left == nullptr && node->right == nullptr) return to_string(node->result); //! tr
			return to_string(node->result)+"("+left +","+right+")";
		}
		void print(){
			//! trường hợp rỗng bỏ qua
			if(this->size() == 0){
				solution << "EMPTY" ;
				return;
			}
			solution << "inoder: ";
			string s = print_recursive(root);
			solution << "\nTree: " << s;
			std::queue<int> tempQueue = queueTime;
			solution << "\nQueue: ";
			while (!tempQueue.empty()) {
				solution << tempQueue.front() << " ";
				tempQueue.pop();
			}
		}
	//^ ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	private:
		class Node{
		private:
			int result;
			Node* left;
			Node* right;
			friend class Tree_BST;
		public:
			Node(int result) : result(result), left(NULL), right(NULL) {}
		};
	};
};

class HuffTree_AVL{
	class Node;
private:
	Node* root = nullptr;
public:
	vector<pair<char, int>> string_Processing(string& name)
	{
		//TODO: implement
		//TODO: implement string_Processing
				//* bước 1: liệt kê tuần suất xuất hiện của các kí tự riêng biệt trong tên của khách hàng (phân biệt hoa và thường)
		//* tạo thành một danh sách theo vị trí của các kí tự vào trước và vào sau 
		//! VD : name = "aDdbaaabbb" -> kết quả bước này: freq_prev = [{a, 4}, {D,1}, {d,1}, {b,4}]
		//TODO
		vector<pair<char, int>> freq_prev;
        for (char c : name){
            bool found = false;
            for (int i = 0; i < freq_prev.size(); i++){
                if (freq_prev[i].first == c){
                    freq_prev[i].second++;
                    found = true;
                    break;
                }
            }
            if (!found){
                freq_prev.push_back({c, 1});
            }
        }

		//* bước 2: mã hóa Caesar chuỗi name thành chuỗi mới và mã hóa luôn freq_prev 
		//! VD : name = "aDdbaaabbb", freq_prev = [{a, 4}, {D,1}, {d,1}, {b,4}]
		//! kq : name = "eEefeeefff", freq_prev = [{e,4}, {E,1}, {e,1}, {f,4}]
		//TODO
        for (int i = 0; i < name.length(); i++){
            int shift = 0;
            for (int j = 0; j < freq_prev.size(); j++){
                if (freq_prev[j].first == name[i]){
                    shift = freq_prev[j].second;
                    break;
                }
            }
            if (isupper(name[i])){
                name[i] = char(int('A' + (name[i] - 'A' + shift) % 26));
            } else if (islower(name[i])){
                name[i] = char(int('a' + (name[i] - 'a' + shift) % 26));
            }
        }

        for (int i = 0; i < freq_prev.size(); i++){
            if (isupper(freq_prev[i].first)){
                freq_prev[i].first = char(int('A' + (freq_prev[i].first - 'A' + freq_prev[i].second) % 26));
            } else if (islower(freq_prev[i].first)){
                freq_prev[i].first = char(int('a' + (freq_prev[i].first - 'a' + freq_prev[i].second) % 26));
            }
        }

		//* bước 3: công dồn freq_prev với các kí tự giống nhau sau khi mã hóa
		//^ chú ý cộng dồn lên phái đầu ví dụ dưới 'e' có 2 chỗ nên ta chọn đầu vector để giữ lại
		//! vd freq_prev = [{e,4}, {E,1}, {e,1}, {f,4}] -> kq:  freq = [{e,5}, {E,1}, {f,4}]
		//TODO
		vector<pair<char, int>> freq;
		freq.push_back(freq_prev[0]);
		for(int i = 1; i < freq_prev.size(); i++) {
			bool found = false;
			for(int j = 0; j < freq.size(); j++) {
				if(freq[j].first == freq_prev[i].first) {
					freq[j].second += freq_prev[i].second;
					found = true;
					break;
				}
			}
			if(!found) freq.push_back(freq_prev[i]);
		}

		//* bước 4: sort chuỗi freq mới tìm được phía trên theo chiều giảm dần
		//^ chú ý nếu tuần suất hiện bằng nhau thì kí tự nào lớn hơn thì lớn hơn, kí tự hoa lớn hơn kí tự thường
		//TODO
		sort(freq.begin(), freq.end(), [](const pair<char, int>& a, const pair<char, int>& b) {
			if (a.second == b.second) {
				if(isupper(a.first) && islower(b.first)) return true;
				else if(islower(a.first) && isupper(b.first)) return false;
				else return a.first > b.first;
			}
			return a.second > b.second;
		});


		return freq;
	}

	int height(Node* node) {
		if (node == nullptr) {
			return 0;
		}
		return 1 + max(height(node->left), height(node->right));
	}

	int balanceFactor(Node* node) {
		if(node == nullptr) return 0;
		return height(node->left) - height(node->right);
	}

	Node* rotateLeft(Node* root) {
		Node* newRoot = root->right;
		Node* transferNode = newRoot->left;
		newRoot->left = root;
		root->right = transferNode;
		root->height = max(height(root->left), height(root->right)) + 1;
		newRoot->height = max(height(newRoot->left), height(newRoot->right)) + 1;
		return newRoot;
	}

	Node* rotateRight(Node* root) {
		Node* newRoot = root->left;
		Node* transferNode = newRoot->right;
		newRoot->right = root;
		root->left = transferNode;
		root->height = max(height(root->left), height(root->right)) + 1;
		newRoot->height = max(height(newRoot->left), height(newRoot->right)) + 1;
		return newRoot;

	}


	Node* balanceNode(Node* node, int& count) 
	{
		//TODO
		// if(node == nullptr || count >= 3) return node;
		// if(node->left) node->left = balanceNode(node->left, count);
		// if(node->right) node->right = balanceNode(node->right, count);

		node->height = 1 + max(height(node->left), height(node->right));
	
		int balance = balanceFactor(node);

		if (balance > 1 && balanceFactor(node->left) >= 0) {
			count++;
			node = rotateRight(node);
		}
		if (balance > 1 && balanceFactor(node->left) < 0) {
			node->left = rotateLeft(node->left);
			count += 2;
			if (count >= 4) return node;
			node = rotateRight(node);
		}
		if (balance < -1 && balanceFactor(node->right) <= 0) {
			count++;
			node = rotateLeft(node);
		}
		if (balance < -1 && balanceFactor(node->right) > 0) {
			node->right = rotateRight(node->right);
			count += 2;
			if (count >= 4) return node;
			node = rotateLeft(node);
		}
		
		return node;

	}

	//* tiến hành đệ quy theo preOrder -> nếu count >= 3 thì dừng lại không cân bằng nữa
	Node* balanceTree(Node* node, int& count)
	{
		//TODO
		if(node && count <= 3) {
			node = balanceNode(node, count);
			node->left = balanceTree(node->left, count);
			
			node->right =balanceTree(node->right, count);
			return node;
		}
		return node;
	}

	Node* buildHuff(vector<pair<char, int>> freq)
	{
		// //TODO: implement
		// //* bước 1 : chuyển freq thành build theo thứ tự 0 -> n
		// //TODO: này không làm được đăng kí môn đi nha

		// vector<Node*> build;
		// int timestamp = 0;
		// for(int i = 0; i < freq.size(); i++) {
		// 	build.push_back(new Node(freq[i].second, freq[i].first, nullptr, nullptr, timestamp++));
		// }
		
		// while(build.size() > 1)
		// {
		// 	//TODO: lấy ra node nhỏ nhất thứ nhất và nhỏ nhất thứ 2 (phần tử cuối vector)
		// 	//TODO: tạo ra node nới có con bên trái là node nhỏ nhất và bên phải là node nhỏ nhất thứ 2 -> cập nhật weight, height của node mới
		// 	//^ chú ý : cập nhật height, weight
		// 	int count = 0;
		// 	Node* newNode = nullptr;
		// 	Node* node1 = build.back();
		// 	build.pop_back();
		// 	Node* node2 = build.back();
		// 	build.pop_back();

		// 	// if (node1->weight == node2->weight && (node1->left == nullptr && node1->right == nullptr) && (node2->left != nullptr || node2->right != nullptr)){
		// 	// 	Node* temp = node1;
		// 	// 	node1 = node2;
		// 	// 	node2 = temp;
		// 	// }

		// 	newNode = new Node(node1->weight + node2->weight, '\0', node1, node2, timestamp++);
		// 	build.push_back(newNode);

		// 	build[build.size() - 1] = balanceTree(build[build.size() - 1], count);
		// 	// sort(build.begin(), build.end(), [](Node* node1, Node* node2) {
		// 	// 	if (node1->weight == node2->weight /*&& node1->c != '\0' && node2->c != '\0'*/) {
		// 	// 		return node1->timestamp < node2->timestamp;
		// 	// 	}
		// 	// 	return node1->weight >= node2->weight;
		// 	// });
		// 	sort(build.begin(), build.end(), [](Node* a, Node* b) {
		// 		if(a->weight == b->weight) {
		// 			while(true) {
		// 				if(a == nullptr || b == nullptr) break; 
		// 				if(a->height == b->height) {
		// 					if(a->c != '\0' && b->c != '\0') {
		// 						if(isupper(a->c) && islower(b->c)) return true;
		// 						else if(islower(a->c) && isupper(b->c)) return false;
		// 						else return a->c > b->c;
		// 					}
		// 					if(a->c == '\0' && b->c != '\0') return true;
		// 					if(a->c != '\0' && b->c == '\0') return false;
		// 					if(a->c == '\0' && b->c == '\0') {
		// 						a = a->right;
		// 						b = b->right;
		// 					}   
		// 				} else {
		// 					return a->height > b->height;
		// 				}
		// 			}      
		// 		}
		// 		return a->weight >= b->weight;
		// 	});
		// 	// auto pos = std::upper_bound(build.begin(), build.end(), newNode, [](Node* a, Node* b){
		// 	// 	if (a->weight == b->weight){
		// 	// 		return a->height < b->height;
		// 	// 	}
		// 	// 	return a->weight < b->weight;
		// 	// });
		// 	// build.insert(pos, newNode);
		// 	newNode->height = 1 + max(node1->height, node2->height);

		// 	//TODO: đưa node mới vào trong vector -> đảm bảo vector luôn giảm dần như ban đầu
		// 	//^ chú ý nếu bằng nhau thì xem như node mới luôn lớn hơn các node bằng giá trị weight -> ý là xếp nó gần head hơn

		// }		
		int timestamp = 0;
    vector<Node*> build;
    for(int i = 0; i < freq.size(); i++) {
        build.push_back(new Node(freq[i].second, freq[i].first, nullptr, nullptr, timestamp++));
    }
    
    while(build.size() > 1)
    {
        //TODO: lấy ra node nhỏ nhất thứ nhất và nhỏ nhất thứ 2 (phần tử cuối vector)
        //TODO: tạo ra node nới có con bên trái là node nhỏ nhất và bên phải là node nhỏ nhất thứ 2 -> cập nhật weight, height của node mới
        //^ chú ý : cập nhật height, weight
        int count = 0;
        Node* newNode = nullptr;
        Node* node1 = build.back();
        build.pop_back();
        Node* node2 = build.back();
        build.pop_back();

        newNode = new Node(node1->weight + node2->weight, '\0', node1, node2, timestamp++);
        newNode->height = 1 + max(node1->height, node2->height);
        newNode = balanceTree(newNode, count);

        int index = -1;
        for (int i = 0; i < build.size(); i++) {
            if (build[i]->weight <= newNode->weight) {
                index = i;
                break;
            }
        }
        if (index == -1) {
            build.push_back(newNode);
        } else {
            build.insert(build.begin() + index, newNode);
        }
        // build.push_back(newNode);

        // build[build.size() - 1] = balanceTree(build[build.size() - 1], count);
        // sort(build.begin(), build.end(), [](Node* node1, Node* node2) {
        //     if (node1->weight == node2->weight && node1->c != '\0' && node2->c != '\0'){
        //         return node1->timestamp < node2->timestamp;
        //     }
        //     return node1->weight >= node2->weight;
        // });

        //TODO: đưa node mới vào trong vector -> đảm bảo vector luôn giảm dần như ban đầu
        //^ chú ý nếu bằng nhau thì xem như node mới luôn lớn hơn các node bằng giá trị weight -> ý là xếp nó gần head hơn

    }		
		return build[0];
	}


	int encode(string name){

		if(name.length() < 3) return -1;

		//* bước 1 xử lí chuỗi thu được list để tới phần sau
		vector<pair<char, int>> freq = this->string_Processing(name);
		solution << "freq     : {";
    for (int i = 0; i <freq.size();i++){
		if(i == freq.size() - 1)  solution << "{" <<"'"<< freq[i].first <<"'" << "," << freq[i].second << "}";
		else  solution << "{" <<"'"<< freq[i].first <<"'" << "," << freq[i].second << "},";
	}
		solution << "}"<<endl;
		
		//* bước 2 xây dựng cây huff
		root = this->buildHuff(freq);
	
		if(root->left == nullptr && root->right == nullptr) return 0; //! trường hợp chỉ có 1 node
		this->print();
		return -1;
	}

	void rec_print(const Node* tree) {
		if (tree == nullptr) {
			return;
		}
		if(tree->c) solution << "[" << tree->weight << "," << tree->c << "]";
		else solution << "[" << tree->weight << "]";
		
		if (tree->left != nullptr || tree->right != nullptr) {
			solution << "(";
			rec_print(tree->left);
			solution << ",";
			rec_print(tree->right);
			solution << ")";
		}
	}
	
	void print()
	{	
		//* print theo chiều rộng anh có hướng dẫn rồi queue
		//* khi in chuyển từ cout << "char-freq/n" thành solution << "char-freq/n" cho anh dễ test
		solution << "root : ";
		rec_print(root);
		solution << '\n';
	}

private:
	class Node{
	public:
		int weight;
		char c;
		int height;
		Node* left;
		Node* right;
		int timestamp;
		friend class HuffTree_AVL;
	public:
		Node(int weight, char c = '\0',Node* left = nullptr, Node* right = nullptr, int timestamp = 0 ): height(1), weight(weight), c(c), left(left), right(right), timestamp(timestamp) {}
	};
};


class JJK_RESTAURANT_OPERATIONS
{
private:
	HuffTree_AVL New_customers_arrive;
	RESTAURANT_Gojo hash;
	RESTAURANT_Sukuna heap;
	
public:

	void LAPSE(string name)
	{
		//* mã hóa HuffTree_AVL kết quả là 10 kí tự nhị phân cuối chuyển sang thập phân
		int result = New_customers_arrive.encode(name);
		return;
	}	

	//* xử lí nhà hàng gojo
	void KOKUSEN(){}
	void LIMITLESS(int num){}
	
	//* xử lí nhà hàng Sukuna
	void KEITEIKEN(int num){}
	void CLEAVE(int num){}

	//* xử lý HuffTree_AVL
	void HAND(){New_customers_arrive.print();}
};


