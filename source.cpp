#include <Windows.h>
#include <iostream>
#include <string>
#include <ostream>
#define messagelol(a) MessageBoxA(NULL,a,"hi lol",MB_OK);
//include this as your own header. SCANNER HEADER BELOW
//https://ghostbin.com/paste/ba5qt
//include this as your own header. ADDRESS HEADER BELOW
//https://ghostbin.com/paste/6wgkr

/*
This was written on Ghostbin directly, it was not tested, however, it should work.
Written by Pudding Mug
*/

//using namespace std;
using std::string;
bool aftercmd = false;

/*
Here is my custom created functions to make commands easier.
Now you'll notice for some I use LUA_GLOBALSINDEX and some I use -10002, don't get confused these are exactly the same.
You'll also notice I don't use getglobal anywhere here and that's because simply doing getfield(rs, -10002, "global"); would be the same.

NOTE: For some of my functions, they give you a choice for another route such as: game.Players.LocalPlayer.Character and one without Character. To use
this feature you'll have to have 1 as the 2nd arg. With that being said if you'd like to not have it just use 0 as the 2nd arg.
*/
void getService(string service)
{
	getfield(rstate, LUA_GLOBALSINDEX, "game");
	getfield(rstate, -1, "GetService");
	pushvalue(rstate, -2);
	pushstring(rstate, service.c_str());
	pcall2(rstate, 2, 1, 0);
}

void InstanceNew(int rs, const char* i) {
	getfield(rs, -10002, "Instance");
	getfield(rs, -1, "new");
	pushstring(rs, i);
	pushvalue(rs, -4);
	pcall2(rs, 2, 1, 0);
}

void getLocalPlayer(int rs, bool character) {
	getfield(rs, -10002, "game");
	getfield(rs, -1, "Players");
	getfield(rs, -1, "LocalPlayer");
	if (character)
		getfield(rs, -1, "Character");
}

void lightingmacro(int rs) {
	getfield(rs, -10002, "game");
	getfield(rstate, -1, "Lighting");
}

void NewLighting(string yes) {
	lightingmacro(rstate);
	InstanceNew(rstate, yes.c_str());
}

void CreateInstanceOnChar(string instance) {
	getLocalPlayer(rstate, 1);
	getfield(rstate, -1, "Torso");
	InstanceNew(rstate, instance.c_str());
}

void mousehit(int rs, bool p) {
	getfield(rs, -1, "GetMouse");
	pushvalue(rs, -2);
	pcall2(rs, 1, 1, 0);
	getfield(rs, -1, "Hit");
	if (p)
		getfield(rstate, -1, "p");
}

void InstanceNewParentWorkspace(int rs, const char* i) {
	getglobal(rstate, "game");
	getfield(rstate, -1, "Workspace");
	InstanceNew(rstate, i);
	pushvalue(rstate, -5);
}


void transpforbody(int rs, const char* i, int o) {
	getLocalPlayer(rs, 1);
	getfield(rs, -1, i); //getfield rstate -1 bodypart
	pushnumber(rs, o); //transp level 0
	setfield(rs, -2, "Transparency");
}

void btools(int rs, int i) {
	getLocalPlayer(rs, 0);
	getfield(rs, -1, "Backpack");
	InstanceNew(rs, "HopperBin");
	pushnumber(rs, i);
	setfield(rs, -2, "BinType");
}

void bodypart(int rs, string body) {
	getLocalPlayer(rstate, 1);
	getfield(rs, -1, body.c_str());
}

void outputwarn(int rs, string ya) {

	getfield(rs, -10002, "warn");
	pushstring(rs, ya.c_str());
	pcall2(rs, 1, 0, 0);
}

void outputprint(int rs, string ya) {

	getfield(rs, -10002, "print");
	pushstring(rs, ya.c_str());
	pcall2(rs, 1, 0, 0);
}

void parteffect(int rs, string input) {
	getfield(rs, -1, input.c_str);
	pushvalue(rs, -2);
	pcall2(rs, 1, 0, 0);
}

void fullbody(int rs, int val) {
	transpforbody(rs, "Torso", val);
	transpforbody(rs, "Left Leg", val);
	transpforbody(rs, "Right Leg", val);
	transpforbody(rs, "Left Arm", val);
	transpforbody(rs, "Right Arm", val);
	transpforbody(rs, "Head", val);
}


/*
Now this is where you can make your own commands using the functions I created for you earlier.
*/

void keyCheck() {
	do {
		if (GetAsyncKeyState(VK_F1)) { //Let's make a full body invis command.
			fullbody(rstate, 1); //The fullbody takes 2 arguments and that is the rstate and the value of transparency ranging from 0-1
		} //0 would be solid and 1 would be transparent
		aftercmd = true;
		Sleep(20);
		aftercmd = false;
		//without this, the command will forever loop due to GetASyncKeyState
		
		if (GetAsyncKeyState(VK_F2)) { //Now that we've made a command to make you invisible let's return the char back to visible.
			fullbody(rstate, 0); //Using the logic I've given to you, you could make a ghost command which I'll setup the keybind but you can write the actual command.
		}
		aftercmd = true;
		Sleep(20);
		aftercmd = false;
		if (GetAsyncKeyState(VK_F3)) { 

		}
	} while (true); // have to add a while part to the do-while statement or else it won't compile
}



void Main() {
	int ScriptContext = ScanForScriptContext((char*)&aScriptContext);
	rstate = Getrstate(ScriptContext);
	messagelol("hi whats up");
	keyCheck();

}



bool __stdcall DllMain(HINSTANCE hDll, DWORD dwReason, PVOID pvReserved)
{
	if (dwReason == DLL_PROCESS_ATTACH) {
		DisableThreadLibraryCalls(hDll);
		CreateThread(0, 0, (LPTHREAD_START_ROUTINE)Main, 0, 0, 0);
	}
	return TRUE;
}
