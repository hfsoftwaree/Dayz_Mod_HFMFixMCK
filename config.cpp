class CfgPatches
{
    class CarScript
    {
        units[] = {};
        weapons[] = {};
        requiredVersion = 0.1;
        requiredAddons[] = {"DZ_Scripts"};
    };
};

class CfgMods
{
    class CarScript
    {
        dir="HFMFixMck";
        picture="";
        action="";
        hideName=0;
        hidePicture=1;
        name="HFMFixMck";
        credits="HF";
        author="HF";
        authorID="0";
        version="1.0";
        extra=0;
        type="mod";
        dependencies[]=
        {
            "World", "Mission"
        };
        class defs
        {      			
			class worldScriptModule
            {
                value="";
                files[]=
                {
                    "HFMFixMck/scripts/4_World"
                };
            };
			
			class missionScriptModule
            {
                value="";
                files[]=
                {
                    "HFMFixMck/scripts/5_Mission"
                };
            };
        };
    };
};
