#ifdef SERVER
modded class MissionServer
{
    override void OnInit()
    {
        super.OnInit();
        HFM_InitVehicleLog();
    }
}
#endif

#ifdef SERVER
void HFM_InitVehicleLog()
{
    if (CarScript.logFileName) return; 

    int year, month, day, h, m, s;
    GetYearMonthDay(year, month, day);
    GetHourMinuteSecond(h, m, s);

    string dateTime = "_" + year.ToStringLen(4) + "-" + month.ToStringLen(2) + "-" + day.ToStringLen(2) + "_" + h.ToStringLen(2) + "-" + m.ToStringLen(2) + "-" + s.ToStringLen(2);

    CarScript.logFileName = "$profile:HFM_Vehicles_FixMck" + dateTime + ".log";

    FileHandle file = OpenFile(CarScript.logFileName, FileMode.WRITE);
    if (file)
    {
        FPrintln(file, "Log Created: " + dateTime);
        CloseFile(file);
    }

    Print("HFM: Vehicle log initialized -> " + CarScript.logFileName);
}
#endif

