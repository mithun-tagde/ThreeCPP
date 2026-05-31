#include "../../include/threecpp/vector3.h"
#include <sstream>

namespace threecpp {

std::string Vector3::ToString() const {
    std::ostringstream oss;
    oss << "Vector3(" << x << ", " << y << ", " << z << ")";
    return oss.str();
}

} // namespace threecpp
