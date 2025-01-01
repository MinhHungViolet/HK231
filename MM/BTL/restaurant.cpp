#include "main.h"

int MAXSIZE = 0;

class JJK_RES;
class OPERATOR_RES;
class GOJO_RES;
class SUKUNA_RES;


class OPERATOR_RES{
	class Node;
private:
	Node* root = nullptr;
public:
	~OPERATOR_RES(){clear(root);}
	void clear(Node* node)
	{
		if(node)
		{
			clear(node->left);
			clear(node->right);
			delete node;
		}
	}

	vector<pair<char, int>> readName(string& name)
	{
		vector<pair<char, int>> prefq;
		for (char c : name){
            bool found = false;
            for (int i = 0; i < prefq.size(); i++){
                if (prefq[i].first == c){
                    prefq[i].second++;
                    found = true;
                    break;
                }
            }
            if (found == false){
                prefq.push_back({c, 1});
            }
        }
		if(prefq.size() < 3) return {};

		for (int i = 0; i < name.length(); i++){
            int shift = 0;
            for (int j = 0; j < prefq.size(); j++){
                if (prefq[j].first == name[i]){
                    shift = prefq[j].second;
                    break;
                }
            }
            if (isupper(name[i])){
                name[i] = char(int('A' + (name[i] - 'A' + shift) % 26));
            } else if (islower(name[i])){
                name[i] = char(int('a' + (name[i] - 'a' + shift) % 26));
            }
        }

        for (int i = 0; i < prefq.size(); i++){
            if (isupper(prefq[i].first)){
                prefq[i].first = char(int('A' + (prefq[i].first - 'A' + prefq[i].second) % 26));
            } else if (islower(prefq[i].first)){
                prefq[i].first = char(int('a' + (prefq[i].first - 'a' + prefq[i].second) % 26));
            }
        }

		vector<pair<char, int>> fq;
		fq.push_back(prefq[0]);
		for(int i = 1; i < prefq.size(); i++) {
			bool found = false;
			for(int j = 0; j < fq.size(); j++) {
				if(fq[j].first == prefq[i].first) {
					fq[j].second += prefq[i].second;
					found = true;
					break;
				}
			}
			if(!found) fq.push_back(prefq[i]);
		}

		sort(fq.begin(), fq.end(), [](const pair<char, int>& a, const pair<char, int>& b) {
			if (a.second == b.second) {
				if(isupper(a.first) && islower(b.first)) return true;
				else if(islower(a.first) && isupper(b.first)) return false;
				else return a.first > b.first;
			}
			return a.second > b.second;
		});

		return fq;
	}

	int getHeight(Node* node) {
		if (node == nullptr) {
			return 0;
		}
		return 1 + max(getHeight(node->left), getHeight(node->right));
	}

	Node* leftRotate(Node* root) {
		Node* newNode = root->right;
		Node* transferNode = newNode->left;

		root->right = transferNode;
		newNode->left = root;

		root->height = max(getHeight(root->left), getHeight(root->right));
		newNode->height = max(getHeight(newNode->left), getHeight(newNode->right));
		
		return newNode;
	}

	Node* rightRotate(Node* root) {
		Node* newNode = root->left;
		Node* transferNode = newNode->right;

		root->left = transferNode;
		newNode->right = root;

		root->height = max(getHeight(root->left), getHeight(root->right));
		newNode->height = max(getHeight(newNode->left), getHeight(newNode->right));
		
		return newNode;

	}

	int balanceFactor(Node* node) {
		if(node == nullptr) return 0;
		return getHeight(node->left) - getHeight(node->right);
	}

