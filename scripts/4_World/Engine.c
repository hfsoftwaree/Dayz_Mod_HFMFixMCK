#ifdef SERVER
void HFM_LogVehicleEngine(Transport transport, PlayerBase player, string action)
{
    if (!transport || !player || !player.GetIdentity()) return;
    if (!CarScript.logFileName) return;

    int h, m, s;
    GetHourMinuteSecond(h, m, s);
    string time = h.ToStringLen(2) + ":" + m.ToStringLen(2) + ":" + s.ToStringLen(2) + " | ";

    vector pos = player.GetPosition();

    int mckId = MCK_Transport.GetTransportId(transport);
    if (mckId == -1) return; 

    string line = time + "Player " + player.GetIdentity().GetName() + " (" + pos + ") " + action + " vehicle " + transport.GetDisplayName() + " [" + transport.GetType() + "] (ID: " + mckId + ")";

    FileHandle file = OpenFile(CarScript.logFileName, FileMode.APPEND);
    if (file)
    {
        FPrintln(file, line);
        CloseFile(file);
    }
}
#endif


#ifdef SERVER
modded class ActionStartEngine
{
    override void OnEndServer(ActionData action_data)
    {
        super.OnEndServer(action_data);
        if (!action_data.m_Player) return;
		
        HumanCommandVehicle cmd = action_data.m_Player.GetCommand_Vehicle();
        if (!cmd) return;
        
		Transport transport = Transport.Cast(cmd.GetTransport());
        if (!transport) return;
        
		HFM_LogVehicleEngine(transport, action_data.m_Player, "started");
    }
};
#endif

#ifdef SERVER
modded class ActionStopEngine
{
    override void OnEndServer(ActionData action_data)
	{
		super.OnEndServer(action_data);
		if (!action_data.m_Player) return;

		HumanCommandVehicle cmd = action_data.m_Player.GetCommand_Vehicle();
		Transport transport;

		if (cmd)
		{
			transport = Transport.Cast(cmd.GetTransport());
		}

		if (!transport)
		{
			GetOutTransportActionData got = GetOutTransportActionData.Cast(action_data);
			if (got)
				transport = got.m_Vehicle;
		}

		if (!transport) return;

		HFM_LogVehicleEngine(transport, action_data.m_Player, "stopped");
	}

};
#endif

