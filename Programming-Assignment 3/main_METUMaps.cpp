#include "METUMaps.h"
#include <iostream>
class PA3_MAPS_TEST_CASE
{
    public:
        void operator()() const;
};

void PA3_MAPS_TEST_CASE::operator()() const
{
    METUMaps maps(2, "metu_campus.map");

    // Set Proper Locations
    maps.SetStartingLocation("A7_Gate");
    maps.SetDestination("A4_Gate");
    maps.StartJourney();
    std::cout << "================" << std::endl;
    maps.Display();
    std::cout << "================" << std::endl;
    maps.UpdateLocation("Teknokent");
    std::cout << "================" << std::endl;
    maps.Display();
    std::cout << "================" << std::endl;
    maps.UpdateLocation("Tekno_A8");
    maps.UpdateLocation("FL");
    maps.UpdateLocation("FL_I");
    maps.UpdateLocation("Lib_I");
    std::cout << "================" << std::endl;
    maps.Display();
    std::cout << "================" << std::endl;
    maps.UpdateLocation("C_Statue");
    maps.UpdateLocation("A4_Gate");
    maps.EndJourney();
}

int main()
{
    /* METUMaps maps(2, "metu_campus.map");

    // Set Proper Locations
    maps.SetStartingLocation("Ceng");
    maps.SetDestination("Library");
    maps.StartJourney();
    std::cout << "================" << std::endl;
    maps.Display();
    std::cout << "================" << std::endl;
    maps.UpdateLocation("EE");
    std::cout << "================" << std::endl;
    maps.Display();
    std::cout << "================" << std::endl;
    maps.UpdateLocation("Library");
    maps.EndJourney();

    // ======================== //
    // OUTPUT OF THE CODE ABOVE //
    // ======================== //
    // Calculating Route(s) between "Ceng" and "Library"...
    // ================
    // Journey         : Ceng->Library
    // Current Location: Ceng
    // Time Left       : 7 minutes
    // Current Route   : Ceng--5->EE--2->Library
    // ================
    // Route between "EE" and "Library" is in cache, using that...
    // ================
    // Journey         : Ceng->Library
    // Current Location: EE
    // Time Left       : 2 minutes
    // Current Route   : EE--2->Library
    // ================
    // Journey Completed! */
    
    PA3_MAPS_TEST_CASE tc;
    tc();

}
