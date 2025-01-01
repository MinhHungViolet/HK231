#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include<vector>
#include<map>
#include<stack>
#include<queue>
#include<list>
#include <utility> 
#include <algorithm>
#include <sstream>
using namespace std;

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
    Node(int weight, char c = '\0',Node* left = nullptr, Node* right = nullptr, int timestamp = 0): height(1), weight(weight), c(c), left(left), right(right), timestamp(timestamp) {}
};

//* cân bằng node yêu cầu xét mất cân bằng loại nào rồi quay nhưng count >= 3 thì dừng
//* trường hợp LL -> tính là count được cộng thêm 1
//* trường hợp RR -> tính là count được cộng thêm 1
//* trường hợp RL -> tính là count được cộng thêm 2
//* trường hợp LR -> tính là count được cộng thêm 2
//* nếu trường hợp LL cũng là LR -> xét như Trường hợp LL
//* nếu trường hợp RL cũng là RR -> xét như Trường hợp RR
//* yêu cầu dùng height để xử lí -> cấm dùng tính height đệ quy :<< độ phức tạp hơi mệt đó
//^ chú ý vì RL LR tính 2 lần nên khi count = 2 mà phải xử lí 1 này thì -> làm 1 lần rồi dừng
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
    if(node == nullptr || count >= 3) return node;
    if(node->left) node->left = balanceNode(node->left, count);
    if(node->right) node->right = balanceNode(node->right, count);

    
  
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
    node->height = 1 + max(height(node->left), height(node->right));
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
    //* bước 1 : chuyển freq thành build theo thứ tự 0 -> n
    //TODO: này không làm được đăng kí môn đi nha

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



//*********** code bên dưới không bận tâm ***************************
bool areHuffmanTreesEqual(const Node* tree1, const Node* tree2);
void printHuffmanTree(const Node* tree);
std::string huffmanTreeToString(const Node* tree) ;
int main()
{
    //* test 1
    {
        vector<pair<char, int>> v = {{'c', 2}, {'b', 1}, {'a', 1}};
        Node* root = new Node(4, '\0', 
                                 new Node(2, 'c'),
                                new Node(2, '\0',
                                    new Node(1, 'a'),
                                    new Node(1, 'b')));
        Node* result = buildHuff(v);
        if(! areHuffmanTreesEqual(root, result))
        {
            cout << "fail test 1 \n";
            cout << "result     = ";printHuffmanTree(root);cout << "\n";
            cout << "output_you = ";printHuffmanTree(result);cout << "\n";
        }
        else cout << "pass test 1 \n";
    }

    //* test 2
    {
        vector<pair<char, int>> v = {{'d',3}, {'c', 2}, {'b', 1}, {'a', 1}};
        Node* root = new Node(4, '\0',
                                new Node(7, '\0',
                                    new Node(3, 'd'),
                                    new Node(2, 'c')),
                                new Node(2, '\0',
                                    new Node(1, 'a'),
                                    new Node(1, 'b')));
        Node* result = buildHuff(v);
        if(! areHuffmanTreesEqual(root, result))
        {
            cout << "fail test 2 \n";
            cout << "result     = ";printHuffmanTree(root);cout << "\n";
            cout << "output_you = ";printHuffmanTree(result);cout << "\n";
        }
        else cout << "pass test 2 \n";
    }

    //* test 3
    {
        vector<pair<char, int>> v = {{'d',6}, {'c', 3}, {'b', 1}, {'a', 1}};
        Node* root = new Node(5, '\0',
                                new Node(2, '\0',
                                    new Node(1, 'a'),
                                    new Node(1, 'b')),
                                new Node(11, '\0',
                                    new Node(3, 'c'),
                                    new Node(6, 'd')));
        Node* result = buildHuff(v);
        if(! areHuffmanTreesEqual(root, result))
        {
            cout << "fail test 3 \n";
            cout << "result     = ";printHuffmanTree(root);cout << "\n";
            cout << "output_you = ";printHuffmanTree(result);cout << "\n";
        }
        else cout << "pass test 3 \n";
    }
    
    //* test 4
    {
        vector<pair<char, int>> v = {{'d',5}, {'c', 3}, {'b', 1}, {'a', 1}};
        Node* root = new Node(2, '\0',
                                new Node(10, '\0',
                                    new Node(5, 'd'),
                                    new Node(1, 'a')),
                                new Node(5, '\0',
                                    new Node(1, 'b'),
                                    new Node(3, 'c')));
        Node* result = buildHuff(v);
        if(! areHuffmanTreesEqual(root, result))
        {
            cout << "fail test 4 \n";
            cout << "result     = ";printHuffmanTree(root);cout << "\n";
            cout << "output_you = ";printHuffmanTree(result);cout << "\n";
        }
        else cout << "pass test 4 \n";
    }


    //* test 5
    {
        vector<pair<char, int>> v = {{'d',5}, {'c', 2}, {'b', 1}, {'a', 1}};
        Node* root = new Node(2, '\0',
                                new Node(4, '\0',
                                    new Node(2, 'c'),
                                    new Node(1, 'a')),
                                new Node(9, '\0',
                                    new Node(1, 'b'),
                                    new Node(5, 'd')));
        Node* result = buildHuff(v);
        if(! areHuffmanTreesEqual(root, result))
        {
            cout << "fail test 5 \n";
            cout << "result     = ";printHuffmanTree(root);cout << "\n";
            cout << "output_you = ";printHuffmanTree(result);cout << "\n";
        }
        else cout << "pass test 5 \n";
    }


    //* test 6
    {
        vector<pair<char, int>> v = {{'e', 10},{'d',3}, {'c', 2}, {'b', 1}, {'a', 1}};
        Node* root = new Node(4, '\0',
                                new Node(7, '\0',
                                    new Node(3, 'd'),
                                    new Node(2, 'c')),
                                new Node(14, '\0',
                                    new Node(2, '\0',
                                        new Node(1, 'a'),
                                        new Node(1, 'b')),
                                    new Node(10, 'e')));
        Node* result = buildHuff(v);
        if(! areHuffmanTreesEqual(root, result))
        {
            cout << "fail test 6 \n";
            cout << "result     = ";printHuffmanTree(root);cout << "\n";
            cout << "output_you = ";printHuffmanTree(result);cout << "\n";
        }
        else cout << "pass test 6 \n";
    }

    // //* test 7
    {
        vector<pair<char, int>> v = {{'f', 20}, {'e', 10},{'d',3}, {'c', 2}, {'b', 1}, {'a', 1}};
        string output_you = huffmanTreeToString(buildHuff(v));
        string result = "[14]([4]([7]([3,d],[2,c]),[2]([1,a],[1,b])),[24]([10,e],[20,f]))";
        
        if(output_you != result)
        {
            cout << "fail test 7 \n";
            cout << "result     = " << result << endl;
            cout << "output_you = " << output_you << endl;
        }
        else cout << "pass test 7 \n";
    }

    // //* test 8
    {
        vector<pair<char, int>> v = {{'g', 20},{'f', 20}, {'e', 10},{'d',3}, {'c', 2}, {'b', 1}, {'a', 1}};
        string output_you = huffmanTreeToString(buildHuff(v));
        string result = "[14]([4]([7]([3,d],[2,c]),[2]([1,a],[1,b])),[34]([24]([10,e],[20,f]),[20,g]))";
        
        if(output_you != result)
        {
            cout << "fail test 8 \n";
            cout << "result     = " << result << endl;
            cout << "output_you = " << output_you << endl;
        }
        else cout << "pass test 8 \n";
    }


    // //* test 9
    {
        vector<pair<char, int>> v = {{'h', 21}, {'g', 20},{'f', 20}, {'e', 10},{'d',3}, {'c', 2}, {'b', 1}, {'a', 1}};
        string output_you = huffmanTreeToString(buildHuff(v));
        string result = "[14]([4]([7]([3,d],[2,c]),[2]([1,a],[1,b])),[34]([24]([10,e],[20,f]),[35]([20,g],[21,h])))";
        
        if(output_you != result)
        {
            cout << "fail test 9 \n";
            cout << "result     = " << result << endl;
            cout << "output_you = " << output_you << endl;
        }
        else cout << "pass test 9 \n";
    }
}

