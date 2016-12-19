#include "plugin.h"

#define MAX_SCAN_SIZE 0x1000

static duint cbStackContains(int argc, duint* argv, void* userdata)
{
    // Make sure the right amount of arguments was supplied
    if(argc < 2)
        return 0;

    // Get the 'csp' (address to start scanning from).
    auto csp = argv[0];
    duint size;
    auto base = DbgMemFindBaseAddr(csp, &size);
    
    // Make sure that the supplied address is in a valid memory range
    if(!base)
        return 0;

    // Read MAX_SCAN_SIZE bytes from the stack to scan
    duint data[MAX_SCAN_SIZE / sizeof(duint)];
    auto sizeLeft = size - (csp - base);
    auto readSize = sizeLeft >= sizeof(data) ? sizeof(data) : sizeLeft;
    DbgMemRead(csp, data, readSize);

    // Scan the bytes to see if it contains the requested value
    for(duint i = 0; i * sizeof(duint) < readSize; i++)
        if(data[i] == argv[1])
            return true;
    return false;
}

//Initialize your plugin data here.
bool pluginInit(PLUG_INITSTRUCT* initStruct)
{
    if(!_plugin_registerexprfunction(pluginHandle, "stack.contains", 2, cbStackContains, nullptr))
        _plugin_logputs("[" PLUGIN_NAME "] Error registering the stack.contains expression function!");
    return true; //Return false to cancel loading the plugin.
}

//Deinitialize your plugin data here (clearing menus optional).
bool pluginStop()
{
    return true;
}

//Do GUI/Menu related things here.
void pluginSetup()
{
}
