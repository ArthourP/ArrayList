/*
ArrayList
Jelly23
*/


#define TYPE_INTEGER (1)
#define TYPE_FLOAT   (2)

native CreateArrayList(capacity);
native ClearArrayList(listid);
native IsValidArrayList(listid);
native GetArrayListCapacity(listid);
native SetArrayListCapacity(listid, capacity);
native GetArrayListSize(listid);
native ArrayListAdd(listid, {_,Float}:value, type);
native ArrayListRemove(listid, index);
native ArrayListGetItem(listid, index);
native ArrayListGetType(listid, index);

//Tag List: antes das fun��es, mesmo que n�o seja necess�rio.
#define List: 

#define CreateList CreateArrayList
#define ClearList ClearArrayList
#define IsValidList IsValidArrayList
#define GetListCapacity GetArrayListCapacity
#define SetListCapacity SetArrayListCapacity
#define GetListSize GetArrayListSize
#define AddToList _ArrayListAdd
#define RemoveFromList ArrayListRemove
#define GetListItem ArrayListGetItem
#define GetItemType ArrayListGetType

//Assim n�o � necess�rio definir o tipo de valor que ser� colocado na lista.
stock _ArrayListAdd(listid, {_,Float}:value, type = tagof(value))
	return ArrayListAdd(listid, value, type = ( type == tagof(Float:)) ? TYPE_FLOAT : TYPE_INTEGER);