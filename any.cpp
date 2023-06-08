#include "any.h"

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
