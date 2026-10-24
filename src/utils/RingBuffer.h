
#pragma once

#include<stddef.h>
#include<stdint.h>

namespace vending {
    
    template<size_t Capacity>
    class RingBuffer {
        public:

            bool push(uint8_t value) {
                if (isFull()){
                    return false;
                }

                buffer_[head_] = value;
                head_ = next(head_);
                ++size_;
                return true;
            }

            bool pop(uint8_t& value) {
                if (isEmpty()){
                    return false;
                }

                value = buffer_[tail_];
                tail_ = next(tail_);
                --size_;
                return true;
            }

            /* define the methods for getting implementation */
            size_t size() const { return size_;}
            bool isEmpty() const { return size_ == 0; }
            bool isFull() const { return size_ == Capacity; }

            void clear(){
                head_ = 0;
                tail_ = 0;
                size_ = 0;
            }
            
        private:
            static constexpr size_t next(size_t index){
                return (index + 1) & Capacity;
            }

            uint8_t buffer_[Capacity]{};
            size_t head_ = 0;
            size_t tail_ = 0;
            size_t size_ = 0;
    };
} // namespace vending