std::string huffmanTreeToString(const Node* tree) {
    std::stringstream ss;

    if (tree == nullptr) {
        return "";
    }

    if (tree->c) {
        ss << "[" << tree->weight << "," << tree->c << "]";
    } else {
        ss << "[" << tree->weight << "]";
    }

    if (tree->left != nullptr || tree->right != nullptr) {
        ss << "(";
        ss << huffmanTreeToString(tree->left);
        ss << ",";
        ss << huffmanTreeToString(tree->right);
        ss << ")";
    }

    return ss.str();
}


void printHuffmanTree(const Node* tree) {
    if (tree == nullptr) {
        return;
    }
    if(tree->c) std::cout << "[" << tree->weight << "," << tree->c << "]";
    else std::cout << "[" << tree->weight << "]";
    
    if (tree->left != nullptr || tree->right != nullptr) {
        std::cout << "(";
        printHuffmanTree(tree->left);
        std::cout << ",";
        printHuffmanTree(tree->right);
        std::cout << ")";
    }
}

bool areHuffmanTreesEqual(const Node* tree1, const Node* tree2) {
    // Nếu cả hai cây đều rỗng (nullptr), coi chúng là giống nhau
    if (tree1 == nullptr && tree2 == nullptr) {
        return true;
    }

    // Nếu chỉ một trong hai cây rỗng, coi chúng khác nhau
    if (tree1 == nullptr || tree2 == nullptr) {
        return false;
    }

    // So sánh giá trị và cấu trúc của hai nút
    return (tree1->weight == tree2->weight) &&
           (tree1->c == tree2->c) &&
           areHuffmanTreesEqual(tree1->left, tree2->left) &&
           areHuffmanTreesEqual(tree1->right, tree2->right);
}