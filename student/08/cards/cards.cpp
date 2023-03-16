#include "cards.hh"

// A dynamic structure must have a constructor
// that initializes the top item as nullptr.
Cards::Cards(): top_(nullptr){

}

// Get the topmost card for testing.
// Note: Usually allowing such access to the inner mechanisms ( through non-const pointer )
// of the class is against many programming principles. It is now too,
// but also required for complete tests.
Card_data* Cards::get_topmost(){
    return top_;
}

// Adds a new card with the given id as the topmost element.
void Cards::add(int id){
    Card_data* new_item = new Card_data{id, nullptr};

    if ( top_ == nullptr ) {
       top_ = new_item;
    } else {
       top_->next = new_item;
    }
}

// Prints the content of the data structure with ordinal numbers to the
// output stream given as a parameter starting from the first element.
void Cards::print_from_top_to_bottom(std::ostream& s){
    int i = 0;
    Card_data* current = top_;
    while (current != nullptr){
        s << i << ": " << current->data << std::endl;
        current = current->next;
        i++;
    }
}

// Removes the topmost card and passes it in the reference parameter id to the caller.
// Returns false, if the data structure is empty, otherwise returns true.
bool Cards::remove(int& id){
    if ( top_ == nullptr ) {
       return false;
    }

    Card_data* item_to_be_removed = top_;

    //removed_task = item_to_be_removed->next;

    if ( top_->next == nullptr ) {
       top_ = nullptr;
    } else {
       top_ = top_->next;
    }

    delete item_to_be_removed;

    return true;
}


// Moves the last element of the data structure as the first one.
// Returns false, if the data structure is empty, otherwise returns true.
bool Cards::bottom_to_top(){
    return true;
}

// Moves the first element of the data structure as the last one.
// Returns false, if the data structure is empty, otherwise returns true.
bool Cards::top_to_bottom(){
    return true;
}

// Prints the content of the data structure with ordinal numbers to the
// output stream given as a parameter starting from the last element.
void Cards::print_from_bottom_to_top(std::ostream& s){
}

Cards::~Cards(){
    Card_data* current = top_;
    while (current != nullptr){
        Card_data* next = current->next;
        delete current;
        current = next;
    }
}
