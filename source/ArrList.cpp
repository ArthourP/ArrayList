#include "../SDK/plugin.h"

#include <vector>
#include <map>

typedef void
(*logprintf_t)(char* format, ...)
;

logprintf_t
logprintf
; 

void
**ppPluginData
;

extern void
*pAMXFunctions
;

#include "Internal.h"

PLUGIN_EXPORT bool PLUGIN_CALL Load(void **ppData)
{
	pAMXFunctions = ppData[PLUGIN_DATA_AMX_EXPORTS];
	logprintf = (logprintf_t)ppData[PLUGIN_DATA_LOGPRINTF];
	logprintf("ArrayList plugin loaded - Jelly23"); 
	return 1;
}

PLUGIN_EXPORT void PLUGIN_CALL Unload()
{
	logprintf("ArrayList plugin Un-Loaded - Jelly23");
}

cell AMX_NATIVE_CALL CreateArrayList(AMX* amx, cell* params)
{
	ArrLists[amx].push_back(jLists());
	ArrLists[amx][ArrLists[amx].size() - 1].ListItems.reserve(params[1]);

	return ArrLists[amx].size() - 1;
}

cell AMX_NATIVE_CALL ClearArrayList(AMX* amx, cell* params){

	if (internal_is_valid_list(amx, params[1]) == 0)
	{
		return INVALID_LIST_ID;
	}
	ArrLists[amx][params[1]].Clear();
	return 1;
}

cell AMX_NATIVE_CALL IsValidArrayList(AMX* amx, cell* params)
{
	return internal_is_valid_list(amx, params[1]);
}

cell AMX_NATIVE_CALL GetArrayListCapacity(AMX* amx, cell* params)
{
	if (internal_is_valid_list(amx, params[1]) == 0)
	{
		return INVALID_LIST_ID;
	}
	return ArrLists[amx][params[1]].ListItems.capacity();
}

cell AMX_NATIVE_CALL SetArrayListCapacity(AMX* amx, cell* params)
{
	if (internal_is_valid_list(amx, params[1]) == 0)
	{
		return INVALID_LIST_ID;
	}
	ArrLists[amx][params[1]].ListItems.reserve(params[2]);
	return 1;

}

cell AMX_NATIVE_CALL GetArrayListSize(AMX* amx, cell* params)
{
	if (internal_is_valid_list(amx, params[1]) == 0)
	{
		return INVALID_LIST_ID;
	}
	return ArrLists[amx][params[1]].ListItems.size();
}

cell AMX_NATIVE_CALL ArrayListAdd(AMX* amx, cell* params){

	if (internal_is_valid_list(amx, params[1]) == 0)
	{
		return INVALID_LIST_ID;
	}
	Lists add;

	add.value = params[2];
	add.type = params[3];

	ArrLists[amx][params[1]].PutValue(add);
	return 1;
}

cell AMX_NATIVE_CALL ArrayListRemove(AMX* amx, cell* params){

	if (internal_is_valid_list(amx, params[1]) == 0 || internal_is_valid_item(amx, params[1], params[2]) == 0)
	{
		return INVALID_LIST_ID;
	}

	ArrLists[amx][params[1]].ListItems.erase(ArrLists[amx][params[1]].ListItems.begin() + params[2]);
	return 1;
}

cell AMX_NATIVE_CALL ArrayListGetItem(AMX* amx, cell* params)
{
	if (internal_is_valid_list(amx, params[1]) == 0 || internal_is_valid_item(amx, params[1], params[2]) == 0)
	{
		return INVALID_LIST_ID;
	}
	Lists GetLValue = ArrLists[amx][params[1]].ListItems.at(params[2]);
	return GetLValue.value;
}

cell AMX_NATIVE_CALL ArrayListGetType(AMX* amx, cell* params)
{
	if (internal_is_valid_list(amx, params[1]) == 0 || internal_is_valid_item(amx, params[1], params[2]) == 0)
	{
		return INVALID_LIST_ID;
	}
	return ArrLists[amx][params[1]].GetType(params[2]);
}

AMX_NATIVE_INFO Natives[] =
{
	{ "CreateArrayList", CreateArrayList },
	{ "ClearArrayList", ClearArrayList },
	{ "IsValidArrayList", IsValidArrayList },
	{ "GetArrayListCapacity", GetArrayListCapacity },
	{ "SetArrayListCapacity", SetArrayListCapacity },
	{ "GetArrayListSize", GetArrayListSize },
	{ "ArrayListAdd", ArrayListAdd },
	{ "ArrayListRemove", ArrayListRemove },
	{ "ArrayListGetItem", ArrayListGetItem },
	{ "ArrayListGetType", ArrayListGetType },
	{ 0, 0 }
};

PLUGIN_EXPORT unsigned int PLUGIN_CALL Supports()
{
	return SUPPORTS_VERSION | SUPPORTS_AMX_NATIVES;
}

PLUGIN_EXPORT int PLUGIN_CALL AmxLoad(AMX *amx)
{
	return amx_Register(amx, Natives, -1);
}

PLUGIN_EXPORT int PLUGIN_CALL AmxUnload(AMX *amx)
{
	return AMX_ERR_NONE;
}
