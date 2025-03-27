#include <bits/stdc++.h>
using namespace std;

struct Column;
struct Cell {
    Column *prev, *next;
};

struct Column {
    int value;
    vector<Cell> cells;
};

struct Skiplists {
    static const int Max_Level = 20;
    Column *head, *tail;
    Skiplists();
    bool Empty();
    Column *lower_bound(int);
    Column *upper_bound(int);
    void insert(int);
    void erase(int);
    void print();
};

Skiplists::Skiplists() {
    head = new Column;
    tail = new Column;
    head->value = INT_MIN;
    tail->value = INT_MAX;
    for (int i = 0; i < Max_Level; i++) {
        head->cells.push_back({nullptr, tail});
        tail->cells.push_back({head, nullptr});
    }
}

bool Skiplists::Empty() {
    return head->cells[0].next == tail;
}

Column *Skiplists::lower_bound(int value) {
    Column *iter = head;
    for (int level = Max_Level - 1; level >= 0; level--) {
        while (iter->cells[level].next != tail && iter->cells[level].next->value < value) {
            iter = iter->cells[level].next;
        }
    }
    return iter->cells[0].next;
}

Column *Skiplists::upper_bound(int value) {
    Column *iter = head;
    for (int level = Max_Level - 1; level >= 0; level--) {
        while (iter->cells[level].next != tail && iter->cells[level].next->value <= value) {
            iter = iter->cells[level].next;
        }
    }
    return iter->cells[0].next;
}

void Skiplists::insert(int value) {
    // Kiểm tra value đã tồn tại chưa
    Column *temp = lower_bound(value);
    if(temp != tail && temp->value == value) {
        return;
    }
    // Tạo inserted_column là cột chứa value để chèn vào SkipLists
    Column *inserted_column = new Column;
    inserted_column->value = value;
    inserted_column->cells.push_back((Cell){NULL, NULL});
    // Tung đồng xu tăng chiều cao
    while(inserted_column->cells.size() < Max_Level && rand() % 2 == 0) {
        inserted_column->cells.push_back((Cell){NULL, NULL});
    }
    // Duyệt để chèn
    Column *iter = head;
    for(int level = Max_Level - 1; level >= 0; level--) {
        while(iter->cells[level].next != tail && iter->cells[level].next->value < value) {
            iter = iter->cells[level].next;
        }
        if(level < inserted_column->cells.size()) {
            // Nối iter với inserted_column, nối inserted_column với next_iter
            Column *next_iter = iter->cells[level].next;
            iter->cells[level].next = inserted_column;
            next_iter->cells[level].prev = inserted_column;
            inserted_column->cells[level].prev = iter;
            inserted_column->cells[level].next = next_iter;
        }
    }
}

void Skiplists::erase(int value) {
    // Kiểm tra value đã tồn tại chưa
    Column *erased_column = lower_bound(value);
    if(erased_column == tail || erased_column->value != value) {
        return;
    }
    // Duyệt để xóa
    Column *iter = head;
    for(int level = Max_Level - 1; level >= 0; level--) {
        while(iter->cells[level].next != tail && iter->cells[level].next->value <= value) {
            iter = iter->cells[level].next;
        }
        if(iter == erased_column) {
            // Nối previous_iter với next_iter
            Column *previous_iter = iter->cells[level].prev, *next_iter = iter->cells[level].next;
            previous_iter->cells[level].next = next_iter;
            next_iter->cells[level].prev = previous_iter;
        }
    }
    delete erased_column;
}

void Skiplists::print() {
    Column *iter = head->cells[0].next;
    while (iter != tail) {
        cout << iter->value << " ";
        iter = iter->cells[0].next;
    }
    cout << endl;
}

int main() {
    srand(time(0));
    Skiplists sk;
    vector<int> values = {10, 20, 30, 40, 50, 60};
    
    cout << "Inserting values: ";
    for (int v : values) {
        sk.insert(v);
        cout << v << " ";
    }
    cout << "\nSkipList after insertions: ";
    sk.print();
    
    cout << "Erasing value 30\n";
    sk.erase(30);
    cout << "SkipList after deletion: ";
    sk.print();
    
    cout << "Finding lower_bound(25): " << sk.lower_bound(25)->value << endl;
    cout << "Finding upper_bound(40): " << sk.upper_bound(40)->value << endl;
    
    return 0;
}
