modded class CarScript
{
    static string logFileName;

    override void EEInit()
    {
        super.EEInit();
        if (!GetGame().IsServer()) return;
        GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(LogVehicleWithMCKId, 500, false);
    }

    void LogVehicleWithMCKId()
    {
        Transport transport = Transport.Cast(this);
        if (!transport) return;

        int mckId = MCK_Transport.GetTransportId(transport);
        if (mckId == -1)
        {
            GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(LogVehicleWithMCKId, 500, false);
            return;
        }

        if (!logFileName)
        {
            int year, month, day, fHour, fMinute, fSecond;
            GetYearMonthDay(year, month, day);
            GetHourMinuteSecond(fHour, fMinute, fSecond);

            string sYear = year.ToStringLen(4);
            string sMonth = month.ToStringLen(2);
            string sDay = day.ToStringLen(2);
            string sHour = fHour.ToStringLen(2);
            string sMinute = fMinute.ToStringLen(2);
            string sSecond = fSecond.ToStringLen(2);

            string dateTime = "_" + sYear + "-" + sMonth + "-" + sDay + "_" + sHour + "-" + sMinute + "-" + sSecond;
            logFileName = "$profile:HFM_Vehicles_FixMck" + dateTime + ".log";

            FileHandle headerFile = OpenFile(logFileName, FileMode.WRITE);
            if (headerFile)
            {
                FPrintln(headerFile, "Log Created: " + dateTime);
                CloseFile(headerFile);
            }
        }

        int logHour, logMinute, logSecond;
        GetHourMinuteSecond(logHour, logMinute, logSecond);
        string time = logHour.ToStringLen(2) + ":" + logMinute.ToStringLen(2) + ":" + logSecond.ToStringLen(2) + " | ";

        vector pos = GetPosition();
		
		int remainingTime = MCK_Transport.GetRemainingTimeTilDespawn(this, 0, false);
		string remainingLifetime = SecondsToDays(remainingTime);

		string logLine = time + "Vehicle in map: " + GetDisplayName() + " [" + GetType() + "] " + "(ID: " + mckId + " - pos " + pos + ") "+ "initialized. Remaining lifetime: "	+ remainingLifetime;
		

        FileHandle file = OpenFile(logFileName, FileMode.APPEND);
        if (file)
        {
            FPrintln(file, logLine);
            CloseFile(file);
        }
    }
}
