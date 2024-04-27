#pragma once
#include <list>
#include <string>
#include <utility>

namespace CircularBufferSpace{
    typedef char value_type;
    class CircularBuffer final {
    private:
        value_type* buffer_;
        int head_{};
        int tail_{};
        int capacity_{};
        int size_{};
        void copy_buffer(const CircularBuffer& cb){
            for(int i = 0; i < cb.size_; i++) {
                buffer_[i] = cb.buffer_[i];
            }
        }
    public:
        CircularBuffer() : buffer_(nullptr), head_(0), tail_(0), capacity_(0), size_(0) {};
        ~CircularBuffer();
        CircularBuffer(const CircularBuffer& cb);

        explicit CircularBuffer(int capacity);
        CircularBuffer(int capacity, const value_type& elem);

        value_type& operator[](int i);
        const value_type& operator[](int i) const;

        value_type& at(int i);
        [[nodiscard]] const value_type& at(int i) const;

        value_type& front();
        value_type& back();
        [[nodiscard]] const value_type& front() const;
        [[nodiscard]] const value_type& back() const;

        value_type* linearize();
        [[nodiscard]] bool is_linearized() const;
        void rotate(int new_begin);
        [[nodiscard]] int size() const;
        [[nodiscard]] bool empty() const;
        [[nodiscard]] bool full() const;
        [[nodiscard]] int reserve() const;
        [[nodiscard]] int capacity() const;

        void set_capacity(int new_capacity);
        void resize(int new_size, const value_type& item = value_type());
        CircularBuffer& operator=(const CircularBuffer& cb) ;
        void swap(CircularBuffer& cb);

        void push_back(const value_type& item = value_type());
        void push_front(const value_type& item = value_type());
        void pop_back();
        void pop_front();

        void insert(int pos, const value_type & item = value_type());
        void erase(int first, int last);
        void clear();
    };

    bool operator==(const CircularBuffer& a, const CircularBuffer& b);

    bool operator!=(const CircularBuffer& a, const CircularBuffer& b);

    class CircularBufferError: public std::exception {
    public:
        explicit CircularBufferError(std::string  message): message{std::move(message)} {}
        [[nodiscard]] const char* what() const noexcept override {
            return message.c_str();
        }
    private:
        std::string message;
    };
}
