#define INVALID_LIST_ID (-1) 

#define TYPE_INTEGER (1) 
#define TYPE_FLOAT   (2) 

struct Lists
{
	cell value;
	int type;
};

class jLists
{
	public:
		std::vector<Lists> ListItems;
		int IsValid(unsigned int jid);
		int GetType(int index);
		void PutValue(Lists value);
		void Clear();
};

std::map<AMX*, std::vector<jLists>> ArrLists;

int internal_is_valid_list(AMX* amx, unsigned int listid)
{
	if (0 <= listid && listid < ArrLists[amx].size())
	{
		return 1;
	}
	else return 0;
}

int internal_is_valid_item(AMX* amx, int listid, int index)
{
	return ArrLists[amx][listid].IsValid(index);
}

void jLists::PutValue(Lists value)
{
	if (this->ListItems.size() < this->ListItems.capacity())
	{
		this->ListItems.push_back(value);
	}
}

void jLists::Clear()
{
	this->ListItems.clear();
}

int jLists::IsValid(unsigned int index)
{
	if (index >= 0 && this->ListItems.size() > index)
	{
		return 1;
	}
	return 0;
}

int jLists::GetType(int index)
{
	return this->ListItems[index].type;
}