	Node* balanceNode(Node* node, int& count){
		if(node == nullptr || count >= 3) return node;
		if(node->left) node->left = balanceNode(node->left, count);
		if(node->right) node->right = balanceNode(node->right, count);

		int balance = balanceFactor(node);

		// if (balance > 1 && balanceFactor(node->left) >= 0) {
		// 	count++;
		// 	node = rightRotate(node);
		// }
		// if (balance > 1 && balanceFactor(node->left) < 0) {
		// 	node->left = leftRotate(node->left);
		// 	count ++;
		// 	if (count >= 3) return node;
		// 	node = rightRotate(node);
		// }
		// if (balance < -1 && balanceFactor(node->right) <= 0) {
		// 	count++;
		// 	node = leftRotate(node);
		// }
		// if (balance < -1 && balanceFactor(node->right) > 0) {
		// 	node->right = rightRotate(node->right);
		// 	count ++;
		// 	if (count >= 3) return node;
		// 	node = leftRotate(node);
		// }

		if(balance > 1) {
			//trường hợp LL hoặc LR
			if(node->left->right && /*(height(node->left->right) > height(node->left->left))*/ balanceFactor(node->left) < 0) {
				node->left = leftRotate(node->left);
				count++;
			}
			if(count < 3) {
				node = rightRotate(node);
				count++;
			}
		}
		if(balance < -1)  {
			//trrường hợp RR hoặc RL
			if(node->right->left && /*(height(node->right->left) > height(node->right->right))*/ balanceFactor(node->right) > 0) {
				node->right = rightRotate(node->right);
				count++;
			}
			if(count < 3) {
				node = leftRotate(node);
				count++;
			}
		}

		node->height = max(getHeight(node->left), getHeight(node->right));
		return node;
	}
	Node* balanceTree(Node* node, int count = 0)
	{
		if(node == nullptr  || count == 1) return node;
		node = balanceNode(node, count);
		node->left = balanceTree(node->left, count);
		node->right = balanceTree(node->right, count);
		return node;
	}
	Node* buildHuff(vector<pair<char, int>> fq)
	{
		vector<Node*> forestNode;
		for(int i = 0; i < fq.size(); i++) {
			forestNode.push_back(new Node(fq[i].second, fq[i].first));
		}


		while(forestNode.size() > 1)
		{
			Node* node1 = forestNode.back();
			forestNode.pop_back();
			Node* node2 = forestNode.back();
			forestNode.pop_back();

			Node* newNode = new Node(node1->weight + node2->weight, '\0', node1, node2);
			newNode->height = max(getHeight(newNode->left), getHeight(newNode->right));

			newNode = balanceTree(newNode);
			newNode = balanceTree(newNode);
			newNode = balanceTree(newNode);

			int index = -1;
			for(int i = 0; i < forestNode.size(); i++) {
                if(newNode->weight >= forestNode[i]->weight) {
                    index = i;
                    break;
                }
            }
            if(index == -1) forestNode.push_back(newNode);
            else forestNode.insert(forestNode.begin() + index, newNode);
		}		
		return forestNode[0];
	}
	void encodeTree_help(vector<string>& codeName, Node* node, string s = ""){
		if(node == nullptr) return;
		if(node->isChar()) {
			codeName[node->c] = s;
			return;
		}
		encodeTree_help(codeName, node->left, s + "0");
		encodeTree_help(codeName, node->right, s + "1");
	}
	int encodeTree(Node * root,string name){
		if(root->left == nullptr && root->right == nullptr) return 0;

		vector<string> codeName(256, "");
		encodeTree_help(codeName, root);

		string bin = "";
		for(int i = 0; i < name.length(); i++) {
			bin += codeName[name[i]];
		}
		if(bin.length() > 10) bin = bin.substr(bin.length() - 10, 10);
		reverse(bin.begin(), bin.end());

		//bin to dec
		int result = 0;
		int power = 0;
		for(int i = bin.size() - 1; i >= 0 ;i--) {
			if(bin[i] == '1') result += pow(2, power);
			power++;
		}
		return result;
	}


