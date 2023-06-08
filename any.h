#pragma once
#include <stdexcept>
#include <typeinfo>

class Any {
private:
public:
    Any() : storage_(nullptr) {
    }

    template <class T>
    explicit Any(const T& value) : storage_(new Derived(value)) {
    }

    void Swap(Any& rhs);

    template <class T>
    Any& operator=(const T& value) {
        delete storage_;
        storage_ = new Derived<T>(value);
        return *this;
    }

    Any(const Any& rhs) : storage_(rhs.storage_->GetCopy()) {
    }

    Any& operator=(Any rhs);

    ~Any();

    bool Empty() const;

    void Clear() {
        delete storage_;
        storage_ = nullptr;
    }

    template <class T>
    const T& GetValue() const {
        if (!storage_ || storage_->Type() != typeid(T)) {
            throw std::bad_cast();
        }
        return static_cast<Derived<T>*>(storage_)->value_;
    }

private:
    struct Base {
        virtual Base* GetCopy() = 0;
        virtual const std::type_info& Type() const = 0;
        virtual ~Base() {
        }
    };
    template <typename T>
    struct Derived : public Base {
        T value_;
        explicit Derived(const T& value) : value_(value) {
        }
        Base* GetCopy() override {
            return new Derived<T>(value_);
        }
        const std::type_info& Type() const override {
            return typeid(T);
        }
    };
    Base* storage_;
};
