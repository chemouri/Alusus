/**
 * @file Core/core.h
 * The main header file of the core. Contains include statements for the entire
 * core.
 *
 * @copyright Copyright (C) 2019 Sarmad Khalid Abdullah
 *
 * @license This file is released under Alusus Public License, Version 1.0.
 * For details on usage and copying conditions read the full license in the
 * accompanying license file or at <https://alusus.org/alusus_license_1_0>.
 */
//==============================================================================

// System header files
#include <memory>
#include <array>
#include <vector>
#include <list>
#include <utility>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cassert>
#include <exception>
#include <string.h>
#include <type_traits>
#include <atomic>
#include <functional>

// Include global storage functions.
#include "core_global_storage.h"

namespace Core
{

/**
 * @defgroup core Core
 */

}

// "realpath" wrapper for MinGW
#if defined(__MINGW32__) || defined(__MINGW64__)
    #ifndef PATH_MAX
    #define PATH_MAX _MAX_PATH
    #endif
    #define realpath(N,R) _fullpath((R),(N),_MAX_PATH)
#endif

// Alusus's core base header files

#include "Basic/basic.h"
// Since basic datatypes should be available everywhere, we'll just open up the namespace.
using namespace Core::Basic;

#include "Data/data.h"
#include "Notices/notices.h"
#include "Processing/processing.h"
#include "Main/main.h"
