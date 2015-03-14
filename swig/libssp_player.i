 %module libssp_player
 %{
 /* Includes the header in the wrapper code */
 #include "../player/ssp_public.h"
/*
#include "../player/ssp_structs.h"

extern int SSP_GetVersion();
extern int SSP_Init(const char* pathForPlugins);
extern int SSP_InitDevice(int device, int sampleRate, int bufferSize, int updatePeriod, bool useFloatingPoint);
extern int SSP_FreeDevice();
extern int SSP_Free();

extern int SSP_GetDevice(SSP_DEVICE* device);
*/
 %}
 
 /* Parse the header file to generate wrappers */
 %include "../player/ssp_public.h"

/*
#include "../player/ssp_structs.h"

extern int SSP_GetVersion();
extern int SSP_Init(const char* pathForPlugins);
extern int SSP_InitDevice(int device, int sampleRate, int bufferSize, int updatePeriod, bool useFloatingPoint);
extern int SSP_FreeDevice();
extern int SSP_Free();

extern int SSP_GetDevice(SSP_DEVICE* device);
*/