	int encode(string name){

		vector<pair<char, int>> fq  = this->readName(name);
		if(fq.size() == 0) return -1;


		this->clear(root);
		root = this->buildHuff(fq);
		if(root->left == nullptr && root->right == nullptr) return 0; 
		
		int result = this->encodeTree(root ,name);
		return result;
	}


	void print_help(Node* node){
		if(node == nullptr) return;
		print_help(node->left);
		if(node->c == '\0') cout << node->weight << "\n";
		else cout << node->c << "\n";
		print_help(node->right);
	}
	void print_HAND(){
		print_help(root);
	}

private:
	class Node{
	public:
		int weight;
		int height;
		char c;
		Node* left;
		Node* right;
		friend class OPERATOR_RES;
	public:
		Node(int weight, char c = '\0',Node* left = nullptr, Node* right = nullptr ):  weight(weight), c(c), left(left), right(right) {}
		bool isChar() const { return c != '\0'; }
	};
};

class SUKUNA_RES{
	class Node;
private:
	vector<Node* > area;
	list<Node* > LRU; 
private:
	void ReHeap_down(int index){
		int leftChild = 2 * index + 1;
		int rightChild = 2 * index + 2;
		int smallest = index;

		if (leftChild < area.size() && 
			(area[leftChild]->size() < area[smallest]->size() ||
			(area[leftChild]->size() == area[smallest]->size() && 
			std::distance(LRU.begin(), std::find(LRU.begin(), LRU.end(), area[leftChild])) >
			std::distance(LRU.begin(), std::find(LRU.begin(), LRU.end(), area[smallest]))))){
			smallest = leftChild;
		}

		if (rightChild < area.size() && 
        	(area[rightChild]->size() < area[smallest]->size() ||
        	(area[rightChild]->size() == area[smallest]->size() && 
        	std::distance(LRU.begin(), std::find(LRU.begin(), LRU.end(), area[rightChild])) > 
        	std::distance(LRU.begin(), std::find(LRU.begin(), LRU.end(), area[smallest]))))) {
        	smallest = rightChild;
    	}

		if (smallest != index) {
        // Swap the smallest node with the root
        std::swap(area[index], area[smallest]);

        // Recursively heapify the affected sub-tree
        ReHeap_down(smallest);
    	}
	}
	void ReHeap_up(int index){
		if (index <= 0) return;
		int parentIndex = (index - 1) / 2;

		if (area[index]->size() < area[parentIndex]->size() ||
			(area[index]->size() == area[parentIndex]->size() &&
			std::distance(LRU.begin(), std::find(LRU.begin(), LRU.end(), area[index])) >
			std::distance(LRU.begin(), std::find(LRU.begin(), LRU.end(), area[parentIndex])))) {
			std::swap(area[index], area[parentIndex]);
			ReHeap_up(parentIndex);
		}
	}
	void moveUp(Node* node){
		auto it = find(LRU.begin(), LRU.end(), node);
		if(it != LRU.end()) {
			LRU.splice(LRU.begin(), LRU, it);
		} else {
			LRU.push_front(node);
		}
	}
    void removeNode(Node* node){
		LRU.remove(node);
	}
public:
	SUKUNA_RES(){}
	~SUKUNA_RES(){
		for(int i = 0; i < area.size(); i++){
			delete area[i];
		}
	}

