class CfgPatches
{
	class Codelock_Example_Scripts
	{
		requiredVersion=0.1;
		requiredAddons[]=
		{
			"DZ_Data",
			"CodeLock",
			"cfgpatches-name-of-mod"
		};
	};
};
class CfgMods
{
	class Codelock_Example
	{
		dir="Codelock-Example";
		hideName=1;
		hidePicture=1;
		name="Codelock-Example";
		author="TrueDolphin";
		authorID="0";
		version="0.1";
		extra=0;
		type="mod";
		dependencies[]=
		{
			"World"
		};
		class defs
		{
			class worldScriptModule
			{
				value="";
				files[]=
				{
					"CodeLock-Example/Scripts/4_World"
				};
			};
		};
	};
};