#include "any.h"

Any::Any() : storage_(nullptr) {
}

Any::Any(const Any& rhs) : storage_(rhs.storage_->GetCopy()) {
}

void Any::Swap(Any& rhs) {
    Base* tmp = storage_;
    storage_ = rhs.storage_;  // NOLINT
    rhs.storage_ = tmp;
}

Any& Any::operator=(Any rhs) {
    Swap(rhs);
    return *this;
}

bool Any::Empty() const {
    return !storage_;
}

Any::~Any() {
    Clear();
}
void Any::Clear() {
    delete storage_;
    storage_ = nullptr;
}
