using System;
using org.sessionsapp.player;

namespace playersampleconsolecsharp
{
    class MainClass
    {
        public static void Main(string[] args)
        {
            Console.WriteLine("Hello World!");

            int version = SSP.SSP_GetVersion();
            int error = SSP.SSP_Init();
            if (error != SSP.SSP_OK)
            {
                Console.WriteLine("Error");
                return;
            }

            Console.WriteLine("Success");
        }
    }
}
