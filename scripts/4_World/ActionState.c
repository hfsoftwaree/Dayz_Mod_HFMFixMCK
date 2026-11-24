#ifdef SERVER

void HFM_LogLine(string line)
{
    if (!CarScript.logFileName) return;
    FileHandle file = OpenFile(CarScript.logFileName, FileMode.APPEND);
    if (file) { FPrintln(file, line); CloseFile(file); }
}

string HFM_GetTime()
{
    int h, m, s;
    GetHourMinuteSecond(h, m, s);
    return h.ToStringLen(2) + ":" + m.ToStringLen(2) + ":" + s.ToStringLen(2) + " | ";
}

string HFM_GetSeatName(Transport transport, int componentIndex)
{
    int crew = transport.CrewPositionIndex(componentIndex);
    if (crew == 0) return "Driver seat";
    if (crew == 1) return "CoDriver seat";
    if (crew == 2) return "Passenger Left seat";
    if (crew == 3) return "Passenger Right seat";
    return "Unknown seat";
}

modded class ActionGetInTransport: ActionBase
{
    override void OnEndServer(ActionData action_data)
    {
        super.OnEndServer(action_data);

        if (!action_data.m_Player || !action_data.m_Player.GetIdentity()) return;

        HumanCommandVehicle cmd = action_data.m_Player.GetCommand_Vehicle();
        if (!cmd) return;

        Transport transport = Transport.Cast(cmd.GetTransport());
        if (!transport) return;

        string time = HFM_GetTime();
        string player = action_data.m_Player.GetIdentity().GetName();
        string seat = HFM_GetSeatName(transport, action_data.m_Target.GetComponentIndex());

		int mckId = MCK_Transport.GetTransportId(transport);
		if (mckId == -1) return;

		string line = time + "Player " + player + " (" + action_data.m_Player.GetPosition() + ") entered in vehicle " + transport.GetDisplayName() + " [" + transport.GetType() + "] (ID: " + mckId + ") on " + seat;

        HFM_LogLine(line);
    }
}

modded class ActionGetOutTransport
{
    override void OnEndServer(ActionData action_data)
    {
        super.OnEndServer(action_data);

        if (!action_data.m_Player || !action_data.m_Player.GetIdentity()) return;

        GetOutTransportActionData got = GetOutTransportActionData.Cast(action_data);
        if (!got) return;

        Transport transport = got.m_Vehicle;
        if (!transport) return;

        string time = HFM_GetTime();
        string player = action_data.m_Player.GetIdentity().GetName();

		int mckId = MCK_Transport.GetTransportId(transport);
		if (mckId == -1) return;

		string line = time + "Player " + player + " (" + action_data.m_Player.GetPosition() + ") exited vehicle " + transport.GetDisplayName() + " [" + transport.GetType() + "] (ID: " + mckId + ")";

        HFM_LogLine(line);
    }
}

#endif

#ifdef SERVER
void HFM_LogVehicleLifecycle(Transport transport, string message)
{
    if (!transport) return;
    if (!CarScript.logFileName) return;

    int h, m, s;
    GetHourMinuteSecond(h, m, s);

    string time = h.ToStringLen(2) + ":" + m.ToStringLen(2) + ":" + s.ToStringLen(2) + " | ";

    vector pos = transport.GetPosition();

	int mckId = MCK_Transport.GetTransportId(transport);
	if (mckId == -1) return;

	string line = time + transport.GetDisplayName() + " [" + transport.GetType() + "] (ID: " + mckId + " - pos " + pos + ") " + message;

    FileHandle file = OpenFile(CarScript.logFileName, FileMode.APPEND);
    if (file)
    {
        FPrintln(file, line);
        CloseFile(file);
    }
}
#endif

#ifdef SERVER
modded class CarScript
{
    bool HFM_DestroyLogged = false;

    override void EEHitBy(TotalDamageResult damageResult, int damageType, EntityAI source, int component, string dmgZone, string ammo, vector modelPos, float speedCoef)
    {
        super.EEHitBy(damageResult, damageType, source, component, dmgZone, ammo, modelPos, speedCoef);

        if (HFM_DestroyLogged) return;
        if (GetHealth("", "") > 0) return;

        HFM_DestroyLogged = true;

        string killerName = "UNKNOWN";
		string weaponName = "UNKNOWN";

		EntityAI entity = EntityAI.Cast(source);
		if (entity)
		{
			PlayerBase killerPlayer = PlayerBase.Cast(entity.GetHierarchyRootPlayer());
			if (killerPlayer && killerPlayer.GetIdentity())
			{
				killerName = killerPlayer.GetIdentity().GetName();

				EntityAI weapon = killerPlayer.GetHumanInventory().GetEntityInHands();
				if (weapon)
				{
					weaponName = weapon.GetType();
				}
			}
		}

		HFM_LogVehicleLifecycle(this, "has been destroyed by: " + killerName + " using " + weaponName);

    }
}
#endif

#ifdef SERVER
modded class CarScript
{
    override void EEDelete(EntityAI parent)
    {
        super.EEDelete(parent);

        HFM_LogVehicleLifecycle(this, "is being deleted. This log doesn't mean that the mod deleted it.");

        if (GetLifetime() <= 0)
        {
            HFM_LogVehicleLifecycle(this, "Remaining DB lifetime: " + GetLifetime());
        }
    }
}
#endif

#ifdef SERVER
modded class ActionPushObject: ActionBase
{
    override void OnEndServer(ActionData action_data)
    {
        super.OnEndServer(action_data);

        if (!action_data.m_Player || !action_data.m_Player.GetIdentity()) return;

        ActionPushObjectData data = ActionPushObjectData.Cast(action_data);
        Transport transport = Transport.Cast(data.m_Object);
        if (!transport) return;

        int mckId = MCK_Transport.GetTransportId(transport);
        if (mckId == -1) return;

        string time = HFM_GetTime();
        string playerName = action_data.m_Player.GetIdentity().GetName();
        vector playerPos = action_data.m_Player.GetPosition();

        string line = time + "Player " + playerName + " (" + playerPos + ") pushed vehicle " + transport.GetDisplayName() + " [" + transport.GetType() + "] (ID: " + mckId + ")";

        HFM_LogLine(line);
    }
}
#endif