	void addArea(int result){
		int ID = result % MAXSIZE + 1;
		int index = -1;
		for(int i = 0; i < area.size(); i++) {
			if(area[i]->ID == ID) {
				index = i;
				break;
			}
		}

		if(index == -1){
			area.push_back(new Node(ID));
			index = area.size() - 1;
			area[index]->insert(result);
			this->moveUp(area[index]);
			this->ReHeap_up(index);
		}
		else 
		{
			area[index]->insert(result);
			this->moveUp(area[index]);
			this->ReHeap_down(index);
		}
	}
	void KEITEIKEN_help(int number)
	{
		if(area.size() <= 0) return;
		vector<Node* > newArea(area.begin(), area.end());
		queue<Node* > delList; 
		int i = 0;
		while(area.size() && i < number)
		{
			Node* nodeDelete = area[0];
			swap(area[0], area[area.size() - 1]);
			area.pop_back();
			this->ReHeap_down(0);

			delList.push(nodeDelete);

			i++;
		}

		area = newArea;

		while(delList.size()){
			Node* nodeDelete = delList.front();
			delList.pop();

			nodeDelete->remove(number);

			int index = 0;
			while(area[index] !=  nodeDelete) index++;

			if(nodeDelete->size() == 0)
			{
				swap(area[index], area[area.size() - 1]);
				this->removeNode(area[area.size() - 1]);
				delete area[area.size() - 1];

				area.pop_back();
			}
			this->ReHeap_down(index);
		}
 	
	}

	void print_preorder(int index, int number)
	{	
		if(index >= this->area.size() || number <= 0) return;
		this->area[index]->print(number);
		print_preorder(index * 2 + 1, number);
		print_preorder(index * 2 + 2, number);
	}
	void LIMITLESS_help(int number){
		print_preorder(0, number);
	}
private:
	class Node{
	private:
		int ID;					
		list<int> head; 	
		friend class SUKUNA_RES;
	public:
		Node(int ID) : ID(ID) {}
		int size() const { 
			return head.size(); 
		}
		void insert(int result){
			head.push_front(result);
		}
		void remove(int number)
		{
			int i = 0;
			while(i < number && !head.empty())
			{
				cout << head.back() << "-" <<ID << "\n";
				head.pop_back();
				i++;
			}
		}
		void print(int number)
		{
			for(list<int>::iterator it = head.begin(); number > 0 && it != head.end(); ++it, --number)
			{
				cout << ID << "-" << *it  << "\n";
			}
		}
	};
};

class GOJO_RES{
	class BST;
private:
	vector<BST> area;
public:
	GOJO_RES():area(MAXSIZE + 1){}

	void LIMITLESS_help(int number)
	{
		if(number <= 0 || number > MAXSIZE) return;
		area[number].print();
	}


	void KOKUSEN_help()
	{
		for(int i = 1; i < MAXSIZE + 1; i++) area[i].remove();
 	}

	void addArea(int result){
		int ID = result % MAXSIZE + 1;
		area[ID].insert(result); 
	}

private:
	class BST{
		class Node;
	private:
		Node* root;	
		queue<int> queueTime; 
	public:
		BST():root(nullptr){}
		~BST()
		{
			for(int i = queueTime.size(); i > 0; --i)
			{
				int temp = queueTime.front();		
				queueTime.pop(); 						
				root = remove_help(root ,temp);
			}
		}
		int size(){
			return queueTime.size();
		}
		Node* insert_help(Node* node, int result){
			if(node == nullptr) {
				queueTime.push(result);
				return new Node(result);
			}
			if(result < node->result) {
				node->left = insert_help(node->left, result);
			} else {
				node->right = insert_help(node->right, result);
			}
			return node;
		}
		void insert(int result){
			root = insert_help(root, result);
		}
		Node* remove_help(Node* node,int result){
			if (node == nullptr) return nullptr;
			if (result < node->result){
				node->left = remove_help(node->left, result);
			}
			else if (result > node->result){
				node->right = remove_help(node->right, result);
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
				node->right = remove_help(node->right, temp->result);
			}
			return node;
		}

		void remove(){
			if(queueTime.empty()) return;
			
			unsigned long long number = DFS(root) % MAXSIZE;
		
			while(number != 0 && !queueTime.empty())
			{
				int temp = queueTime.front();		
				queueTime.pop(); 					
				root = remove_help(root ,temp);
				number --;
			}
		}

