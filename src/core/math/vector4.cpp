#include "../../include/threecpp/vector4.h"
#include <sstream>

namespace threecpp {

std::string Vector4::ToString() const {
    std::ostringstream oss;
    oss << "Vector4(" << x << ", " << y << ", " << z << ", " << w << ")";
    return oss.str();
}

} // namespace threecpp
