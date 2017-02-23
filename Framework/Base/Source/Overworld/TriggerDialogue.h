#pragma once
#include "TriggerArea.h"

#include <vector>
#include <string>

using std::string;
using std::vector;

class TriggerDialogue : public TriggerArea
{
	bool active;
	vector<string> dialogue;

	virtual void OnTrigger();

public:
	TriggerDialogue();
	virtual ~TriggerDialogue();

	void LoadDialogue(string fileName);
};

