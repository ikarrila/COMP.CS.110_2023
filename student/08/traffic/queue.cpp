#include "queue.hh"
#include <string>
#include <iostream>

using namespace std;

Queue::Queue(unsigned int cycle): cycle_(cycle) {
}

Queue::~Queue() {
   while ( first_ != nullptr ) {
      Vehicle* item_to_be_released = first_;
      first_ = first_->next;

      delete item_to_be_released;
   }
}

void Queue::enqueue(string const& reg) {
    if (!is_green_) {
        Vehicle* new_vehicle = new Vehicle{reg, nullptr};
        if (first_) {
            last_->next = new_vehicle;
            last_ = new_vehicle;
        } else {
            first_ = new_vehicle;
            last_ = new_vehicle;
        }
    } else {
        std::cout << "GREEN: The vehicle " << reg << " need not stop to wait" << std::endl;
    }
}

void Queue::switch_light() {
    //IF RED
    if(is_green_ == false){
        if (first_ != nullptr){
            std::cout << "GREEN: Vehicle(s) ";
            for (unsigned int i = 0; i < cycle_; ++i) {
                if (first_) {
                    Vehicle* to_delete = first_;
                    first_ = first_->next;
                    std::cout << to_delete->reg_num << " ";
                    delete to_delete;
                } else {
                    break;
                }
            }
            std::cout << "can go on" << std::endl;
            is_green_ = false;
        } else {
            std::cout << "GREEN: No vehicles waiting in traffic lights" << std::endl;
            is_green_ = true;
        }
    //IF GREEN
    } else {
        if (first_ != nullptr){
            std::cout << (is_green_ ? "GREEN: " : "RED: ") << "Vehicle(s)";
            for (Vehicle* vehicle = first_; vehicle; vehicle = vehicle->next) {
                std::cout << vehicle->reg_num << " ";
            }
            cout << "waiting in traffic lights" << endl;
        } else {
            is_green_ = false;
            std::cout << "RED: No vehicles waiting in traffic lights" << std::endl;
        }
    }
    }

void Queue::reset_cycle(unsigned int cycle) {
    cycle_ = cycle;
}

void Queue::print() const{
    if (first_ == nullptr){
        std::cout << (is_green_ ? "GREEN: " : "RED: ") << "No vehicles waiting in traffic lights" << endl;
    } else {
        std::cout << (is_green_ ? "GREEN: " : "RED: ") << "Vehicle(s) ";
        for (Vehicle* vehicle = first_; vehicle; vehicle = vehicle->next) {
                         cout << vehicle->reg_num << " ";
        }
    cout << "waiting in traffic lights" << endl;
    }
}