		int nodeNumber(Node* node){
			if (node == nullptr) return 0;
				else return 1 + nodeNumber(node->left) + nodeNumber(node->right);
		}
		unsigned long long tohop(int x, int n){
			if(x == 0 || x == n) return 1;
			vector<vector<unsigned long long>> C(n + 1, vector<unsigned long long>(x + 1, 0));
			for(unsigned long long i = 0; i <= n; i++) {
				for(unsigned long long j = 0; j <= i && j <= x; j++) {
					if(j == 0 || j == i) C[i][j] = 1;
					else C[i][j] = C[i-1][j-1] % MAXSIZE + C[i-1][j] % MAXSIZE;
				}
			}
			return C[n][x] % MAXSIZE;
		}
		unsigned long long DFS(Node* node){
			if(node == NULL) return 1;
			unsigned long long numLeft = nodeNumber(node->left);
			unsigned long long numRight = nodeNumber(node->right);
			return (tohop(numLeft, numLeft + numRight) * (DFS(node->left) % MAXSIZE) * (DFS(node->right) % MAXSIZE));
		}
		
		void print_help(Node* node)
		{
			if(node != NULL){
				print_help(node->left);
				cout << node->result << "\n";
				print_help(node->right);
			}
		}
		void print(){
			print_help(root);
		}

	private:
		class Node{
		private:
			int result;
			Node* left;
			Node* right;
			friend class BST;
		public:
			Node(int result) : result(result), left(NULL), right(NULL) {}
		};

	};

};

class JJK_RES
{
private:
	OPERATOR_RES newCus;
	GOJO_RES hash;
	SUKUNA_RES heap;
	
public:

	bool check(int result){
			if (result % 2 == 0) return true;
				else return false;
		}
	void LAPSE(string name)
	{

		if(name[0] >= '0' && name[0] <= '9') //! BỎ lúc nộp
		{
			int result = stoi(name);
			if(result % 2 == 1) hash.addArea(result);
			else heap.addArea(result);
			return;
		}

		int result = newCus.encode(name);
		if(result == -1) return;

		if (check(result)) heap.addArea(result);
			else hash.addArea(result);
	}	

	void KOKUSEN(){
		hash.KOKUSEN_help();
	}

	void KEITEIKEN(int num){
		heap.KEITEIKEN_help(num);
	}

	void HAND(){
		newCus.print_HAND();
	}

	void LIMITLESS(int num){
		hash.LIMITLESS_help(num);
	}
	
	void CLEAVE(int num){
		heap.LIMITLESS_help(num);
	}

};


enum Operation {
	LAPSE,
	KOKUSEN,
	KEITEIKEN,
	HAND,
	LIMITLESS,
	CLEAVE,
	UNKNOWN
};

std::map<std::string, Operation> strToOp {
	{"LAPSE", LAPSE},
	{"KOKUSEN", KOKUSEN},
	{"KEITEIKEN", KEITEIKEN},
	{"HAND", HAND},
	{"LIMITLESS", LIMITLESS},
	{"CLEAVE", CLEAVE}
};

void simulate(string filename)
{
	ifstream ss(filename);
	string str, name;
	int num;

	ss >> str; 
	ss >> MAXSIZE;

	JJK_RES* op = new JJK_RES();

	while (ss >> str)
	{
		Operation operation = UNKNOWN;
		auto it = strToOp.find(str);
		if (it != strToOp.end()) {
			operation = it->second;
		}

		switch(operation) {
			case LAPSE:
				ss >> name;
				op->LAPSE(name);
				break;
			case KOKUSEN:
				op->KOKUSEN();
				break;
			case KEITEIKEN:
				ss >> num;
				op->KEITEIKEN(num);
				break;
			case HAND:
				op->HAND();
				break;
			case LIMITLESS:
				ss >> num;
				op->LIMITLESS(num);
				break;
			case CLEAVE:
				ss >> num;
				op->CLEAVE(num);
				break;
			default:
				// handle unknown operation
				break;
		}
	}
	delete op;
}