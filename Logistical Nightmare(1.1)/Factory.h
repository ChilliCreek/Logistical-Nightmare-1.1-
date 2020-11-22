#pragma once
#include<string>
#include<map>
using namespace std;

class Factory 
{
private:
    float m_factoryOutput = 100.0;
	string m_equipmentName;
	float m_productionCost;
	string m_defaultEquipment = "Panzer 4 G";
public:
	static map <string, float> productionCostMap;
	string getEquipmentName()const;
	void setEquipment(string&);
protected:
	int produce(float);
};