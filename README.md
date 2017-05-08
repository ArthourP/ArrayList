# ArrayList

## Function list:
```pawn
native List:CreateList(capacity);
native List:ClearList(listid);
native List:IsValidList(listid);
native List:GetListCapacity(listid);
native List:SetListCapacity(listid, capacity);
native List:GetListSize(listid);
native List:AddToList(listid, {_,Float}:value);
native List:RemoveFromList(listid, index);
native List:GetListItem(listid, index);
native List:GetItemType(listid, index);
```
