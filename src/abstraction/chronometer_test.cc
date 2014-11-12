// EPOS Chronometer Abstraction Test Program

#include <utility/ostream_kernel.h>
#include <chronometer.h>
#include <alarm.h>

using namespace EPOS_Kernel;

int main()
{
    OStream cout;

    cout << "Chronometer test" << endl;

    Chronometer timepiece;

    cout << "Chronometer start." << endl;
    timepiece.start();
    Alarm::delay(1500000);
    timepiece.stop();
    cout << "Chronometer stop." << endl;

    cout << "\nElapsed time = " << timepiece.read() << " us" << endl;

    return 0;
}
