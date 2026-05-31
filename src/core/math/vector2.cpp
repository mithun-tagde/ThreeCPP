#include "../../include/threecpp/vector2.h"
#include <sstream>

namespace threecpp {

std::string Vector2::ToString() const {
    std::ostringstream oss;
    oss << "Vector2(" << x << ", " << y << ")";
    return oss.str();
}

} // namespace threecpp
