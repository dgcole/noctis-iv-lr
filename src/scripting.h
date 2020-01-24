//
// Created by bryce on 1/22/20.
//

#ifndef NIVLR_SCRIPTING_H
#define NIVLR_SCRIPTING_H

#include <angelscript.h>
#include <list>
#include <string>

namespace as {
    // Location of AngelScript .as files
    extern const char * SCRIPT_DIR;

    extern std::string script_output;

    extern asIScriptEngine *engine;
    extern std::list<asIScriptModule *> modules;

    extern void init();
    extern void register_functions();
    extern void load_script(const char *);
    extern asIScriptContext* get_main_context(asIScriptModule *);
}

#endif // NIVLR_SCRIPTING_H
