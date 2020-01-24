//
// Created by bryce on 1/22/20.
//

#include "scripting.h"
#include "noctis-d.h"
#include <string>
#include <exception>
#include "angelscript_addons/scriptstdstring/scriptstdstring.h"

namespace as {
const char * SCRIPT_DIR = "./res/scripts";

std::string script_output;

asIScriptEngine *engine;

void engine_callback(const asSMessageInfo *msg, void *param) {
    const char *type = "ERR ";
    if (msg->type == asMSGTYPE_WARNING) {
        type = "WARN";
    } else if (msg->type == asMSGTYPE_INFORMATION) {
        type = "INFO";
    }

    printf("%s (%d, %d) : %s : %s\n", msg->section, msg->row, msg->col, type,
           msg->message);
}

void init() {
    // TODO: Check if already created
    engine = asCreateScriptEngine();

    int r = as::engine->SetMessageCallback(asFUNCTION(engine_callback), 0,
                                           asCALL_CDECL);

    assert(r >= 0);

    // Set engine to use character literals
    engine->SetEngineProperty(asEP_USE_CHARACTER_LITERALS, true);
}

// Global functions to be available within scripts
namespace sfunctions {

//Bypasses GOESNet screen and prints directly to the console
void console_print(const std::string &str) {
    printf("%s", str.c_str());

}

void print(const std::string &str) {
    script_output += str;
}
}

template<class T>
void register_function(const char *script_func_sig, T (*func_ptr)) {
    int r = engine->RegisterGlobalFunction(script_func_sig, asFUNCTION(func_ptr), asCALL_CDECL);
    assert(r >= 0); //TODO: This probably isn't a good idea, might remove it
}

void register_functions() {
    // AngelScript StdString Add-On
    RegisterStdString(engine);

    printf("Loading console_print...");
    fflush(stdout);
    register_function("void realprint(const string str)", sfunctions::console_print);
    printf("Done\nLoading print...");
    fflush(stdout);
    register_function("void print(const string str)", sfunctions::print);
    printf("Done\n");
}

// If the script wasn't already loaded into memory, it should be now.
void load_script(const char * name) {
    printf("== SCRIPT LOADING DEBUG ==\n");

    printf("Forming filename...");
    fflush(stdout);
    std::string filename = "res/scripts/" + std::string(name) + ".as";
    printf("Done\n");
    printf("Filename: %s\n", filename.c_str());

    printf("Creating module...");
    fflush(stdout);
    asIScriptModule *module = engine->GetModule(name, asGM_ALWAYS_CREATE);
    printf("Done\n");

    printf("Running  fopen...");
    fflush(stdout);
    FILE *file = fopen(filename.c_str(), "r");
    printf("Done\n");

    std::string scriptsrc;
    char buffer[80];

    if (file == nullptr) {
        if (errno == ENOENT) {
            // File does not exist
            // TODO: OUTPUT ERROR to GOES Net Screen properly
            script_output = "(UNKNOWN MODULE)";
            printf("Script was not found\n");
            // TODO: Create exception
            //throw new ScriptFileNotFoundException();
            printf("==========================\n");
            throw std::exception();
        }

        // TODO: Well, shit idk what to do if we get here
    }

    printf("Reading script into buffer...");
    fflush(stdout);
    // TODO: Error checking
    int nread;
    while ((nread = fread(&buffer, sizeof(char), 80, file)) > 0) {
        scriptsrc.append(buffer, nread);
    }
    printf("Done\n");

    fclose(file);

    printf("Adding section to module...");
    fflush(stdout);
    module->AddScriptSection(filename.c_str(), scriptsrc.c_str());
    printf("Done\n");

    module->Build();

    printf("==========================\n");
}

// Creates a context for the module with the main() function prepared.
asIScriptContext* get_main_context(asIScriptModule *module) {
    asIScriptFunction *main_function = module->GetFunctionByDecl("void main()");

    if (main_function == nullptr) {
        printf("Script is missing main()");
        throw std::exception();
    }

    asIScriptContext *context = engine->CreateContext();
    context->Prepare(main_function);

    return context;
}

/*namespace classes {

class string : public asIStringFactory {
    std::string s;

  public:
    const void* GetStringConstant(const char *data, asUINT length) override;
    int GetRawStringData(const void *str, char *data, asUINT length) const;
    int ReleaseStringConstant(const void *str) override;
};

int string::GetRawStringData(const void *str, char *data, asUINT length) const {
    return 0;
}

const void* string::GetStringConstant(const char *data, asUINT length) {
    return this;
}

int string::ReleaseStringConstant(const void *str) { return 0; }

}*/

}