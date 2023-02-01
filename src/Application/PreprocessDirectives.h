#pragma once

#define BUILD_EDITOR // <-- Remove to disable editors

#ifdef BUILD_EDITOR
    #define EDITOR_ENABLED
#else
    #define EDITOR_DISABLED
#endif
