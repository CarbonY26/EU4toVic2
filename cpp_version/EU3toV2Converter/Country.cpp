// ****************************************************************************
// *                                                                          *
// *		     EU3 to Victoria 2 conversion project                     *
// *                                                                          *
// ****************************************************************************

// standard includes
#include "stdafx.h"
#include "Country.h"

void Country::Init(Object* obj) 
{
   ObjectHandler::Init(obj);

   // Now let's populate our flags
   std::string key, strVal;   
   std::vector<Object*> leaves = m_source->getLeaves();

   // Add a flag that will be present in all countries
   m_flags.SetFlag(std::string("ALL"), std::string("1"));

   for (int i = 0; i < leaves.size(); i++)
   {
      key = leaves[i]->getKey();
      strVal = obj->safeGetString(key);

      if (leaves[i]->isLeaf())
      {
	 m_flags.SetFlag(key, strVal);
      }
      else if (key.compare("technology") == 0)
      {
	 // Retrieve individual tech values
	 std::vector<Object*> techs = leaves[i]->getLeaves();
	 for (int j = 0; j < techs.size(); j++)
	 {
	    key = techs[j]->getKey();
	    strVal = techs[j]->getToken(0);
	    m_flags.SetFlag(key, strVal);
	 }
      }
      else if (key.compare("flags") == 0)
      {
	 std::vector<Object*> flags = leaves[i]->getLeaves();
	 for (int j = 0; j < flags.size(); j++)
	 {
	    key = flags[j]->getKey();
	    strVal = leaves[i]->safeGetString(key);
	    m_flags.SetFlag(key, strVal);
	 }
      }
   }
};