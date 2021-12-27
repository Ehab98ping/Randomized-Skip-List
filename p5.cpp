#include <iostream>
using namespace std;
class SkipList
{
private:
    class Node
    {
    public:
        int key;
        Node* below = nullptr;
        Node* next = nullptr;
    };
    Node* head;
    int maxLevel;

    void Insert(Node*& node, int number, int level, int nodeLevel, Node*& inserted)
    {

        Node* temp = node;
        while (temp->next != nullptr && temp->next->key < number)
        {
            temp = temp->next;
        }
        if (level <= nodeLevel)
        {
            if (temp->next == nullptr)
            {
                temp->next = inserted;
                inserted->key = number;
                if (level == 0)
                {
                    return;
                }
                else
                {
                    inserted->below = new Node;
                    Insert(temp->below, number, level - 1, nodeLevel, inserted->below);
                }
            }
            else if(temp->next->key!=number)
            {
                Node* temp2 = temp->next;
                temp->next = inserted;
                inserted->key = number;
                inserted->next = temp2;
                if (level == 0)
                {
                    return;
                }
                else
                {
                    inserted->below = new Node;
                    Insert(temp->below, number, level - 1, nodeLevel, inserted->below);
                }
            }
        }
        else
        {
            Insert(temp->below, number, level - 1, nodeLevel, inserted);
        }
    }
    void Remove(Node*& node, int number, int level)
    {
        Node* temp = node;
        while (temp->next != nullptr && temp->next->key < number)
        {
            temp = temp->next;
        }
        if (temp->next == nullptr)
        {
            if (level == 0)
            {
                return;
            }
            else
            {
                Remove(temp->below, number, level - 1);
            }
        }
        else if (temp->next->key == number)
        {
            Node* toBeDeleted = temp->next;
            if (temp->next->next == nullptr)
            {
                temp->next = nullptr;
            }
            else
            {
                temp->next = temp->next->next;
            }
            delete toBeDeleted;
            if (level == 0)
            {
                return;
            }
            else
            {
                Remove(temp->below, number, level - 1);
            }
        }
        else
        {
            if (level == 0)
            {
                return;
            }
            else
            {
                Remove(temp->below, number, level - 1);
            }
        }
    }
    int Search(Node* node, int number, int level, int steps, bool& found)
    {
        Node* temp = node;
        while (temp->next != nullptr && temp->next->key < number)
        {
            temp = temp->next;
            steps += 1;
        }
        if (temp->next == nullptr)
        {
            if (level == 0)
                return -1;
            steps += Search(temp->below, number, level - 1, 0, found);
        }
        else if (temp->next->key == number)
        {
            found = true;
            return steps + 1;
        }
        else
        {
            if (level == 0)
                return -1;
            steps= Search(temp->below, number, level - 1, 0, found);
        }
        return steps;
    }
    int getRndLevel(int level = 0)
    {
        int rnd = rand() % 2 + 1;
        if (rnd == 1)
        {
            level += 1;
            if (level == maxLevel)
                return level;
            level = getRndLevel(level);
        }
        else
        {
            return level;
        }
    }

public:
    SkipList() { SkipList(1); }
    SkipList(int maxLevel) 
    {
        this->maxLevel = maxLevel;
        head = new Node;
        Node* temp = head;
        for (int i = 0; i < maxLevel; i++)
        {
            temp->below = new Node;
            temp = temp->below;
        }
    }
    void insert(int number)
    {
        Node* temp = head;
        Node* inserted = new Node;
        Insert(temp, number, maxLevel, getRndLevel(), inserted);
    }
    void remove(int number)
    {
        Node* temp = head;
        Remove(temp, number, maxLevel);
    }
    void search(int number)
    {
        Node* temp = head;
        bool found = false;
        int steps = Search(temp, number, maxLevel, 0, found);
        if (found == true)
            cout << steps << " step\n";
        else
            cout << "-1 \n";
    }
    void printLayer(int layer)
    {
        Node* temp = head;
        for (int i = 0; i < maxLevel - layer; i++)
        {
            temp = temp->below;
        }
        while (temp->next != nullptr)
        {
            cout << temp->next->key << " ";
            temp = temp->next;
        }
        cout << "\n";
    }
    
   
};


int main()
{
    SkipList skiplist(2);

    skiplist.insert(5);
    skiplist.insert(2);
    skiplist.insert(9);
    skiplist.insert(7);
    skiplist.insert(4);
    skiplist.insert(10);
    skiplist.insert(15);
    skiplist.insert(70);

    skiplist.search(2);
    skiplist.search(15);
    skiplist.search(3);
    skiplist.search(70);
    cout << "-----------------------------------------\n";
    skiplist.printLayer(0);
    skiplist.printLayer(1);
    skiplist.printLayer(2);

}
